// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/ShaderBindingRegion.hpp>

namespace ae::gfx_low {
class SampledImageView;
}

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// SampledImage 用デスクリプタの情報。
class SampledImageDescriptorInfo {
public:
    /// @name プロパティ
    //@{
    /// バインド範囲。（初期値：デフォルトコンストラクタの値）
    ShaderBindingRegion Region() const { return region_; }

    /// Region() の設定。
    SampledImageDescriptorInfo& SetRegion(const ShaderBindingRegion& region)
    {
        region_ = region;
        return *this;
    }

    /// SampledImageView の配列ポインタ。（初期値：nullptr）
    const SampledImageView** Views() const { return views_.Get(); }

    /// Views() の設定。
    /// @param views Region().ElemCount() 長の配列ポインタ。
    SampledImageDescriptorInfo& SetViews(const SampledImageView** views)
    {
        views_.Reset(views);
        return *this;
        ;
    }
    //@}

private:
    ShaderBindingRegion region_;
    base::Pointer<const SampledImageView*> views_;
};

} // namespace ae::gfx_low
// EOF
