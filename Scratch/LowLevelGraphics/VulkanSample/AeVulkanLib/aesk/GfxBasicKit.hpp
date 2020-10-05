// 文字コード：UTF-8
#pragma once

#include <ae/base/RuntimeAutoArray.hpp>
#include <ae/gfx_low/CommandBuffer.hpp>
#include <ae/gfx_low/DepthStencilImageView.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/Fence.hpp>
#include <ae/gfx_low/ImageResource.hpp>
#include <ae/gfx_low/UniqueResourceMemory.hpp>
#include <ae/gfx_low/SwapchainMaster.hpp>
#include <ae/gfx_low/System.hpp>

namespace ae {
namespace base {
class Display;
}
} // namespace ae

//------------------------------------------------------------------------------
namespace aesk {

/// グラフィックスサンプルで使うオブジェクト郡をまとめた基本キット。
class GfxBasicKit {
public:
    /// @name 公開定数
    //@{
    static const ::ae::gfx_low::ImageFormat DepthBufferFormat =
        ::ae::gfx_low::ImageFormat::D32Sfloat;
    static const int SwapchainImageCount = 3;
    //@}

    /// @name コンストラクタとデストラクタ
    //@{
    GfxBasicKit(::ae::base::Display* display);
    ~GfxBasicKit();
    //@}

    /// @name 基本プロパティ
    //@{
    ::ae::gfx_low::System& System() { return *system_; }
    ::ae::gfx_low::Device& Device() { return *device_; }
    ::ae::gfx_low::Queue& Queue() { return device_->Queue(0); }
    ::ae::gfx_low::DepthStencilImageView& DepthBufferView() {
        return *depthBufferView_;
    }
    //@}

    /// @name 毎フレーム処理関連
    //@{
    /// 前回実行した処理の完了を保証するために待つ。
    void WaitToResourceUsable(bool useSwapchain = true);
    /// 現在記録可能な汎用コマンドバッファの取得。
    ::ae::gfx_low::CommandBuffer& CurrentCommandBuffer() {
        return commandBuffers_[bufferIndex_];
    }
    /// Swapchain バッファ確保同期。
    void QueuePushSwapchainWait();
    /// Swapchain 提出。
    void QueuePushSwapchainPresent();
    /// GPU送信。
    void QueueSubmit();
    //@}

private:
    ::std::unique_ptr<::ae::gfx_low::System> system_;
    ::std::unique_ptr<::ae::gfx_low::Device> device_;
    ::std::unique_ptr<::ae::gfx_low::SwapchainMaster> swapchainMaster_;
    ::ae::gfx_low::SwapchainHandle swapchain_;
    ::ae::gfx_low::UniqueResourceMemory depthBufferMemory_;
    ::std::unique_ptr<::ae::gfx_low::ImageResource> depthBufferImage_;
    ::std::unique_ptr<::ae::gfx_low::DepthStencilImageView> depthBufferView_;
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::CommandBuffer> commandBuffers_;
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::Fence> fences_;
    int bufferIndex_ = 0;
};

} // namespace aesk
// EOF
