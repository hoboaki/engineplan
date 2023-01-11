// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// 頂点バッファ内の頂点属性データ参照位置を移動する単位を示す列挙値。
enum class VertexStepRate
{
    /// 無効値。
    Invalid,

    /// 頂点IDごとに参照位置を移動。
    Vertex,

    /// インスタンスIDごとに参照位置を移動。
    Instance,

    TERM,
};

} // namespace ae::gfx_low
// EOF
