// 文字コード：UTF-8
#include <ae/gfx_low/RenderTargetSpecInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
RenderTargetSpecInfo& RenderTargetSpecInfo::SetFormat(const gfx_low::Format format) {
    AE_BASE_ASSERT_ENUM(format, Format);
    AE_BASE_ASSERT(format != gfx_low::Format::Invalid);
    format_ = format;
    return *this;
}

}  // namespace gfx_low
}  // namespace ae
// EOF
