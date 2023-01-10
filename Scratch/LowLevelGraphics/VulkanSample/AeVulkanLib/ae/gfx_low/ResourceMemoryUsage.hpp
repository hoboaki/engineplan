// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// リソースメモリの使用法。
enum class ResourceMemoryUsage
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

    /// ImageResourceTiling::Optimal なイメージ。
    OptimalTilingImage,

    /// ユニフォームバッファ。
    UniformBuffer,

    /// ストレージバッファ。
    StorageBuffer,

    /// レンダリングパスのインデックスバッファ。
    IndexBuffer,

    /// レンダリングパスの頂点バッファ。
    VertexBuffer,

    /// インダイレクト引数用バッファ。
    IndirectBuffer,

    /// コンパイル済シェーダモジュール。
    CompiledShaderModule,

    TERM,
};

} // namespace gfx_low
} // namespace ae
// EOF
