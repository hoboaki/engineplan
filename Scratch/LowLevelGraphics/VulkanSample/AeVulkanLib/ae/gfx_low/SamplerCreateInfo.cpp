// 文字コード：UTF-8
#include <ae/gfx_low/SamplerCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
SamplerCreateInfo& SamplerCreateInfo::SetMinFilter(
    const SamplerMinMagFilter filter)
{
    AE_BASE_ASSERT_ENUM(filter, SamplerMinMagFilter);
    AE_BASE_ASSERT(filter != SamplerMinMagFilter::Invalid);
    minFilter_ = filter;
    return *this;
}

//------------------------------------------------------------------------------
SamplerCreateInfo& SamplerCreateInfo::SetMagFilter(
    const SamplerMinMagFilter filter)
{
    AE_BASE_ASSERT_ENUM(filter, SamplerMinMagFilter);
    AE_BASE_ASSERT(filter != SamplerMinMagFilter::Invalid);
    magFilter_ = filter;
    return *this;
}

//------------------------------------------------------------------------------
SamplerCreateInfo& SamplerCreateInfo::SetMipmapMode(
    const SamplerMipmapMode mode)
{
    AE_BASE_ASSERT_ENUM(mode, SamplerMipmapMode);
    AE_BASE_ASSERT(mode != SamplerMipmapMode::Invalid);
    mipmapMode_ = mode;
    return *this;
}

//------------------------------------------------------------------------------
SamplerCreateInfo& SamplerCreateInfo::SetAddressModeU(
    const SamplerAddressMode mode)
{
    AE_BASE_ASSERT_ENUM(mode, SamplerAddressMode);
    AE_BASE_ASSERT(mode != SamplerAddressMode::Invalid);
    addressModeU_ = mode;
    return *this;
}

//------------------------------------------------------------------------------
SamplerCreateInfo& SamplerCreateInfo::SetAddressModeV(
    const SamplerAddressMode mode)
{
    AE_BASE_ASSERT_ENUM(mode, SamplerAddressMode);
    AE_BASE_ASSERT(mode != SamplerAddressMode::Invalid);
    addressModeV_ = mode;
    return *this;
}

//------------------------------------------------------------------------------
SamplerCreateInfo& SamplerCreateInfo::SetAddressModeW(
    const SamplerAddressMode mode)
{
    AE_BASE_ASSERT_ENUM(mode, SamplerAddressMode);
    AE_BASE_ASSERT(mode != SamplerAddressMode::Invalid);
    addressModeW_ = mode;
    return *this;
}

//------------------------------------------------------------------------------
SamplerCreateInfo& SamplerCreateInfo::SetBorderColor(
    const SamplerBorderColor color)
{
    AE_BASE_ASSERT_ENUM(color, SamplerBorderColor);
    AE_BASE_ASSERT(color != SamplerBorderColor::Invalid);
    borderColor_ = color;
    return *this;
}

//------------------------------------------------------------------------------
SamplerCreateInfo& SamplerCreateInfo::SetMaxAnisotropy(
    const int maxAnisotropy)
{
    AE_BASE_ASSERT_MIN_MAX(maxAnisotropy, 1, 16);
    maxAnisotropy_ = maxAnisotropy;
    return *this;
}

//------------------------------------------------------------------------------
SamplerCreateInfo& SamplerCreateInfo::SetCompareOp(
    const gfx_low::CompareOp op)
{
    AE_BASE_ASSERT_ENUM(op, gfx_low::CompareOp);
    AE_BASE_ASSERT(op != gfx_low::CompareOp::Invalid);
    compareOp_ = op;
    return *this;
}

} // namespace ae::gfx_low
// EOF
