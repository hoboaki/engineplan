// 文字コード：UTF-8
#include <ae/gfx_low/Swapchain.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/ImageResourceCreateInfo.hpp>
#include <ae/gfx_low/RenderTargetViewCreateInfo.hpp>
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
void Swapchain::InternalInitialize(gfx_low::SwapchainMaster* swapchainMaster,
    const ::vk::SwapchainKHR& swapchain, uint32_t uniqueId, int minImageCount,
    ::vk::Format imageFormat) {
    AE_BASE_ASSERT(!InternalIsInitialized());
    swapchainMaster_.reset(swapchainMaster);
    swapchain_ = swapchain;
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
            {
                const auto result = device.InternalInstance().createSemaphore(
                    &semaphoreCreateInfo, nullptr, &target.AcquireSemaphore);
                AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
            }
            {
                const auto result = device.InternalInstance().createSemaphore(
                    &semaphoreCreateInfo, nullptr,
                    &target.ReadyToPresentSemaphore);
                AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
            }
            target.ImageResource.init(
                ImageResourceCreateInfo()
                    .SetDevice(&device)
                    .InternalSetImagePtr(&swapchainImages[i]));
            target.RenderTargetView.init(
                RenderTargetViewCreateInfo()
                    .SetDevice(&device)
                    .SetImageResource(target.ImageResource.ptr())
                    .InternalSetRawFormat(imageFormat));
        }
    }
    uniqueId_ = uniqueId_;
    currentFrameIndex_ = 0;
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
            target.RenderTargetView.reset();
            target.ImageResource.reset();
            device.InternalInstance().destroySemaphore(
                target.ReadyToPresentSemaphore, nullptr);
            device.InternalInstance().destroySemaphore(
                target.AcquireSemaphore, nullptr);
        }
    }
    swapchain_ = ::vk::SwapchainKHR();
    swapchainMaster_.reset();
    AE_BASE_ASSERT(!InternalIsInitialized());
}

}  // namespace gfx_low
}  // namespace ae
// EOF
