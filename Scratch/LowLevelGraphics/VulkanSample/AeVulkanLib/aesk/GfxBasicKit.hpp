// 文字コード：UTF-8
#pragma once

#include <ae/base/Extent2i.hpp>
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
    /// @name コンストラクタとデストラクタ
    //@{
    GfxBasicKit(::ae::base::Display* display);
    ~GfxBasicKit();
    //@}

    /// @name 基本プロパティ
    //@{
    ::ae::gfx_low::System& System() const { return *system_; }
    ::ae::gfx_low::Device& Device() const { return *device_; }
    ::ae::gfx_low::Queue& Queue() const { return device_->Queue(0); }
    ::ae::gfx_low::SwapchainHandle Swapchain() const { return swapchain_; }
    ::ae::gfx_low::DepthStencilImageView& DepthBufferView() const {
        return *depthBufferView_;
    }
    ::ae::gfx_low::ImageFormat DepthBufferFormat() const {
        return DefaultDepthBufferFormat;
    }
    int SwapchainImageCount() const { return DefaultSwapchainImageCount; }
    //@}

    /// @name 毎フレーム処理関連
    //@{
    /// 前回実行した処理の完了を保証するために待つ。
    /// @details Swapchain::AcquireNextImage() を呼ぶ前にこの関数で待つ必要がある。
    void WaitToResourceUsable();

    /// スクリーンリサイズ処理が必要なら行う。
    /// @return リサイズ処理が行われたら true を返す。
    /// @details
    /// リサイズ処理が行われたときは Queue に提出された全てのコマンドが
    /// 実行を完了した状態になっています。
    bool ScreenResizeProcessIfNeeds();

    /// 現在記録可能な汎用コマンドバッファの取得。
    ::ae::gfx_low::CommandBuffer& CurrentCommandBuffer() {
        return commandBuffers_[bufferIndex_];
    }

    /// GPU送信＆ CurrentBufferIndex() を１つ進める。
    void QueueSubmit();

    /// 現在対象となっている SwapchainImage の index 値。
    /// @return [0, SwapchainImageCount()) の範囲の値。
    int CurrentBufferIndex() const { return bufferIndex_; }
    //@}

    /// @name その他
    //@{
    /// Queue に送信した全ての処理が完了するのを待つ。
    void WaitAllDone();
    //@}

private:
    const ::ae::gfx_low::ImageFormat DefaultDepthBufferFormat =
        ::ae::gfx_low::ImageFormat::D32Sfloat;
    const int DefaultSwapchainImageCount = 3;
    //------------------------------------------------------------------------------
    void SetupSwapchainAndDepthBuffer();
    void CleanupSwapchainAndDepthBuffer();
    //------------------------------------------------------------------------------
    ::ae::base::Display& display_;
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
    ::ae::base::Extent2i currentSwapchainExtent_ = {};
};

} // namespace aesk
// EOF
