// 文字コード：UTF-8
#include <ae/base/Extent2i.hpp>

// includes
#include <ae/base/Extent2.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
Extent2Pod Extent2iPod::ToExtent2() const
{
    return Extent2(float(width), float(height));
}

//------------------------------------------------------------------------------
Extent2i::Extent2i(int width, int height)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, width);
    AE_BASE_ASSERT_LESS_EQUALS(0, height);
    this->width = width;
    this->height = height;
}

} // namespace ae::base
// EOF
