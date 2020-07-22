// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// バッファフォーマット。
/// @details
/// 列挙値の名前がメモリ上における要素の並び順を表しているわけではありません。
/// 例えば　R8G8 というフォーマットがメモリ的には G のほうが先に配置されていることもありえます。
/// 配置の仕様は動作プラットフォームに依存します。 
///
/// （開発用メモ）非圧縮名前順、圧縮名前順で列挙値を定義しています。
enum class Format {
    /// 無効値。
    Invalid,

    R8Unorm,
    R8Uint,
    R8Sint,
    R8Snorm,
    R16Unorm,
    R16Uint,
    R16Sfloat,
    R16Sint,
    R16Snorm,

    R8G8Unorm,
    R8G8Uint,
    R8G8Sint,
    R8G8Snorm,
    R16G16Unorm,
    R16G16Uint,
    R16G16Sfloat,
    R16G16Sint,
    R16G16Snorm,

    R11G11B10Ufloat,

    R8G8B8A8Uint,
    R8G8B8A8Unorm,
    R8G8B8A8UnormSrgb,
    R10G10B10A2Unorm,
    R10G10B10A2Uint,
    R16G16B16A16Sfloat,
    R16G16B16A16Sint,
    R16G16B16A16Snorm,
    R16G16B16A16Uint,
    R16G16B16A16Unorm,

    TERM,
};

}  // namespace gfx_low
}  // namespace ae
// EOF
