// 文字コード：UTF-8
#include <ae/gfx_low/CommandBuffer.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/CommandBufferCreateInfo.hpp>
#include <ae/gfx_low/DepthStencilImageView.hpp>
#include <ae/gfx_low/DepthStencilSetting.hpp>
#include <ae/gfx_low/DepthStencilSpecInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/EventCreateInfo.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/Queue.hpp>
#include <ae/gfx_low/RenderPassBeginInfo.hpp>
#include <ae/gfx_low/RenderPassSpecInfo.hpp>
#include <ae/gfx_low/RenderTargetImageView.hpp>
#include <ae/gfx_low/RenderTargetSetting.hpp>
#include <ae/gfx_low/RenderTargetSpecInfo.hpp>
#include <ae/gfx_low/System.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
CommandBuffer::CommandBuffer(const CommandBufferCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, queuePtr_(createInfo.Queue())
, level_(createInfo.Level())
, features_(createInfo.Features())
, nativeObject_()
, completeEvent_(EventCreateInfo().SetDevice(&device_))
, renderPassProperties_(
      createInfo.RenderPassCountMax(), device_.System().ObjectAllocator_()) {
    // 今は Primary のみサポート
    AE_BASE_ASSERT(level_ == CommandBufferLevel::Primary);

    const auto allocateInfo = ::vk::CommandBufferAllocateInfo()
                                  .setCommandPool(queuePtr_->CommandPool_())
                                  .setLevel(::vk::CommandBufferLevel::ePrimary)
                                  .setCommandBufferCount(1);

    auto result = device_.NativeObject_().allocateCommandBuffers(
        &allocateInfo, &nativeObject_);
    AE_BASE_ASSERT(result == vk::Result::eSuccess);
}

//------------------------------------------------------------------------------
CommandBuffer::~CommandBuffer() {
    Reset();
    device_.NativeObject_().freeCommandBuffers(
        queuePtr_->CommandPool_(), nativeObject_);
}

//------------------------------------------------------------------------------
void CommandBuffer::BeginRecord() {
    Reset();
    AE_BASE_ASSERT(state_ == CommandBufferState::Initial);
    const auto beginInfo =
        ::vk::CommandBufferBeginInfo().setPInheritanceInfo(nullptr);
    const auto result = nativeObject_.begin(&beginInfo);
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    state_ = CommandBufferState::Recording;
}

//------------------------------------------------------------------------------
void CommandBuffer::EndRecord() {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
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
            "[CommandBuffer::Reset] Invalid State(%d).", state_);
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
void CommandBuffer::CmdBeginRenderPass(const RenderPassBeginInfo& info) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.IsAllOff());

    activePass_.Set(CommandBufferFeature::Render, true);

    RenderPassProperty prop;
    const bool hasDepthStencil = info.DepthStencilSettingPtr() != nullptr;
    const int attachmentsCount = info.RenderPassSpecInfo().RenderTargetCount() +
                                 (hasDepthStencil ? 1 : 0);
    const int depthStencilIdx = hasDepthStencil ? attachmentsCount - 1 : -1;
    {
        // RenderPass 作成
        std::array<::vk::AttachmentDescription,
            Device::SupportedAttachmentCountMax_>
            attachments;
        std::array<::vk::AttachmentReference,
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
                        setting.FinalImageResourceState(), spec.ImageFormat()));
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
                .setDstAccessMask(vk::AccessFlagBits::eColorAttachmentWrite |
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
                &renderPassCreateInfo, nullptr, &prop.renderPass);
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
                &createInfo, nullptr, &prop.framebuffer);
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
            std::array<float, 4>({color.r, color.g, color.b, color.a});
        clearValues[i].setColor(val);
    }
    if (hasDepthStencil) {
        const auto& setting = base::PtrToRef(info.DepthStencilSettingPtr());
        clearValues[depthStencilIdx].setDepthStencil(
            ::vk::ClearDepthStencilValue(setting.DepthClearValue(),
                uint32_t(setting.StencilClearValue())));
    }

    auto const passInfo =
        ::vk::RenderPassBeginInfo()
            .setRenderPass(prop.renderPass)
            .setFramebuffer(prop.framebuffer)
            .setRenderArea(
                ::vk::Rect2D(::vk::Offset2D(info.RenderArea().Begin().x,
                                 info.RenderArea().Begin().y),
                    ::vk::Extent2D(uint32_t(info.RenderArea().Width()),
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

} // namespace gfx_low
} // namespace ae
// EOF
