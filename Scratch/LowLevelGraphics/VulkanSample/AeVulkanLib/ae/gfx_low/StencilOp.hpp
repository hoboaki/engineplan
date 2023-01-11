// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ステンシルに対する動作を示す列挙値。
enum class StencilOp
{
    /// 無効値。
    Invalid,

    /// 値を維持。
    Keep,

    /// ゼロに設定。
    Zero,

    /// 指定した値に設定。
    Replace,

    /// +1 する。元の値が最大値の場合は値を維持。
    IncrementAndClamp,

    /// -1 する。元の値が最小値の場合は値を維持。
    DecrementAndClamp,

    /// ビット反転。
    Invert,

    /// +1 する。元の値が最大値の場合は最小値にラップする。
    IncrementAndWrap,

    /// -1 する。元の値が最小値の場合は最大値にラップする。
    DecrementAndWrap,

    TERM,
};

} // namespace ae::gfx_low
// EOF
