// 文字コード：UTF-8
#include <ae/gfx_low/RenderPipelineCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
PipelineShaderInfo RenderPipelineCreateInfo::ShaderInfo(
    const RenderPipelineShaderStage stage) const
{
    AE_BASE_ASSERT(stage != RenderPipelineShaderStage::Invalid);
    return shaderInfos_[stage];
}

//------------------------------------------------------------------------------
RenderPipelineCreateInfo& RenderPipelineCreateInfo::SetShaderInfo(
    const RenderPipelineShaderStage stage,
    const PipelineShaderInfo& shaderInfo)
{
    AE_BASE_ASSERT(stage != RenderPipelineShaderStage::Invalid);
    shaderInfos_[stage] = shaderInfo;
    return *this;
}

//------------------------------------------------------------------------------
RenderPipelineCreateInfo& RenderPipelineCreateInfo::SetPrimitiveTopologyKind(
    const gfx_low::PrimitiveTopologyKind kind)
{
    AE_BASE_ASSERT_ENUM(kind, gfx_low::PrimitiveTopologyKind);
    AE_BASE_ASSERT(kind != gfx_low::PrimitiveTopologyKind::Invalid);
    primitiveTopologyKind_ = kind;
    return *this;
}

} // namespace ae::gfx_low
// EOF
