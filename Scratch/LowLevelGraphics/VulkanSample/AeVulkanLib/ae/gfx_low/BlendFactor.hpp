// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ブレンド要素に乗算される係数を示す列挙値。
enum class BlendFactor
{
    /// 無効値。
    Invalid,

    /// 0で乗算。
    Zero,

    /// 1で乗算。
    One,

    /// SrcColor で乗算。
    SrcColor,

    /// (1 - SrcColor) で乗算。
    OneMinusSrcColor,

    /// DstColor で乗算。
    DstColor,

    /// (1 - DstColor) で乗算。
    OneMinusDstColor,

    /// SrcAlpha で乗算。
    SrcAlpha,

    /// (1 - SrcAlpha) で乗算。
    OneMinusSrcAlpha,

    /// DstAlpha で乗算。
    DstAlpha,

    /// (1 - DstAlpha) で乗算。
    OneMinusDstAlpha,

    /// Constant で乗算。
    Constant,

    /// (1 - Constant) で乗算。
    OneMinusConstant,

    /// RGBA(vec3.one * min(SrcAlpha, 1 - DstAlpha), 1) で乗算。
    SrcAlphaSaturate,

    /// Src1 の SrcColor で乗算。
    Src1Color,

    /// Src1 の (1 - SrcColor) で乗算。
    OneMinusSrc1Color,

    /// Src1 の SrcAlpha で乗算。
    Src1Alpha,

    /// Src1 の (1 - SrcAlpha) で乗算。
    OneMinusSrc1Alpha,

    TERM,
};

} // namespace ae::gfx_low
// EOF
