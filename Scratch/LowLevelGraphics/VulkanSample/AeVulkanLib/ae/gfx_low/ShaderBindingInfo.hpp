// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/ShaderBindingStageBitSet.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// シェーダーバインディングに関する情報。
class ShaderBindingInfo {
public:
    /// @name プロパティ
    //@{
    /// 参照するシェーダーステージ郡。（初期値：AllOff()）
    ShaderBindingStageBitSet Stages() const { return stages_; }

    /// Stages() の設定。
    ShaderBindingInfo& SetStages(const ShaderBindingStageBitSet& stages)
    {
        stages_ = stages;
        return *this;
    }

    /// バインディングする際の番号。（初期値：0）
    /// @details HLSL において、配列の場合は先頭の番号として扱われます。
    int BindingIndex() const { return bindingIndex_; }

    /// BindingIndex() の設定。
    /// @param index 0以上。
    ShaderBindingInfo& SetBindingIndex(int index);

    ///  バインディングする要素数。（初期値：1）
    /// @details 配列の場合はこの値を配列長として扱います。
    int ElemCount() const { return elemCount_; }

    /// ElemCount() の設定。
    /// @param count 1以上。
    ShaderBindingInfo& SetElemCount(int count);
    //@}

private:
    ShaderBindingStageBitSet stages_;
    int bindingIndex_ = 0;
    int elemCount_ = 1;
};

} // namespace ae::gfx_low
// EOF
