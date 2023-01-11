// 文字コード：UTF-8
#pragma once

#include <ae/base/BitSet.hpp>
#include <ae/gfx_low/QueueKind.hpp>
#include <array>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// GPU デバイス情報。
class PhysicalDeviceInfo {
public:
    /// 指定の QueueKind の Queue の作成可能最大数。
    /// @details
    /// Intel Ice Lake 世代のGPUなどは Normal を1つしか作れないようです。
    /// オンボードチップでも動くプログラムを書く場合は1つのQueueで動くことをサポートしてください。
    int CreatableQueueCount(QueueKind queueKind) const
    {
        return CreatableQueueCounts_[int(queueKind)];
    }

    // internal
    ::std::array<int, static_cast<int>(QueueKind::TERM)>
        CreatableQueueCounts_ = {};
};

} // namespace ae::gfx_low
// EOF
