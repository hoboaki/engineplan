// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/ShaderBindingRegion.hpp>

namespace ae::gfx_low {
class UniformBufferView;
}

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// UniformBuffer 用デスクリプタの情報。
class UniformBufferDescriptorInfo {
public:
    /// @name プロパティ
    //@{
    /// バインド範囲。（初期値：デフォルトコンストラクタの値）
    ShaderBindingRegion Region() const { return region_; }

    /// Region() の設定。
    UniformBufferDescriptorInfo& SetRegion(const ShaderBindingRegion& region)
    {
        region_ = region;
        return *this;
    }

    /// ユニフォームバッファビューの配列ポインタ。（初期値：nullptr）
    const UniformBufferView** Views() const { return views_.Get(); }

    /// Views() の設定。
    /// @param views Region().ElemCount() 長の配列ポインタ。
    UniformBufferDescriptorInfo& SetViews(const UniformBufferView** views)
    {
        views_.Reset(views);
        return *this;
        ;
    }
    //@}

private:
    ShaderBindingRegion region_;
    base::Pointer<const UniformBufferView*> views_;
};

} // namespace ae::gfx_low
// EOF
