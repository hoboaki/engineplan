// 文字コード：UTF-8
#include <ae/gfx_low/RenderPass.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/DepthStencilImageView.hpp>
#include <ae/gfx_low/DepthStencilSetting.hpp>
#include <ae/gfx_low/DepthStencilSpecInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/InternalUtility.hpp>
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

    // RenderPass 作成
    InternalUtility::CreateRenderPass(
        &renderPass_,
        info.Device(),
        info.RenderPassSpecInfo(),
        info.RenderTargetSettings(),
        info.DepthStencilSettingPtr());

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
