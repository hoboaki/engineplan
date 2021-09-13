// 文字コード：UTF-8
#include <ae/gfx_low/CommandBuffer.hpp>

// includes
#include <ae/base/Extent2.hpp>
#include <ae/base/Extent2i.hpp>
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/BufferResource.hpp>
#include <ae/gfx_low/CommandBufferBeginRecordInfo.hpp>
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
#include <ae/gfx_low/RenderPass.hpp>
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
, renderPassCountMax_(createInfo.RenderPassCountMax())
, commandPool_()
, nativeObject_()
, completeEvent_(EventCreateInfo().SetDevice(&device_))  {
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
    BeginRecord(CommandBufferBeginRecordInfo());
}

    //------------------------------------------------------------------------------
void CommandBuffer::BeginRecord(const CommandBufferBeginRecordInfo& info) {
    Reset();
    AE_BASE_ASSERT(state_ == CommandBufferState::Initial);
    auto inheritanceInfo = ::vk::CommandBufferInheritanceInfo();
    if (level_ == CommandBufferLevel::Secondary &&
        features_.Get(CommandBufferFeature::Render)) {
        const auto& renderPass = base::PtrToRef(info.InheritRenderPassPtr());
        inheritanceInfo.framebuffer = *renderPass.Framebuffer_();
        inheritanceInfo.renderPass = *renderPass.RenderPass_();
    }
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
    if (level_ == CommandBufferLevel::Primary) {
        return;
    }

    // 以降、セカンダリ専用処理
    // メモ：
    // ビューポート＆シザー設定について
    // DX12 のようにプライマリから設定値を引き継ぐのが理想だが
    // Vulkan の仕様では引き継がれないためコマンドバッファの先頭で設定するようにしている。
    activePass_ = features_;
    CmdSetViewportsDetails(
        base::PtrToRef(info.InheritRenderPassPtr()).RenderTargetCount_(),
        info.InheritViewportSettingsPtr());
    CmdSetScissorsDetails(
        base::PtrToRef(info.InheritRenderPassPtr()).RenderTargetCount_(),
        info.InheritScissorSettingsPtr());
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
    renderPassCount_ = 0;
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
    AE_BASE_ASSERT_LESS(renderPassCount_, renderPassCountMax_);
    activePass_.Set(CommandBufferFeature::Render, true);
    currentRenderPipeline_.Reset();
    ++renderPassCount_;
    nativeObject_.beginRenderPass(
        base::PtrToRef(info.RenderPass()).RenderPassBeginInfo_(),
        level_ == CommandBufferLevel::Primary ? vk::SubpassContents::eSecondaryCommandBuffers
                                              : vk::SubpassContents::eInline);
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
    AE_BASE_ASSERT(level_ == CommandBufferLevel::Primary);
    CmdSetViewportsDetails(count, settings);
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdSetScissors(
    const int count,
    const ScissorSetting* settings) {
    AE_BASE_ASSERT(level_ == CommandBufferLevel::Primary);
    CmdSetScissorsDetails(count, settings);
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

//------------------------------------------------------------------------------
void CommandBuffer::CmdSetViewportsDetails(
    const int count,
    const ViewportSetting* settings) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.Get(CommandBufferFeature::Render));
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
void CommandBuffer::CmdSetScissorsDetails(
    const int count,
    const ScissorSetting* settings) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.Get(CommandBufferFeature::Render));
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


} // namespace gfx_low
} // namespace ae
// EOF
