// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class RenderPassCreateInfo;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// レンダーパスを扱うクラス。
class RenderPass {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    RenderPass(const RenderPassCreateInfo& createInfo);
    ~RenderPass();
    //@}

    /// @name プロパティ
    //@{
    /// 所属する Device。
    gfx_low::Device& Device() const { return device_; }
    //@}

    /// @name 内部処理用機能
    //@{
    int RenderTargetCount_() const { return renderTargetCount_; }
    ::vk::RenderPassBeginInfo RenderPassBeginInfo_() const
    {
        return renderPassBeginInfo_;
    }
    const ::vk::RenderPass* RenderPass_() const { return &renderPass_; }
    const ::vk::Framebuffer* Framebuffer_() const { return &framebuffer_; }
    //@}

private:
    gfx_low::Device& device_;
    const int renderTargetCount_ = {};
    ::vk::RenderPass renderPass_ = {};
    ::vk::Framebuffer framebuffer_ = {};
    std::array<::vk::ClearValue, Device::SupportedAttachmentCountMax_>
        clearValues_ = {};
    ::vk::RenderPassBeginInfo renderPassBeginInfo_;
};

} // namespace ae::gfx_low
// EOF
