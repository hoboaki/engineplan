// 文字コード：UTF-8
#pragma once

#include <ae/base/Extent3i.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ディスパッチコールに必要な情報。
class DispatchCallInfo {
public:
    /// @name プロパティ
    //@{
    /// 1スレッドグループあたりのスレッド数。（初期値：1, 1, 1）
    base::Extent3i ThreadsPerThreadGroup() const
    {
        return threadsPerThreadGroup_;
    }

    /// ThreadsPerThreadGroup() の設定。
    /// @param threads 各要素1以上。
    DispatchCallInfo& SetThreadsPerThreadGroup(const base::Extent3i& threads);

    /// 総スレッドグループ数。（初期値：1, 1, 1）
    base::Extent3i ThreadGroups() const { return threadGroups_; }

    /// ThreadGroups() の設定。
    /// @param threadGroups 各要素1以上。
    DispatchCallInfo& SetThreadGroups(const base::Extent3i& threadGroups);
    //@}

private:
    base::Extent3i threadsPerThreadGroup_;
    base::Extent3i threadGroups_;
};

} // namespace ae::gfx_low
// EOF
