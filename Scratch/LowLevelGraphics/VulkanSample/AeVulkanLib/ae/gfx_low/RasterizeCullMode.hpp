// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ラスタライズ時に行われるポリゴン面カリングの動作を表す列挙値。
enum class RasterizeCullMode
{
    /// 無効値。
    Invalid,

    /// 面カリングしない。
    None,

    /// 表面をカリング。
    Front,

    /// 裏面をカリング。
    Back,

    TERM,
};

} // namespace ae::gfx_low
// EOF
