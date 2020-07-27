// 文字コード：UTF-8
#include <ae/gfx_low/Device.hpp>

// includes
#include <ae/base/EnumKeyArray.hpp>
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeArray.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/RuntimeMarray.hpp>
#include <ae/gfx_low/DeviceCreateInfo.hpp>
#include <ae/gfx_low/EnumUtil.hpp>
#include <ae/gfx_low/PhysicalDeviceInfo.hpp>
#include <ae/gfx_low/Queue.hpp>
#include <ae/gfx_low/QueueCreateInfo.hpp>
#include <ae/gfx_low/RenderPassBeginInfo.hpp>
#include <ae/gfx_low/RenderTargetImageView.hpp>
#include <ae/gfx_low/RenderTargetSetting.hpp>
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
        ::ae::base::EnumKeyArray<QueueKind, int> queueCounts;
        for (int i = 0; i < createInfo.QueueCreateInfoCount(); ++i) {
            ++queueCounts[createInfo.QueueCrateInfos()[i].Kind()];
        }
        for (int i = 0; i < int(queueCounts.count()); ++i) {
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
        queueCountTable;  // QueueKind ごとの作成総数
    ::ae::base::RuntimeArray<int> indexInQueueKindTable(queueCreateCount,
        &system_
             .InternalTempWorkAllocator());  // 各 Queue が同じ QueueKind
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
        queuePriorityTable[queueKind].resize(
            queueCount, &system_.InternalTempWorkAllocator());
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
            physicalDevice.createDevice(&deviceInfo, nullptr, &device_);
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
            const auto result =
                device_.createCommandPool(&createInfo, nullptr, &commandPool);
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
        }
        const auto& queueCreateInfo = queueCreateInfos[i];
        queues_.add(this,
            device_.getQueue(queueFamilyIndex, indexInQueueKindTable[i]),
            queueCreateInfo.Kind(), queueCreateInfo.OperationCountMax(),
            commandPool);
    }
}

//------------------------------------------------------------------------------
Device::~Device() {
    // Acquire されたリソースの破棄
    for (auto framebuffer : acquiredFramebufferList_) {
        device_.destroyFramebuffer(framebuffer, nullptr);
    }
    acquiredFramebufferList_.clear();
    for (auto renderPass : acquiredRenderPassList_) {
        device_.destroyRenderPass(renderPass, nullptr);
    }
    acquiredRenderPassList_.clear();


    for (int i = queues_.count() - 1; 0 <= i; --i) {
        device_.destroyCommandPool(queues_[i].InternalCommandPool(), nullptr);
    }
    queues_.clear();
    device_.destroy(nullptr);
    device_ = ::vk::Device();
}

//------------------------------------------------------------------------------
gfx_low::Queue& Device::Queue(const int queueIndex) const {
    return queues_[queueIndex];
}

//------------------------------------------------------------------------------
::vk::RenderPass Device::InternalAcquireRenderPass(
    const RenderPassBeginInfo& beginInfo)
{
    // @todo スレッドセーフ対応
    // @todo キャッシュ対応

    std::array<::vk::AttachmentDescription, InternalSupportedAttachmentCountMax>
        attachments;
    for (int i = 0; i < beginInfo.RenderPassSpecInfo().RenderTargetCount();
         ++i) {
        const auto& renderTargetSpec = beginInfo.RenderPassSpecInfo().RenderTargetSpecInfos()[i];
        const auto& renderTargetSetting = beginInfo.RenderTargetSettings()[i];
        auto& attachment = attachments[i];

        // @todo 普通の Format での指定
        AE_BASE_ASSERT(renderTargetSpec.InternalNativeFormat() !=
                       ::vk::Format::eUndefined);
        attachment.setFormat(renderTargetSpec.InternalNativeFormat());

        // その他の設定
        attachment.setSamples(::vk::SampleCountFlagBits::e1)
            .setLoadOp(EnumUtil::ToNative(renderTargetSetting.LoadOp()))
            .setStoreOp(EnumUtil::ToNative(renderTargetSetting.StoreOp()))
            .setStencilLoadOp(vk::AttachmentLoadOp::eDontCare)
            .setStencilStoreOp(vk::AttachmentStoreOp::eDontCare)
            .setInitialLayout(EnumUtil::ToImageLayoutForColorAttachment(renderTargetSetting.InitialImageResourceState()))
            .setFinalLayout(EnumUtil::ToImageLayoutForColorAttachment(renderTargetSetting.FinalImageResourceState()));
    }

    auto const colorReference =
        vk::AttachmentReference().setAttachment(0).setLayout(
            vk::ImageLayout::eColorAttachmentOptimal);

    auto const subpass =
        vk::SubpassDescription()
            .setPipelineBindPoint(vk::PipelineBindPoint::eGraphics)
            .setInputAttachmentCount(0)
            .setPInputAttachments(nullptr)
            .setColorAttachmentCount(1)
            .setPColorAttachments(&colorReference)
            .setPResolveAttachments(nullptr)
            .setPDepthStencilAttachment(nullptr)
            .setPreserveAttachmentCount(0)
            .setPPreserveAttachments(nullptr);

    vk::PipelineStageFlags stages =
        vk::PipelineStageFlagBits::eEarlyFragmentTests |
        vk::PipelineStageFlagBits::eLateFragmentTests;
    vk::SubpassDependency const dependencies[1] = {
        vk::SubpassDependency()  // Image layout transition
            .setSrcSubpass(VK_SUBPASS_EXTERNAL)
            .setDstSubpass(0)
            .setSrcStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput)
            .setDstStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput)
            .setSrcAccessMask(vk::AccessFlagBits())
            .setDstAccessMask(vk::AccessFlagBits::eColorAttachmentWrite |
                              vk::AccessFlagBits::eColorAttachmentRead)
            .setDependencyFlags(vk::DependencyFlags()),
    };

    auto const renderPassCreateInfo = vk::RenderPassCreateInfo()
                             .setAttachmentCount(1)
                             .setPAttachments(&attachments[0])
                             .setSubpassCount(1)
                             .setPSubpasses(&subpass)
                             .setDependencyCount(1)
                             .setPDependencies(dependencies);

    ::vk::RenderPass renderPass;
    {
        const auto result = device_.createRenderPass(
            &renderPassCreateInfo, nullptr, &renderPass);
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }
    acquiredRenderPassList_.push_back(renderPass);
    return renderPass;
}

//------------------------------------------------------------------------------
::vk::Framebuffer Device::InternalAcquireFramebuffer(
    const RenderPassBeginInfo& beginInfo) {
    // @todo スレッドセーフ対応
    // @todo キャッシュ対応

    std::array<::vk::ImageView, InternalSupportedAttachmentCountMax> imageViews;
    for (int i = 0; i < beginInfo.RenderPassSpecInfo().RenderTargetCount();
         ++i) {
        imageViews[i] = beginInfo.RenderTargetSettings()[i]
                            .RenderTargetImageView()
                            ->InternalInstance();
    }

    auto const createInfo =
        vk::FramebufferCreateInfo()
            .setRenderPass(InternalAcquireRenderPass(beginInfo))
            .setAttachmentCount(1)
            .setPAttachments(&imageViews[0])
            .setWidth(uint32_t(beginInfo.RenderArea().width()))
            .setHeight(uint32_t(beginInfo.RenderArea().height()))
            .setLayers(1);
    ::vk::Framebuffer framebuffer;
    {
        const auto result = device_.createFramebuffer(
            &createInfo, nullptr, &framebuffer);
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }
    acquiredFramebufferList_.push_back(framebuffer);
    return framebuffer;
}

}  // namespace gfx_low
}  // namespace ae
// EOF
