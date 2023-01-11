// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// レンダーパイプラインにおけるプログラマブルシェーダーをアサインできるステージを表す列挙値。
/// @todo テッセレーションなど他のステージの対応。
enum class RenderPipelineShaderStage
{
    /// 無効値。
    Invalid,

    /// 頂点シェーダーステージ。
    Vertex,

    /// ジオメトリシェーダーステージ。
    Geometry,

    /// フラグメントシェーダーステージ。
    Fragment,

    TERM,
};

} // namespace ae::gfx_low
// EOF
