// 文字コード：UTF-8
#include <ae/base/Extent2i.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Extent2i::Extent2i(int width, int height) {
    AE_BASE_ASSERT_LESS_EQUALS(0, width);
    AE_BASE_ASSERT_LESS_EQUALS(0, height);
    this->width = width;
    this->height = height;
}

} // namespace base
} // namespace ae
// EOF
