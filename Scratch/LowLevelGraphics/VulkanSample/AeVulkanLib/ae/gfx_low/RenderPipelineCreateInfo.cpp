// 文字コード：UTF-8
#include <ae/gfx_low/RenderPipelineCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
PipelineShaderInfo RenderPipelineCreateInfo::ShaderInfo(
    const RenderPipelineShaderStage stage) const {
    AE_BASE_ASSERT(stage != RenderPipelineShaderStage::Invalid);
    return shaderInfos_[stage];
}

//------------------------------------------------------------------------------
RenderPipelineCreateInfo& RenderPipelineCreateInfo::SetShaderInfo(
    const RenderPipelineShaderStage stage,
    const PipelineShaderInfo& shaderInfo) {
    AE_BASE_ASSERT(stage != RenderPipelineShaderStage::Invalid);
    shaderInfos_[stage] = shaderInfo;
    return *this;
}

} // namespace gfx_low
} // namespace ae
// EOF
