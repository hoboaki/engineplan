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
#include <ae/gfx_low/ImageSubresourceDataInfo.hpp>
#include <ae/gfx_low/ImageSubresourceLocation.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/PhysicalDeviceInfo.hpp>
#include <ae/gfx_low/Queue.hpp>
#include <ae/gfx_low/QueueCreateInfo.hpp>
#include <ae/gfx_low/ResourceMemory.hpp>
#include <ae/gfx_low/ResourceMemoryAllocInfo.hpp>
#include <ae/gfx_low/ResourceMemoryRegion.hpp>
#include <ae/gfx_low/ResourceMemoryRequirements.hpp>
#include <ae/gfx_low/ShaderModuleResourceSpecInfo.hpp>
#include <ae/gfx_low/System.hpp>
#include <array>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
Device::Device(const DeviceCreateInfo& createInfo)
: system_(::ae::base::PtrToRef(createInfo.System()))
, nativeObject_()
, physicalDeviceIndex_(createInfo.PhysicalDeviceIndex())
, queues_(
      createInfo.QueueCreateInfoCount(),
      &::ae::base::PtrToRef(createInfo.System()).ObjectAllocator_())
{
    const auto physicalDeviceIndex = createInfo.PhysicalDeviceIndex();
    AE_BASE_ASSERT_MIN_TERM(
        physicalDeviceIndex,
        0,
        system_.PhysicalDeviceCount());
    const auto& physicalDevice = system_.PhysicalDevice_(physicalDeviceIndex);
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

    // 使用できる機能は全て有効化
    auto features = physicalDevice.getFeatures2();

    // 各 QueueKind の作成総数とIndex表を作成
    ::ae::base::EnumKeyArray<QueueKind, int>
        queueCountTable; // QueueKind ごとの作成総数
    ::ae::base::RuntimeArray<int> indexInQueueKindTable(
        queueCreateCount,
        &system_
             .TempWorkAllocator_()); // 各 Queue が同じ QueueKind における何個目の Queue かの情報
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
            queueCount,
            &system_.TempWorkAllocator_());
    }
    const float priorityTable[int(QueuePriority::TERM)] = {
        -1.0f,
        0.0f,
        0.5f,
        1.0f
    };
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
    uint32_t enabledExtensionCount = 0;
    const int extensionCountMax = 64;
    const char* extensionNames[extensionCountMax] = {};
    const char* const findExtensionNames[] = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
#if defined(VK_USE_PLATFORM_METAL_EXT)
        VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,
#endif
    };
    bool foundExtensions[AE_BASE_ARRAY_LENGTH(findExtensionNames)] = {};
    {
        uint32_t deviceExtensionCount = 0;
        auto result = physicalDevice.enumerateDeviceExtensionProperties(
            nullptr,
            &deviceExtensionCount,
            static_cast<vk::ExtensionProperties*>(nullptr));
        AE_BASE_ASSERT(result == vk::Result::eSuccess);

        if (0 < deviceExtensionCount) {
            base::RuntimeArray<::vk::ExtensionProperties> deviceExtensions(
                int(deviceExtensionCount),
                &system_.TempWorkAllocator_());
            result = physicalDevice.enumerateDeviceExtensionProperties(
                nullptr,
                &deviceExtensionCount,
                deviceExtensions.Head());
            AE_BASE_ASSERT(result == vk::Result::eSuccess);

            for (uint32_t i = 0; i < deviceExtensionCount; i++) {
                for (int findExtIdx = 0;
                     findExtIdx < AE_BASE_ARRAY_LENGTH(findExtensionNames);
                     ++findExtIdx) {
                    if (!std::strcmp(
                            findExtensionNames[findExtIdx],
                            deviceExtensions[i].extensionName)) {
                        foundExtensions[findExtIdx] = true;
                        extensionNames[enabledExtensionCount++] =
                            findExtensionNames[findExtIdx];
                    }
                }
            }
        }

        for (int findExtIdx = 0;
             findExtIdx < AE_BASE_ARRAY_LENGTH(findExtensionNames);
             ++findExtIdx) {
            if (!foundExtensions[findExtIdx]) {
                AE_BASE_ASSERT_NOT_REACHED_MSGFMT(
                    "vkEnumerateDeviceExtensionProperties failed to find "
                    "the %s"
                    " extension.\n\n"
                    "Do you have a compatible Vulkan installable client driver "
                    "(ICD) "
                    "installed?\n"
                    "Please look at the Getting Started guide for additional "
                    "information.\n",
                    findExtensionNames[findExtIdx]);
            }
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
                          .setPEnabledFeatures(nullptr)
                          .setPNext(&features);
    {
        auto result =
            physicalDevice.createDevice(&deviceInfo, nullptr, &nativeObject_);
        AE_BASE_ASSERT(result == vk::Result::eSuccess);
#if VULKAN_HPP_DISPATCH_LOADER_DYNAMIC == 1
        VULKAN_HPP_DEFAULT_DISPATCHER.init(nativeObject_);
#endif
    }

    // Queue オブジェクト作成
    for (int i = 0; i < queueCreateCount; ++i) {
        const auto queueFamilyIndex =
            deviceQueueCreateInfos[i].queueFamilyIndex;
        const auto& queueCreateInfo = queueCreateInfos[i];
        queues_.Add(
            this,
            nativeObject_.getQueue(queueFamilyIndex, indexInQueueKindTable[i]),
            queueCreateInfo.Kind(),
            queueFamilyIndex,
            queueCreateInfo.OperationCountMax());
    }

    // メモリプロパティを記録
    physicalDevice.getMemoryProperties(&memoryProps_);

    // GPUメモリが共有メモリか調べる
    {
        const auto mask = ::vk::MemoryPropertyFlagBits::eDeviceLocal |
                          ::vk::MemoryPropertyFlagBits::eHostVisible |
                          ::vk::MemoryPropertyFlagBits::eHostCached;
        isDeviceLocalMemoryShared_ = false;
        for (uint32_t i = 0; i < memoryProps_.memoryTypeCount; ++i) {
            if ((memoryProps_.memoryTypes[i].propertyFlags & mask) == mask) {
                isDeviceLocalMemoryShared_ = true;
                break;
            }
        }
    }

    // DeviceLocal で Optimal な MemoryType 番号をメモする
    {
        // ダミーのImageを作って　MemoryType 情報を取得
        vk::MemoryRequirements reqs;
        {
            ::vk::Image tmpImage;
            const auto createInfo =
                ImageResourceCreateInfo()
                    .SetSpecInfo(
                        ImageResourceSpecInfo()
                            .SetKind(ImageResourceKind::Image2d)
                            .SetFormat(ImageFormat::D32Sfloat)
                            .SetExtent(base::Extent2i(16, 16))
                            .SetTiling(ImageResourceTiling::Optimal)
                            .SetUsageBitSet(ImageResourceUsageBitSet().On(
                                ImageResourceUsage::DepthStencilImage)))
                    .NativeCreateInfo_();
            [[maybe_unused]] auto result =
                nativeObject_.createImage(&createInfo, nullptr, &tmpImage);
            nativeObject_.getImageMemoryRequirements(tmpImage, &reqs);
            nativeObject_.destroyImage(tmpImage, nullptr);
        }

        // 該当する番号をメモ
        const auto mask = ::vk::MemoryPropertyFlagBits::eDeviceLocal;
        for (uint32_t i = 0; i < memoryProps_.memoryTypeCount; ++i) {
            if ((memoryProps_.memoryTypes[i].propertyFlags & mask) == mask &&
                (reqs.memoryTypeBits & (1 << i)) != 0) {
                deviceLocalOptimalImageMemoryTypeIndex_ = i;
                break;
            }
        }
        AE_BASE_ASSERT_LESS_EQUALS(0, deviceLocalOptimalImageMemoryTypeIndex_);
    }
}

//------------------------------------------------------------------------------
Device::~Device()
{
    queues_.Clear();
    nativeObject_.destroy(nullptr);
    nativeObject_ = ::vk::Device();
}

//------------------------------------------------------------------------------
gfx_low::Queue& Device::Queue(const int queueIndex) const
{
    return queues_[queueIndex];
}

//------------------------------------------------------------------------------
ResourceMemory Device::AllocResourceMemory(
    const ResourceMemoryAllocInfo& allocInfo)
{
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
    const ResourceMemoryAllocInfo& allocInfo)
{
    // チェック
    AE_BASE_ASSERT(allocInfo.Kind() != ResourceMemoryKind::Invalid);

    // 0 専用対応
    if (allocInfo.Size() == 0) {
        return ResourceMemory();
    }

    // CompiledShaderModule 用処理
    if (allocInfo.UsageBitSet().Get(
            ResourceMemoryUsage::CompiledShaderModule)) {
        // CompiledShaderModule 以外のフラグがたっていないことを確認
        AE_BASE_ASSERT(
            ResourceMemoryUsageBitSet(allocInfo.UsageBitSet())
                .Set(ResourceMemoryUsage::CompiledShaderModule, false)
                .IsAllOff());

        // CPU用のメモリを確保して返す
        return ResourceMemory(
            system_.ObjectAllocator_().Alloc(allocInfo.Size()));
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
    if (allocInfo.Kind() == ResourceMemoryKind::DeviceLocal &&
        allocInfo.UsageBitSet().Get(ResourceMemoryUsage::OptimalTilingImage)) {
        memoryTypeIndex = deviceLocalOptimalImageMemoryTypeIndex_;
    }
    if (memoryTypeIndex < 0) {
        for (int i = 0; i < int(memoryProps_.memoryTypeCount); ++i) {
            if ((memoryProps_.memoryTypes[i].propertyFlags & memoryMask) ==
                memoryMask) {
                memoryTypeIndex = i;
                break;
            }
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
void Device::FreeResourceMemory(const ResourceMemory& memory)
{
    AE_BASE_ASSERT(memory.IsValid());
    if (memory.Head_() != nullptr) {
        system_.ObjectAllocator_().Free(memory.Head_());
        return;
    }
    nativeObject_.freeMemory(memory.NativeObject_());
}

//------------------------------------------------------------------------------
ResourceMemoryRequirements Device::CalcResourceMemoryRequirements(
    const ImageResourceSpecInfo& specInfo) const
{
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
        [[maybe_unused]] auto result =
            nativeObject_.createImage(&createInfo, nullptr, &tmpImage);
        nativeObject_.getImageMemoryRequirements(tmpImage, &reqs);
        nativeObject_.destroyImage(tmpImage, nullptr);
    }

    return ResourceMemoryRequirements()
        .SetSize(reqs.size)
        .SetAlignment(reqs.alignment)
        .SetUsageBitSet(
            EnumUtil::ToResourceMemoryUsageBitSet(specInfo.UsageBitSet())
                .Set(
                    ResourceMemoryUsage::OptimalTilingImage,
                    specInfo.Tiling() == ImageResourceTiling::Optimal));
}

//------------------------------------------------------------------------------
ResourceMemoryRequirements Device::CalcResourceMemoryRequirements(
    const BufferResourceSpecInfo& specInfo) const
{
    // Vulkan 環境は VkBuffer を作成しないと値が取得できないため
    // 一時的に VkBuffer を作成して求める。
    // 将来的には同じ specInfo が渡された場合は
    // 前回求めた値を返すようにして無駄な VkBuffer 生成を省略したい。
    // @todo 計算結果のキャッシュ対応

    vk::MemoryRequirements reqs;
    {
        ::vk::Buffer tmpBuffer;
        const auto createInfo = BufferResourceCreateInfo()
                                    .SetSpecInfo(specInfo)
                                    .NativeCreateInfo_();
        [[maybe_unused]] auto result =
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

//------------------------------------------------------------------------------
ResourceMemoryRequirements Device::CalcResourceMemoryRequirements(
    const ShaderModuleResourceSpecInfo& specInfo) const
{
    return ResourceMemoryRequirements()
        .SetSize(specInfo.Size())
        .SetAlignment(sizeof(size_t))
        .SetUsageBitSet(ResourceMemoryUsageBitSet().Set(
            ResourceMemoryUsage::CompiledShaderModule,
            true));
}

//------------------------------------------------------------------------------
uint8_t* Device::MapResourceMemory(
    const ResourceMemory& resourceMemory,
    const ResourceMemoryRegion& region)
{
    AE_BASE_ASSERT(resourceMemory.IsValid());
    // CompiledShaderModule 用処理
    if (resourceMemory.Head_() != nullptr) {
        return resourceMemory.Head_();
    }

    const auto result = nativeObject_.mapMemory(
        resourceMemory.NativeObject_(),
        region.Offset(),
        region.Size());
    AE_BASE_ASSERT(result.result == ::vk::Result::eSuccess);
    return static_cast<uint8_t*>(result.value);
}

//------------------------------------------------------------------------------
void Device::UnmapResourceMemory(const ResourceMemory& resourceMemory)
{
    // CompiledShaderModule 用処理
    if (resourceMemory.Head_() != nullptr) {
        return;
    }

    nativeObject_.unmapMemory(resourceMemory.NativeObject_());
}

//------------------------------------------------------------------------------
ImageSubresourceDataInfo Device::CalcImageSubresourceDataInfo(
    const ImageResourceSpecInfo& specInfo,
    const ImageSubresourceLocation& location) const
{
    // Vulkan 環境は VkImage を作成しないと値が取得できないため
    // 一時的に VkImage を作成して求める。
    // 将来的には同じ specInfo が渡された場合は
    // 前回求めた値を返すようにして無駄な VkImage 生成を省略したい。
    // @todo 計算結果のキャッシュ対応

    ::vk::SubresourceLayout layout;
    {
        ::vk::Image tmpImage;
        const auto createInfo =
            ImageResourceCreateInfo().SetSpecInfo(specInfo).NativeCreateInfo_();
        [[maybe_unused]] auto result =
            nativeObject_.createImage(&createInfo, nullptr, &tmpImage);

        const int layerCountPerArrayIndex =
            specInfo.Kind() == ImageResourceKind::ImageCube ? 6 : 1;
        const auto subres =
            ::vk::ImageSubresource()
                .setAspectMask(vk::ImageAspectFlagBits::eColor)
                .setMipLevel(location.MipLevel())
                .setArrayLayer(
                    location.FaceIndex() +
                    location.ArrayIndex() * layerCountPerArrayIndex);

        nativeObject_.getImageSubresourceLayout(tmpImage, &subres, &layout);
        nativeObject_.destroyImage(tmpImage, nullptr);
    }

    return ImageSubresourceDataInfo(
        layout.offset,
        layout.rowPitch,
        layout.depthPitch);
}

} // namespace ae::gfx_low
// EOF
