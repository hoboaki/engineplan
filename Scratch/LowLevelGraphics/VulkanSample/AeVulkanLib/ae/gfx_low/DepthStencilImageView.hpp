// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class Device;
class DepthStencilImageViewCreateInfo;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// レンダリングパイプラインにおけるデプスステンシルを扱うビューデスクリプタ。
class DepthStencilImageView {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    DepthStencilImageView(const DepthStencilImageViewCreateInfo& createInfo);
    ~DepthStencilImageView();
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
