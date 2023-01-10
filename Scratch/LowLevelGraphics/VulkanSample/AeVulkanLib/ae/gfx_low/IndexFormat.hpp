// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// インデックスバッファのフォーマット。
enum class IndexFormat
{
    /// 無効値。
    Invalid,

    Uint16,

    Uint32,

    TERM,
};

} // namespace gfx_low
} // namespace ae
// EOF
