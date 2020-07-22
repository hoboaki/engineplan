// 文字コード：UTF-8
#include <ae/gfx_low/SwapchainMasterCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
SwapchainMasterCreateInfo& SwapchainMasterCreateInfo::SetSwapchainCountMax(
    const int count) {
    AE_BASE_ASSERT_LESS_EQUALS(1, count);
    swapchainCountMax_ = count;
    return *this;
}

}  // namespace gfx_low
}  // namespace ae
// EOF
