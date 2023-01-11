// 文字コード：UTF-8
#include <ae/gfx_low/Sampler.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/SamplerCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
Sampler::Sampler(const SamplerCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, nativeObject_()
{
    // VkSampler の作成
    {
        const auto nativeCreateInfo =
            ::vk::SamplerCreateInfo()
                .setMinFilter(
                    InternalEnumUtil::ToFilter(createInfo.MinFilter()))
                .setMagFilter(
                    InternalEnumUtil::ToFilter(createInfo.MagFilter()))
                .setMipmapMode(InternalEnumUtil::ToSamplerMipmapMode(
                    createInfo.MipmapMode()))
                .setAddressModeU(InternalEnumUtil::ToSamplerAddressMode(
                    createInfo.AddressModeU()))
                .setAddressModeV(InternalEnumUtil::ToSamplerAddressMode(
                    createInfo.AddressModeV()))
                .setAddressModeW(InternalEnumUtil::ToSamplerAddressMode(
                    createInfo.AddressModeW()))
                .setBorderColor(
                    InternalEnumUtil::ToBorderColor(createInfo.BorderColor()))
                .setAnisotropyEnable(
                    createInfo.AnisotropyEnable() ? VK_TRUE : VK_FALSE)
                .setMaxAnisotropy(float(createInfo.MaxAnisotropy()))
                .setCompareEnable(
                    createInfo.CompareEnable() ? VK_TRUE : VK_FALSE)
                .setCompareOp(
                    InternalEnumUtil::ToCompareOp(createInfo.CompareOp()))
                .setMipLodBias(0.0f)
                .setMinLod(createInfo.MinLod())
                .setMaxLod(createInfo.MaxLod())
                .setUnnormalizedCoordinates(
                    createInfo.UnnormalizedCoordinates() ? VK_TRUE : VK_FALSE);
        const auto result = device_.NativeObject_().createSampler(
            &nativeCreateInfo,
            nullptr,
            &nativeObject_);
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }
}

//------------------------------------------------------------------------------
Sampler::~Sampler()
{
    device_.NativeObject_().destroySampler(nativeObject_, nullptr);
    nativeObject_ = ::vk::Sampler();
}

} // namespace ae::gfx_low
// EOF
