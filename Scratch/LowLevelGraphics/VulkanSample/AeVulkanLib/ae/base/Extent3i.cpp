// 文字コード：UTF-8
#include <ae/base/Extent3i.hpp>

// includes
#include <ae/base/Extent2i.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
Extent3i::Extent3i(const Extent2iPod& extent, int depth)
: Extent3i(extent.width, extent.height, depth)
{
}

//------------------------------------------------------------------------------
Extent3i::Extent3i(int width, int height, int depth)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, width);
    AE_BASE_ASSERT_LESS_EQUALS(0, height);
    AE_BASE_ASSERT_LESS_EQUALS(0, depth);
    this->width = width;
    this->height = height;
    this->depth = depth;
}

} // namespace ae::base
// EOF
