// 文字コード：UTF-8
#include <ae/gfx_low/RenderTargetSetting.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
RenderTargetSetting& RenderTargetSetting::SetInitialImageResourceState(
    const ImageResourceState state)
{
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);
    AE_BASE_ASSERT(state != ImageResourceState::Invalid);
    initialImageResourceState_ = state;
    return *this;
}

//------------------------------------------------------------------------------
RenderTargetSetting& RenderTargetSetting::SetFinalImageResourceState(
    const ImageResourceState state)
{
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);
    AE_BASE_ASSERT(state != ImageResourceState::Invalid);
    finalImageResourceState_ = state;
    return *this;
}

//------------------------------------------------------------------------------
RenderTargetSetting& RenderTargetSetting::SetLoadOp(
    const AttachmentLoadOp loadOp)
{
    AE_BASE_ASSERT_ENUM(loadOp, AttachmentLoadOp);
    AE_BASE_ASSERT(loadOp != AttachmentLoadOp::Invalid);
    loadOp_ = loadOp;
    return *this;
}

//------------------------------------------------------------------------------
RenderTargetSetting& RenderTargetSetting::SetStoreOp(
    const AttachmentStoreOp storeOp)
{
    AE_BASE_ASSERT_ENUM(storeOp, AttachmentStoreOp);
    AE_BASE_ASSERT(storeOp != AttachmentStoreOp::Invalid);
    storeOp_ = storeOp;
    return *this;
}

} // namespace ae::gfx_low
// EOF
