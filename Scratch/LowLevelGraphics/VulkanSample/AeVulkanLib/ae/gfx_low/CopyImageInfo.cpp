// 文字コード：UTF-8
#include <ae/gfx_low/CopyImageInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
CopyImageInfo& CopyImageInfo::SetSrcImageResourceState(
    const ImageResourceState state)
{
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);

    // 現時点では CopySrc のみサポート
    AE_BASE_ASSERT(state == ImageResourceState::CopySrc);
    dstImageResourceState_ = state;
    return *this;
}

//------------------------------------------------------------------------------
CopyImageInfo& CopyImageInfo::SetSrcImageOffset(
    const base::Vector3iPod& offset)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, offset.x);
    AE_BASE_ASSERT_LESS_EQUALS(0, offset.y);
    AE_BASE_ASSERT_LESS_EQUALS(0, offset.z);
    dstImageOffset_ = offset;
    return *this;
}

//------------------------------------------------------------------------------
CopyImageInfo& CopyImageInfo::SetDstImageResourceState(
    const ImageResourceState state)
{
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);

    // 現時点では CopyDst のみサポート
    AE_BASE_ASSERT(state == ImageResourceState::CopyDst);
    dstImageResourceState_ = state;
    return *this;
}

//------------------------------------------------------------------------------
CopyImageInfo& CopyImageInfo::SetDstImageOffset(
    const base::Vector3iPod& offset)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, offset.x);
    AE_BASE_ASSERT_LESS_EQUALS(0, offset.y);
    AE_BASE_ASSERT_LESS_EQUALS(0, offset.z);
    dstImageOffset_ = offset;
    return *this;
}

} // namespace ae::gfx_low
// EOF
