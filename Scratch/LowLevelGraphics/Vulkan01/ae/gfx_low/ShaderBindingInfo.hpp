// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/ShaderBindingBitSet.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// シェーダーバインディングに関する情報。
class ShaderBindingInfo {
public:
    /// @name プロパティ
    //@{
    /// 参照するシェーダーステージ郡。（初期値：AllOff()）
    ShaderBindingStageBitSet Stages() const { return stages_; }

    /// Stages() の設定。
    ShaderBindingInfo& SetStages(const ShaderBindingStageBitSet& stages) {
        stages_ = stages;
        return *this;
    }
    //@}

private:
    ShaderBindingStageBitSet stages_;
};

} // namespace gfx_low
} // namespace ae
// EOF
