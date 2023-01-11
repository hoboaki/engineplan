// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// Queue の種類。
enum class QueueKind
{
    /// 無効値。
    Invalid,

    /// Render、Present、Compute、Copy、をサポート。
    Normal,

    /// Compute のみをサポート。
    ComputeOnly,

    /// Copy のみをサポート。
    CopyOnly,

    TERM,
};

} // namespace ae::gfx_low
// EOF
