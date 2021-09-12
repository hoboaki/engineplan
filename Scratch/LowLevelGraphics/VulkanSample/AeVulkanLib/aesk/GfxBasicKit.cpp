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
: display_(::ae::base::PtrToRef(display))
, commandBuffers_(DefaultSwapchainImageCount)
, fences_(DefaultSwapchainImageCount) {
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

    // Swapchain と DepthBuffer を作成
    SetupSwapchainAndDepthBuffer();
}

//------------------------------------------------------------------------------
GfxBasicKit::~GfxBasicKit() {}

//------------------------------------------------------------------------------
void GfxBasicKit::WaitToResourceUsable() {
    // 処理完了待ち
    fences_[bufferIndex_].Wait();
}

//------------------------------------------------------------------------------
bool GfxBasicKit::ScreenResizeProcessIfNeeds() {
    if (currentSwapchainExtent_ == display_.MainScreen().Extent()) {
        return false;
    }
    WaitAllDone();
    CleanupSwapchainAndDepthBuffer();
    SetupSwapchainAndDepthBuffer();
    return true;
}

//------------------------------------------------------------------------------
void GfxBasicKit::QueueSubmit() {
    // GPU送信
    Queue().Submit(&fences_[bufferIndex_]);

    // バッファを進める
    bufferIndex_ = (bufferIndex_ + 1) % SwapchainImageCount();
}

//------------------------------------------------------------------------------
void GfxBasicKit::WaitAllDone() {
    for (auto& fence : fences_) {
        fence.Wait();
    }
}

//------------------------------------------------------------------------------
void GfxBasicKit::SetupSwapchainAndDepthBuffer() {
    // Swapchain の作成
    {
        auto& createInfo = ::ae::gfx_low::SwapchainMasterCreateInfo()
                               .SetDevice(device_.get())
                               .SetScreen(&display_.MainScreen())
                               .SetSwapchainCountMax(1);
        swapchainMaster_.reset(new ::ae::gfx_low::SwapchainMaster(createInfo));
    }
    swapchain_ = swapchainMaster_->CreateSwapchain(
        ae::gfx_low::SwapchainCreateInfo().SetImageCount(
            DefaultSwapchainImageCount));
    currentSwapchainExtent_ = display_.MainScreen().Extent();

    // DepthBuffer 作成
    {
        const auto specInfo =
            ::ae::gfx_low::ImageResourceSpecInfo()
                .SetKind(::ae::gfx_low::ImageResourceKind::Image2d)
                .SetFormat(DefaultDepthBufferFormat)
                .SetTiling(::ae::gfx_low::ImageResourceTiling::Optimal)
                .SetExtent(::ae::base::Extent2i(
                    display_.MainScreen().Width(),
                    display_.MainScreen().Height()))
                .SetUsageBitSet(::ae::gfx_low::ImageResourceUsageBitSet().Set(
                    ::ae::gfx_low::ImageResourceUsage::DepthStencilImage,
                    true));
        depthBufferMemory_.Reset(
            device_.get(),
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
                .SetFormat(DefaultDepthBufferFormat)));
    }
}

//------------------------------------------------------------------------------
void GfxBasicKit::CleanupSwapchainAndDepthBuffer() {
    depthBufferView_.reset();
    depthBufferImage_.reset();
    depthBufferMemory_.Reset();
    swapchainMaster_->DestroySwapchain(swapchain_);
    swapchain_ = ::ae::gfx_low::SwapchainHandle();
    currentSwapchainExtent_ = ::ae::base::Extent2i();
}

} // namespace aesk
// EOF
