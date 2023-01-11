// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ポリゴンの表面解釈の方法を示す列挙値。
enum class PolygonFrontFace
{
    /// 無効値。
    Invalid,

    /// 頂点の並びが時計回りとして表面を解釈。
    Clockwise,

    /// 頂点の並びが反時計周りとして表面を解釈。
    CounterClockwise,

    TERM,
};

} // namespace ae::gfx_low
// EOF
