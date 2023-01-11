// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// コマンドバッファの階層レベルを表す列挙値。
enum class CommandBufferLevel
{
    /// 無効値。
    Invalid,

    /// プライマリレベル。Queue に直接詰むことが可能。
    Primary,

    /// セカンダリレベル。Queue に直接詰むことはできず Primary
    /// のコマンドバッファから Call して使用する。
    /// @details
    /// Secondary はいくつか制限があります。詳細は CommandBuffer
    /// のクラスコメントを参照してください。
    Secondary,

    TERM,
};

} // namespace ae::gfx_low
// EOF
