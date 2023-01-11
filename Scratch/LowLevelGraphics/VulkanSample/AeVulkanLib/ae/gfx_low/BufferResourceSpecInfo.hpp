// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/BufferResourceUsageBitSet.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// BufferResource のデータ構造仕様に関する情報。
class BufferResourceSpecInfo {
public:
    /// @name プロパティ
    //@{
    /// バッファのサイズ。（初期値：0）
    size_t Size() const { return size_; }

    /// Size() の設定。
    /// @param size 0以上。
    BufferResourceSpecInfo& SetSize(size_t size)
    {
        size_ = size;
        return *this;
    }

    /// 使用方法を示すビットセット。（初期値：全てOff）
    BufferResourceUsageBitSet UsageBitSet() const { return usageBitSet_; }

    /// UsageBitSet() の設定。（設定必須）
    BufferResourceSpecInfo& SetUsageBitSet(
        const BufferResourceUsageBitSet& usageBitSet)
    {
        usageBitSet_ = usageBitSet;
        return *this;
    }
    //@}

private:
    size_t size_ = 0;
    BufferResourceUsageBitSet usageBitSet_;
};

} // namespace ae::gfx_low
// EOF
