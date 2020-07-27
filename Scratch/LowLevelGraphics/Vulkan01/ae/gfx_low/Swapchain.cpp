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
    AE_BASE_ASSERT(!InternalIsInitialized());
}

//------------------------------------------------------------------------------
void Swapchain::AcquireNextImage() {
    AE_BASE_ASSERT(InternalIsInitialized());
    auto& device = swapchainMaster_->Device();
    {
        currentFrameIndex_ =
            (currentFrameIndex_ + 1) % frameProperties_.count();
        currentFrameIndex_ = base::Math::Clamp(
            currentFrameIndex_, 0, frameProperties_.count() - 1);
        auto currentBufferIdxUint = uint32_t();
        auto result = device.InternalInstance().acquireNextImageKHR(swapchain_,
            UINT64_MAX,
            frameProperties_[currentFrameIndex_]
                .AcquireEvent->InternalInstance(),
            ::vk::Fence(), &currentBufferIdxUint);
        AE_BASE_ASSERT(result == vk::Result::eSuccess);
        AE_BASE_ASSERT_EQUALS(currentFrameIndex_, int(currentBufferIdxUint));
    }
}

//------------------------------------------------------------------------------
void Swapchain::InternalInitialize(gfx_low::SwapchainMaster* swapchainMaster,
    const ::vk::SwapchainKHR& swapchain, uint32_t uniqueId, int minImageCount,
    ::vk::Format imageFormat) {
    AE_BASE_ASSERT(!InternalIsInitialized());
    swapchainMaster_.reset(swapchainMaster);
    swapchain_ = swapchain;
    renderTargetSpecInfo_ =
        gfx_low::RenderTargetSpecInfo().InternalSetNativeFormat(imageFormat);
    {
        auto& device = swapchainMaster_->Device();

        auto swapchainImageCount = uint32_t();
        {
            const auto result =
                device.InternalInstance().getSwapchainImagesKHR(swapchain_,
                    &swapchainImageCount, static_cast<::vk::Image*>(nullptr));
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
            AE_BASE_ASSERT_LESS(0, minImageCount);
        }

        frameProperties_.resize(int(swapchainImageCount),
            &swapchainMaster_->Device().System().InternalObjectAllocator());

        base::RuntimeArray<::vk::Image> swapchainImages(
            frameProperties_.count(),
            &device.System().InternalTempWorkAllocator());
        {
            const auto result = device.InternalInstance().getSwapchainImagesKHR(
                swapchain_, &swapchainImageCount, swapchainImages.head());
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
        }

        const auto semaphoreCreateInfo = ::vk::SemaphoreCreateInfo();
        for (int i = 0; i < frameProperties_.count(); ++i) {
            auto& target = frameProperties_[i];
            target.AcquireEvent.init(EventCreateInfo().SetDevice(&device));
            target.ReadyToPresentEvent.init(
                EventCreateInfo().SetDevice(&device));
            target.ImageResource.init(
                ImageResourceCreateInfo()
                    .SetDevice(&device)
                    .InternalSetImagePtr(&swapchainImages[i]));
            target.RenderTargetImageView.init(
                RenderTargetImageViewCreateInfo()
                    .SetDevice(&device)
                    .SetImageResource(target.ImageResource.ptr())
                    .InternalSetRawFormat(imageFormat));
        }
    }
    uniqueId_ = uniqueId_;
    currentFrameIndex_ = -1;
    AE_BASE_ASSERT(InternalIsInitialized());
}

//------------------------------------------------------------------------------
void Swapchain::InternalFinalize() {
    if (!InternalIsInitialized()) {
        return;
    }
    uniqueId_ = InternalInvalidUniqueId;
    {
        auto& device = swapchainMaster_->Device();
        for (int i = frameProperties_.count() - 1; 0 <= i; --i) {
            auto& target = frameProperties_[i];
            target.RenderTargetImageView.reset();
            target.ImageResource.reset();
            target.ReadyToPresentEvent.reset();
            target.AcquireEvent.reset();
        }
    }
    swapchain_ = ::vk::SwapchainKHR();
    swapchainMaster_.reset();
    AE_BASE_ASSERT(!InternalIsInitialized());
}

}  // namespace gfx_low
}  // namespace ae
// EOF
