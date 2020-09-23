// 文字コード：UTF-8
#include <ae/gfx_low/CopyBufferToImageInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
CopyBufferToImageInfo& CopyBufferToImageInfo::SetDstImageResourceState(
    const ImageResourceState state) {
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);

    // 現時点では CopyDstOptimal のみサポート
    AE_BASE_ASSERT(state == ImageResourceState::CopyDstOptimal);
    dstImageResourceState_ = state;
    return *this;
}

//------------------------------------------------------------------------------
CopyBufferToImageInfo& CopyBufferToImageInfo::SetDstImageOffset(
    const base::Vector3iPod& offset)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, offset.x);
    AE_BASE_ASSERT_LESS_EQUALS(0, offset.y);
    AE_BASE_ASSERT_LESS_EQUALS(0, offset.z);
    dstImageOffset_ = offset;
    return *this;
}

} // namespace gfx_low
} // namespace ae
// EOF
