// 文字コード：UTF-8
#include <ae/gfx_low/CopyImageToBufferInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
CopyImageToBufferInfo& CopyImageToBufferInfo::SetSrcImageResourceState(
    const ImageResourceState state)
{
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);

    // 現時点では CopySrc のみサポート
    AE_BASE_ASSERT(state == ImageResourceState::CopySrc);
    srcImageResourceState_ = state;
    return *this;
}

//------------------------------------------------------------------------------
CopyImageToBufferInfo& CopyImageToBufferInfo::SetSrcImageOffset(
    const base::Vector3iPod& offset)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, offset.x);
    AE_BASE_ASSERT_LESS_EQUALS(0, offset.y);
    AE_BASE_ASSERT_LESS_EQUALS(0, offset.z);
    srcImageOffset_ = offset;
    return *this;
}

//------------------------------------------------------------------------------
CopyImageToBufferInfo& CopyImageToBufferInfo::SetDstImageFormat(
    const ImageFormat format)
{
    AE_BASE_ASSERT_ENUM(format, ImageFormat);
    AE_BASE_ASSERT(format != ImageFormat::Invalid);
    dstImageFormat_ = format;
    return *this;
}

} // namespace ae::gfx_low
// EOF
