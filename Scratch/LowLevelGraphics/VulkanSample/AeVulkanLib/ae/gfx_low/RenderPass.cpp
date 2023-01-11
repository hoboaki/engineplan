// 文字コード：UTF-8
#include <ae/gfx_low/RenderPass.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/DepthStencilImageView.hpp>
#include <ae/gfx_low/DepthStencilSetting.hpp>
#include <ae/gfx_low/DepthStencilSpecInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/RenderPassCreateInfo.hpp>
#include <ae/gfx_low/RenderTargetImageView.hpp>
#include <ae/gfx_low/RenderTargetSetting.hpp>
#include <ae/gfx_low/RenderTargetSpecInfo.hpp>
#include <array>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
RenderPass::RenderPass(const RenderPassCreateInfo& info)
: device_(base::PtrToRef(info.Device()))
, renderTargetCount_(info.RenderPassSpecInfo().RenderTargetCount())
{
    AE_BASE_ASSERT_LESS_EQUALS(
        info.RenderPassSpecInfo().RenderTargetCount(),
        Device::SupportedRenderTargetCountMax_);
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
                &renderPass_);
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
                .setRenderPass(renderPass_)
                .setAttachmentCount(attachmentsCount)
                .setPAttachments(&imageViews[0])
                .setWidth(uint32_t(info.RenderArea().Width()))
                .setHeight(uint32_t(info.RenderArea().Height()))
                .setLayers(1);
        {
            const auto result = device_.NativeObject_().createFramebuffer(
                &createInfo,
                nullptr,
                &framebuffer_);
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
        }
    }
    {
        // ClearColor 生成
        for (int i = 0; i < info.RenderPassSpecInfo().RenderTargetCount();
             ++i) {
            const auto color = info.RenderTargetSettings()[i].ClearColor();
            ::vk::ClearColorValue val;
            val.float32 =
                std::array<float, 4>({ color.r, color.g, color.b, color.a });
            clearValues_[i].setColor(val);
        }
        if (hasDepthStencil) {
            const auto& setting = base::PtrToRef(info.DepthStencilSettingPtr());
            clearValues_[depthStencilIdx].setDepthStencil(
                ::vk::ClearDepthStencilValue(
                    setting.DepthClearValue(),
                    uint32_t(setting.StencilClearValue())));
        }
    }
    renderPassBeginInfo_ = ::vk::RenderPassBeginInfo()
                               .setRenderPass(renderPass_)
                               .setFramebuffer(framebuffer_)
                               .setRenderArea(::vk::Rect2D(
                                   ::vk::Offset2D(
                                       info.RenderArea().Begin().x,
                                       info.RenderArea().Begin().y),
                                   ::vk::Extent2D(
                                       uint32_t(info.RenderArea().Width()),
                                       uint32_t(info.RenderArea().Height()))))
                               .setClearValueCount(attachmentsCount)
                               .setPClearValues(&clearValues_[0]);
}

//------------------------------------------------------------------------------
RenderPass::~RenderPass()
{
    device_.NativeObject_().destroyFramebuffer(framebuffer_, nullptr);
    device_.NativeObject_().destroyRenderPass(renderPass_, nullptr);
}

} // namespace ae::gfx_low
// EOF
