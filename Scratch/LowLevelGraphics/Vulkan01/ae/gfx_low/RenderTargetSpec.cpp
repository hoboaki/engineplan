// 文字コード：UTF-8
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/RenderTargetSpec.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
RenderTargetSpec& RenderTargetSpec::SetFormat(const gfx_low::Format format) {
    AE_BASE_ASSERT_ENUM(format, Format);
    AE_BASE_ASSERT(format != gfx_low::Format::Invalid);
    format_ = format;
    return *this;
}

}  // namespace gfx_low
}  // namespace ae
// EOF
