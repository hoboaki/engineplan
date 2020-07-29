// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class Device;
class ImageResource;
}
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// RenderTargetImageView オブジェクト作成に必要な情報。
class RenderTargetImageViewCreateInfo {
public:
    /// @name 属する Device オブジェクトのポインタ（設定必須、初期値：nullptr）
    //@{
    gfx_low::Device* Device() const { return device_.get(); }
    RenderTargetImageViewCreateInfo& SetDevice(gfx_low::Device* system) {
        device_.reset(system);
        return *this;
    }
    //@}

    /// @name 対象となる ImageResource のポインタ（設定必須、初期値：nullptr）
    //@{
    gfx_low::ImageResource* ImageResource() const { return imageResource_.get(); }
    RenderTargetImageViewCreateInfo& SetImageResource(gfx_low::ImageResource* system) {
        imageResource_.reset(system);
        return *this;
    }
    //@}

    /// @name 内部処理用関数群
    //@{
    /// Vulkan ライブラリのフォーマット。こちらが指定されている場合は Format() よりも優先して使う。
    ::vk::Format PrvRawFormat() const { return rawFormat_; }
    RenderTargetImageViewCreateInfo& PrvSetRawFormat(::vk::Format rawFormat) {
        rawFormat_ = rawFormat;
        return *this;
    }
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    base::Pointer<gfx_low::ImageResource> imageResource_;
    ::vk::Format rawFormat_ = ::vk::Format::eUndefined;
};

}  // namespace gfx_low
}  // namespace ae
// EOF