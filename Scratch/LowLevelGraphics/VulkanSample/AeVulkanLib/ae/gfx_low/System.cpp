// 文字コード：UTF-8
#include <ae/gfx_low/System.hpp>

// includes
#include <ae/base/ArrayLength.hpp>
#include <ae/base/IAllocator.hpp>
#include <ae/base/Os.hpp>
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeArray.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/PhysicalDeviceInfo.hpp>
#include <ae/gfx_low/SystemCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

namespace {

bool fCheckLayers(
    uint32_t checkCount,
    char const* const* const checkNames,
    uint32_t layerCount,
    ::vk::LayerProperties* layers)
{
    for (uint32_t i = 0; i < checkCount; i++) {
        bool found = false;
        for (uint32_t j = 0; j < layerCount; j++) {
            if (!::std::strcmp(checkNames[i], layers[j].layerName)) {
                found = true;
                break;
            }
        }
        if (!found) {
            fprintf(stderr, "Cannot find layer: %s\n", checkNames[i]);
            return false;
        }
    }
    return true;
}

} // namespace

//------------------------------------------------------------------------------
System::System(const SystemCreateInfo& createInfo)
: objectAllocator_(
      createInfo.ObjectAllocator() == nullptr
          ? ::ae::base::IAllocator::Default()
          : ::ae::base::PtrToRef(createInfo.ObjectAllocator()))
, tempWorkAllocator_(
      createInfo.TempWorkAllocator() == nullptr
          ? ::ae::base::IAllocator::Default()
          : ::ae::base::PtrToRef(createInfo.TempWorkAllocator()))
{
    // 複数作成防止
    AE_BASE_ASSERT(!IsInstanceCreated);
    IsInstanceCreated = true;

    // 関数ロード
#if VULKAN_HPP_DISPATCH_LOADER_DYNAMIC == 1
    VULKAN_HPP_DEFAULT_DISPATCHER.init(
        vkLoader_.getProcAddress<PFN_vkGetInstanceProcAddr>(
            "vkGetInstanceProcAddr"));
#endif

    // ValidationLayer 検索
    char const* const instanceValidationLayers[] = {
        "VK_LAYER_KHRONOS_validation"
    };
    uint32_t instanceLayerCount = 0;
    vk::Bool32 validationFound = VK_FALSE;
    if (createInfo.DebugLevel() != SystemDebugLevel::NoDebug) {
        auto result = vk::enumerateInstanceLayerProperties(
            &instanceLayerCount,
            static_cast<vk::LayerProperties*>(nullptr));
        AE_BASE_ASSERT(result == vk::Result::eSuccess);

        if (0 < instanceLayerCount) {
            base::RuntimeArray<::vk::LayerProperties> instanceLayers(
                instanceLayerCount,
                &tempWorkAllocator_);
            result = vk::enumerateInstanceLayerProperties(
                &instanceLayerCount,
                instanceLayers.Head());
            AE_BASE_ASSERT(result == vk::Result::eSuccess);

            validationFound = fCheckLayers(
                AE_BASE_ARRAY_LENGTH(instanceValidationLayers),
                instanceValidationLayers,
                instanceLayerCount,
                instanceLayers.Head());
            if (validationFound) {
                enabledLayerCount_ =
                    AE_BASE_ARRAY_LENGTH(instanceValidationLayers);
                enabledLayers_[0] = instanceValidationLayers[0];
            }
        }

        if (!validationFound) {
            AE_BASE_ASSERT_NOT_REACHED_MSG(
                "vkEnumerateInstanceLayerProperties failed to find required "
                "validation layer.\n\n"
                "Please look at the Getting Started guide for additional "
                "information.\n");
        }
    }

    // InstanceExtension 検索
    uint32_t instanceExtensionCount = 0;
    vk::Bool32 surfaceExtFound = VK_FALSE;
    vk::Bool32 platformSurfaceExtFound = VK_FALSE;
    memset(extensionNames_, 0, sizeof(extensionNames_));

    auto result = vk::enumerateInstanceExtensionProperties(
        nullptr,
        &instanceExtensionCount,
        static_cast<vk::ExtensionProperties*>(nullptr));
    AE_BASE_ASSERT(result == vk::Result::eSuccess);

    if (0 < instanceExtensionCount) {
        base::RuntimeArray<::vk::ExtensionProperties> instanceExtensions(
            instanceExtensionCount,
            &tempWorkAllocator_);
        result = vk::enumerateInstanceExtensionProperties(
            nullptr,
            &instanceExtensionCount,
            instanceExtensions.Head());
        AE_BASE_ASSERT(result == vk::Result::eSuccess);

        for (uint32_t i = 0; i < instanceExtensionCount; i++) {
            if (!std::strcmp(
                    VK_KHR_SURFACE_EXTENSION_NAME,
                    instanceExtensions[i].extensionName)) {
                surfaceExtFound = 1;
                extensionNames_[enabledExtensionCount_++] =
                    VK_KHR_SURFACE_EXTENSION_NAME;
            }
#if defined(VK_USE_PLATFORM_WIN32_KHR)
            if (!std::strcmp(
                    VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
                    instanceExtensions[i].extensionName)) {
                platformSurfaceExtFound = 1;
                extensionNames_[enabledExtensionCount_++] =
                    VK_KHR_WIN32_SURFACE_EXTENSION_NAME;
            }
#elif defined(VK_USE_PLATFORM_METAL_EXT)
            if (!std::strcmp(
                    VK_EXT_METAL_SURFACE_EXTENSION_NAME,
                    instanceExtensions[i].extensionName)) {
                platformSurfaceExtFound = 1;
                extensionNames_[enabledExtensionCount_++] =
                    VK_EXT_METAL_SURFACE_EXTENSION_NAME;
            }
#endif
            AE_BASE_ASSERT_LESS(enabledExtensionCount_, ExtensionCountMax);
        }
    }

    if (!surfaceExtFound) {
        AE_BASE_ASSERT_NOT_REACHED_MSG(
            "vkEnumerateInstanceExtensionProperties failed to find "
            "the " VK_KHR_SURFACE_EXTENSION_NAME
            " extension.\n\n"
            "Do you have a compatible Vulkan installable client driver (ICD) "
            "installed?\n"
            "Please look at the Getting Started guide for additional "
            "information.\n");
    }

    if (!platformSurfaceExtFound) {
#if defined(VK_USE_PLATFORM_WIN32_KHR)
        AE_BASE_ASSERT_NOT_REACHED_MSG(
            "vkEnumerateInstanceExtensionProperties failed to find "
            "the " VK_KHR_WIN32_SURFACE_EXTENSION_NAME
            " extension.\n\n"
            "Do you have a compatible Vulkan installable client driver (ICD) "
            "installed?\n"
            "Please look at the Getting Started guide for additional "
            "information.\n");
#elif defined(VK_USE_PLATFORM_METAL_EXT)
        AE_BASE_ASSERT_NOT_REACHED_MSG(
            "vkEnumerateInstanceExtensionProperties failed to find "
            "the " VK_EXT_METAL_SURFACE_EXTENSION_NAME
            " extension.\n\nDo you have a compatible "
            "Vulkan installable client driver (ICD) installed?\nPlease "
            "look at the Getting Started guide for additional "
            "information.\n");
#endif
    }

    // インスタンス作成
    {
        auto const appInfo = ::vk::ApplicationInfo()
                                 .setPApplicationName("AdelEngineSample")
                                 .setApplicationVersion(0)
                                 .setPEngineName("AdelEngineSample")
                                 .setEngineVersion(0)
                                 .setApiVersion(VK_API_VERSION_1_2);
        auto const instInfo =
            ::vk::InstanceCreateInfo()
                .setPApplicationInfo(&appInfo)
                .setEnabledLayerCount(enabledLayerCount_)
                .setPpEnabledLayerNames(instanceValidationLayers)
                .setEnabledExtensionCount(enabledExtensionCount_)
                .setPpEnabledExtensionNames(extensionNames_);
        auto result = ::vk::createInstance(&instInfo, nullptr, &nativeObject_);
        if (result == vk::Result::eErrorIncompatibleDriver) {
            AE_BASE_ASSERT_NOT_REACHED_MSG(
                "Cannot find a compatible Vulkan installable client driver "
                "(ICD).\n\n"
                "Please look at the Getting Started guide for additional "
                "information.\n");
        } else if (result == vk::Result::eErrorExtensionNotPresent) {
            AE_BASE_ASSERT_NOT_REACHED_MSG(
                "Cannot find a specified extension library.\n"
                "Make sure your layers path is set appropriately.\n");
        } else if (result != vk::Result::eSuccess) {
            AE_BASE_ASSERT_NOT_REACHED_MSG(
                "vkCreateInstance failed.\n\n"
                "Do you have a compatible Vulkan installable client driver "
                "(ICD) "
                "installed?\n"
                "Please look at the Getting Started guide for additional "
                "information.\n");
        }
#if VULKAN_HPP_DISPATCH_LOADER_DYNAMIC == 1
        VULKAN_HPP_DEFAULT_DISPATCHER.init(nativeObject_);
#endif
    }

    // GPU列挙
    {
        uint32_t physicalDeviceCount;
        result = nativeObject_.enumeratePhysicalDevices(
            &physicalDeviceCount,
            static_cast<vk::PhysicalDevice*>(nullptr));
        AE_BASE_ASSERT(result == vk::Result::eSuccess);
        AE_BASE_ASSERT_MIN_TERM(
            int(physicalDeviceCount),
            1,
            PhysicalDeviceCountMax);
        result = nativeObject_.enumeratePhysicalDevices(
            &physicalDeviceCount,
            &physicalDevices_[0]);
        AE_BASE_ASSERT(result == vk::Result::eSuccess);
        physicalDeviceCount_ = int(physicalDeviceCount);
    }
}

//------------------------------------------------------------------------------
System::~System()
{
    // インスタンス破棄
    nativeObject_.destroy(nullptr);
    nativeObject_ = ::vk::Instance();

    // 複数作成防止
    AE_BASE_ASSERT(IsInstanceCreated);
    IsInstanceCreated = false;
}

//------------------------------------------------------------------------------
PhysicalDeviceInfo System::PhysicalDeviceInfo(
    const int physicalDeviceIndex) const
{
    AE_BASE_ASSERT_LESS(physicalDeviceIndex, physicalDeviceCount_);
    const auto device = physicalDevices_[physicalDeviceIndex];

    gfx_low::PhysicalDeviceInfo info;

    // Queue 特性
    {
        ::vk::QueueFamilyProperties
            queueFamilyProperties[QueueFamilyCountMax] = {};
        uint32_t queueFamilyCount = 0;
        device.getQueueFamilyProperties(
            &queueFamilyCount,
            static_cast<::vk::QueueFamilyProperties*>(nullptr));
        AE_BASE_ASSERT_LESS(queueFamilyCount, QueueFamilyCountMax);
        device.getQueueFamilyProperties(
            &queueFamilyCount,
            queueFamilyProperties);

        QueueFamilyIndexTableType_ queueFamilyIndexTable;
        QueueFamilyIndexTable_(&queueFamilyIndexTable, physicalDeviceIndex);

        // Normal
        {
            const auto queueFamilyIndex =
                queueFamilyIndexTable[int(QueueKind::Normal)];
            if (0 <= queueFamilyIndex) {
                info.CreatableQueueCounts_[int(QueueKind::Normal)] =
                    int(queueFamilyProperties[queueFamilyIndex].queueCount);
            }
        }

        // ComputeOnly
        {
            const auto queueFamilyIndex =
                queueFamilyIndexTable[int(QueueKind::ComputeOnly)];
            if (0 <= queueFamilyIndex) {
                info.CreatableQueueCounts_[int(QueueKind::ComputeOnly)] =
                    int(queueFamilyProperties[queueFamilyIndex].queueCount);
            }
        }

        // CopyOnly
        {
            const auto queueFamilyIndex =
                queueFamilyIndexTable[int(QueueKind::CopyOnly)];
            if (0 <= queueFamilyIndex) {
                info.CreatableQueueCounts_[int(QueueKind::CopyOnly)] =
                    int(queueFamilyProperties[queueFamilyIndex].queueCount);
            }
        }
    }

    return info;
}

//------------------------------------------------------------------------------
void System::DumpAllPhysicalDeviceInfo() const
{
    AE_BASE_COUTFMT_LINE("PhysicalDeviceCount: %d", physicalDeviceCount_);
    for (int i = 0; i < physicalDeviceCount_; ++i) {
        const auto info = PhysicalDeviceInfo(i);
        AE_BASE_COUTFMT_LINE("    PhysicalDevice #%d:", i);
        AE_BASE_COUTFMT_LINE(
            "        CreatableQueueCount[Normal]: %d",
            info.CreatableQueueCount(QueueKind::Normal));
        AE_BASE_COUTFMT_LINE(
            "        CreatableQueueCount[ComputeOnly]: %d",
            info.CreatableQueueCount(QueueKind::ComputeOnly));
        AE_BASE_COUTFMT_LINE(
            "        CreatableQueueCount[CopyOnly]: %d",
            info.CreatableQueueCount(QueueKind::CopyOnly));
    }
}

//------------------------------------------------------------------------------
void System::QueueFamilyIndexTable_(
    QueueFamilyIndexTableType_* result,
    const int physicalDeviceIndex) const
{
    auto& resultRef = ::ae::base::PtrToRef(result);
    AE_BASE_ASSERT_LESS(physicalDeviceIndex, physicalDeviceCount_);
    const auto device = physicalDevices_[physicalDeviceIndex];
    ::vk::QueueFamilyProperties queueFamilyProperties[QueueFamilyCountMax] = {};
    uint32_t queueFamilyCount = 0;
    device.getQueueFamilyProperties(
        &queueFamilyCount,
        static_cast<::vk::QueueFamilyProperties*>(nullptr));
    AE_BASE_ASSERT_LESS(queueFamilyCount, QueueFamilyCountMax);
    device.getQueueFamilyProperties(&queueFamilyCount, queueFamilyProperties);

    // -1 で初期化
    resultRef.Fill(-1);

    // 最初に見つかった物を採用する
    for (uint32_t i = 0; i < queueFamilyCount; ++i) {
        // Normal
        const auto& queueProps = queueFamilyProperties[i];
        if (resultRef[QueueKind::Normal] < 0 &&
            (uint32_t(queueProps.queueFlags) & uint32_t(::vk::QueueFlagBits::eGraphics)) != 0) {
            resultRef[QueueKind::Normal] = int(i);
        }

        // ComputeOnly
        if (resultRef[QueueKind::ComputeOnly] < 0 &&
            (uint32_t(queueProps.queueFlags) & uint32_t(::vk::QueueFlagBits::eGraphics)) == 0 &&
            (uint32_t(queueProps.queueFlags) & uint32_t(::vk::QueueFlagBits::eCompute)) != 0) {
            resultRef[QueueKind::ComputeOnly] = int(i);
        }

        // CopyOnly
        if (resultRef[QueueKind::CopyOnly] < 0 &&
            (uint32_t(queueProps.queueFlags) &
                uint32_t(::vk::QueueFlagBits::eGraphics | ::vk::QueueFlagBits::eCompute)) == 0 &&
            (queueProps.queueFlags | ::vk::QueueFlagBits::eTransfer)) {
            resultRef[QueueKind::CopyOnly] = int(i);
        }
    }
}

//------------------------------------------------------------------------------
bool System::IsInstanceCreated = false;
} // namespace ae::gfx_low
// EOF
