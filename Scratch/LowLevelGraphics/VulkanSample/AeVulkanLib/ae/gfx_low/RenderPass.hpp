// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class RenderPassCreateInfo;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

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
    ::vk::RenderPassBeginInfo RenderPassBeginInfo_() const {
        return renderPassBeginInfo_;
    }
    //::vk::RenderPass* RenderPass_() { return &renderPass_; }
    //const ::vk::RenderPass* RenderPass_() const { return &renderPass_; }
    //::vk::Framebuffer* Framebuffer_() { return &framebuffer_; }
    //const ::vk::Framebuffer* Framebuffer_() const { return &framebuffer_; }
    //const ::vk::ClearValue* ClearValues_() const { return &clearValues_[0]; }
    //@}

private:
    gfx_low::Device& device_;
    ::vk::RenderPass renderPass_ = {};
    ::vk::Framebuffer framebuffer_ = {};
    std::array<::vk::ClearValue, Device::SupportedAttachmentCountMax_>
        clearValues_ = {};
    ::vk::RenderPassBeginInfo renderPassBeginInfo_;
};

} // namespace gfx_low
} // namespace ae
// EOF
