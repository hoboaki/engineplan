// 文字コード：UTF-8
#include <ae/gfx_low/ImageResourceSpecInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
ImageResourceSpecInfo& ImageResourceSpecInfo::SetKind(
    const ImageResourceKind kind)
{
    AE_BASE_ASSERT_ENUM(kind, ImageResourceKind);
    AE_BASE_ASSERT(kind != ImageResourceKind::Invalid);
    kind_ = kind;
    return *this;
}

//------------------------------------------------------------------------------
ImageResourceSpecInfo& ImageResourceSpecInfo::SetFormat(
    const ImageFormat format)
{
    AE_BASE_ASSERT_ENUM(format, ImageFormat);
    AE_BASE_ASSERT(format != ImageFormat::Invalid);
    format_ = format;
    return *this;
}

//------------------------------------------------------------------------------
ImageResourceSpecInfo& ImageResourceSpecInfo::SetTiling(
    const ImageResourceTiling tiling)
{
    AE_BASE_ASSERT_ENUM(tiling, ImageResourceTiling);
    AE_BASE_ASSERT(tiling != ImageResourceTiling::Invalid);
    tiling_ = tiling;
    return *this;
}

//------------------------------------------------------------------------------
ImageResourceSpecInfo& ImageResourceSpecInfo::SetMipLevels(
    const int mipLevels)
{
    AE_BASE_ASSERT_LESS_EQUALS(1, mipLevels);
    mipLevels_ = mipLevels;
    return *this;
}

//------------------------------------------------------------------------------
ImageResourceSpecInfo& ImageResourceSpecInfo::SetArrayLength(
    const int arrayLength)
{
    AE_BASE_ASSERT_LESS_EQUALS(1, arrayLength);
    arrayLength_ = arrayLength;
    return *this;
}

} // namespace ae::gfx_low
// EOF
