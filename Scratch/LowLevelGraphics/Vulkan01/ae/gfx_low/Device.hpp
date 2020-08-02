// 文字コード：UTF-8
#pragma once

#include <ae/base/RuntimeAutoArray.hpp>
#include <ae/gfx_low/SdkHeader.hpp>
#include <list>

namespace ae {
namespace gfx_low {
class DeviceCreateInfo;
class ImageResourceSpecInfo;
class Queue;
class ResourceMemory;
class ResourceMemoryAllocInfo;
class ResourceMemoryRequirements;
class System;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// グラフィックスデバイスを扱うクラス。
/// @details
/// １つの Device オブジェクトで１つのGPUを扱います。
/// １つのアプリケーションで複数のGPUを扱う場合は複数のDeviceを作ります。
/// Device は作成時に Queue も内部で作成するため、
/// コンストラクタで渡す DeviceCreateInfo を通じて Queue の作成情報も渡します。
class Device {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    Device(const DeviceCreateInfo& createInfo);
    ~Device();
    //@}

    /// @name プロパティ
    //@{
    ///  コンストラクタで渡した System オブジェクト。
    gfx_low::System& System() const { return system_; }

    /// コンストラクタで渡した PhysicalDeviceIndex。
    int PhysicalDeviceIndex() const { return physicalDeviceIndex_; }

    /// 保持している Queue の総数。
    int QueueCount() const { return queues_.Count(); }

    /// 指定番目の Queue の取得。
    /// @param queueIndex [0, QueueCount())
    gfx_low::Queue& Queue(int queueIndex) const;

    /// ResourceMemoryKind::DeviceLocal タイプが共有メモリ上に配置されるか。
    bool IsDeviceLocalMemoryShared() const {
        return isDeviceLocalMemoryShared_;
    }
    //@}

    /// @name リソースメモリ
    //@{
    /// リソースメモリを確保する。
    /// @details メモリ確保に失敗したら ASSERTION FAILED し、
    /// FINAL 版では IsValid() == false なオブジェクトを返します。
    ResourceMemory AllocResourceMemory(
        const ResourceMemoryAllocInfo& allocInfo);

    /// リソースメモリの確保を試み、もし失敗したら IsValid() == false
    /// なオブジェクトを返す。
    ResourceMemory TryToAllocResourceMemory(
        const ResourceMemoryAllocInfo& allocInfo);

    /// リソースメモリを破棄する。
    /// @param memory IsValid() == true なオブジェクト。
    void FreeResourceMemory(const ResourceMemory& memory);

    /// 指定のイメージリソースのリソースメモリ要件を計算して返す。
    ResourceMemoryRequirements CalcResourceMemoryRequirements(
        const ImageResourceSpecInfo& specInfo);
    //@}

    /// @name 内部処理用API
    //@{
    static const int SupportedAttachmentCountMax_ = 8;

    ::vk::Device& Instance_() { return device_; }
    //@}

private:
    gfx_low::System& system_;
    ::vk::Device device_;
    const int physicalDeviceIndex_;
    base::RuntimeAutoArray<gfx_low::Queue> queues_;
    ::vk::PhysicalDeviceMemoryProperties memoryProps_ = {};
    bool isDeviceLocalMemoryShared_ = bool();
};

} // namespace gfx_low
} // namespace ae
// EOF
