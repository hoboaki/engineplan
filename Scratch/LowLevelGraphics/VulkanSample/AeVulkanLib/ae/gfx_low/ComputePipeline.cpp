// 文字コード：UTF-8
#include <ae/gfx_low/ComputePipeline.hpp>

// includes
#include <ae/base/ArrayLength.hpp>
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/ComputePipelineCreateInfo.hpp>
#include <ae/gfx_low/DepthStencilSpecInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/ShaderBindingInfo.hpp>
#include <ae/gfx_low/ShaderModuleResource.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
ComputePipeline::ComputePipeline(const ComputePipelineCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, descriptorSetLayouts_(&device_, createInfo.DescriptorSetSpecInfo())
, pushConstantRanges_(createInfo.DescriptorSetSpecInfo())
, pipelineLayout_()
, nativeObject_()
{
    // PipelineLayout
    {
        AE_BASE_ASSERT_LESS(
            0,
            descriptorSetLayouts_.DescriptorSetLayoutCount());
        const auto pipelineLayoutCreateInfo =
            ::vk::PipelineLayoutCreateInfo()
                .setSetLayoutCount(
                    descriptorSetLayouts_.DescriptorSetLayoutCount())
                .setPSetLayouts(descriptorSetLayouts_.DescriptorSetLayouts())
                .setPushConstantRangeCount(
                    pushConstantRanges_.PushConstantRangeCount())
                .setPPushConstantRanges(
                    pushConstantRanges_.PushConstantRanges());

        const auto result = device_.NativeObject_().createPipelineLayout(
            &pipelineLayoutCreateInfo,
            nullptr,
            &pipelineLayout_);
        AE_BASE_ASSERT(result == vk::Result::eSuccess);
    }

    // Pipeline
    {
        ::vk::PipelineShaderStageCreateInfo shaderStageInfo = {};
        {
            const auto shaderInfo = createInfo.ShaderInfo();
            const auto* resourcePtr = shaderInfo.Resource();
            AE_BASE_ASSERT_POINTER(resourcePtr);

            shaderStageInfo =
                ::vk::PipelineShaderStageCreateInfo()
                    .setStage(::vk::ShaderStageFlagBits::eCompute)
                    .setModule(base::PtrToRef(resourcePtr).NativeObject_())
                    .setPName(shaderInfo.EntryPointNamePtr());
        }

        const auto nativeCreateInfo = ::vk::ComputePipelineCreateInfo()
                                          .setStage(shaderStageInfo)
                                          .setLayout(pipelineLayout_);

        {
            const auto result = device_.NativeObject_().createComputePipelines(
                nullptr,
                1,
                &nativeCreateInfo,
                nullptr,
                &nativeObject_);
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
        }
    }
}

//------------------------------------------------------------------------------
ComputePipeline::~ComputePipeline()
{
    device_.NativeObject_().destroyPipeline(nativeObject_, nullptr);
    nativeObject_ = ::vk::Pipeline();
    device_.NativeObject_().destroyPipelineLayout(pipelineLayout_, nullptr);
    pipelineLayout_ = ::vk::PipelineLayout();
}

} // namespace ae::gfx_low
// EOF
