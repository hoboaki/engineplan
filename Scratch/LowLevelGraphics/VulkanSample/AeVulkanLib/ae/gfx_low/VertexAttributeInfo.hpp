// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/VertexFormat.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// 頂点属性に関する情報。
/// @todo HLSL 用の文字列ラベル対応。
class VertexAttributeInfo {
public:
    /// @name プロパティ
    //@{
    /// データ形式。（初期値：Invalid）
    VertexFormat Format() const { return format_; }

    /// Format() の設定。（設定必須）
    VertexAttributeInfo& SetFormat(VertexFormat format);

    /// 参照するデータが可能されている頂点バッファスロット番号。（初期値：0）
    int Slot() const { return slot_; }

    /// Slot() の設定。
    /// @param slot 0以上。
    VertexAttributeInfo& SetSlot(int slot);

    /// 頂点データブロックの先頭メモリアドレスから参照するデータまでのオフセット位置。（初期値：0）
    int Offset() const { return offset_; }

    /// Offset() の設定。
    /// @param offset 0以上。
    VertexAttributeInfo& SetOffset(int offset);
    //@}

private:
    int slot_ = 0;
    int offset_ = 0;
    VertexFormat format_ = VertexFormat::Invalid;
};

} // namespace ae::gfx_low
// EOF
