// 文字コード：UTF-8
#include <ae/gfx_low/DepthStencilImageViewCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
DepthStencilImageViewCreateInfo& DepthStencilImageViewCreateInfo::SetFormat(
    const ImageFormat format)
{
    AE_BASE_ASSERT_ENUM(format, ImageFormat);
    AE_BASE_ASSERT(format != ImageFormat::Invalid);
    format_ = format;
    return *this;
}

} // namespace ae::gfx_low
// EOF
