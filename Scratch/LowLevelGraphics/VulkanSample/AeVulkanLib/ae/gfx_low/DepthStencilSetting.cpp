// 文字コード：UTF-8
#include <ae/gfx_low/DepthStencilSetting.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
DepthStencilSetting& DepthStencilSetting::SetInitialImageResourceState(
    const ImageResourceState state)
{
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);
    AE_BASE_ASSERT(state != ImageResourceState::Invalid);
    initialImageResourceState_ = state;
    return *this;
}

//------------------------------------------------------------------------------
DepthStencilSetting& DepthStencilSetting::SetFinalImageResourceState(
    const ImageResourceState state)
{
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);
    AE_BASE_ASSERT(state != ImageResourceState::Invalid);
    finalImageResourceState_ = state;
    return *this;
}

//------------------------------------------------------------------------------
DepthStencilSetting& DepthStencilSetting::SetDepthLoadOp(
    const AttachmentLoadOp loadOp)
{
    AE_BASE_ASSERT_ENUM(loadOp, AttachmentLoadOp);
    AE_BASE_ASSERT(loadOp != AttachmentLoadOp::Invalid);
    depthLoadOp_ = loadOp;
    return *this;
}

//------------------------------------------------------------------------------
DepthStencilSetting& DepthStencilSetting::SetDepthStoreOp(
    const AttachmentStoreOp storeOp)
{
    AE_BASE_ASSERT_ENUM(storeOp, AttachmentStoreOp);
    AE_BASE_ASSERT(storeOp != AttachmentStoreOp::Invalid);
    depthStoreOp_ = storeOp;
    return *this;
}

//------------------------------------------------------------------------------
DepthStencilSetting& DepthStencilSetting::SetDepthClearValue(
    const float clearValue)
{
    AE_BASE_ASSERT_MIN_MAX(clearValue, 0.0f, 1.0f);
    depthClearValue_ = clearValue;
    return *this;
}

//------------------------------------------------------------------------------
DepthStencilSetting& DepthStencilSetting::SetStencilLoadOp(
    const AttachmentLoadOp loadOp)
{
    AE_BASE_ASSERT_ENUM(loadOp, AttachmentLoadOp);
    AE_BASE_ASSERT(loadOp != AttachmentLoadOp::Invalid);
    stencilLoadOp_ = loadOp;
    return *this;
}

//------------------------------------------------------------------------------
DepthStencilSetting& DepthStencilSetting::SetStencilStoreOp(
    const AttachmentStoreOp storeOp)
{
    AE_BASE_ASSERT_ENUM(storeOp, AttachmentStoreOp);
    AE_BASE_ASSERT(storeOp != AttachmentStoreOp::Invalid);
    stencilStoreOp_ = storeOp;
    return *this;
}

//------------------------------------------------------------------------------
DepthStencilSetting& DepthStencilSetting::SetStencilClearValue(
    const int clearValue)
{
    AE_BASE_ASSERT_MIN_MAX(clearValue, 0, 0xFF);
    stencilClearValue_ = clearValue;
    return *this;
}

} // namespace ae::gfx_low
// EOF
