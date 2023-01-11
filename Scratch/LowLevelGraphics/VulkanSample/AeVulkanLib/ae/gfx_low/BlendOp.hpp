// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ブレンド演算を示す列挙値。
enum class BlendOp
{
    /// 無効値。
    Invalid,

    /// 加算。
    Add,

    /// Src - Dst の減算。　
    Subtract,

    /// Dst - Src の減算。
    ReverseSubtract,

    /// 最小値を選択。
    Min,

    /// 最大値を選択。
    Max,

    TERM,
};

} // namespace ae::gfx_low
// EOF
