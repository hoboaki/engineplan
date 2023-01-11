// 文字コード：UTF-8
#include <ae/gfx_low/RenderTargetBlendInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
RenderTargetBlendInfo& RenderTargetBlendInfo::SetSrcColorBlendFactor(
    const BlendFactor factor)
{
    AE_BASE_ASSERT_ENUM(factor, BlendFactor);
    AE_BASE_ASSERT(factor != BlendFactor::Invalid);
    srcColorBlendFactor_ = factor;
    return *this;
}

//------------------------------------------------------------------------------
RenderTargetBlendInfo& RenderTargetBlendInfo::SetDstColorBlendFactor(
    const BlendFactor factor)
{
    AE_BASE_ASSERT_ENUM(factor, BlendFactor);
    AE_BASE_ASSERT(factor != BlendFactor::Invalid);
    dstColorBlendFactor_ = factor;
    return *this;
}

//------------------------------------------------------------------------------
RenderTargetBlendInfo& RenderTargetBlendInfo::SetColorBlendOp(
    const BlendOp op)
{
    AE_BASE_ASSERT_ENUM(op, BlendOp);
    AE_BASE_ASSERT(op != BlendOp::Invalid);
    colorBlendOp_ = op;
    return *this;
}

//------------------------------------------------------------------------------
RenderTargetBlendInfo& RenderTargetBlendInfo::SetSrcAlphaBlendFactor(
    const BlendFactor factor)
{
    AE_BASE_ASSERT_ENUM(factor, BlendFactor);
    AE_BASE_ASSERT(factor != BlendFactor::Invalid);
    srcAlphaBlendFactor_ = factor;
    return *this;
}

//------------------------------------------------------------------------------
RenderTargetBlendInfo& RenderTargetBlendInfo::SetDstAlphaBlendFactor(
    const BlendFactor factor)
{
    AE_BASE_ASSERT_ENUM(factor, BlendFactor);
    AE_BASE_ASSERT(factor != BlendFactor::Invalid);
    dstAlphaBlendFactor_ = factor;
    return *this;
}

//------------------------------------------------------------------------------
RenderTargetBlendInfo& RenderTargetBlendInfo::SetAlphaBlendOp(
    const BlendOp op)
{
    AE_BASE_ASSERT_ENUM(op, BlendOp);
    AE_BASE_ASSERT(op != BlendOp::Invalid);
    alphaBlendOp_ = op;
    return *this;
}

} // namespace ae::gfx_low
// EOF
