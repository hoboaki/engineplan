// 文字コード：UTF-8
#include <ae/gfx_low/GraphicsPipelineCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
PipelineShaderInfo GraphicsPipelineCreateInfo::ShaderInfo(
    const GraphicsPipelineShaderStage stage) const {
    AE_BASE_ASSERT(stage != GraphicsPipelineShaderStage::Invalid);
    return shaderInfos_[stage];
}

//------------------------------------------------------------------------------
GraphicsPipelineCreateInfo& GraphicsPipelineCreateInfo::SetShaderInfo(
    const GraphicsPipelineShaderStage stage,
    const PipelineShaderInfo& shaderInfo) {
    AE_BASE_ASSERT(stage != GraphicsPipelineShaderStage::Invalid);
    shaderInfos_[stage] = shaderInfo;
    return *this;
}

//------------------------------------------------------------------------------
GraphicsPipelineCreateInfo& GraphicsPipelineCreateInfo::SetPrimitiveTopologyKind(
    const gfx_low::PrimitiveTopologyKind kind) {
    AE_BASE_ASSERT_ENUM(kind, gfx_low::PrimitiveTopologyKind);
    AE_BASE_ASSERT(kind != gfx_low::PrimitiveTopologyKind::Invalid);
    primitiveTopologyKind_ = kind;
    return *this;
}



} // namespace gfx_low
} // namespace ae
// EOF
