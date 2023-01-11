// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// 比較演算を示す列挙値。
enum class CompareOp
{
    /// 無効値。
    Invalid,

    /// 常に偽。
    Never,

    /// '<'。
    Less,

    /// '=='。
    Equal,

    /// '<='。
    LessEqual,

    /// '>'。
    Greater,

    /// '!='。
    NotEqual,

    /// '>='。
    GreaterEqual,

    /// 常に真。
    Always,

    TERM,
};

} // namespace ae::gfx_low
// EOF
