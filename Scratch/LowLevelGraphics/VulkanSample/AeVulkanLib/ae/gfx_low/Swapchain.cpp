// 文字コード：UTF-8
#include <ae/gfx_low/Swapchain.hpp>

// includes
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/EventCreateInfo.hpp>
#include <ae/gfx_low/ImageResourceCreateInfo.hpp>
#include <ae/gfx_low/RenderTargetImageViewCreateInfo.hpp>
#include <ae/gfx_low/SwapchainMaster.hpp>
#include <ae/gfx_low/System.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
Swapchain::~Swapchain() {
    AE_BASE_ASSERT(!IsInitialized_());
}

//------------------------------------------------------------------------------
void Swapchain::AcquireNextImage() {
    AE_BASE_ASSERT(IsInitialized_());
    auto& device = swapchainMaster_->Device();
    {
        currentFrameIndex_ =
            (currentFrameIndex_ + 1) % frameProperties_.Count();
        currentFrameIndex_ = base::Math::Clamp(
            currentFrameIndex_,
            0,
            frameProperties_.Count() - 1);
        auto currentBufferIdxUint = uint32_t();
        auto result = device.NativeObject_().acquireNextImageKHR(
            swapchain_,
            UINT64_MAX,
            frameProperties_[currentFrameIndex_].AcquireEvent->NativeObject_(),
            ::vk::Fence(),
            &currentBufferIdxUint);
        AE_BASE_ASSERT(result == vk::Result::eSuccess);
        AE_BASE_ASSERT_EQUALS(currentFrameIndex_, int(currentBufferIdxUint));
    }
}

//------------------------------------------------------------------------------
void Swapchain::Initialize_(
    gfx_low::SwapchainMaster* swapchainMaster,
    const ::vk::SwapchainKHR& swapchain,
    uint32_t uniqueId,
    int minImageCount,
    ::vk::Format imageFormat) {
    AE_BASE_ASSERT(!IsInitialized_());
    swapchainMaster_.Reset(swapchainMaster);
    swapchain_ = swapchain;
    renderTargetSpecInfo_ =
        gfx_low::RenderTargetSpecInfo().SetNativeFormat_(imageFormat);
    {
        auto& device = swapchainMaster_->Device();

        auto swapchainImageCount = uint32_t();
        {
            const auto result = device.NativeObject_().getSwapchainImagesKHR(
                swapchain_,
                &swapchainImageCount,
                static_cast<::vk::Image*>(nullptr));
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
            AE_BASE_ASSERT_LESS(0, minImageCount);
        }

        frameProperties_.Resize(
            int(swapchainImageCount),
            &swapchainMaster_->Device().System().ObjectAllocator_());

        base::RuntimeArray<::vk::Image> swapchainImages(
            frameProperties_.Count(),
            &device.System().TempWorkAllocator_());
        {
            const auto result = device.NativeObject_().getSwapchainImagesKHR(
                swapchain_,
                &swapchainImageCount,
                swapchainImages.Head());
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
        }

        for (int i = 0; i < frameProperties_.Count(); ++i) {
            auto& target = frameProperties_[i];
            target.AcquireEvent.Init(EventCreateInfo().SetDevice(&device));
            target.ReadyToPresentEvent.Init(
                EventCreateInfo().SetDevice(&device));
            target.ImageResource.Init(
                ImageResourceCreateInfo()
                    .SetDevice(&device)
                    .SetNativeObjectPtr_(&swapchainImages[i])
                    .SetNativeFormat_(imageFormat));
            target.RenderTargetImageView.Init(
                RenderTargetImageViewCreateInfo()
                    .SetDevice(&device)
                    .SetResource(target.ImageResource.Ptr())
                    .SetRawFormat_(imageFormat));
        }
    }
    uniqueId_ = uniqueId;
    currentFrameIndex_ = -1;
    AE_BASE_ASSERT(IsInitialized_());
}

//------------------------------------------------------------------------------
void Swapchain::Finalize_() {
    if (!IsInitialized_()) {
        return;
    }
    uniqueId_ = InvalidUniqueId_;
    {
        for (int i = frameProperties_.Count() - 1; 0 <= i; --i) {
            auto& target = frameProperties_[i];
            target.RenderTargetImageView.Reset();
            target.ImageResource.Reset();
            target.ReadyToPresentEvent.Reset();
            target.AcquireEvent.Reset();
        }
    }
    swapchain_ = ::vk::SwapchainKHR();
    swapchainMaster_.Reset();
    AE_BASE_ASSERT(!IsInitialized_());
}

} // namespace gfx_low
} // namespace ae
// EOF
