// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/ShaderBindingRegion.hpp>

namespace ae::gfx_low {
class StorageImageView;
}

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// StorageImage 用デスクリプタの情報。
class StorageImageDescriptorInfo {
public:
    /// @name プロパティ
    //@{
    /// バインド範囲。（初期値：デフォルトコンストラクタの値）
    ShaderBindingRegion Region() const { return region_; }

    /// Region() の設定。
    StorageImageDescriptorInfo& SetRegion(const ShaderBindingRegion& region)
    {
        region_ = region;
        return *this;
    }

    /// StorageImageView の配列ポインタ。（初期値：nullptr）
    const StorageImageView** Views() const { return views_.Get(); }

    /// Views() の設定。
    /// @param views Region().ElemCount() 長の配列ポインタ。
    StorageImageDescriptorInfo& SetViews(const StorageImageView** views)
    {
        views_.Reset(views);
        return *this;
        ;
    }
    //@}

private:
    ShaderBindingRegion region_;
    base::Pointer<const StorageImageView*> views_;
};

} // namespace ae::gfx_low
// EOF
