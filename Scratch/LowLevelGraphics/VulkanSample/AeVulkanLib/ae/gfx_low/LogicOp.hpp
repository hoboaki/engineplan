// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// 論理演算を示す列挙値。
enum class LogicOp
{
    /// 無効値。
    Invalid,

    /// 0 を設定。
    Clear,

    /// 1 を設定。
    Set,

    /// src を設定。
    Copy,

    /// ~src を設定。
    CopyInverted,

    /// dst を設定。
    NoOp,

    /// ~dst を設定。
    Invert,

    /// src & dst を設定。
    And,

    /// src & ~dst を設定。
    AndReverse,

    /// ~src & dst を設定。
    AndInverted,

    /// ~(src & dst) を設定。
    Nand,

    /// src | dst を設定。
    Or,

    /// src | ~dst を設定。
    OrReverse,

    /// ~src | dst を設定。
    OrInverted,

    /// ~(src | dst)
    Nor,

    /// src ^ dst を設定。
    Xor,

    /// ~(src ^ dst) を設定。
    Equivalent,

    TERM,
};

} // namespace ae::gfx_low
// EOF
