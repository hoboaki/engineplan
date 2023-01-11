// 文字コード：UTF-8
#pragma once

#include <cstddef>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// リソースメモリの範囲を示すクラス。
class ResourceMemoryRegion {
public:
    /// 参照するデータアドレスのリソースメモリ先頭からのオフセット値。（初期値：0）
    size_t Offset() const { return offset_; }

    /// Offset() の設定。
    /// @param offset 参照する ResourceMemory のデータサイズ以下となる値。
    ResourceMemoryRegion& SetOffset(size_t offset)
    {
        offset_ = offset;
        return *this;
    }

    /// Offset() からの参照範囲サイズ。 （初期値：0）
    size_t Size() const { return size_; }

    /// Size() の設定
    /// @param size Offset() + size が参照する ResourceMemory のデータサイズ以下となる値。
    ResourceMemoryRegion& SetSize(size_t size)
    {
        size_ = size;
        return *this;
        ;
    }

private:
    size_t size_ = 0;
    size_t offset_ = 0;
};

} // namespace ae::gfx_low
// EOF
