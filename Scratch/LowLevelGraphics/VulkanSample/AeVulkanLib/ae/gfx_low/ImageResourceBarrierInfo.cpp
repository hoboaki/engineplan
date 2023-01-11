// 文字コード：UTF-8
#include <ae/gfx_low/ImageResourceBarrierInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
ImageResourceBarrierInfo& ImageResourceBarrierInfo::SetOldState(
    const ImageResourceState state)
{
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);
    AE_BASE_ASSERT(state != ImageResourceState::Invalid);
    newState_ = state;
    return *this;
}

//------------------------------------------------------------------------------
ImageResourceBarrierInfo& ImageResourceBarrierInfo::SetNewState(
    const ImageResourceState state)
{
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);
    AE_BASE_ASSERT(state != ImageResourceState::Invalid);
    oldState_ = state;
    return *this;
}

} // namespace ae::gfx_low
// EOF
