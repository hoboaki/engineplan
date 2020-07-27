// 文字コード：UTF-8
#pragma once

#include <ae/base/RuntimeAutoArray.hpp>
#include <ae/gfx_low/SdkHeader.hpp>
#include <list>

namespace ae {
namespace gfx_low {
class DeviceCreateInfo;
class RenderPassBeginInfo;
class Queue;
class System;
}
}  // namespace ae

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
    int QueueCount() const { return queues_.count(); }

    /// 指定番目の Queue の取得。
    /// @param queueIndex [0, QueueCount())
    gfx_low::Queue& Queue(int queueIndex) const;
    //@}

    /// @name 内部処理用API
    //@{
    static const int InternalSupportedAttachmentCountMax = 8;

    ::vk::Device& InternalInstance() { return device_; }

    /// beginInfo に必要な RenderPass オブジェクトを返す。
    ::vk::RenderPass InternalAcquireRenderPass(const RenderPassBeginInfo& beginInfo);
    
    /// beginInfo に必要な FrameBuffer オブジェクトを返す。
    ::vk::Framebuffer InternalAcquireFramebuffer(const RenderPassBeginInfo& beginInfo);
    //@}

private:
    gfx_low::System& system_;
    ::vk::Device device_;
    int physicalDeviceIndex_;
    base::RuntimeAutoArray<gfx_low::Queue> queues_;
    std::list<::vk::RenderPass> acquiredRenderPassList_;
    std::list<::vk::Framebuffer> acquiredFramebufferList_;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
