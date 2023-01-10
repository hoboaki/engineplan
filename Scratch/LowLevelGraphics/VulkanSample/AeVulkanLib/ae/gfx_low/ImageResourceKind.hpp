// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// イメージリソースの種類。
enum class ImageResourceKind
{
    /// 無効値。
    Invalid,

    /// １次元イメージ。
    Image1d,

    /// ２次元イメージ。
    Image2d,

    /// ３次元イメージ。
    Image3d,

    /// キューブイメージ。
    ImageCube,

    TERM,
};

} // namespace gfx_low
} // namespace ae
// EOF
