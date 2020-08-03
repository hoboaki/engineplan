// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// イメージリソースのフォーマット。
/// @details
/// 列挙値の名前がメモリ上における要素の並び順を表しているわけではありません。
/// 例えば　R8G8 というフォーマットがメモリ的には G
/// のほうが先に配置されていることもありえます。
/// 配置の仕様は動作プラットフォームに依存します。
///
/// （開発用メモ）非圧縮名前順、圧縮名前順で列挙値を定義しています。
enum class ImageFormat {
    /// 無効値。
    Invalid,

    R8Sint,
    R8Snorm,
    R8Uint,
    R8Unorm,
    R16Sfloat,
    R16Sint,
    R16Snorm,
    R16Uint,
    R16Unorm,

    R8G8Sint,
    R8G8Snorm,
    R8G8Uint,
    R8G8Unorm,
    R16G16Sfloat,
    R16G16Sint,
    R16G16Snorm,
    R16G16Uint,
    R16G16Unorm,

    R11G11B10Ufloat,

    R8G8B8A8Uint,
    R8G8B8A8Unorm,
    R8G8B8A8UnormSrgb,
    R10G10B10A2Uint,
    R10G10B10A2Unorm,
    R16G16B16A16Sfloat,
    R16G16B16A16Sint,
    R16G16B16A16Snorm,
    R16G16B16A16Uint,
    R16G16B16A16Unorm,

    
    D16Unorm,
    D32Sfloat,

    D16UnormS8Uint,
    D24UnormS8Uint,
    D32SfloatS8Uint,

    S8Uint,

    TERM,
};

} // namespace gfx_low
} // namespace ae
// EOF
