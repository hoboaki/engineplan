// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumKeyArray.hpp>
#include <ae/base/IAllocator.hpp>
#include <ae/base/Noncopyable.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/QueueKind.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class PhysicalDeviceInfo;
class SystemCreateInfo;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

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
    ::vk::Instance& NativeObject_() { return nativeObject_; }

    ::ae::base::IAllocator& ObjectAllocator_() const
    {
        return objectAllocator_;
    }

    ::ae::base::IAllocator& TempWorkAllocator_() const
    {
        return tempWorkAllocator_;
    }

    /// QueueKind に対応する QueueFamilyIndex を格納するテーブルの型。
    /// @details
    /// 対応する QueueFamilyIndex が存在しない場合、負の値が格納されます。
    using QueueFamilyIndexTableType_ = ::ae::base::EnumKeyArray<QueueKind, int>;

    /// QueueFamilyIndex を返す。見つからない場合は負の値を返す。
    void QueueFamilyIndexTable_(
        QueueFamilyIndexTableType_* result,
        int physicalDeviceIndex) const;

    const ::vk::PhysicalDevice& PhysicalDevice_(int physicalDeviceIndex) const
    {
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
    ::vk::DynamicLoader vkLoader_;
    ::vk::Instance nativeObject_;
    int enabledExtensionCount_ = 0;
    int enabledLayerCount_ = 0;
    int physicalDeviceCount_ = 0;
    const char* extensionNames_[ExtensionCountMax] = {};
    const char* enabledLayers_[LayerCountMax] = {};
    std::array<::vk::PhysicalDevice, PhysicalDeviceCountMax> physicalDevices_;
};

} // namespace ae::gfx_low
// EOF
