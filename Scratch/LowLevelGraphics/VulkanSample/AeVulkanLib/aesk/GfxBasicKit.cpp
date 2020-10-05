// 文字コード：UTF-8
#include <aesk/GfxBasicKit.hpp>

// includes
#include <ae/base/Display.hpp>
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/CommandBufferCreateInfo.hpp>
#include <ae/gfx_low/DepthStencilImageViewCreateInfo.hpp>
#include <ae/gfx_low/DeviceCreateInfo.hpp>
#include <ae/gfx_low/FenceCreateInfo.hpp>
#include <ae/gfx_low/ImageResourceCreateInfo.hpp>
#include <ae/gfx_low/Queue.hpp>
#include <ae/gfx_low/QueueCreateInfo.hpp>
#include <ae/gfx_low/ResourceMemoryAllocInfo.hpp>
#include <ae/gfx_low/ResourceMemoryRequirements.hpp>
#include <ae/gfx_low/SwapchainCreateInfo.hpp>
#include <ae/gfx_low/SwapchainMasterCreateInfo.hpp>
#include <ae/gfx_low/SystemCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace aesk {

//------------------------------------------------------------------------------
GfxBasicKit::GfxBasicKit(::ae::base::Display* display)
: commandBuffers_(SwapchainImageCount)
, fences_(SwapchainImageCount) {
    // メモ
    auto& disp = ::ae::base::PtrToRef(display);

    // グラフィックスシステムインスタンス作成
    system_.reset(new ::ae::gfx_low::System(
        ::ae::gfx_low::SystemCreateInfo().SetDebugLevel(
            ::ae::gfx_low::SystemDebugLevel::Normal)));

    // Device & Queue 作成
    {
        // Queue の作成情報を用意
        const int queueCount = 1;
        ::ae::gfx_low::QueueCreateInfo queueCreateInfos[queueCount];
        queueCreateInfos[0] =
            ::ae::gfx_low::QueueCreateInfo()
                .SetKind(::ae::gfx_low::QueueKind::Normal)
                .SetPriority(::ae::gfx_low::QueuePriority::Normal)
                .SetOperationCountMax(32);

        // Device の作成
        device_.reset(new ::ae::gfx_low::Device(
            ::ae::gfx_low::DeviceCreateInfo()
                .SetSystem(system_.get())
                .SetQueueCreateInfos(queueCount, queueCreateInfos)));
    }

    // Swapchain の作成
    {
        auto& createInfo = ::ae::gfx_low::SwapchainMasterCreateInfo()
                               .SetDevice(device_.get())
                               .SetScreen(&disp.MainScreen())
                               .SetSwapchainCountMax(1);
        swapchainMaster_.reset(new ::ae::gfx_low::SwapchainMaster(createInfo));
    }
    swapchain_ = swapchainMaster_->CreateSwapchain(
        ae::gfx_low::SwapchainCreateInfo().SetImageCount(SwapchainImageCount));

    // DepthBuffer 作成
    {
        const auto specInfo =
            ::ae::gfx_low::ImageResourceSpecInfo()
                .SetKind(::ae::gfx_low::ImageResourceKind::Image2d)
                .SetFormat(DepthBufferFormat)
                .SetTiling(::ae::gfx_low::ImageResourceTiling::Optimal)
                .SetExtent(::ae::base::Extent2i(
                    disp.MainScreen().Width(), disp.MainScreen().Height()))
                .SetUsageBitSet(::ae::gfx_low::ImageResourceUsageBitSet().Set(
                    ::ae::gfx_low::ImageResourceUsage::DepthStencilImage,
                    true));
        depthBufferMemory_.Reset(device_.get(),
            ::ae::gfx_low::ResourceMemoryAllocInfo()
                .SetKind(::ae::gfx_low::ResourceMemoryKind::DeviceLocal)
                .SetParams(device_->CalcResourceMemoryRequirements(specInfo)));
        depthBufferImage_.reset(new ::ae::gfx_low::ImageResource(
            ::ae::gfx_low::ImageResourceCreateInfo()
                .SetDevice(device_.get())
                .SetSpecInfo(specInfo)
                .SetDataAddress(*depthBufferMemory_)));
        depthBufferView_.reset(new ::ae::gfx_low::DepthStencilImageView(
            ::ae::gfx_low::DepthStencilImageViewCreateInfo()
                .SetDevice(device_.get())
                .SetResource(depthBufferImage_.get())
                .SetFormat(DepthBufferFormat)));
    }

    // CommandBuffer の作成
    for (int i = 0; i < commandBuffers_.CountMax(); ++i) {
        commandBuffers_.Add(::ae::gfx_low::CommandBufferCreateInfo()
                                .SetDevice(device_.get())
                                .SetQueue(&Queue())
                                .SetRenderPassCountMax(16));
    }

    // Fence の作成
    for (int i = 0; i < fences_.CountMax(); ++i) {
        fences_.Add(::ae::gfx_low::FenceCreateInfo().SetDevice(device_.get()));
    }
}

//------------------------------------------------------------------------------
GfxBasicKit::~GfxBasicKit() {}

//------------------------------------------------------------------------------
void GfxBasicKit::WaitToResourceUsable(const bool useSwapchain) {
    // 処理完了待ち
    fences_[bufferIndex_].Wait();
    
    /// 次フレーム用バッファ確保要求。
    if (useSwapchain) {
        swapchain_->AcquireNextImage();
    }
}

//------------------------------------------------------------------------------
void GfxBasicKit::QueuePushSwapchainWait() {
    Queue().PushSwapchainWait(&swapchain_.Ref());
}

//------------------------------------------------------------------------------
void GfxBasicKit::QueuePushSwapchainPresent() {
    Queue().PushSwapchainPresent(&swapchain_.Ref());
}

//------------------------------------------------------------------------------
void GfxBasicKit::QueueSubmit() {
    // GPU送信
    Queue().Submit(&fences_[bufferIndex_]);

    // バッファを進める
    bufferIndex_ = (bufferIndex_ + 1) % SwapchainImageCount;
}

} // namespace aesk
// EOF
