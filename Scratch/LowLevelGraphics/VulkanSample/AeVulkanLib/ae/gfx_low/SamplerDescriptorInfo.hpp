// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/ShaderBindingRegion.hpp>

namespace ae::gfx_low {
class Sampler;
}

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// Sampler 用デスクリプタの情報。
class SamplerDescriptorInfo {
public:
    /// @name プロパティ
    //@{
    /// バインド範囲。（初期値：デフォルトコンストラクタの値）
    ShaderBindingRegion Region() const { return region_; }

    /// Region() の設定。
    SamplerDescriptorInfo& SetRegion(const ShaderBindingRegion& region)
    {
        region_ = region;
        return *this;
    }

    /// サンプラーの配列ポインタ。（初期値：nullptr）
    const Sampler** Samplers() const { return samplers_.Get(); }

    /// Sampler() の設定。
    /// @param views Region().ElemCount() 長の配列ポインタ。
    SamplerDescriptorInfo& SetSamplers(const Sampler** samplers)
    {
        samplers_.Reset(samplers);
        return *this;
    }
    //@}

private:
    ShaderBindingRegion region_;
    base::Pointer<const Sampler*> samplers_;
};

} // namespace ae::gfx_low
// EOF
