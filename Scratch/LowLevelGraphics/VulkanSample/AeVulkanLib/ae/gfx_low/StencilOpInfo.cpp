// 文字コード：UTF-8
#include <ae/gfx_low/StencilOpInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
StencilOpInfo& StencilOpInfo::SetFailOp(const StencilOp op)
{
    AE_BASE_ASSERT_ENUM(op, StencilOp);
    AE_BASE_ASSERT(op != StencilOp::Invalid);
    failOp_ = op;
    return *this;
}

//------------------------------------------------------------------------------
StencilOpInfo& StencilOpInfo::SetDepthFailOp(const StencilOp op)
{
    AE_BASE_ASSERT_ENUM(op, StencilOp);
    AE_BASE_ASSERT(op != StencilOp::Invalid);
    depthFailOp_ = op;
    return *this;
}

//------------------------------------------------------------------------------
StencilOpInfo& StencilOpInfo::SetPassOp(const StencilOp op)
{
    AE_BASE_ASSERT_ENUM(op, StencilOp);
    AE_BASE_ASSERT(op != StencilOp::Invalid);
    passOp_ = op;
    return *this;
}

//------------------------------------------------------------------------------
StencilOpInfo& StencilOpInfo::SetCompareOp(const gfx_low::CompareOp op)
{
    AE_BASE_ASSERT_ENUM(op, CompareOp);
    AE_BASE_ASSERT(op != CompareOp::Invalid);
    compareOp_ = op;
    return *this;
}

} // namespace ae::gfx_low
// EOF
