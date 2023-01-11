// 文字コード：UTF-8
#include <ae/gfx_low/StorageImageViewCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
StorageImageViewCreateInfo& StorageImageViewCreateInfo::SetKind(
    const ImageViewKind kind)
{
    AE_BASE_ASSERT_ENUM(kind, ImageViewKind);
    AE_BASE_ASSERT(kind != ImageViewKind::Invalid);
    kind_ = kind;
    return *this;
}

//------------------------------------------------------------------------------
StorageImageViewCreateInfo& StorageImageViewCreateInfo::SetFormat(
    const ImageFormat format)
{
    AE_BASE_ASSERT_ENUM(format, ImageFormat);
    AE_BASE_ASSERT(format != ImageFormat::Invalid);
    format_ = format;
    return *this;
}

} // namespace ae::gfx_low
// EOF
