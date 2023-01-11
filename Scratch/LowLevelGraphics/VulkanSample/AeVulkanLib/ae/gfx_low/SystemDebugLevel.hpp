// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// デバッグレベルを表す列挙値。
enum class SystemDebugLevel
{
    /// デバッグ動作なし。
    NoDebug,

    /// 重要な情報に絞って出力。
    Normal,

    /// 全ての情報を出力。
    All,

    TERM,
};

} // namespace ae::gfx_low
// EOF
