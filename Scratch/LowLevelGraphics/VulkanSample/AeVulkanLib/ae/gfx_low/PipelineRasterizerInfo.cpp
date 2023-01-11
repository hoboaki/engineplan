// 文字コード：UTF-8
#include <ae/gfx_low/PipelineRasterizerInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
PipelineRasterizerInfo& PipelineRasterizerInfo::SetCullMode(
    const RasterizeCullMode mode)
{
    AE_BASE_ASSERT_ENUM(mode, RasterizeCullMode);
    AE_BASE_ASSERT(mode != RasterizeCullMode::Invalid);
    cullMode_ = mode;
    return *this;
}

//------------------------------------------------------------------------------
PipelineRasterizerInfo& PipelineRasterizerInfo::SetFillMode(
    const RasterizeFillMode mode)
{
    AE_BASE_ASSERT_ENUM(mode, RasterizeFillMode);
    AE_BASE_ASSERT(mode != RasterizeFillMode::Invalid);
    fillMode_ = mode;
    return *this;
}

//------------------------------------------------------------------------------
PipelineRasterizerInfo& PipelineRasterizerInfo::SetFrontFace(
    const PolygonFrontFace frontFace)
{
    AE_BASE_ASSERT_ENUM(frontFace, PolygonFrontFace);
    AE_BASE_ASSERT(frontFace != PolygonFrontFace::Invalid);
    frontFace_ = frontFace;
    return *this;
}

//------------------------------------------------------------------------------
PipelineRasterizerInfo& PipelineRasterizerInfo::SetLineWidth(
    const float lineWidth)
{
    AE_BASE_ASSERT_LESS_EQUALS(0.0f, lineWidth_);
    lineWidth_ = lineWidth;
    return *this;
}

} // namespace ae::gfx_low
// EOF
