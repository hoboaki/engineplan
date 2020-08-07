// 文字コード：UTF-8
#pragma once

namespace {}

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// グラフィックスパイプラインにおけるプログラマブルシェーダーをアサインできるステージを表す列挙値。
/// @todo テッセレーションなど他のステージの対応。
enum class GraphicsPipelineShaderStage {
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

} // namespace gfx_low
} // namespace ae
// EOF
