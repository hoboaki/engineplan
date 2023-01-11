// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// プリミティブトポロジの種類を示す列挙値。
enum class PrimitiveTopologyKind
{
    Invalid,

    /// 点リスト。
    PointList,

    /// 線分リスト。
    LineList,

    /// 連続した線分リスト。
    LineStrip,

    /// 三角形リスト。
    TriangleList,

    /// 連続した三角形リスト。
    TriangleStrip,

    TERM,
};

} // namespace ae::gfx_low
// EOF
