// 文字コード：UTF-8
#include <ae/gfx_low/SampledImageViewCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
SampledImageViewCreateInfo& SampledImageViewCreateInfo::SetKind(
    const ImageViewKind kind)
{
    AE_BASE_ASSERT_ENUM(kind, ImageViewKind);
    AE_BASE_ASSERT(kind != ImageViewKind::Invalid);
    kind_ = kind;
    return *this;
}

//------------------------------------------------------------------------------
SampledImageViewCreateInfo& SampledImageViewCreateInfo::SetFormat(
    const ImageFormat format)
{
    AE_BASE_ASSERT_ENUM(format, ImageFormat);
    AE_BASE_ASSERT(format != ImageFormat::Invalid);
    format_ = format;
    return *this;
}

} // namespace ae::gfx_low
// EOF
