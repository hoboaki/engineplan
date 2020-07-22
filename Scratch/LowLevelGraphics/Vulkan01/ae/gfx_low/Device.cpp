// 文字コード：UTF-8
#include <ae/gfx_low/Device.hpp>

// includes
#include <ae/base/EnumKeyArray.hpp>
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeArray.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/DeviceCreateInfo.hpp>
#include <ae/gfx_low/PhysicalDeviceInfo.hpp>
#include <ae/gfx_low/Queue.hpp>
#include <ae/gfx_low/QueueCreateInfo.hpp>
#include <ae/gfx_low/System.hpp>
#include <array>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
Device::Device(const DeviceCreateInfo& createInfo)
: system_(::ae::base::PtrToRef(createInfo.System()))
, device_()
, physicalDeviceIndex_(createInfo.PhysicalDeviceIndex())
, queues_(createInfo.QueueCreateInfoCount(),
      &::ae::base::PtrToRef(createInfo.System()).InternalObjectAllocator()) {
    const auto physicalDeviceIndex = createInfo.PhysicalDeviceIndex();
    AE_BASE_ASSERT_MIN_TERM(
        physicalDeviceIndex, 0, system_.PhysicalDeviceCount());
    const auto physicalDeviceInfo =
        system_.PhysicalDeviceInfo(physicalDeviceIndex);
    const auto queueCreateCount = createInfo.QueueCreateInfoCount();
    AE_BASE_ASSERT_LESS(0, queueCreateCount);
    const auto* queueCreateInfos = createInfo.QueueCrateInfos();
    AE_BASE_ASSERT_POINTER(queueCreateInfos);

#if defined(AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR)
    // Queue の作成数が上限を越えていないかのチェック
    {
        ::ae::base::EnumKeyArray<QueueType, int> queueCounts;
        for (int i = 0; i < createInfo.QueueCreateInfoCount(); ++i) {
            ++queueCounts[createInfo.QueueCrateInfos()[i].Type()];
        }
        for (int i = 0; i < int(queueCounts.count()); ++i) {
            if (physicalDeviceInfo.CreatableQueueCount(QueueType(i)) <
                queueCounts[i]) {
                AE_BASE_ASSERT_NOT_REACHED_MSGFMT(
                    "Create queue count (for QueueType: %d) is too large.",
                    queueCounts[i]);
            }
        }
    }
#endif

    // 各 QueueType の作成総数とIndex表を作成
    ::ae::base::EnumKeyArray<QueueType, int>
        queueCountTable;  // QueueType ごとの作成総数
    ::ae::base::RuntimeArray<int> indexInQueueTypeTable(queueCreateCount,
        &system_
             .InternalTempWorkAllocator());  // 各 Queue が同じ QueueType
                                             // における何個目の Queue かの情報
    for (int queueIdx = 0; queueIdx < queueCreateCount; ++queueIdx) {
        const auto& queueCreateInfo = queueCreateInfos[queueIdx];
        indexInQueueTypeTable[queueIdx] =
            queueCountTable[queueCreateInfo.Type()];
        ++queueCountTable[queueCreateInfo.Type()];
    }

    // 各 QueueFamily ごとの Priority 配列を作成
    ::ae::base::EnumKeyArray<QueueType, ::ae::base::RuntimeArray<float>>
        queuePriorityTable;
    for (int queueType = 0; queueType < int(QueueType::TERM); ++queueType) {
        const auto queueCount = queueCountTable[queueType];
        if (queueCount == 0) {
            continue;
        }
        queuePriorityTable[queueType].resize(
            queueCount, &system_.InternalTempWorkAllocator());
    }
    const float priorityTable[int(QueuePriority::TERM)] = {0.0f, 0.5f, 1.0f};
    for (int queueIdx = 0; queueIdx < queueCreateCount; ++queueIdx) {
        const auto indexInQueueType = indexInQueueTypeTable[queueIdx];
        const auto priorityEnum = queueCreateInfos[queueIdx].Priority();
        AE_BASE_ASSERT_ENUM(priorityEnum, QueuePriority);
        const float priority = priorityTable[int(priorityEnum)];
        queuePriorityTable[queueCreateInfos[queueIdx].Type()]
                          [indexInQueueType] = priority;
    }

    // QueueType -> QueueFamilyIndex テーブル
    System::InternalQueueFamilyIndexTableType queueFamilyIndexTable;
    system_.InternalQueueFamilyIndexTable(
        &queueFamilyIndexTable, physicalDeviceIndex);

    // SwapchainExtension対応
    const auto& physicalDevice =
        system_.InternalPhysicalDevice(physicalDeviceIndex);
    uint32_t enabledExtensionCount = 0;
    const int extensionCountMax = 64;
    const char* extensionNames[extensionCountMax] = {};
    ::vk::Bool32 swapchainExtFound = VK_FALSE;
    {
        uint32_t deviceExtensionCount = 0;
        auto result = physicalDevice.enumerateDeviceExtensionProperties(nullptr,
            &deviceExtensionCount,
            static_cast<vk::ExtensionProperties*>(nullptr));
        AE_BASE_ASSERT(result == vk::Result::eSuccess);

        if (0 < deviceExtensionCount) {
            base::RuntimeArray<::vk::ExtensionProperties> deviceExtensions(
                int(deviceExtensionCount),
                &system_.InternalTempWorkAllocator());
            result = physicalDevice.enumerateDeviceExtensionProperties(
                nullptr, &deviceExtensionCount, deviceExtensions.head());
            AE_BASE_ASSERT(result == vk::Result::eSuccess);

            for (uint32_t i = 0; i < deviceExtensionCount; i++) {
                if (!std::strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME,
                        deviceExtensions[i].extensionName)) {
                    swapchainExtFound = 1;
                    extensionNames[enabledExtensionCount++] =
                        VK_KHR_SWAPCHAIN_EXTENSION_NAME;
                }
                AE_BASE_ASSERT(enabledExtensionCount < extensionCountMax);
            }
        }

        if (!swapchainExtFound) {
            AE_BASE_ASSERT_NOT_REACHED_MSG(
                "vkEnumerateDeviceExtensionProperties failed to find "
                "the " VK_KHR_SWAPCHAIN_EXTENSION_NAME
                " extension.\n\n"
                "Do you have a compatible Vulkan installable client driver "
                "(ICD) "
                "installed?\n"
                "Please look at the Getting Started guide for additional "
                "information.\n");
        }
    }

    // vkDeviceQueueCreateInfo の作成
    std::array<::vk::DeviceQueueCreateInfo, static_cast<int>(QueueType::TERM)>
        deviceQueueCreateInfos;
    int deviceQueueCreateInfoCount = 0;
    for (int queueType = 0; queueType < int(QueueType::TERM); ++queueType) {
        if (queueCountTable[queueType] == 0) {
            continue;
        }
        auto& target = deviceQueueCreateInfos[queueType];
        target.setQueueFamilyIndex(queueFamilyIndexTable[queueType]);
        target.setQueueCount(queueCountTable[queueType]);
        target.setPQueuePriorities(&queuePriorityTable[queueType][0]);
        ++deviceQueueCreateInfoCount;
    }
    auto deviceInfo = vk::DeviceCreateInfo()
                          .setQueueCreateInfoCount(queueCreateCount)
                          .setPQueueCreateInfos(&deviceQueueCreateInfos[0])
                          .setEnabledLayerCount(0)
                          .setPpEnabledLayerNames(nullptr)
                          .setEnabledExtensionCount(enabledExtensionCount)
                          .setPpEnabledExtensionNames(extensionNames)
                          .setPEnabledFeatures(nullptr);
    {
        auto result =
            physicalDevice.createDevice(&deviceInfo, nullptr, &device_);
        AE_BASE_ASSERT(result == vk::Result::eSuccess);
    }

    // Queue オブジェクト作成
    for (int i = 0; i < queueCreateCount; ++i) {
        queues_.add(this,
            device_.getQueue(deviceQueueCreateInfos[i].queueFamilyIndex,
                indexInQueueTypeTable[i]),
            queueCreateInfos[i].Type());
    }
}

//------------------------------------------------------------------------------
Device::~Device() {
    queues_.clear();
    device_.destroy(nullptr);
    device_ = ::vk::Device();
}

//------------------------------------------------------------------------------
gfx_low::Queue& Device::Queue(const int queueIndex) const {
    return queues_[queueIndex];
}

}  // namespace gfx_low
}  // namespace ae
// EOF
