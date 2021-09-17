// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/PrimitiveTopologyKind.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// ドローコールに必要な情報。
class DrawCallInfo {
public:
    /// @name プロパティ
    //@{
    /// プリミティブトポロジの種類。（初期値：Invalid）
    gfx_low::PrimitiveTopologyKind PrimitiveTopologyKind() const {
        return primitiveTopologyKind_;
    }

    /// PrimitiveTopologyKind() の設定。（設定必須）
    DrawCallInfo& SetPrimitiveTopologyKind(gfx_low::PrimitiveTopologyKind kind);

    /// 描画処理の起点となる頂点番号。（初期値：0）
    int VertexOffset() const { return vertexOffset_; }

    /// VertexOffset() の設定。
    /// @param offset 0以上。
    DrawCallInfo& SetVertexOffset(int offset);

    /// 描画処理をする頂点数。 （初期値：0）
    int VertexCount() const { return vertexCount_; }

    /// VertexCount() の設定。
    /// @param count 1以上。
    DrawCallInfo& SetVertexCount(int count);

    /// インデックスバッファを使用するか。 （初期値：false）
    bool UseIndexBuffer() const { return useIndexBuffer_; }

    /// UseIndexBuffer() の設定。
    DrawCallInfo& SetUseIndexBuffer(bool useIndexBuffer) {
        useIndexBuffer_ = useIndexBuffer;
        return *this;
    }

    /// インデックスバッファの起点となる番号。 （初期値：0）
    int IndexOffset() const { return indexOffset_; }

    /// IndexOffset() の設定。
    /// @param offset 0以上。
    DrawCallInfo& SetIndexOffset(int offset);

    /// インスタンス番号の起点となる番号。 （初期値：0）
    int InstanceOffset() const { return instanceOffset_; }

    /// InstanceOffset() の設定。
    /// @param offset 0以上。
    DrawCallInfo& SetInstanceOffset(int offset);

    /// 描画処理をするインスタンス数。 （初期値：1）
    int InstanceCount() const { return instanceCount_; }

    /// InstanceCount() の設定。
    /// @param count 1以上。
    DrawCallInfo& SetInstanceCount(int count);
    //@}

private:
    gfx_low::PrimitiveTopologyKind primitiveTopologyKind_ =
        PrimitiveTopologyKind::Invalid;
    int vertexOffset_ = 0;
    int vertexCount_ = 0;
    int indexOffset_ = 0;
    int instanceOffset_ = 0;
    int instanceCount_ = 1;
    bool useIndexBuffer_ = false;
};

} // namespace gfx_low
} // namespace ae
// EOF
