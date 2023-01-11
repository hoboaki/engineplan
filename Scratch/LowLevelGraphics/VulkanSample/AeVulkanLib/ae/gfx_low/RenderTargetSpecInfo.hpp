// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/ImageFormat.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// RenderTarget の仕様情報。
class RenderTargetSpecInfo {
public:
    /// @name プロパティ
    //@{
    /// イメージフォーマット。（初期値：Invalid）
    gfx_low::ImageFormat ImageFormat() const { return imageFormat_; }

    /// ImageFormat() の設定。
    RenderTargetSpecInfo& SetImageFormat(
        const gfx_low::ImageFormat imageFormat);
    //@}

    /// @name 内部処理用機能群
    //@{
    /// Native フォーマット。Format() より優先される。
    ::vk::Format NativeFormat_() const { return nativeFormat_; }

    /// NativeFormat() 設定。
    RenderTargetSpecInfo& SetNativeFormat_(::vk::Format format)
    {
        nativeFormat_ = format;
        return *this;
    }
    //@}

private:
    gfx_low::ImageFormat imageFormat_ = ImageFormat::Invalid;
    ::vk::Format nativeFormat_ = ::vk::Format::eUndefined;
};

} // namespace ae::gfx_low
// EOF
