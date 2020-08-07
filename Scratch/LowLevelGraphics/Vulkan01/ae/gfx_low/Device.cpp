// 文字コード：UTF-8
#include <ae/gfx_low/Device.hpp>

// includes
#include <ae/base/ArrayLength.hpp>
#include <ae/base/EnumKeyArray.hpp>
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeArray.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/RuntimeMarray.hpp>
#include <ae/gfx_low/BufferResourceCreateInfo.hpp>
#include <ae/gfx_low/DeviceCreateInfo.hpp>
#include <ae/gfx_low/EnumUtil.hpp>
#include <ae/gfx_low/ImageResourceCreateInfo.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/PhysicalDeviceInfo.hpp>
#include <ae/gfx_low/Queue.hpp>
#include <ae/gfx_low/QueueCreateInfo.hpp>
#include <ae/gfx_low/ResourceMemory.hpp>
#include <ae/gfx_low/ResourceMemoryAllocInfo.hpp>
#include <ae/gfx_low/ResourceMemoryRequirements.hpp>
#include <ae/gfx_low/System.hpp>
#include <array>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
Device::Device(const DeviceCreateInfo& createInfo)
: system_(::ae::base::PtrToRef(createInfo.System()))
, nativeObject_()
, physicalDeviceIndex_(createInfo.PhysicalDeviceIndex())
, queues_(createInfo.QueueCreateInfoCount(),
      &::ae::base::PtrToRef(createInfo.System()).ObjectAllocator_()) {
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
        ::ae::base::EnumKeyArray<QueueKind, int> queueCounts;
        for (int i = 0; i < createInfo.QueueCreateInfoCount(); ++i) {
            ++queueCounts[createInfo.QueueCrateInfos()[i].Kind()];
        }
        for (int i = 0; i < int(queueCounts.Count()); ++i) {
            if (physicalDeviceInfo.CreatableQueueCount(QueueKind(i)) <
                queueCounts[i]) {
                AE_BASE_ASSERT_NOT_REACHED_MSGFMT(
                    "Create queue count (for QueueKind: %d) is too large.",
                    queueCounts[i]);
            }
        }
    }
#endif

    // 各 QueueKind の作成総数とIndex表を作成
    ::ae::base::EnumKeyArray<QueueKind, int>
        queueCountTable; // QueueKind ごとの作成総数
    ::ae::base::RuntimeArray<int> indexInQueueKindTable(queueCreateCount,
        &system_.TempWorkAllocator_()); // 各 Queue が同じ QueueKind
                                        // における何個目の Queue かの情報
    for (int queueIdx = 0; queueIdx < queueCreateCount; ++queueIdx) {
        const auto& queueCreateInfo = queueCreateInfos[queueIdx];
        indexInQueueKindTable[queueIdx] =
            queueCountTable[queueCreateInfo.Kind()];
        ++queueCountTable[queueCreateInfo.Kind()];
    }

    // 各 QueueFamily ごとの Priority 配列を作成
    ::ae::base::EnumKeyArray<QueueKind, ::ae::base::RuntimeArray<float>>
        queuePriorityTable;
    for (int queueKind = 0; queueKind < int(QueueKind::TERM); ++queueKind) {
        const auto queueCount = queueCountTable[queueKind];
        if (queueCount == 0) {
            continue;
        }
        queuePriorityTable[queueKind].Resize(
            queueCount, &system_.TempWorkAllocator_());
    }
    const float priorityTable[int(QueuePriority::TERM)] = {
        -1.0f, 0.0f, 0.5f, 1.0f};
    for (int queueIdx = 0; queueIdx < queueCreateCount; ++queueIdx) {
        const auto indexInQueueKind = indexInQueueKindTable[queueIdx];
        const auto priorityEnum = queueCreateInfos[queueIdx].Priority();
        AE_BASE_ASSERT_ENUM(priorityEnum, QueuePriority);
        const float priority = priorityTable[int(priorityEnum)];
        queuePriorityTable[queueCreateInfos[queueIdx].Kind()]
                          [indexInQueueKind] = priority;
    }

    // QueueKind -> QueueFamilyIndex テーブル
    System::QueueFamilyIndexTableType_ queueFamilyIndexTable;
    system_.QueueFamilyIndexTable_(&queueFamilyIndexTable, physicalDeviceIndex);

    // SwapchainExtension対応
    const auto& physicalDevice = system_.PhysicalDevice_(physicalDeviceIndex);
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
                int(deviceExtensionCount), &system_.TempWorkAllocator_());
            result = physicalDevice.enumerateDeviceExtensionProperties(
                nullptr, &deviceExtensionCount, deviceExtensions.Head());
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
    std::array<::vk::DeviceQueueCreateInfo, static_cast<int>(QueueKind::TERM)>
        deviceQueueCreateInfos;
    int deviceQueueCreateInfoCount = 0;
    for (int queueKind = 0; queueKind < int(QueueKind::TERM); ++queueKind) {
        if (queueCountTable[queueKind] <= 0) {
            continue;
        }
        auto& target = deviceQueueCreateInfos[deviceQueueCreateInfoCount];
        target.setQueueFamilyIndex(queueFamilyIndexTable[queueKind]);
        target.setQueueCount(queueCountTable[queueKind]);
        target.setPQueuePriorities(&queuePriorityTable[queueKind][0]);
        ++deviceQueueCreateInfoCount;
    }
    auto deviceInfo = vk::DeviceCreateInfo()
                          .setQueueCreateInfoCount(deviceQueueCreateInfoCount)
                          .setPQueueCreateInfos(&deviceQueueCreateInfos[0])
                          .setEnabledLayerCount(0)
                          .setPpEnabledLayerNames(nullptr)
                          .setEnabledExtensionCount(enabledExtensionCount)
                          .setPpEnabledExtensionNames(extensionNames)
                          .setPEnabledFeatures(nullptr);
    {
        auto result =
            physicalDevice.createDevice(&deviceInfo, nullptr, &nativeObject_);
        AE_BASE_ASSERT(result == vk::Result::eSuccess);
    }

    // Queue オブジェクト作成
    for (int i = 0; i < queueCreateCount; ++i) {
        const auto queueFamilyIndex =
            deviceQueueCreateInfos[i].queueFamilyIndex;
        ::vk::CommandPool commandPool;
        {
            const auto createInfo =
                ::vk::CommandPoolCreateInfo()
                    .setQueueFamilyIndex(queueFamilyIndex)
                    .setFlags(
                        ::vk::CommandPoolCreateFlagBits::eResetCommandBuffer);
            const auto result = nativeObject_.createCommandPool(
                &createInfo, nullptr, &commandPool);
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
        }
        const auto& queueCreateInfo = queueCreateInfos[i];
        queues_.Add(this,
            nativeObject_.getQueue(queueFamilyIndex, indexInQueueKindTable[i]),
            queueCreateInfo.Kind(), queueCreateInfo.OperationCountMax(),
            commandPool);
    }

    // GPUメモリが共有メモリか調べる
    {
        const auto mask = ::vk::MemoryPropertyFlagBits::eDeviceLocal |
                          ::vk::MemoryPropertyFlagBits::eHostVisible;
        physicalDevice.getMemoryProperties(&memoryProps_);
        isDeviceLocalMemoryShared_ = false;
        for (uint32_t i = 0; i < memoryProps_.memoryTypeCount; ++i) {
            if ((memoryProps_.memoryTypes[i].propertyFlags & mask) == mask) {
                isDeviceLocalMemoryShared_ = true;
                break;
            }
        }
    }
}

//------------------------------------------------------------------------------
Device::~Device() {
    for (int i = queues_.Count() - 1; 0 <= i; --i) {
        nativeObject_.destroyCommandPool(queues_[i].CommandPool_(), nullptr);
    }
    queues_.Clear();
    nativeObject_.destroy(nullptr);
    nativeObject_ = ::vk::Device();
}

//------------------------------------------------------------------------------
gfx_low::Queue& Device::Queue(const int queueIndex) const {
    return queues_[queueIndex];
}

//------------------------------------------------------------------------------
ResourceMemory Device::AllocResourceMemory(
    const ResourceMemoryAllocInfo& allocInfo) {
    // 0 専用対応
    if (allocInfo.Size() == 0) {
        return ResourceMemory();
    }

    const auto result = TryToAllocResourceMemory(allocInfo);
    AE_BASE_ASSERT(result.IsValid());
    return result;
}

//------------------------------------------------------------------------------
ResourceMemory Device::TryToAllocResourceMemory(
    const ResourceMemoryAllocInfo& allocInfo) {
    // チェック
    AE_BASE_ASSERT(allocInfo.Kind() != ResourceMemoryKind::Invalid);

    // 0 専用対応
    if (allocInfo.Size() == 0) {
        return ResourceMemory();
    }

    // メモリフラグマスクの作成
    const ::vk::Flags<::vk::MemoryPropertyFlagBits> memoryMaskTable[] = {
        ::vk::MemoryPropertyFlagBits(0), // Invalid,
        ::vk::MemoryPropertyFlagBits::eDeviceLocal, // DeviceLocal,
        ::vk::MemoryPropertyFlagBits::eHostVisible |
            ::vk::MemoryPropertyFlagBits::eHostCoherent, // SharedNonCached,
        ::vk::MemoryPropertyFlagBits::eHostVisible |
            ::vk::MemoryPropertyFlagBits::eHostCoherent |
            ::vk::MemoryPropertyFlagBits::eHostCached, // SharedCached
    };
    AE_BASE_ARRAY_LENGTH_CHECK(memoryMaskTable, int(ResourceMemoryKind::TERM));
    const auto memoryMask = memoryMaskTable[int(allocInfo.Kind())];

    // 適切なメモリタイプを探す
    int memoryTypeIndex = -1;
    for (int i = 0; i < int(memoryProps_.memoryTypeCount); ++i) {
        if ((memoryProps_.memoryTypes[i].propertyFlags & memoryMask) ==
            memoryMask) {
            memoryTypeIndex = i;
            break;
        }
    }
    if (memoryTypeIndex < 0) {
        // 確保失敗
        return ResourceMemory();
    }

    // 確保
    ::vk::DeviceMemory memory;
    {
        const auto allocateInfo =
            ::vk::MemoryAllocateInfo()
                .setAllocationSize(allocInfo.Size())
                .setMemoryTypeIndex(uint32_t(memoryTypeIndex));
        if (nativeObject_.allocateMemory(&allocateInfo, nullptr, &memory) !=
            ::vk::Result::eSuccess) {
            // 確保失敗
            return ResourceMemory();
        }
    }
    return ResourceMemory(memory);
}

//------------------------------------------------------------------------------
void Device::FreeResourceMemory(const ResourceMemory& memory) {
    AE_BASE_ASSERT(memory.IsValid());
    nativeObject_.freeMemory(memory.NativeObject_());
}

//------------------------------------------------------------------------------
ResourceMemoryRequirements Device::CalcResourceMemoryRequirements(
    const ImageResourceSpecInfo& specInfo) {
    // Vulkan 環境は VkImage を作成しないと値が取得できないため
    // 一時的に VkImage を作成して求める。
    // 将来的には同じ specInfo が渡された場合は
    // 前回求めた値を返すようにして無駄な VkImage 生成を省略したい。
    // @todo 計算結果のキャッシュ対応

    vk::MemoryRequirements reqs;
    {
        ::vk::Image tmpImage;
        const auto createInfo =
            ImageResourceCreateInfo().SetSpecInfo(specInfo).NativeCreateInfo_();
        auto result =
            nativeObject_.createImage(&createInfo, nullptr, &tmpImage);
        nativeObject_.getImageMemoryRequirements(tmpImage, &reqs);
        nativeObject_.destroyImage(tmpImage, nullptr);
    }

    return ResourceMemoryRequirements()
        .SetSize(reqs.size)
        .SetAlignment(reqs.alignment)
        .SetUsageBitSet(
            EnumUtil::ToResourceMemoryUsageBitSet(specInfo.UsageBitSet()));
}

//------------------------------------------------------------------------------
ResourceMemoryRequirements Device::CalcResourceMemoryRequirements(
    const BufferResourceSpecInfo& specInfo) {
    // Vulkan 環境は VkBuffer を作成しないと値が取得できないため
    // 一時的に VkBuffer を作成して求める。
    // 将来的には同じ specInfo が渡された場合は
    // 前回求めた値を返すようにして無駄な VkBuffer 生成を省略したい。
    // @todo 計算結果のキャッシュ対応

    vk::MemoryRequirements reqs;
    {
        ::vk::Buffer tmpBuffer;
        const auto createInfo =
            BufferResourceCreateInfo().SetSpecInfo(specInfo).NativeCreateInfo_();
        auto result =
            nativeObject_.createBuffer(&createInfo, nullptr, &tmpBuffer);
        nativeObject_.getBufferMemoryRequirements(tmpBuffer, &reqs);
        nativeObject_.destroyBuffer(tmpBuffer, nullptr);
    }

    return ResourceMemoryRequirements()
        .SetSize(reqs.size)
        .SetAlignment(reqs.alignment)
        .SetUsageBitSet(
            EnumUtil::ToResourceMemoryUsageBitSet(specInfo.UsageBitSet()));
}

} // namespace gfx_low
} // namespace ae
// EOF
