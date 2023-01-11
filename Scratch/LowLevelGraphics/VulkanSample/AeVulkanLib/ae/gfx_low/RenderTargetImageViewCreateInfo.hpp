// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/ImageSubresourceLocation.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class Device;
class ImageResource;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// RenderTargetImageView オブジェクト作成に必要な情報。
class RenderTargetImageViewCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// 属する Device オブジェクトのポインタ。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須）
    RenderTargetImageViewCreateInfo& SetDevice(gfx_low::Device* device)
    {
        device_.Reset(device);
        return *this;
    }

    /// 対象となる ImageResource のポインタ。（初期値：nullptr）
    ImageResource* Resource() const { return resource_.Get(); }

    /// Resource() の設定。（設定必須）
    RenderTargetImageViewCreateInfo& SetResource(ImageResource* imageResource)
    {
        resource_.Reset(imageResource);
        return *this;
    }

    /// 対象となる ImageSubresource。（初期値：デフォルトコンストラクタの値）
    ImageSubresourceLocation SubresouceLocation() const
    {
        return subresourceLocation_;
    }

    /// SubresourceLocation() の設定。
    RenderTargetImageViewCreateInfo& SetSubresourceLocation(
        const ImageSubresourceLocation& location)
    {
        subresourceLocation_ = location;
        return *this;
    }
    //@}

    /// @name 内部処理用関数群
    //@{
    /// Vulkan ライブラリのフォーマット。こちらが指定されている場合は Format()
    /// よりも優先して使う。
    ::vk::Format RawFormat_() const { return rawFormat_; }
    RenderTargetImageViewCreateInfo& SetRawFormat_(::vk::Format rawFormat)
    {
        rawFormat_ = rawFormat;
        return *this;
    }
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    base::Pointer<ImageResource> resource_;
    ImageSubresourceLocation subresourceLocation_;
    ::vk::Format rawFormat_ = ::vk::Format::eUndefined;
};

} // namespace ae::gfx_low
// EOF
