// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/ResourceMemoryKind.hpp>
#include <ae/gfx_low/ResourceMemoryUsageBitSet.hpp>

namespace ae::gfx_low {
class ResourceMemoryRequirements;
}

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ResourceMemory 確保に必要な情報。
class ResourceMemoryAllocInfo {
public:
    /// メモリの種類。（初期値：Invalid）
    ResourceMemoryKind Kind() const { return kind_; }

    /// Kind() の設定。（設定必須）
    ResourceMemoryAllocInfo& SetKind(ResourceMemoryKind kind);

    /// 使用方法を示すビットセット。（初期値：全てOff）
    ResourceMemoryUsageBitSet UsageBitSet() const { return usageBitSet_; }

    /// UsageBitSet() の設定。（設定必須）
    ResourceMemoryAllocInfo& SetUsageBitSet(
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
    ResourceMemoryAllocInfo& SetSize(size_t size)
    {
        size_ = size;
        return *this;
    }

    /// 確保するメモリのアラインメント。（初期値：0）
    size_t Alignment() const { return alignment_; }

    /// Alignment() の設定。
    ResourceMemoryAllocInfo& SetAlignment(size_t alignment)
    {
        alignment_ = alignment;
        return *this;
    }

    /// ResourceMemoryRequirements の要件を各パラメータに設定する。
    ResourceMemoryAllocInfo& SetParams(
        const ResourceMemoryRequirements& requirement);

private:
    ResourceMemoryKind kind_ = ResourceMemoryKind::Invalid;
    ResourceMemoryUsageBitSet usageBitSet_;
    size_t size_ = 0;
    size_t alignment_ = 0;
};

} // namespace ae::gfx_low
// EOF
