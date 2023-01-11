// 文字コード：UTF-8
#include <ae/gfx_low/ImageSubresourceLocation.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
ImageSubresourceLocation& ImageSubresourceLocation::SetMipLevel(
    const int level)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, level);
    mipLevel_ = level;
    return *this;
}

//------------------------------------------------------------------------------
ImageSubresourceLocation& ImageSubresourceLocation::SetArrayIndex(
    const int index)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, index);
    arrayIndex_ = index;
    return *this;
}

//------------------------------------------------------------------------------
ImageSubresourceLocation& ImageSubresourceLocation::SetFaceIndex(
    const int index)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, index);
    faceIndex_ = index;
    return *this;
}

} // namespace ae::gfx_low
// EOF
