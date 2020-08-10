// 文字コード：UTF-8
#include <ae/gfx_low/RenderPipeline.hpp>

// includes
#include <ae/base/ArrayLength.hpp>
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/DepthStencilSpecInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/RenderPipelineCreateInfo.hpp>
#include <ae/gfx_low/RenderTargetBlendInfo.hpp>
#include <ae/gfx_low/RenderTargetSpecInfo.hpp>
#include <ae/gfx_low/ShaderBindingInfo.hpp>
#include <ae/gfx_low/ShaderModuleResource.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
RenderPipeline::RenderPipeline(const RenderPipelineCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, descriptorSetLayouts_()
, pipelineLayout_()
, nativeObject_() {
    // RenderPass(Spec)
    {
        AE_BASE_ASSERT_LESS_EQUALS(
            createInfo.RenderPassSpecInfo().RenderTargetCount(),
            Device::SupportedRenderTargetCountMax_);
        const auto specInfo = createInfo.RenderPassSpecInfo();
        const bool hasDepthStencil =
            specInfo.DepthStencilSpecInfoPtr() != nullptr;
        const int attachmentsCount =
            specInfo.RenderTargetCount() + (hasDepthStencil ? 1 : 0);
        const int depthStencilIdx = hasDepthStencil ? attachmentsCount - 1 : -1;

        std::array<::vk::AttachmentDescription,
            Device::SupportedAttachmentCountMax_>
            attachments;
        std::array<::vk::AttachmentReference,
            Device::SupportedAttachmentCountMax_>
            attachmentRefs;
        for (int i = 0; i < specInfo.RenderTargetCount(); ++i) {
            const auto& spec = specInfo.RenderTargetSpecInfos()[i];
            auto& attachment = attachments[i];
            auto& attachmentRef = attachmentRefs[i];

            const auto format =
                spec.NativeFormat_() != ::vk::Format::eUndefined
                    ? spec.NativeFormat_()
                    : InternalEnumUtil::ToFormat(spec.ImageFormat());

            attachment.setFormat(format)
                .setSamples(::vk::SampleCountFlagBits::e1)
                .setLoadOp(::vk::AttachmentLoadOp::eDontCare)
                .setStoreOp(::vk::AttachmentStoreOp::eDontCare)
                .setStencilLoadOp(::vk::AttachmentLoadOp::eDontCare)
                .setStencilStoreOp(::vk::AttachmentStoreOp::eDontCare)
                .setInitialLayout(::vk::ImageLayout::eUndefined)
                .setFinalLayout(::vk::ImageLayout::eColorAttachmentOptimal);
            attachmentRef.setAttachment(i).setLayout(
                ::vk::ImageLayout::eColorAttachmentOptimal);
        }
        if (hasDepthStencil) {
            const auto& spec =
                base::PtrToRef(specInfo.DepthStencilSpecInfoPtr());
            auto& attachment = attachments[depthStencilIdx];
            auto& attachmentRef = attachmentRefs[depthStencilIdx];
            attachment.setFormat(InternalEnumUtil::ToFormat(spec.ImageFormat()))
                .setSamples(::vk::SampleCountFlagBits::e1)
                .setLoadOp(::vk::AttachmentLoadOp::eDontCare)
                .setStoreOp(::vk::AttachmentStoreOp::eDontCare)
                .setStencilLoadOp(::vk::AttachmentLoadOp::eDontCare)
                .setStencilStoreOp(::vk::AttachmentStoreOp::eDontCare)
                .setInitialLayout(::vk::ImageLayout::eUndefined)
                .setFinalLayout(
                    ::vk::ImageLayout::eDepthStencilAttachmentOptimal);
            attachmentRef.setAttachment(depthStencilIdx)
                .setLayout(::vk::ImageLayout::eDepthStencilAttachmentOptimal);
        }

        auto const subpass =
            vk::SubpassDescription()
                .setPipelineBindPoint(vk::PipelineBindPoint::eGraphics)
                .setInputAttachmentCount(0)
                .setPInputAttachments(nullptr)
                .setColorAttachmentCount(specInfo.RenderTargetCount())
                .setPColorAttachments(&attachmentRefs[0])
                .setPResolveAttachments(nullptr)
                .setPDepthStencilAttachment(
                    hasDepthStencil ? &attachmentRefs[depthStencilIdx]
                                    : nullptr)
                .setPreserveAttachmentCount(0)
                .setPPreserveAttachments(nullptr);

        std::array<::vk::SubpassDependency, 2> dependencies;
        if (hasDepthStencil) {
            const ::vk::PipelineStageFlags stages =
                ::vk::PipelineStageFlagBits::eEarlyFragmentTests |
                ::vk::PipelineStageFlagBits::eLateFragmentTests;
            dependencies[0] =
                ::vk::SubpassDependency()
                    .setSrcSubpass(VK_SUBPASS_EXTERNAL)
                    .setDstSubpass(0)
                    .setSrcStageMask(stages)
                    .setDstStageMask(stages)
                    .setSrcAccessMask(
                        vk::AccessFlagBits::eDepthStencilAttachmentWrite)
                    .setDstAccessMask(
                        vk::AccessFlagBits::eDepthStencilAttachmentRead |
                        vk::AccessFlagBits::eDepthStencilAttachmentWrite)
                    .setDependencyFlags(vk::DependencyFlags());
        }
        dependencies[hasDepthStencil ? 1 : 0] =
            ::vk::SubpassDependency()
                .setSrcSubpass(VK_SUBPASS_EXTERNAL)
                .setDstSubpass(0)
                .setSrcStageMask(
                    vk::PipelineStageFlagBits::eColorAttachmentOutput)
                .setDstStageMask(
                    vk::PipelineStageFlagBits::eColorAttachmentOutput)
                .setSrcAccessMask(vk::AccessFlagBits())
                .setDstAccessMask(vk::AccessFlagBits::eColorAttachmentWrite |
                                  vk::AccessFlagBits::eColorAttachmentRead)
                .setDependencyFlags(vk::DependencyFlags());

        const auto renderPassCreateInfo =
            vk::RenderPassCreateInfo()
                .setAttachmentCount(attachmentsCount)
                .setPAttachments(&attachments[0])
                .setSubpassCount(1)
                .setPSubpasses(&subpass)
                .setDependencyCount(hasDepthStencil ? 2 : 1)
                .setPDependencies(&dependencies[0]);
        {
            const auto result = device_.NativeObject_().createRenderPass(
                &renderPassCreateInfo, nullptr, &renderPass_);
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
        }
    }

    // DescriptorSetLayout
    {
        // Buffer, Image, Sampler の順番で DescriptorSet 番号を確保する。
        // Buffer は UniformBuffer StorageBuffer の順番で Binding
        // 番号を確保する。 Texture は SampledImage、StorageImage の順番で
        // Binding 番号を確保する。

        // 各 DescriptorSetLayou 内でこの数まで binding を記述できる。
        // スタック上に確保することで new/delete オーバーヘッドをなくす。
        constexpr int bindingsCountMax = 64;
        int bindingsCount = 0;
        std::array<::vk::DescriptorSetLayoutBinding, bindingsCountMax> bindings;
        const auto info = createInfo.DescriptorSetSpecInfo();

        // 汎用的な確保関数
        auto addBinding = [bindingsCountMax](int& bindingsCount,
                              ::vk::DescriptorSetLayoutBinding* bindingsPtr,
                              const int bindingInfosIdx,
                              const ShaderBindingInfo* bindingInfosPtr,
                              const ::vk::DescriptorType descriptorType) {
            AE_BASE_ASSERT_LESS(bindingsCount, bindingsCountMax);
            const auto& info =
                base::PtrToRef(&bindingInfosPtr[bindingInfosIdx]);
            bindingsPtr[bindingsCount] =
                ::vk::DescriptorSetLayoutBinding()
                    .setBinding(info.BindingIndex())
                    .setDescriptorType(descriptorType)
                    .setDescriptorCount(info.BindingCount())
                    .setStageFlags(
                        InternalEnumUtil::ToShaderStageFlags(info.Stages()))
                    .setPImmutableSamplers(nullptr);
            ++bindingsCount;
        };
        auto addSetLayout =
            [](gfx_low::Device& device, int& layoutsCount,
                ::vk::DescriptorSetLayout* layoutsPtr, int& bindingsCount,
                const ::vk::DescriptorSetLayoutBinding* bindingsPtr) {
                AE_BASE_ASSERT_LESS(
                    layoutsCount, DescriptorSetLayoutsCountMax_);

                const auto info = ::vk::DescriptorSetLayoutCreateInfo()
                                      .setBindingCount(bindingsCount)
                                      .setPBindings(bindingsPtr);
                const auto result =
                    device.NativeObject_().createDescriptorSetLayout(
                        &info, nullptr, &layoutsPtr[layoutsCount]);
                AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
                ++layoutsCount;
                bindingsCount = 0;
            };

        // Buffer
        if (0 < info.UniformBufferCount() || 0 < info.StorageBufferCount()) {
            // UniformBuffer
            for (int i = 0; i < info.UniformBufferCount(); ++i) {
                addBinding(bindingsCount, &bindings[0], i,
                    info.UniformBufferBindingInfos(),
                    ::vk::DescriptorType::eUniformBuffer);
            }

            // StorageBuffer
            for (int i = 0; i < info.StorageBufferCount(); ++i) {
                addBinding(bindingsCount, &bindings[0], i,
                    info.StorageBufferBindingInfos(),
                    ::vk::DescriptorType::eStorageBuffer);
            }

            // 作成
            addSetLayout(device_, descriptorSetLayoutsCount_,
                &descriptorSetLayouts_[0], bindingsCount, &bindings[0]);
        }

        // Image
        if (0 < info.SampledImageCount() || 0 < info.StorageImageCount()) {
            // SampledImage
            for (int i = 0; i < info.SampledImageCount(); ++i) {
                addBinding(bindingsCount, &bindings[0], i,
                    info.SampledImageBindingInfos(),
                    ::vk::DescriptorType::eSampledImage);
            }

            // StorageImage
            for (int i = 0; i < info.StorageImageCount(); ++i) {
                addBinding(bindingsCount, &bindings[0], i,
                    info.StorageImageBindingInfos(),
                    ::vk::DescriptorType::eStorageImage);
            }

            // 作成
            addSetLayout(device_, descriptorSetLayoutsCount_,
                &descriptorSetLayouts_[0], bindingsCount, &bindings[0]);
        }

        // Sampler
        if (0 < info.SamplerCount()) {
            for (int i = 0; i < info.SamplerCount(); ++i) {
                addBinding(bindingsCount, &bindings[0], i,
                    info.SamplerBindingInfos(), ::vk::DescriptorType::eSampler);
            }

            // 作成
            addSetLayout(device_, descriptorSetLayoutsCount_,
                &descriptorSetLayouts_[0], bindingsCount, &bindings[0]);
        }
    }

    // PipelineLayout
    {
        AE_BASE_ASSERT_LESS(0, descriptorSetLayoutsCount_);
        const auto pipelineLayoutCreateInfo =
            ::vk::PipelineLayoutCreateInfo()
                .setSetLayoutCount(descriptorSetLayoutsCount_)
                .setPSetLayouts(&descriptorSetLayouts_[0]);

        const auto result = device_.NativeObject_().createPipelineLayout(
            &pipelineLayoutCreateInfo, nullptr, &pipelineLayout_);
        AE_BASE_ASSERT(result == vk::Result::eSuccess);
    }

    // Pipeline
    {
        std::array<::vk::PipelineShaderStageCreateInfo,
            int(RenderPipelineShaderStage::TERM)>
            shaderStageInfos;
        int shaderStageInfosCount = 0;
        for (int i = int(RenderPipelineShaderStage::Invalid) + 1;
             i < int(RenderPipelineShaderStage::TERM); ++i) {
            const auto stage = RenderPipelineShaderStage(i);
            const auto shaderInfo = createInfo.ShaderInfo(stage);
            const auto* resourcePtr = shaderInfo.Resource();
            if (resourcePtr == nullptr) {
                continue;
            }
            shaderStageInfos[shaderStageInfosCount] =
                ::vk::PipelineShaderStageCreateInfo()
                    .setStage(InternalEnumUtil::ToShaderStageFlagBits(stage))
                    .setModule(base::PtrToRef(resourcePtr).NativeObject_())
                    .setPName(shaderInfo.EntryPointNamePtr());
            ++shaderStageInfosCount;
        }

        const ::vk::PipelineVertexInputStateCreateInfo vertexInputInfo;

        const auto inputAssemblyInfo =
            ::vk::PipelineInputAssemblyStateCreateInfo().setTopology(
                InternalEnumUtil::ToPrimitiveTopology(
                    createInfo.PrimitiveTopologyKind()));

        const auto viewportInfo = vk::PipelineViewportStateCreateInfo()
                                      .setViewportCount(1)
                                      .setScissorCount(1);

        const auto rasterizationInfo =
            ::vk::PipelineRasterizationStateCreateInfo()
                .setDepthClampEnable(VK_FALSE)
                .setRasterizerDiscardEnable(VK_FALSE)
                .setPolygonMode(InternalEnumUtil::ToPolygonMode(
                    createInfo.RasterizerInfo().FillMode()))
                .setCullMode(InternalEnumUtil::ToCullModeFlags(
                    createInfo.RasterizerInfo().CullMode()))
                .setFrontFace(InternalEnumUtil::ToFrontFace(
                    createInfo.RasterizerInfo().FrontFace()))
                .setDepthBiasEnable(VK_FALSE)
                .setLineWidth(1.0f);

        const auto multisampleInfo = ::vk::PipelineMultisampleStateCreateInfo();

        auto toStencilOpState =
            [](const PipelineDepthStencilInfo& depthStencilInfo,
                const StencilOpInfo& stencilOpInfo) {
                return ::vk::StencilOpState()
                    .setFailOp(
                        InternalEnumUtil::ToStencilOp(stencilOpInfo.FailOp()))
                    .setDepthFailOp(InternalEnumUtil::ToStencilOp(
                        stencilOpInfo.DepthFailOp()))
                    .setPassOp(
                        InternalEnumUtil::ToStencilOp(stencilOpInfo.PassOp()))
                    .setCompareOp(InternalEnumUtil::ToCompareOp(
                        stencilOpInfo.CompareOp()))
                    .setCompareMask(depthStencilInfo.StencilReadMask())
                    .setWriteMask(depthStencilInfo.StencilWriteMask())
                    .setReference(depthStencilInfo.StencilReference());
            };

        const auto depthStencilInfo =
            ::vk::PipelineDepthStencilStateCreateInfo()
                .setDepthTestEnable(
                    createInfo.DepthStencilInfo().DepthTestEnable() ? VK_TRUE
                                                                    : VK_FALSE)
                .setDepthWriteEnable(
                    createInfo.DepthStencilInfo().DepthWriteEnable() ? VK_TRUE
                                                                     : VK_FALSE)
                .setDepthCompareOp(InternalEnumUtil::ToCompareOp(
                    createInfo.DepthStencilInfo().DepthCompareOp()))
                .setDepthBoundsTestEnable(VK_FALSE)
                .setStencilTestEnable(
                    createInfo.DepthStencilInfo().StencilTestEnable()
                        ? VK_TRUE
                        : VK_FALSE)
                .setFront(toStencilOpState(createInfo.DepthStencilInfo(),
                    createInfo.DepthStencilInfo().FrontFaceStencilOpInfo()))
                .setBack((toStencilOpState(createInfo.DepthStencilInfo(),
                    createInfo.DepthStencilInfo().BackFaceStencilOpInfo())));

        std::array<::vk::PipelineColorBlendAttachmentState,
            Device::SupportedAttachmentCountMax_>
            colorBlendAttachments;
        for (int i = 0; i < createInfo.RenderPassSpecInfo().RenderTargetCount();
             ++i) {
            const auto& info = base::PtrToRef(
                &createInfo.BlendInfo().RenderTargetBlendInfos()[i]);
            colorBlendAttachments[i] =
                ::vk::PipelineColorBlendAttachmentState()
                    .setBlendEnable(info.BlendOpEnable() ? VK_TRUE : VK_FALSE)
                    .setSrcColorBlendFactor(
                        InternalEnumUtil::ToBlendFactorForColor(
                            info.SrcColorBlendFactor()))
                    .setDstColorBlendFactor(
                        InternalEnumUtil::ToBlendFactorForColor(
                            info.DstColorBlendFactor()))
                    .setColorBlendOp(
                        InternalEnumUtil::ToBlendOp(info.ColorBlendOp()))
                    .setSrcAlphaBlendFactor(
                        InternalEnumUtil::ToBlendFactorForAlpha(
                            info.SrcAlphaBlendFactor()))
                    .setDstAlphaBlendFactor(
                        InternalEnumUtil::ToBlendFactorForAlpha(
                            info.DstAlphaBlendFactor()))
                    .setAlphaBlendOp(
                        InternalEnumUtil::ToBlendOp(info.AlphaBlendOp()))
                    .setColorWriteMask(InternalEnumUtil::ToColorComponentFlags(
                        info.WriteMask()));
        }

        const auto colorBlendInfo =
            ::vk::PipelineColorBlendStateCreateInfo()
                .setAttachmentCount(
                    createInfo.RenderPassSpecInfo().RenderTargetCount())
                .setPAttachments(&colorBlendAttachments[0]);

        const ::vk::DynamicState dynamicStates[] = {
            ::vk::DynamicState::eViewport, ::vk::DynamicState::eScissor};

        const auto dynamicStateInfo =
            ::vk::PipelineDynamicStateCreateInfo()
                .setPDynamicStates(dynamicStates)
                .setDynamicStateCount(AE_BASE_ARRAY_LENGTH(dynamicStates));

        const auto nativeCreateInfo =
            ::vk::GraphicsPipelineCreateInfo()
                .setStageCount(shaderStageInfosCount)
                .setPStages(&shaderStageInfos[0])
                .setPVertexInputState(&vertexInputInfo)
                .setPInputAssemblyState(&inputAssemblyInfo)
                .setPViewportState(&viewportInfo)
                .setPRasterizationState(&rasterizationInfo)
                .setPMultisampleState(&multisampleInfo)
                .setPDepthStencilState(&depthStencilInfo)
                .setPColorBlendState(&colorBlendInfo)
                .setPDynamicState(&dynamicStateInfo)
                .setLayout(pipelineLayout_)
                .setRenderPass(renderPass_);

        {
            const auto result = device_.NativeObject_().createGraphicsPipelines(
                nullptr, 1, &nativeCreateInfo, nullptr, &nativeObject_);
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
        }
    }
}

//------------------------------------------------------------------------------
RenderPipeline::~RenderPipeline() {
    device_.NativeObject_().destroyPipeline(nativeObject_, nullptr);
    nativeObject_ = ::vk::Pipeline();
    device_.NativeObject_().destroyPipelineLayout(pipelineLayout_, nullptr);
    pipelineLayout_ = ::vk::PipelineLayout();
    for (int i = descriptorSetLayoutsCount_ - 1; 0 <= i; --i) {
        device_.NativeObject_().destroyDescriptorSetLayout(
            descriptorSetLayouts_[i], nullptr);
        descriptorSetLayouts_[i] = ::vk::DescriptorSetLayout();
    }
    device_.NativeObject_().destroyRenderPass(renderPass_);
    renderPass_ = ::vk::RenderPass();
}

} // namespace gfx_low
} // namespace ae
// EOF
