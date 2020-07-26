// 文字コード：UTF-8
#include <ae/gfx_low/RenderPassSpec.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
RenderPassSpec& RenderPassSpec::SetRenderTargetCount(
    const int renderTargetCount) {
    AE_BASE_ASSERT_LESS_EQUALS(0, renderTargetCount);
    renderTargetCount_ = renderTargetCount;
    return *this;
}

}  // namespace gfx_low
}  // namespace ae
// EOF
