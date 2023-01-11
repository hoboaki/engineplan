// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>

namespace ae::gfx_low {
class VertexAttributeInfo;
class VertexBufferLayoutInfo;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// パイプラインの頂点入力に関する情報。
class PipelineVertexInputInfo {
public:
    /// @name プロパティ
    //@{
    /// 参照する頂点バッファの数。（初期値：0）
    int BufferCount() const { return bufferCount_; }

    /// BufferCount() の設定。
    /// @param count 0 以上。
    PipelineVertexInputInfo& SetBufferCount(int count);

    /// 頂点バッファのレイアウト情報配列の先頭アドレス。（初期値：nullptr）
    /// @details
    /// BufferCount() 長の配列として参照されます。
    /// 配列のインデックスは頂点バッファのスロット番号と一致します。
    const VertexBufferLayoutInfo* BufferLayoutInfos() const
    {
        return bufferLayoutInfos_.Get();
    }

    /// BufferLayoutInfos() の設定。
    PipelineVertexInputInfo& SetBufferLayoutInfos(
        const VertexBufferLayoutInfo* infos)
    {
        bufferLayoutInfos_.Reset(infos);
        return *this;
    }

    /// 入力する頂点属性の数。（初期値：0）
    int AttributeCount() const { return attributeCount_; }

    /// AttributeCount() の設定。
    /// @param count 0 以上。
    PipelineVertexInputInfo& SetAttributeCount(int count);

    /// 頂点属性情報配列の先頭アドレス。（初期値：nullptr）
    /// @details
    /// AttributeCount() 長の配列として参照されます。
    /// 配列のインデックスが VK-GLSL では location 番号、MSL では attribute 番号として扱われます。
    const VertexAttributeInfo* AttributeInfos() const
    {
        return attributeInfos_.Get();
    }

    /// AttributeInfos() の設定。
    PipelineVertexInputInfo& SetAttributeInfos(
        const VertexAttributeInfo* infos)
    {
        attributeInfos_.Reset(infos);
        return *this;
    }
    //@}

private:
    int bufferCount_ = 0;
    int attributeCount_ = 0;
    base::Pointer<const VertexBufferLayoutInfo> bufferLayoutInfos_;
    base::Pointer<const VertexAttributeInfo> attributeInfos_;
};

} // namespace ae::gfx_low
// EOF
