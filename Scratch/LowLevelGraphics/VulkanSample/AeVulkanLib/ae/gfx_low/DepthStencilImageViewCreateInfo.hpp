// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/ImageFormat.hpp>
#include <ae/gfx_low/ImageSubresourceLocation.hpp>
#include <ae/gfx_low/ImageViewKind.hpp>

namespace ae::gfx_low {
class Device;
class ImageResource;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// DepthStencilImageView オブジェクト作成に必要な情報。
class DepthStencilImageViewCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// 属する Device オブジェクトのポインタ。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須）
    DepthStencilImageViewCreateInfo& SetDevice(gfx_low::Device* device)
    {
        device_.Reset(device);
        return *this;
    }

    /// 対象となる ImageResource のポインタ。（初期値：nullptr）
    ImageResource* Resource() const { return resource_.Get(); }

    /// ImageResource の設定。（設定必須）
    DepthStencilImageViewCreateInfo& SetResource(
        gfx_low::ImageResource* imageResource)
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
    DepthStencilImageViewCreateInfo& SetSubresourceLocation(
        const ImageSubresourceLocation& location)
    {
        subresourceLocation_ = location;
        return *this;
    }

    /// イメージフォーマット。（初期値：Invalid)
    ImageFormat Format() const { return format_; }

    /// Format() の設定。
    DepthStencilImageViewCreateInfo& SetFormat(ImageFormat format);
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    base::Pointer<gfx_low::ImageResource> resource_;
    ImageSubresourceLocation subresourceLocation_;
    ImageFormat format_ = ImageFormat::Invalid;
};

} // namespace ae::gfx_low
// EOF
