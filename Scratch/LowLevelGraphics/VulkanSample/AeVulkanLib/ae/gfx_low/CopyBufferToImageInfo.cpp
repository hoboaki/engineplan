// 文字コード：UTF-8
#include <ae/gfx_low/CopyBufferToImageInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
CopyBufferToImageInfo& CopyBufferToImageInfo::SetSrcImageFormat(
    const ImageFormat format)
{
    AE_BASE_ASSERT_ENUM(format, ImageFormat);
    AE_BASE_ASSERT(format != ImageFormat::Invalid);
    srcImageFormat_ = format;
    return *this;
}

//------------------------------------------------------------------------------
CopyBufferToImageInfo& CopyBufferToImageInfo::SetDstImageResourceState(
    const ImageResourceState state)
{
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);

    // 現時点では CopyDst のみサポート
    AE_BASE_ASSERT(state == ImageResourceState::CopyDst);
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

} // namespace ae::gfx_low
// EOF
