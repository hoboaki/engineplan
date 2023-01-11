// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// コマンドバッファが扱う機能。
enum class CommandBufferFeature
{
    /// 無効値。
    Invalid,

    /// レンダリングパイプラインを使った描画。
    Render,

    /// コンピュートシェーダーを使った計算。
    Compute,

    /// リソースのメモリコピー。
    Copy,

    TERM,
};

} // namespace ae::gfx_low
// EOF
