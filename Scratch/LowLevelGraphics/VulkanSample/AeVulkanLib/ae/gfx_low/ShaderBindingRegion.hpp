// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/ShaderBindingStageBitSet.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// シェーダーバインディングの範囲を示すクラス。
/// @details
/// 各プロパティは ShaderBindingInfo のプロパティに対応しています。
class ShaderBindingRegion {
public:
    /// @name プロパティ
    //@{
    /// バインディング番号。（初期値：0）
    int BindingIndex() const { return bindingIndex_; }

    /// BindingIndex() の設定。
    /// @param index 0以上。
    ShaderBindingRegion& SetBindingIndex(int index);

    /// 起点となる要素番号。（初期値：0）
    int ElemOffset() const { return elemOffset_; }

    /// ElemOffset() の設定。
    /// @param offset 0以上。
    ShaderBindingRegion& SetElemOffset(int offset);

    /// 起点からの要素数。（初期値：1）
    int ElemCount() const { return elemCount_; }

    /// ElemCount() の設定。
    /// @param count 1以上。
    ShaderBindingRegion& SetElemCount(int count);
    //@}

private:
    ShaderBindingStageBitSet stages_;
    int bindingIndex_ = 0;
    int elemOffset_ = 0;
    int elemCount_ = 1;
};

} // namespace ae::gfx_low
// EOF
