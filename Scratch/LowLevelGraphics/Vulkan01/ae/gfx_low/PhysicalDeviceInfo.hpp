// 文字コード：UTF-8
#pragma once

#include <ae/base/BitSet.hpp>
#include <ae/gfx_low/QueueType.hpp>
#include <array>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// GPU デバイス情報。
class PhysicalDeviceInfo {
public:
    /// 指定の QueueType の Queue の作成可能最大数。
    /// @details
    /// Intel Ice Lake 世代のGPUなどは Normal を1つしか作れないようです。
    /// オンボードチップでも動くプログラムを書く場合は1つのQueueで動くことをサポートしてください。
    int CreatableQueueCount(QueueType queueType) const {
        return InternalCreatableQueueCounts[int(queueType)];
    }

    // internal
    ::std::array<int, static_cast<int>(QueueType::TERM)>
        InternalCreatableQueueCounts = {};
};

}  // namespace gfx_low
}  // namespace ae
// EOF
