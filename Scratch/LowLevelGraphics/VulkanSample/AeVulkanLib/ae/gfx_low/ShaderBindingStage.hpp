// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// プログラマブルシェーダーをアサインできるステージを表す列挙値。
/// @todo テッセレーションなど他のステージの対応。
enum class ShaderBindingStage {
    /// 無効値。
    Invalid,

    /// 頂点シェーダーステージ。
    Vertex,

    /// ジオメトリシェーダーステージ。
    Geometry,

    /// フラグメントシェーダーステージ。
    Fragment,

    /// コンピュートシェーダーステージ。
    Compute,

    TERM,
};

} // namespace gfx_low
} // namespace ae
// EOF
