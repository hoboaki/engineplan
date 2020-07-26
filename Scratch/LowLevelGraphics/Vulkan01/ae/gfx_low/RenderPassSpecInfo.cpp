// 文字コード：UTF-8
#include <ae/gfx_low/RenderPassSpecInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
RenderPassSpecInfo& RenderPassSpecInfo::SetRenderTargetCount(
    const int renderTargetCount) {
    AE_BASE_ASSERT_LESS_EQUALS(0, renderTargetCount);
    renderTargetCount_ = renderTargetCount;
    return *this;
}

}  // namespace gfx_low
}  // namespace ae
// EOF
