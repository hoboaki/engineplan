// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/ImageFormat.hpp>
#include <ae/gfx_low/ImageSubresourceRange.hpp>
#include <ae/gfx_low/ImageViewKind.hpp>

namespace ae {
namespace gfx_low {
class Device;
class ImageResource;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// StorageImageView オブジェクト作成に必要な情報。
class StorageImageViewCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// 属する Device オブジェクトのポインタ。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須）
    StorageImageViewCreateInfo& SetDevice(gfx_low::Device* device) {
        device_.Reset(device);
        return *this;
    }

    /// 対象となる ImageResource のポインタ。（初期値：nullptr）
    ImageResource* Resource() const { return resource_.Get(); }

    /// ImageResource の設定。（設定必須）
    StorageImageViewCreateInfo& SetResource(
        gfx_low::ImageResource* imageResource) {
        resource_.Reset(imageResource);
        return *this;
    }

    /// イメージビューの種類。（初期値：Invalid）
    ImageViewKind Kind() const { return kind_; }

    /// Kind() の設定。
    StorageImageViewCreateInfo& SetKind(ImageViewKind kind);

    /// イメージフォーマット。（初期値：Invalid)
    ImageFormat Format() const { return format_; }

    /// Format() の設定。
    StorageImageViewCreateInfo& SetFormat(ImageFormat format);

    /// 読み取り対象となる ImageSubresourceの範囲。（初期値：デフォルトコンストラクタの値）
    ImageSubresourceRange SubresourceRange() const { return subresourceRange_; }

    /// SubresourceRange() の設定。
    StorageImageViewCreateInfo& SetSubresourceRange(
        const ImageSubresourceRange& range) {
        subresourceRange_ = range;
        return *this;
    }
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    base::Pointer<gfx_low::ImageResource> resource_;
    ImageSubresourceRange subresourceRange_;
    ImageFormat format_ = ImageFormat::Invalid;
    ImageViewKind kind_ = ImageViewKind::Invalid;
};

} // namespace gfx_low
} // namespace ae
// EOF
