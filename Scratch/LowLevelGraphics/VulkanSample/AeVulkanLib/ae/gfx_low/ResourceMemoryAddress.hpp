// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/ResourceMemory.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ResourceMemory のアドレスを扱うクラス。
/// @details
/// ResourceMemory オブジェクトとオフセット値を扱います。
class ResourceMemoryAddress {
public:
    /// @name コンストラクタ
    //@{
    /// 指定の ResourceMemory とオフセットを表すオブジェクトを作成。
    ResourceMemoryAddress(
        const ResourceMemory& memory = ResourceMemory(),
        size_t offset = 0)
    : memory_(memory)
    , offset_(offset)
    {
    }
    //@}

    /// @name プロパティ
    //@{
    /// 先頭アドレスを表す ResourceMemory オブジェクト。
    ResourceMemory Memory() const { return memory_; }

    /// バイトオフセット値。
    size_t Offset() const { return offset_; }
    //@}

private:
    ResourceMemory memory_;
    size_t offset_ = 0;
};

} // namespace ae::gfx_low
// EOF
