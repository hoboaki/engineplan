// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// バッファリソースの使用法。
enum class BufferResourceUsage
{
    /// 無効値。
    Invalid,

    /// コピー読み込み元。
    CopySrc,

    /// コピー書き込み先。
    CopyDst,

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

    TERM,
};

} // namespace ae::gfx_low
// EOF
