// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// SamplerAddressMode が ClampToBorder のときに使われる色。
enum class SamplerBorderColor
{
    /// 無効値。
    Invalid,

    /// RGBA(0, 0, 0, 0) の値。
    TransparentBlack,

    /// RGBA(0, 0, 0, 1) の値。
    OpaqueBlack,

    /// RGBA(1, 1, 1, 1) の値。
    OpaqueWhite,

    TERM,
};

} // namespace ae::gfx_low
// EOF
