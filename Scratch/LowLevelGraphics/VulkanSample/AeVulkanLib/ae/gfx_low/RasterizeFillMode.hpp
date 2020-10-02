// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// ラスタライズ時にポリゴンをどのように埋めるかを示す列挙値。
enum class RasterizeFillMode {
    /// 無効値。
    Invalid,

    /// ワイヤーフレーム状に埋める。
    Wireframe,

    /// 面を全て埋める。
    Solid,

    TERM,
};

} // namespace gfx_low
} // namespace ae
// EOF
