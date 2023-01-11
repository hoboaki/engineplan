// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/ResourceMemoryUsageBitSet.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// リソースが要求する ResoureceMemory の要件。
class ResourceMemoryRequirements {
public:
    /// 使用方法を示すビットセット。（初期値：全てOff）
    ResourceMemoryUsageBitSet UsageBitSet() const { return usageBitSet_; }

    /// UsageBitSet() の設定。（設定必須）
    ResourceMemoryRequirements& SetUsageBitSet(
        const ResourceMemoryUsageBitSet& usageBitSet)
    {
        usageBitSet_ = usageBitSet;
        return *this;
    }

    /// 確保するメモリサイズ。（初期値：0）
    /// @details
    /// 0 の場合はメモリ確保時に IsValid() == false な ResourceMemory
    /// を返します。
    size_t Size() const { return size_; }

    /// Size() の設定。
    ResourceMemoryRequirements& SetSize(size_t size)
    {
        size_ = size;
        return *this;
    }

    /// 確保するメモリのアラインメント。（初期値：0）
    size_t Alignment() const { return alignment_; }

    /// Alignment() の設定。
    ResourceMemoryRequirements& SetAlignment(size_t alignment)
    {
        alignment_ = alignment;
        return *this;
    }

private:
    ResourceMemoryUsageBitSet usageBitSet_;
    size_t size_ = 0;
    size_t alignment_ = 0;
};

} // namespace ae::gfx_low
// EOF
