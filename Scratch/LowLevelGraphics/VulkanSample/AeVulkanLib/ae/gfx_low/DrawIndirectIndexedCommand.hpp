// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// 頂点インデックスを使うタイプの DrawIndirect のコマンド構造体。
/// @details
/// 構造体のデータサイズは使用するグラフィックスAPIによって変わります。
struct DrawIndirectIndexedCommand
{
public:
    /// @name プロパティ
    //@{
    /// 描画処理の起点となるインデックス番号。（初期値：0）
    int IndexOffset() const { return native_.firstIndex; }

    /// IndexOffset() の設定。
    /// @param offset 0以上。
    DrawIndirectIndexedCommand& SetIndexOffset(int offset);

    /// 描画処理の起点となる頂点番号。（初期値：0）
    int VertexOffset() const { return native_.vertexOffset; }

    /// VertexOffset() の設定。
    /// @param offset 0以上。
    DrawIndirectIndexedCommand& SetVertexOffset(int offset);

    /// 描画処理をする頂点数。 （初期値：0）
    int VertexCount() const { return native_.indexCount; }

    /// VertexCount() の設定。
    /// @param count 0以上。
    DrawIndirectIndexedCommand& SetVertexCount(int count);

    /// インスタンス番号の起点となる番号。 （初期値：0）
    int InstanceOffset() const { return native_.firstInstance; }

    /// InstanceOffset() の設定。
    /// @param offset 0以上。
    DrawIndirectIndexedCommand& SetInstanceOffset(int offset);

    /// 描画処理をするインスタンス数。 （初期値：0）
    int InstanceCount() const { return native_.instanceCount; }

    /// InstanceCount() の設定。
    /// @param count 0以上。
    DrawIndirectIndexedCommand& SetInstanceCount(int count);
    //@}

    /// @name 内部処理用API
    //@{
    ::vk::DrawIndexedIndirectCommand native_;
    //@}
};

} // namespace ae::gfx_low
// EOF
