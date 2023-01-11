// 文字コード：UTF-8
#include <ae/gfx_low/ImageSubresourceRange.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/ImageSubresourceLocation.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
ImageSubresourceRange& ImageSubresourceRange::SetMipLevels(const int levels)
{
    AE_BASE_ASSERT_LESS_EQUALS(1, levels);
    mipLevels_ = levels;
    return *this;
}

//------------------------------------------------------------------------------
ImageSubresourceRange& ImageSubresourceRange::SetArrayLength(
    const int arrayLength)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, arrayLength);
    arrayLength_ = arrayLength;
    return *this;
}

} // namespace ae::gfx_low
// EOF
