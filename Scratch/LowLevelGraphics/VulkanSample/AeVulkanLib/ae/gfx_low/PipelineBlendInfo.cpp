// 文字コード：UTF-8
#include <ae/gfx_low/PipelineBlendInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
PipelineBlendInfo& PipelineBlendInfo::SetLogicOp(const gfx_low::LogicOp op)
{
    AE_BASE_ASSERT_ENUM(op, gfx_low::LogicOp);
    AE_BASE_ASSERT(op != gfx_low::LogicOp::Invalid);
    logicOp_ = op;
    return *this;
}

} // namespace ae::gfx_low
// EOF
