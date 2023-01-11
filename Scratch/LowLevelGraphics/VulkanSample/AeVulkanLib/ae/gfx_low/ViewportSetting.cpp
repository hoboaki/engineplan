// 文字コード：UTF-8
#include <ae/gfx_low/ViewportSetting.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
ViewportSetting& ViewportSetting::SetDepthRange(
    const float depthMin,
    const float depthMax)
{
    AE_BASE_ASSERT_MIN_MAX(depthMin, 0.0f, 1.0f);
    AE_BASE_ASSERT_MIN_MAX(depthMax, 0.0f, 1.0f);
    AE_BASE_ASSERT_LESS_EQUALS(depthMin, depthMax);
    minDepth_ = depthMin;
    maxDepth_ = depthMax;
    return *this;
}

} // namespace ae::gfx_low
// EOF
