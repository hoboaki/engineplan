// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class Device;
class ShaderResourceImageViewCreateInfo;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// シェーダーが参照するイメージとしてのビューデスクリプタ。
class ShaderResourceImageView {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    ShaderResourceImageView(const ShaderResourceImageViewCreateInfo& createInfo);
    ~ShaderResourceImageView();
    //@}

    /// @name プロパティ
    //@{
    /// 所属する Device。
    gfx_low::Device& Device() const { return device_; }
    //@}

    /// @name 内部処理用機能
    //@{
    ::vk::ImageView& Instance_() { return imageView_; }
    //@}

private:
    gfx_low::Device& device_;
    ::vk::ImageView imageView_;
};

} // namespace gfx_low
} // namespace ae
// EOF
