// 文字コード：UTF-8
#pragma once

#include <ae/base/RuntimeAutoArray.hpp>
#include <ae/gfx_low/SdkHeader.hpp>
#include <list>

namespace ae::gfx_low {
class DeviceCreateInfo;
class BufferResourceSpecInfo;
class ImageResourceSpecInfo;
class ImageSubresourceDataInfo;
class ImageSubresourceLocation;
class Queue;
class ResourceMemory;
class ResourceMemoryAllocInfo;
class ResourceMemoryRegion;
class ResourceMemoryRequirements;
class ShaderModuleResourceSpecInfo;
class System;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

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
    bool IsDeviceLocalMemoryShared() const
    {
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
        const ImageResourceSpecInfo& specInfo) const;

    /// 指定のバッファリソースのリソースメモリ要件を計算して返す。
    ResourceMemoryRequirements CalcResourceMemoryRequirements(
        const BufferResourceSpecInfo& specInfo) const;

    /// 指定のシェーダーモジュールリソースのリソースメモリ要件を計算して返す。
    ResourceMemoryRequirements CalcResourceMemoryRequirements(
        const ShaderModuleResourceSpecInfo& specInfo) const;

    /// 指定のリソースメモリの指定範囲に対して CPU による読み書きを開始する。
    /// @return region で指定した範囲の先頭アドレス。
    /// @details
    /// 戻り値のアドレスに対して CPU 側で読み書きを行ってください。
    /// Map 中の ResourceMemory オブジェクトに対して Map することはできません。
    uint8_t* MapResourceMemory(
        const ResourceMemory& resourceMemory,
        const ResourceMemoryRegion& region);

    /// 指定のリソースメモリに対する CPU による読み書きを終了する。
    void UnmapResourceMemory(const ResourceMemory& resourceMemory);
    //@}

    /// @name イメージに関するユーティリティ
    //@{
    /// 指定のイメージサブリソースのデータ情報を計算して返す。
    ImageSubresourceDataInfo CalcImageSubresourceDataInfo(
        const ImageResourceSpecInfo& specInfo,
        const ImageSubresourceLocation& location) const;
    //@}

    /// @name 内部処理用API
    //@{
    /// DX12 とあわせて 8 を最大数としている。
    static constexpr int SupportedRenderTargetCountMax_ = 8;
    static constexpr int SupportedAttachmentCountMax_ =
        SupportedRenderTargetCountMax_ + 1;

    ::vk::Device& NativeObject_() { return nativeObject_; }
    //@}

private:
    gfx_low::System& system_;
    ::vk::Device nativeObject_;
    const int physicalDeviceIndex_;
    base::RuntimeAutoArray<gfx_low::Queue> queues_;
    ::vk::PhysicalDeviceMemoryProperties memoryProps_ = {};
    int deviceLocalOptimalImageMemoryTypeIndex_ = -1;
    bool isDeviceLocalMemoryShared_ = bool();
};

} // namespace ae::gfx_low
// EOF
