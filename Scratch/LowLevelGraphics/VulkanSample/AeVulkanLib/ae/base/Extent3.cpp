// 文字コード：UTF-8
#include <ae/base/Extent3.hpp>

// includes
#include <ae/base/Extent2.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
Extent3::Extent3(const Extent2Pod& extent, float depth)
: Extent3(extent.width, extent.height, depth)
{
}

//------------------------------------------------------------------------------
Extent3::Extent3(float width, float height, float depth)
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
