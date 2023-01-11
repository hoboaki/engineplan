// 文字コード：UTF-8
#include <ae/base/Extent2.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
Extent2::Extent2(const float width, const float height)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, width);
    AE_BASE_ASSERT_LESS_EQUALS(0, height);
    this->width = width;
    this->height = height;
}

} // namespace ae::base
// EOF
