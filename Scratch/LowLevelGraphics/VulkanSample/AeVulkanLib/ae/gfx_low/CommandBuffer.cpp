// 文字コード：UTF-8
#include <ae/gfx_low/CommandBuffer.hpp>

// includes
#include <ae/base/Extent2.hpp>
#include <ae/base/Extent2i.hpp>
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/BufferResource.hpp>
#include <ae/gfx_low/CommandBufferCreateInfo.hpp>
#include <ae/gfx_low/ComputePipeline.hpp>
#include <ae/gfx_low/CopyBufferToImageInfo.hpp>
#include <ae/gfx_low/DepthStencilImageView.hpp>
#include <ae/gfx_low/DepthStencilSetting.hpp>
#include <ae/gfx_low/DepthStencilSpecInfo.hpp>
#include <ae/gfx_low/DescriptorSet.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/DispatchCallInfo.hpp>
#include <ae/gfx_low/DrawCallInfo.hpp>
#include <ae/gfx_low/EventCreateInfo.hpp>
#include <ae/gfx_low/ImageResource.hpp>
#include <ae/gfx_low/ImageResourceBarrierInfo.hpp>
#include <ae/gfx_low/IndexBufferView.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/InternalUtility.hpp>
#include <ae/gfx_low/Queue.hpp>
#include <ae/gfx_low/RenderPassBeginInfo.hpp>
#include <ae/gfx_low/RenderPassSpecInfo.hpp>
#include <ae/gfx_low/RenderPipeline.hpp>
#include <ae/gfx_low/RenderTargetImageView.hpp>
#include <ae/gfx_low/RenderTargetSetting.hpp>
#include <ae/gfx_low/RenderTargetSpecInfo.hpp>
#include <ae/gfx_low/ScissorSetting.hpp>
#include <ae/gfx_low/System.hpp>
#include <ae/gfx_low/VertexBufferView.hpp>
#include <ae/gfx_low/ViewportSetting.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
CommandBuffer::CommandBuffer(const CommandBufferCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, queue_(base::PtrToRef(createInfo.Queue()))
, level_(createInfo.Level())
, features_(createInfo.Features())
, commandPool_()
, nativeObject_()
, completeEvent_(EventCreateInfo().SetDevice(&device_))
, renderPassProperties_(
      createInfo.RenderPassCountMax(),
      device_.System().ObjectAllocator_()) {
    // セカンダリの場合は BitSet チェック
    if (level_ == CommandBufferLevel::Secondary) {
        // Render か Compute のどちらかだけ立っている
        AE_BASE_ASSERT(!createInfo.Features().Get(CommandBufferFeature::Copy));
        AE_BASE_ASSERT(
            !(createInfo.Features().Get(CommandBufferFeature::Render) &&
              createInfo.Features().Get(CommandBufferFeature::Compute)));
        AE_BASE_ASSERT(
            createInfo.Features().Get(CommandBufferFeature::Render) ||
            createInfo.Features().Get(CommandBufferFeature::Compute));
    }

    // コマンドプール作成
    {
        const auto poolCreateInfo =
            ::vk::CommandPoolCreateInfo()
                .setQueueFamilyIndex(queue_.QueueFamilyIndex_())
                .setFlags(::vk::CommandPoolCreateFlagBits::eResetCommandBuffer);
        const auto result = device_.NativeObject_().createCommandPool(
            &poolCreateInfo,
            nullptr,
            &commandPool_);
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }

    const auto allocateInfo =
        ::vk::CommandBufferAllocateInfo()
            .setCommandPool(commandPool_)
            .setLevel(
                InternalEnumUtil::ToCommandBufferLevel(createInfo.Level()))
            .setCommandBufferCount(1);

    auto result = device_.NativeObject_().allocateCommandBuffers(
        &allocateInfo,
        &nativeObject_);
    AE_BASE_ASSERT(result == vk::Result::eSuccess);
}

//------------------------------------------------------------------------------
CommandBuffer::~CommandBuffer() {
    Reset();
    device_.NativeObject_().freeCommandBuffers(commandPool_, nativeObject_);
    device_.NativeObject_().destroyCommandPool(commandPool_, nullptr);
}

//------------------------------------------------------------------------------
void CommandBuffer::BeginRecord() {
    Reset();
    AE_BASE_ASSERT(state_ == CommandBufferState::Initial);
    const auto inheritanceInfo = ::vk::CommandBufferInheritanceInfo();
    const auto beginInfo =
        ::vk::CommandBufferBeginInfo()
            .setFlags(
                level_ == CommandBufferLevel::Secondary
                    ? ::vk::CommandBufferUsageFlagBits::eRenderPassContinue
                    : ::vk::CommandBufferUsageFlagBits(0))
            .setPInheritanceInfo(
                level_ == CommandBufferLevel::Secondary ? &inheritanceInfo
                                                        : nullptr);
    const auto result = nativeObject_.begin(&beginInfo);
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    state_ = CommandBufferState::Recording;
    if (level_ == CommandBufferLevel::Secondary) {
        activePass_ = features_;
    }
}

//------------------------------------------------------------------------------
void CommandBuffer::EndRecord() {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    activePass_.Clear();
    const ::vk::Result result = nativeObject_.end();
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    state_ = CommandBufferState::Recorded;
}

//------------------------------------------------------------------------------
void CommandBuffer::Reset() {
    switch (state_) {
    case CommandBufferState::Initial:
        // 何もする必要がない
        return;

    case CommandBufferState::Recorded: {
        // リセット処理が必要なので続行
        break;
    }
    default:
        AE_BASE_ASSERT_NOT_REACHED_MSGFMT(
            "[CommandBuffer::Reset] Invalid State(%d).",
            state_);
        return;
    }

    // コマンドバッファをリセット
    const auto result = nativeObject_.reset(::vk::CommandBufferResetFlags(0));
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    state_ = CommandBufferState::Initial;

    // コマンドバッファで作った情報をリセット
    for (int i = renderPassProperties_.Count() - 1; 0 <= i; --i) {
        auto& prop = renderPassProperties_[i];
        device_.NativeObject_().destroyFramebuffer(prop.framebuffer, nullptr);
        device_.NativeObject_().destroyRenderPass(prop.renderPass, nullptr);
    }
    renderPassProperties_.Clear();
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdCall(const CommandBuffer& secondaryCommands) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(
        secondaryCommands.Level() ==
        ::ae::gfx_low::CommandBufferLevel::Secondary);
    AE_BASE_ASSERT(
        (secondaryCommands.Features().Get(
             ::ae::gfx_low::CommandBufferFeature::Render) &&
         activePass_.Get(::ae::gfx_low::CommandBufferFeature::Render)) ||
        (secondaryCommands.Features().Get(
             ::ae::gfx_low::CommandBufferFeature::Compute) &&
         activePass_.Get(::ae::gfx_low::CommandBufferFeature::Compute)));

    // コール
    nativeObject_.executeCommands(1, &secondaryCommands.nativeObject_);
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdImageResourceBarrier(
    const ImageResourceBarrierInfo& info) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.IsAllOff());

    // アクセスマスクの作成
    auto toAccessMaskFunc = [](const ImageResourceState state) {
        ::vk::AccessFlags mask;
        switch (state) {
        case ImageResourceState::RenderTarget:
            mask = ::vk::AccessFlagBits::eColorAttachmentWrite;
            break;
        case ImageResourceState::PresentSrc:
            mask = ::vk::AccessFlagBits::eMemoryRead;
            break;
        case ImageResourceState::DepthStencil:
            mask = ::vk::AccessFlagBits::eDepthStencilAttachmentWrite;
            break;
        case ImageResourceState::DepthStencilReadOnly:
            mask = ::vk::AccessFlagBits::eShaderRead |
                   ::vk::AccessFlagBits::eInputAttachmentRead;
            break;
        case ImageResourceState::ShaderResourceReadOnly:
            mask = ::vk::AccessFlagBits::eShaderRead |
                   ::vk::AccessFlagBits::eInputAttachmentRead;
            break;
        case ImageResourceState::ShaderResource:
            mask = ::vk::AccessFlagBits::eShaderRead |
                   ::vk::AccessFlagBits::eShaderWrite |
                   ::vk::AccessFlagBits::eInputAttachmentRead;
            break;
        case ImageResourceState::CopySrc:
            mask = ::vk::AccessFlagBits::eTransferRead;
            break;
        case ImageResourceState::CopyDst:
            mask = ::vk::AccessFlagBits::eTransferWrite;
            break;
        default: break;
        }
        return mask;
    };

    const auto& imageResource = base::PtrToRef(info.Resource());
    const auto barrier =
        ::vk::ImageMemoryBarrier()
            .setSrcAccessMask(toAccessMaskFunc(info.OldState()))
            .setDstAccessMask(toAccessMaskFunc(info.NewState()))
            .setOldLayout(InternalEnumUtil::ToImageLayout(info.OldState()))
            .setNewLayout(InternalEnumUtil::ToImageLayout(info.NewState()))
            .setSrcQueueFamilyIndex(VK_QUEUE_FAMILY_IGNORED)
            .setDstQueueFamilyIndex(VK_QUEUE_FAMILY_IGNORED)
            .setImage(imageResource.NativeObject_())
            .setSubresourceRange(
                info.IsSubresourceSpecified()
                    ? InternalUtility::ToImageSubresourceRange(
                          base::PtrToRef(info.Resource()),
                          info.SubresourceLocation())
                    : ::vk::ImageSubresourceRange(
                          InternalEnumUtil::ToImageAspectFlags(
                              imageResource.NativeFormat_()),
                          0, // baseMipLevel
                          imageResource.MipLevels_(),
                          0, // baseArrayLayer
                          imageResource.ArrayLength_() *
                              (imageResource.IsCubeMapImage_() ? 6 : 1)));
    nativeObject_.pipelineBarrier(
        ::vk::PipelineStageFlagBits::eAllGraphics |
            ::vk::PipelineStageFlagBits::eAllCommands,
        ::vk::PipelineStageFlagBits::eAllGraphics |
            ::vk::PipelineStageFlagBits::eAllCommands,
        ::vk::DependencyFlagBits(),
        0, // memoryBarrierCount,
        nullptr, // memoryBarriers
        0, // bufferMemoryBarrierCount,
        nullptr, // bufferMemoryBarriers
        1, // imageMemoryBarrierCount,
        &barrier // imageMemoryBarriers
    );
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdCopyBufferToImage(const CopyBufferToImageInfo& info) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.IsAllOff());
    AE_BASE_ASSERT(features_.Get(CommandBufferFeature::Copy));

    const auto copyInfo =
        ::vk::BufferImageCopy()
            .setBufferOffset(info.SrcBufferOffset())
            .setBufferRowLength(info.SrcImageExtent().width)
            .setBufferImageHeight(info.SrcImageExtent().height)
            .setImageOffset(::vk::Offset3D(
                info.DstImageOffset().x,
                info.DstImageOffset().y,
                info.DstImageOffset().z))
            .setImageSubresource(
                ::vk::ImageSubresourceLayers()
                    .setAspectMask(::vk::ImageAspectFlagBits::eColor)
                    .setMipLevel(info.DstSubresourceLocation().MipLevel())
                    .setBaseArrayLayer(
                        info.DstSubresourceLocation().FaceIndex() +
                        info.DstSubresourceLocation().ArrayIndex() *
                            (info.DstImageResource()->IsCubeMapImage_() ? 6
                                                                        : 1))
                    .setLayerCount(1))
            .setImageExtent(::vk::Extent3D(
                uint32_t(info.SrcImageExtent().width),
                uint32_t(info.SrcImageExtent().height),
                uint32_t(info.SrcImageExtent().depth)));

    nativeObject_.copyBufferToImage(
        base::PtrToRef(info.SrcBufferResource()).NativeObject_(),
        base::PtrToRef(info.DstImageResource()).NativeObject_(),
        InternalEnumUtil::ToImageLayout(info.DstImageResourceState()),
        1, // regionCount
        &copyInfo);
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdBeginRenderPass(const RenderPassBeginInfo& info) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.IsAllOff());
    AE_BASE_ASSERT(features_.Get(CommandBufferFeature::Render));
    AE_BASE_ASSERT_LESS_EQUALS(
        info.RenderPassSpecInfo().RenderTargetCount(),
        Device::SupportedRenderTargetCountMax_);

    activePass_.Set(CommandBufferFeature::Render, true);
    currentRenderPipeline_.Reset();

    RenderPassProperty prop;
    const bool hasDepthStencil = info.DepthStencilSettingPtr() != nullptr;
    const int attachmentsCount = info.RenderPassSpecInfo().RenderTargetCount() +
                                 (hasDepthStencil ? 1 : 0);
    const int depthStencilIdx = hasDepthStencil ? attachmentsCount - 1 : -1;
    {
        // RenderPass 作成
        std::array<
            ::vk::AttachmentDescription,
            Device::SupportedAttachmentCountMax_>
            attachments;
        std::array<
            ::vk::AttachmentReference,
            Device::SupportedAttachmentCountMax_>
            attachmentRefs;
        for (int i = 0; i < info.RenderPassSpecInfo().RenderTargetCount();
             ++i) {
            const auto& spec =
                info.RenderPassSpecInfo().RenderTargetSpecInfos()[i];
            const auto& setting = info.RenderTargetSettings()[i];
            auto& attachment = attachments[i];
            auto& attachmentRef = attachmentRefs[i];

            const auto format =
                spec.NativeFormat_() != ::vk::Format::eUndefined
                    ? spec.NativeFormat_()
                    : InternalEnumUtil::ToFormat(spec.ImageFormat());

            attachment.setFormat(format)
                .setSamples(::vk::SampleCountFlagBits::e1)
                .setLoadOp(
                    InternalEnumUtil::ToAttachmentLoadOp(setting.LoadOp()))
                .setStoreOp(
                    InternalEnumUtil::ToAttachmentStoreOp(setting.StoreOp()))
                .setStencilLoadOp(vk::AttachmentLoadOp::eDontCare)
                .setStencilStoreOp(vk::AttachmentStoreOp::eDontCare)
                .setInitialLayout(
                    InternalEnumUtil::ToImageLayoutForColorAttachment(
                        setting.InitialImageResourceState()))
                .setFinalLayout(
                    InternalEnumUtil::ToImageLayoutForColorAttachment(
                        setting.FinalImageResourceState()));
            attachmentRef.setAttachment(i).setLayout(
                ::vk::ImageLayout::eColorAttachmentOptimal);
        }
        if (info.DepthStencilSettingPtr() != nullptr) {
            const auto& spec = base::PtrToRef(
                info.RenderPassSpecInfo().DepthStencilSpecInfoPtr());
            const auto& setting = base::PtrToRef(info.DepthStencilSettingPtr());
            auto& attachment = attachments[depthStencilIdx];
            auto& attachmentRef = attachmentRefs[depthStencilIdx];
            attachment.setFormat(InternalEnumUtil::ToFormat(spec.ImageFormat()))
                .setSamples(::vk::SampleCountFlagBits::e1)
                .setLoadOp(
                    InternalEnumUtil::ToAttachmentLoadOp(setting.DepthLoadOp()))
                .setStoreOp(InternalEnumUtil::ToAttachmentStoreOp(
                    setting.DepthStoreOp()))
                .setStencilLoadOp(InternalEnumUtil::ToAttachmentLoadOp(
                    setting.StencilLoadOp()))
                .setStencilStoreOp(InternalEnumUtil::ToAttachmentStoreOp(
                    setting.StencilStoreOp()))
                .setInitialLayout(
                    InternalEnumUtil::ToImageLayoutForDepthStencilAttachment(
                        setting.InitialImageResourceState(),
                        spec.ImageFormat()))
                .setFinalLayout(
                    InternalEnumUtil::ToImageLayoutForDepthStencilAttachment(
                        setting.FinalImageResourceState(),
                        spec.ImageFormat()));
            attachmentRef.setAttachment(depthStencilIdx)
                .setLayout(::vk::ImageLayout::eDepthStencilAttachmentOptimal);
        }

        auto const subpass =
            vk::SubpassDescription()
                .setPipelineBindPoint(vk::PipelineBindPoint::eGraphics)
                .setInputAttachmentCount(0)
                .setPInputAttachments(nullptr)
                .setColorAttachmentCount(
                    info.RenderPassSpecInfo().RenderTargetCount())
                .setPColorAttachments(&attachmentRefs[0])
                .setPResolveAttachments(nullptr)
                .setPDepthStencilAttachment(
                    hasDepthStencil ? &attachmentRefs[depthStencilIdx]
                                    : nullptr)
                .setPreserveAttachmentCount(0)
                .setPPreserveAttachments(nullptr);

        std::array<::vk::SubpassDependency, 2> dependencies;
        if (hasDepthStencil) {
            const ::vk::PipelineStageFlags stages =
                ::vk::PipelineStageFlagBits::eEarlyFragmentTests |
                ::vk::PipelineStageFlagBits::eLateFragmentTests;
            dependencies[0] =
                ::vk::SubpassDependency()
                    .setSrcSubpass(VK_SUBPASS_EXTERNAL)
                    .setDstSubpass(0)
                    .setSrcStageMask(stages)
                    .setDstStageMask(stages)
                    .setSrcAccessMask(
                        vk::AccessFlagBits::eDepthStencilAttachmentWrite)
                    .setDstAccessMask(
                        vk::AccessFlagBits::eDepthStencilAttachmentRead |
                        vk::AccessFlagBits::eDepthStencilAttachmentWrite)
                    .setDependencyFlags(vk::DependencyFlags());
        }
        dependencies[hasDepthStencil ? 1 : 0] =
            ::vk::SubpassDependency()
                .setSrcSubpass(VK_SUBPASS_EXTERNAL)
                .setDstSubpass(0)
                .setSrcStageMask(
                    vk::PipelineStageFlagBits::eColorAttachmentOutput)
                .setDstStageMask(
                    vk::PipelineStageFlagBits::eColorAttachmentOutput)
                .setSrcAccessMask(vk::AccessFlagBits())
                .setDstAccessMask(
                    vk::AccessFlagBits::eColorAttachmentWrite |
                    vk::AccessFlagBits::eColorAttachmentRead)
                .setDependencyFlags(vk::DependencyFlags());

        auto const renderPassCreateInfo =
            vk::RenderPassCreateInfo()
                .setAttachmentCount(attachmentsCount)
                .setPAttachments(&attachments[0])
                .setSubpassCount(1)
                .setPSubpasses(&subpass)
                .setDependencyCount(hasDepthStencil ? 2 : 1)
                .setPDependencies(&dependencies[0]);
        {
            const auto result = device_.NativeObject_().createRenderPass(
                &renderPassCreateInfo,
                nullptr,
                &prop.renderPass);
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
        }
    }
    {
        // Framebuffer 生成
        std::array<::vk::ImageView, Device::SupportedAttachmentCountMax_>
            imageViews;
        for (int i = 0; i < info.RenderPassSpecInfo().RenderTargetCount();
             ++i) {
            imageViews[i] = info.RenderTargetSettings()[i]
                                .RenderTargetImageView()
                                ->NativeObject_();
        }
        if (hasDepthStencil) {
            imageViews[depthStencilIdx] =
                base::PtrToRef(info.DepthStencilSettingPtr())
                    .DepthStencilImageView()
                    ->NativeObject_();
        }

        auto const createInfo =
            vk::FramebufferCreateInfo()
                .setRenderPass(prop.renderPass)
                .setAttachmentCount(attachmentsCount)
                .setPAttachments(&imageViews[0])
                .setWidth(uint32_t(info.RenderArea().Width()))
                .setHeight(uint32_t(info.RenderArea().Height()))
                .setLayers(1);
        {
            const auto result = device_.NativeObject_().createFramebuffer(
                &createInfo,
                nullptr,
                &prop.framebuffer);
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
        }
    }
    renderPassProperties_.Add(prop);

    std::array<::vk::ClearValue, Device::SupportedAttachmentCountMax_>
        clearValues;
    for (int i = 0; i < info.RenderPassSpecInfo().RenderTargetCount(); ++i) {
        const auto color = info.RenderTargetSettings()[i].ClearColor();
        ::vk::ClearColorValue val;
        val.float32 =
            std::array<float, 4>({ color.r, color.g, color.b, color.a });
        clearValues[i].setColor(val);
    }
    if (hasDepthStencil) {
        const auto& setting = base::PtrToRef(info.DepthStencilSettingPtr());
        clearValues[depthStencilIdx].setDepthStencil(
            ::vk::ClearDepthStencilValue(
                setting.DepthClearValue(),
                uint32_t(setting.StencilClearValue())));
    }

    auto const passInfo = ::vk::RenderPassBeginInfo()
                              .setRenderPass(prop.renderPass)
                              .setFramebuffer(prop.framebuffer)
                              .setRenderArea(::vk::Rect2D(
                                  ::vk::Offset2D(
                                      info.RenderArea().Begin().x,
                                      info.RenderArea().Begin().y),
                                  ::vk::Extent2D(
                                      uint32_t(info.RenderArea().Width()),
                                      uint32_t(info.RenderArea().Height()))))
                              .setClearValueCount(attachmentsCount)
                              .setPClearValues(&clearValues[0]);

    nativeObject_.beginRenderPass(passInfo, vk::SubpassContents::eInline);
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdEndRenderPass() {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.Get(CommandBufferFeature::Render));

    nativeObject_.endRenderPass();
    activePass_.Set(CommandBufferFeature::Render, false);
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdBeginComputePass(const ComputePassBeginInfo& info) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.IsAllOff());
    AE_BASE_ASSERT(features_.Get(CommandBufferFeature::Copy));
    activePass_.Set(CommandBufferFeature::Compute, true);
    currentComputePipeline_.Reset();
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdEndComputePass() {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.Get(CommandBufferFeature::Compute));

    activePass_.Set(CommandBufferFeature::Compute, false);
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdSetDescriptorSet(const DescriptorSet& descriptorSet) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(
        activePass_.Get(CommandBufferFeature::Render) ||
        activePass_.Get(CommandBufferFeature::Compute));

    if (activePass_.Get(CommandBufferFeature::Render)) {
        AE_BASE_ASSERT(currentRenderPipeline_.IsValid());
        nativeObject_.bindDescriptorSets(
            ::vk::PipelineBindPoint::eGraphics,
            currentRenderPipeline_->PipelineLayout_(),
            0,
            descriptorSet.Layouts_().DescriptorSetLayoutCount(),
            descriptorSet.NativeObjects_(),
            0,
            nullptr);
    } else if (activePass_.Get(CommandBufferFeature::Compute)) {
        AE_BASE_ASSERT(currentComputePipeline_.IsValid());
        nativeObject_.bindDescriptorSets(
            ::vk::PipelineBindPoint::eCompute,
            currentComputePipeline_->PipelineLayout_(),
            0,
            descriptorSet.Layouts_().DescriptorSetLayoutCount(),
            descriptorSet.NativeObjects_(),
            0,
            nullptr);
    } else {
        AE_BASE_ASSERT_NOT_REACHED();
    }
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdSetRenderPipeline(const RenderPipeline& pipeline) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.Get(CommandBufferFeature::Render));
    nativeObject_.bindPipeline(
        ::vk::PipelineBindPoint::eGraphics,
        pipeline.NativeObject_());
    currentRenderPipeline_.Reset(&pipeline);
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdSetViewports(
    const int count,
    const ViewportSetting* settings) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.Get(CommandBufferFeature::Render));
    AE_BASE_ASSERT(level_ == CommandBufferLevel::Primary);
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    AE_BASE_ASSERT_POINTER(settings);
    std::array<::vk::Viewport, Device::SupportedRenderTargetCountMax_>
        viewports;
    for (int i = 0; i < count; ++i) {
        const auto& setting = settings[i];
        viewports[i] = ::vk::Viewport()
                           .setX(setting.Rect().Min().x)
                           .setY(setting.Rect().Min().y)
                           .setWidth(setting.Rect().Width())
                           .setHeight(setting.Rect().Height())
                           .setMinDepth(setting.MinDepth())
                           .setMaxDepth(setting.MaxDepth());
    }
    nativeObject_.setViewport(0, count, &viewports[0]);
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdSetScissors(
    const int count,
    const ScissorSetting* settings) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.Get(CommandBufferFeature::Render));
    AE_BASE_ASSERT(level_ == CommandBufferLevel::Primary);
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    AE_BASE_ASSERT_POINTER(settings);
    std::array<::vk::Rect2D, Device::SupportedRenderTargetCountMax_> rects;
    for (int i = 0; i < count; ++i) {
        const auto& setting = settings[i];
        rects[i] = ::vk::Rect2D(
            { setting.Rect().Begin().x, setting.Rect().Begin().y },
            { uint32_t(setting.Rect().Width()),
              uint32_t(setting.Rect().Height()) });
    }
    nativeObject_.setScissor(0, count, &rects[0]);
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdSetVertexBuffer(
    const int slotIndex,
    const VertexBufferView& view) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.Get(CommandBufferFeature::Render));
    AE_BASE_ASSERT_LESS_EQUALS(0, slotIndex);
    const auto offset = ::vk::DeviceSize(view.Region_().Offset());
    nativeObject_.bindVertexBuffers(
        uint32_t(slotIndex),
        1,
        &view.BufferResource_().NativeObject_(),
        &offset);
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdSetIndexBuffer(
    const IndexBufferView& view) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.Get(CommandBufferFeature::Render));
    const auto offset = ::vk::DeviceSize(view.Region_().Offset());
    nativeObject_.bindIndexBuffer(
        view.BufferResource_().NativeObject_(),
        offset,
        InternalEnumUtil::ToIndexType(view.Format_())
        );
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdDraw(const DrawCallInfo& info) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.Get(CommandBufferFeature::Render));
    if (info.UseIndexBuffer()) {
        nativeObject_.drawIndexed(
            info.VertexCount(),
            info.InstanceCount(),
            info.IndexOffset(),
            info.VertexOffset(),
            info.InstanceOffset());
    } else {
        nativeObject_.draw(
            info.VertexCount(),
            info.InstanceCount(),
            info.VertexOffset(),
            info.InstanceOffset());
    }
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdSetComputePipeline(const ComputePipeline& pipeline) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.Get(CommandBufferFeature::Compute));
    nativeObject_.bindPipeline(
        ::vk::PipelineBindPoint::eCompute,
        pipeline.NativeObject_());
    currentComputePipeline_.Reset(&pipeline);
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdDispatch(const DispatchCallInfo& info) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.Get(CommandBufferFeature::Compute));
    nativeObject_.dispatch(
        info.ThreadGroups().width,
        info.ThreadGroups().height,
        info.ThreadGroups().depth);
}

} // namespace gfx_low
} // namespace ae
// EOF
