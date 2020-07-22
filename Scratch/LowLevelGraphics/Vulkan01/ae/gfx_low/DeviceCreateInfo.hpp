// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>

namespace ae {
namespace gfx_low {
class QueueCreateInfo;
class System;
}  // namespace gfx_low
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// Device オブジェクト作成に必要な情報。
class DeviceCreateInfo {
public:
    /// @name 属する System インスタンスのポインタ（設定必須、初期値：nullptr）
    //@{
    gfx_low::System* System() const { return system_.get(); }
    DeviceCreateInfo& SetSystem(gfx_low::System* system) {
        system_.reset(system);
        return *this;
    }
    //@}

    /// @name System が管理する physicalDeviceIndex 値。（初期値：0）
    //@{
    int PhysicalDeviceIndex() const { return physicalDeviceIndex_; }
    DeviceCreateInfo& SetPhysicalDeviceIndex(int index) {
        physicalDeviceIndex_ = index;
        return *this;
    }
    //@}

    /// @name 作成する Queue 郡の情報（最低１つ以上のQueueの指定が必須、初期値：0）
    //@{
    int QueueCreateInfoCount() const { return queueCreateInfosCount_; }
    const QueueCreateInfo* QueueCrateInfos() const {
        return queueCreateInfos_.get();
    }
    DeviceCreateInfo& SetQueueCreateInfos(
        int count, const QueueCreateInfo* infos) {
        queueCreateInfosCount_ = count;
        queueCreateInfos_.reset(infos);
        return *this;
    }
    //@}

private:
    ::ae::base::Pointer<gfx_low::System> system_;
    int physicalDeviceIndex_ = 0;
    int queueCreateInfosCount_ = 0;
    ::ae::base::Pointer<const QueueCreateInfo> queueCreateInfos_;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
