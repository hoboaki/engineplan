// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class Device;
class RenderTargetImageViewCreateInfo;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// レンダリングパイプラインにおける１枚の描画対象を扱うビューデスクリプタ。
class RenderTargetImageView {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    RenderTargetImageView(const RenderTargetImageViewCreateInfo& createInfo);
    ~RenderTargetImageView();
    //@}

    /// @name プロパティ
    //@{
    /// 所属する Device。
    gfx_low::Device& Device() const { return device_; }
    //@}

    /// @name 内部処理用機能
    //@{
    ::vk::ImageView& NativeObject_() { return nativeObject_; }
    //@}

private:
    gfx_low::Device& device_;
    ::vk::ImageView nativeObject_;
};

} // namespace ae::gfx_low
// EOF
