// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/ImageFormat.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// DepthStencil の仕様情報。
class DepthStencilSpecInfo {
public:
    /// @name プロパティ
    //@{
    /// イメージフォーマット。（初期値：Invalid）
    gfx_low::ImageFormat ImageFormat() const { return imageFormat_; }

    /// ImageFormat() の設定。
    DepthStencilSpecInfo& SetImageFormat(
        const gfx_low::ImageFormat imageFormat);
    //@}

private:
    gfx_low::ImageFormat imageFormat_ = ImageFormat::Invalid;
};

} // namespace ae::gfx_low
// EOF
