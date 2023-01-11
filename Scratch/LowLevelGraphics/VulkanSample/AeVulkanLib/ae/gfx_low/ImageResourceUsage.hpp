// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// イメージリソースの使用法。
enum class ImageResourceUsage
{
    /// 無効値。
    Invalid,

    /// コピー読み込み元。
    CopySrc,

    /// コピー書き込み先。
    CopyDst,

    /// イメージ読み込み。
    SampledImage,

    /// イメージ書き込み。
    StorageImage,

    /// フレームバッファのレンダーターゲットイメージ。
    RenderTargetImage,

    /// フレームバッファのデプスステンシルイメージ。
    DepthStencilImage,

    TERM,
};

} // namespace ae::gfx_low
// EOF
