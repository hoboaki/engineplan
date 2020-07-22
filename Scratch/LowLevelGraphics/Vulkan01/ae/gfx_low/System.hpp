// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumKeyArray.hpp>
#include <ae/base/IAllocator.hpp>
#include <ae/base/Noncopyable.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/QueueType.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class PhysicalDeviceInfo;
class SystemCreateInfo;
}  // namespace gfx_low
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// 低レベルグラフィックスライブラリシステムを扱うクラス。
/// @details
/// 低レベルグラフィックスライブラリの初期化と後始末を行います。
/// 低レベルグラフィックスライブラリを使いはじめる際に最初に作るべきオブジェクトです。
/// ２つ以上作ることはできません。
/// 一般的な処理フローにおいて、System を作成したあとは Device を作成します。
class System : base::Noncopyable<System> {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    System(const SystemCreateInfo& createInfo);
    ~System();
    //@}

    /// @name 情報取得
    //@{
    /// 認識している物理デバイス数。
    int PhysicalDeviceCount() const { return physicalDeviceCount_; }

    /// 指定の物理デバイスの情報を取得。
    /// @param physicalDeviceIndex [0, PhysicalDeviceCount())
    PhysicalDeviceInfo PhysicalDeviceInfo(int physicalDeviceIndex) const;

    /// 全物理デバイスの情報をコンソールにダンプする。
    void DumpAllPhysicalDeviceInfo() const;
    //@}

    /// @name 内部処理用
    //@{
    ::vk::Instance& InternalInstance() { return instance_; }

    ::ae::base::IAllocator& InternalObjectAllocator() const {
        return objectAllocator_;
    }

    ::ae::base::IAllocator& InternalTempWorkAllocator() const {
        return tempWorkAllocator_;
    }

    /// QueueType に対応する QueueFamilyIndex を格納するテーブルの型。
    using InternalQueueFamilyIndexTableType = ::ae::base::EnumKeyArray<QueueType, int>;

    /// を返す。見つからない場合は負の値を返す。
    void InternalQueueFamilyIndexTable(
        InternalQueueFamilyIndexTableType* result,
        int physicalDeviceIndex) const;

    const ::vk::PhysicalDevice& InternalPhysicalDevice(
        int physicalDeviceIndex) const {
        return physicalDevices_[physicalDeviceIndex];
    }
    //@}

private:
    static const int PhysicalDeviceCountMax = 16;
    static const int ExtensionCountMax = 64;
    static const int LayerCountMax = 64;
    static const int QueueFamilyCountMax = 8;

    static bool IsInstanceCreated;

    ::ae::base::IAllocator& objectAllocator_;
    ::ae::base::IAllocator& tempWorkAllocator_;
    ::vk::Instance instance_;
    int enabledExtensionCount_ = 0;
    int enabledLayerCount_ = 0;
    int physicalDeviceCount_ = 0;
    const char* extensionNames_[ExtensionCountMax] = {};
    const char* enabledLayers_[LayerCountMax] = {};
    std::array<::vk::PhysicalDevice, PhysicalDeviceCountMax> physicalDevices_;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
