// 文字コード：UTF-8
#include <ae/gfx_low/SwapchainMaster.hpp>

// includes
#include <ae/base/ArrayLength.hpp>
#include <ae/base/Display.hpp>
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeArray.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/Screen.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/PhysicalDeviceInfo.hpp>
#include <ae/gfx_low/Swapchain.hpp>
#include <ae/gfx_low/SwapchainCreateInfo.hpp>
#include <ae/gfx_low/SwapchainMasterCreateInfo.hpp>
#include <ae/gfx_low/System.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
SwapchainMaster::SwapchainMaster(const SwapchainMasterCreateInfo& createInfo)
: device_(::ae::base::PtrToRef(createInfo.Device()))
, screen_(base::PtrToRef(createInfo.Screen()))
, surface_()
, swapchains_(
      createInfo.SwapchainCountMax(),
      &device_.System().ObjectAllocator_())
{
    // surface 作成
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    {
        auto const surfaceCreateInfo =
            ::vk::Win32SurfaceCreateInfoKHR()
                .setHinstance(screen_.Display_().hinstance)
                .setHwnd(screen_.Display_().hwindow);

        auto result = device_.System().NativeObject_().createWin32SurfaceKHR(
            &surfaceCreateInfo,
            nullptr,
            &surface_);
        AE_BASE_ASSERT(result == vk::Result::eSuccess);
    }
#elif defined(VK_USE_PLATFORM_METAL_EXT)
    {
        auto const createInfo = ::vk::MetalSurfaceCreateInfoEXT().setPLayer(
            static_cast<CAMetalLayer*>(screen_.Ext_().MetalLayer()));

        auto result = device_.System().NativeObject_().createMetalSurfaceEXT(
            &createInfo,
            nullptr,
            &surface_);
        AE_BASE_ASSERT(result == vk::Result::eSuccess);
    }
#endif

    // PhysicalDevice の SurfacePresent 対応確認
    {
        auto pd =
            device_.System().PhysicalDevice_(device_.PhysicalDeviceIndex());
        uint32_t queueFamilyCount = 0;
        pd.getQueueFamilyProperties(
            &queueFamilyCount,
            static_cast<::vk::QueueFamilyProperties*>(nullptr));
        AE_BASE_ASSERT_LESS_EQUALS(1, queueFamilyCount);
        ::vk::Bool32 isSupported = false;
        for (uint32_t i = 0; i < queueFamilyCount && isSupported == VK_FALSE;
             ++i) {
            [[maybe_unused]] auto result =
                pd.getSurfaceSupportKHR(i, surface_, &isSupported);
            AE_BASE_ASSERT(result == vk::Result::eSuccess);
        }
        AE_BASE_ASSERT(isSupported == VK_TRUE);
    }
}

//------------------------------------------------------------------------------
SwapchainMaster::~SwapchainMaster()
{
    // 逆順に破棄
    for (int i = swapchains_.Count() - 1; 0 <= i; --i) {
        auto& swapchain = swapchains_[i];
        if (swapchain.IsInitialized_()) {
            DestroySwapchain(SwapchainHandle(&swapchain));
        }
    }
    device_.System().NativeObject_().destroySurfaceKHR(surface_, nullptr);
    surface_ = ::vk::SurfaceKHR();
}

//------------------------------------------------------------------------------
SwapchainHandle SwapchainMaster::CreateSwapchain(
    const SwapchainCreateInfo& createInfo,
    const SwapchainHandle& oldSwapchain)
{
    // メモ
    const auto& physicalDevice =
        device_.System().PhysicalDevice_(device_.PhysicalDeviceIndex());

    // 古い swapchain をメモ
    Swapchain* entity = nullptr;
    ::vk::SwapchainKHR oldSwapchainInstance;
    if (oldSwapchain.IsValid()) {
        entity = &oldSwapchain.Entity_();
    }

    // Entity を確保
    const uint32_t nextUniqueId = AcquireUniqueId();
    if (entity == nullptr) {
        for (int entityIdx = 0; entityIdx < swapchains_.Count(); ++entityIdx) {
            if (!swapchains_[entityIdx].IsInitialized_()) {
                entity = &swapchains_[entityIdx];
                break;
            }
        }
    }
    entity->Finalize_();

    // サーフェスの対応フォーマットを取得
    uint32_t surfFormatCount = uint32_t();
    auto result = physicalDevice.getSurfaceFormatsKHR(
        surface_,
        &surfFormatCount,
        static_cast<vk::SurfaceFormatKHR*>(nullptr));
    AE_BASE_ASSERT(result == vk::Result::eSuccess);
    base::RuntimeArray<::vk::SurfaceFormatKHR> surfFormats(
        int(surfFormatCount),
        &device_.System().TempWorkAllocator_());
    result = physicalDevice.getSurfaceFormatsKHR(
        surface_,
        &surfFormatCount,
        surfFormats.Head());
    AE_BASE_ASSERT(result == vk::Result::eSuccess);

    // サーフェスが対応するフォーマットを選択
    vk::Format format = ::vk::Format::eUndefined;
    vk::ColorSpaceKHR colorSpace = ::vk::ColorSpaceKHR();
    {
        const ::vk::Format srgbFormats[] = {
            ::vk::Format::eR8G8B8A8Srgb,
            ::vk::Format::eB8G8R8A8Srgb,
            ::vk::Format::eUndefined,
        };
        const ::vk::Format linearFormats[] = {
            ::vk::Format::eR8G8B8A8Unorm,
            ::vk::Format::eB8G8R8A8Unorm,
            ::vk::Format::eUndefined,
        };
        const ::vk::Format* findFormats =
            createInfo.IsSrgbFormat() ? srgbFormats : linearFormats;
        for (int surfFmtIdx = 0; surfFmtIdx < int(surfFormatCount) &&
                                 format == ::vk::Format::eUndefined;
             ++surfFmtIdx) {
            const auto& surfFormat = surfFormats[surfFmtIdx];
            for (int fmtIdx = 0;
                 findFormats[fmtIdx] != ::vk::Format::eUndefined;
                 ++fmtIdx) {
                if (surfFormat.format != findFormats[fmtIdx]) {
                    continue;
                }
                format = surfFormat.format;
                colorSpace = surfFormat.colorSpace;
                break;
            }
        }
        AE_BASE_ASSERT(format != ::vk::Format::eUndefined);
    }

    // Check the surface capabilities and formats
    auto surfCapabilities = ::vk::SurfaceCapabilitiesKHR();
    result =
        physicalDevice.getSurfaceCapabilitiesKHR(surface_, &surfCapabilities);
    AE_BASE_ASSERT(result == vk::Result::eSuccess);

    auto presentModeCount = uint32_t();
    result = physicalDevice.getSurfacePresentModesKHR(
        surface_,
        &presentModeCount,
        static_cast<vk::PresentModeKHR*>(nullptr));
    AE_BASE_ASSERT(result == vk::Result::eSuccess);

    base::RuntimeArray<::vk::PresentModeKHR> presentModes(
        int(presentModeCount),
        &device_.System().TempWorkAllocator_());
    result = physicalDevice.getSurfacePresentModesKHR(
        surface_,
        &presentModeCount,
        presentModes.Head());
    AE_BASE_ASSERT(result == vk::Result::eSuccess);

    vk::Extent2D swapchainExtent;
    swapchainExtent.width = screen_.Width();
    swapchainExtent.height = screen_.Height();
    // width and height are either both -1, or both not -1.
    // if (surfCapabilities.currentExtent.width == (uint32_t)-1) {
    //    // If the surface size is undefined, the size is set to
    //    // the size of the images requested.
    //    swapchainExtent.width = width;
    //    swapchainExtent.height = height;
    //} else {
    //    // If the surface size is defined, the swap chain size must match
    //    swapchainExtent = surfCapabilities.currentExtent;
    //    width = surfCapabilities.currentExtent.width;
    //    height = surfCapabilities.currentExtent.height;
    //}

    // The FIFO present mode is guaranteed by the spec to be supported
    // and to have no tearing.  It's a great default present mode to use.
    vk::PresentModeKHR swapchainPresentMode = vk::PresentModeKHR::eFifo;

    //  There are times when you may wish to use another present mode.  The
    //  following code shows how to select them, and the comments provide some
    //  reasons you may wish to use them.
    //
    // It should be noted that Vulkan 1.0 doesn't provide a method for
    // synchronizing rendering with the presentation engine's display.  There
    // is a method provided for throttling rendering with the display, but
    // there are some presentation engines for which this method will not work.
    // If an application doesn't throttle its rendering, and if it renders much
    // faster than the refresh rate of the display, this can waste power on
    // mobile devices.  That is because power is being spent rendering images
    // that may never be seen.

    // VK_PRESENT_MODE_IMMEDIATE_KHR is for applications that don't care
    // about
    // tearing, or have some way of synchronizing their rendering with the
    // display.
    // VK_PRESENT_MODE_MAILBOX_KHR may be useful for applications that
    // generally render a new presentable image every refresh cycle, but are
    // occasionally early.  In this case, the application wants the new
    // image
    // to be displayed instead of the previously-queued-for-presentation
    // image
    // that has not yet been displayed.
    // VK_PRESENT_MODE_FIFO_RELAXED_KHR is for applications that generally
    // render a new presentable image every refresh cycle, but are
    // occasionally
    // late.  In this case (perhaps because of stuttering/latency concerns),
    // the application wants the late image to be immediately displayed,
    // even
    // though that may mean some tearing.

    ::vk::PresentModeKHR presentMode = vk::PresentModeKHR::eFifo;
    if (presentMode != swapchainPresentMode) {
        for (uint32_t i = 0; i < presentModeCount; ++i) {
            if (presentModes[i] == presentMode) {
                swapchainPresentMode = presentMode;
                break;
            }
        }
    }

    if (swapchainPresentMode != presentMode) {
        AE_BASE_ASSERT_NOT_REACHED_MSG(
            "Present mode specified is not supported\n");
    }

    // Determine the number of VkImages to use in the swap chain.
    // Application desires to acquire 3 images at a time for triple
    // buffering
    uint32_t desiredNumOfSwapchainImages = uint32_t(createInfo.ImageCount());
    if (desiredNumOfSwapchainImages < surfCapabilities.minImageCount) {
        desiredNumOfSwapchainImages = surfCapabilities.minImageCount;
    }

    // If maxImageCount is 0, we can ask for as many images as we want,
    // otherwise
    // we're limited to maxImageCount
    if ((surfCapabilities.maxImageCount > 0) &&
        (desiredNumOfSwapchainImages > surfCapabilities.maxImageCount)) {
        // Application must settle for fewer images than desired:
        desiredNumOfSwapchainImages = surfCapabilities.maxImageCount;
    }

    vk::SurfaceTransformFlagBitsKHR preTransform;
    if (surfCapabilities.supportedTransforms &
        vk::SurfaceTransformFlagBitsKHR::eIdentity) {
        preTransform = vk::SurfaceTransformFlagBitsKHR::eIdentity;
    } else {
        preTransform = surfCapabilities.currentTransform;
    }

    // Find a supported composite alpha mode - one of these is guaranteed to be
    // set
    vk::CompositeAlphaFlagBitsKHR compositeAlpha =
        vk::CompositeAlphaFlagBitsKHR::eOpaque;
    vk::CompositeAlphaFlagBitsKHR compositeAlphaFlags[4] = {
        vk::CompositeAlphaFlagBitsKHR::eOpaque,
        vk::CompositeAlphaFlagBitsKHR::ePreMultiplied,
        vk::CompositeAlphaFlagBitsKHR::ePostMultiplied,
        vk::CompositeAlphaFlagBitsKHR::eInherit,
    };
    for (uint32_t i = 0; i < AE_BASE_ARRAY_LENGTH(compositeAlphaFlags); i++) {
        if (surfCapabilities.supportedCompositeAlpha & compositeAlphaFlags[i]) {
            compositeAlpha = compositeAlphaFlags[i];
            break;
        }
    }

    auto const swapchain_ci =
        vk::SwapchainCreateInfoKHR()
            .setSurface(surface_)
            .setMinImageCount(desiredNumOfSwapchainImages)
            .setImageFormat(format)
            .setImageColorSpace(colorSpace)
            .setImageExtent({ swapchainExtent.width, swapchainExtent.height })
            .setImageArrayLayers(1)
            .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment)
            .setImageSharingMode(vk::SharingMode::eExclusive)
            .setQueueFamilyIndexCount(0)
            .setPQueueFamilyIndices(nullptr)
            .setPreTransform(preTransform)
            .setCompositeAlpha(compositeAlpha)
            .setPresentMode(swapchainPresentMode)
            .setClipped(true)
            .setOldSwapchain(oldSwapchainInstance);

    ::vk::SwapchainKHR swapchain;
    result = device_.NativeObject_().createSwapchainKHR(
        &swapchain_ci,
        nullptr,
        &swapchain);
    AE_BASE_ASSERT(result == vk::Result::eSuccess);

    if (oldSwapchain.IsValid()) {
        DestroySwapchainInstance(oldSwapchainInstance);
    }

    entity->Initialize_(
        this,
        swapchain,
        nextUniqueId,
        desiredNumOfSwapchainImages,
        format);

    return SwapchainHandle(entity);
}

//------------------------------------------------------------------------------
void SwapchainMaster::DestroySwapchain(const SwapchainHandle& swapchain)
{
    AE_BASE_ASSERT(swapchain.IsValid());
    auto& entity = swapchain.Entity_();
    AE_BASE_ASSERT(this == &entity.SwapchainMaster());

    // 破棄
    DestroySwapchainInstance(entity.Instance_());
    entity.Finalize_();
}

//------------------------------------------------------------------------------
uint32_t SwapchainMaster::AcquireUniqueId()
{
    uint32_t uniqueId = lastAcquireUniqueId_;
    while (true) {
        ++uniqueId;
        if (uniqueId == Swapchain::InvalidUniqueId_) {
            continue;
        }
        bool isFound = false;
        for (int i = 0; i < swapchains_.Count(); ++i) {
            if (swapchains_[i].UniqueId_() == uniqueId) {
                isFound = true;
                break;
            }
        }
        if (isFound) {
            continue;
        }
        break;
    }
    lastAcquireUniqueId_ = uniqueId;
    return uniqueId;
}

//------------------------------------------------------------------------------
void SwapchainMaster::DestroySwapchainInstance(::vk::SwapchainKHR instance)
{
    device_.NativeObject_().destroySwapchainKHR(instance);
}

} // namespace ae::gfx_low
// EOF
