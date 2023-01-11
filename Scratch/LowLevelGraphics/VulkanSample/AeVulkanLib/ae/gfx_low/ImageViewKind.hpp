// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// イメージビューの種類。
enum class ImageViewKind
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

    /// １次元イメージ配列。
    Image1dArray,

    /// ２次元イメージ配列。
    Image2dArray,

    /// キューブイメージ配列。
    ImageCubeArray,

    TERM,
};

} // namespace ae::gfx_low
// EOF
