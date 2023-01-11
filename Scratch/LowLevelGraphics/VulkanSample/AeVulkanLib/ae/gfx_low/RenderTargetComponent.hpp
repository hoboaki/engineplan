// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// レンダーターゲットのRGBA要素を示す列挙値。
enum class RenderTargetComponent
{
    /// 無効値。
    Invalid,

    /// R。
    Red,

    /// G。
    Green,

    /// B。
    Blue,

    /// A。
    Alpha,

    TERM,
};

} // namespace ae::gfx_low
// EOF
