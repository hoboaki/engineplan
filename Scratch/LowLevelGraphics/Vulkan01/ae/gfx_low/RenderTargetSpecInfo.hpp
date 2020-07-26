// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/Format.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// RenderTarget の仕様情報。
class RenderTargetSpecInfo {
public:
    /// @name プロパティ
    //@{
    /// イメージフォーマット。（初期値：Invalid）
    gfx_low::Format Format() const { return format_; }

    /// Format() の設定。 
    RenderTargetSpecInfo& SetFormat(const gfx_low::Format format);
    //@}

    /// @name 内部処理用機能群
    //@{
    /// Native フォーマット。Format() より優先される。
    ::vk::Format InternalNativeFormat() const { return nativeFormat_; }

    /// NativeFormat() 設定。 
    RenderTargetSpecInfo& InternalSetNativeFormat(::vk::Format format)
    {
        nativeFormat_ = format;
        return *this;
    }
    //@}

private:
    gfx_low::Format format_ = Format::Invalid;
    ::vk::Format nativeFormat_ = ::vk::Format::eUndefined;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
