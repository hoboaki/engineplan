// 文字コード：UTF-8
#include <ae/gfx_low/RenderTargetSpecInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
RenderTargetSpecInfo& RenderTargetSpecInfo::SetImageFormat(
    const gfx_low::ImageFormat imageFormat)
{
    AE_BASE_ASSERT_ENUM(imageFormat, ImageFormat);
    AE_BASE_ASSERT(imageFormat != gfx_low::ImageFormat::Invalid);
    imageFormat_ = imageFormat;
    return *this;
}

} // namespace ae::gfx_low
// EOF
