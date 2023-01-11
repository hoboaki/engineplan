// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// MipLevel のあるテクスチャからサンプリングするときの値の取得方法。
enum class SamplerMipmapMode
{
    /// 無効値。
    Invalid,

    /// 最寄り１枚の MipLevel テクスチャのサンプリング結果を取得。
    Nearest,

    /// 最寄り２枚の MipLevel テクスチャのサンプリング結果を補間した値を取得。
    Linear,

    TERM,
};

} // namespace ae::gfx_low
// EOF
