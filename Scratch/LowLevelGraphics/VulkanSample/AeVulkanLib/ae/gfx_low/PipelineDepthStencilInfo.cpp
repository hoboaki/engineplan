// 文字コード：UTF-8
#include <ae/gfx_low/PipelineDepthStencilInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
PipelineDepthStencilInfo& PipelineDepthStencilInfo::SetDepthCompareOp(
    const CompareOp op)
{
    AE_BASE_ASSERT_ENUM(op, CompareOp);
    AE_BASE_ASSERT(op != CompareOp::Invalid);
    depthCompareOp_ = op;
    return *this;
}

} // namespace ae::gfx_low
// EOF
