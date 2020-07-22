// 文字コード：UTF-8
#include <ae/gfx_low/SwapchainCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
SwapchainCreateInfo& SwapchainCreateInfo::SetImageCount(const int imageCount) {
    AE_BASE_ASSERT_LESS_EQUALS(1, imageCount);
    imageCount_ = imageCount;
    return *this;
}

}
}  // namespace ae
// EOF
