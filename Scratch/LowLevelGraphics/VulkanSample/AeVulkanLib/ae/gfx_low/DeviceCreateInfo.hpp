// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>

namespace ae::gfx_low {
class QueueCreateInfo;
class System;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// Device オブジェクト作成に必要な情報。
class DeviceCreateInfo {
public:
    /// @name プロパティ
    //@{

    /// 属する System インスタンスのポインタ。（初期値：nullptr）
    gfx_low::System* System() const { return system_.Get(); }

    /// System() の設定。（設定必須）
    DeviceCreateInfo& SetSystem(gfx_low::System* system)
    {
        system_.Reset(system);
        return *this;
    }

    /// System が管理する physicalDeviceIndex 値。（初期値：0）
    int PhysicalDeviceIndex() const { return physicalDeviceIndex_; }

    /// PhysicalDeviceIndex() の設定。
    DeviceCreateInfo& SetPhysicalDeviceIndex(int index)
    {
        physicalDeviceIndex_ = index;
        return *this;
    }

    /// 作成する Queue の数。（初期値：0）
    int QueueCreateInfoCount() const { return queueCreateInfosCount_; }

    /// 作成する Queue 郡の情報。（初期値：nullptr）
    const QueueCreateInfo* QueueCrateInfos() const
    {
        return queueCreateInfos_.Get();
    }

    /// 作成する Queue の数と情報の設定。（最低１つ以上のQueueの指定が必須）
    /// @param infos count 長の情報配列。
    DeviceCreateInfo& SetQueueCreateInfos(
        int count,
        const QueueCreateInfo* infos)
    {
        queueCreateInfosCount_ = count;
        queueCreateInfos_.Reset(infos);
        return *this;
    }
    //@}

private:
    ::ae::base::Pointer<gfx_low::System> system_;
    int physicalDeviceIndex_ = 0;
    int queueCreateInfosCount_ = 0;
    ::ae::base::Pointer<const QueueCreateInfo> queueCreateInfos_;
};

} // namespace ae::gfx_low
// EOF
