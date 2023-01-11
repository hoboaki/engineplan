// 文字コード：UTF-8
#include <ae/gfx_low/ImageResourceCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
ImageResourceCreateInfo& ImageResourceCreateInfo::SetNativeObjectMipLevels_(
    const int levels)
{
    AE_BASE_ASSERT_LESS_EQUALS(1, levels);
    nativeObjectMipLevels_ = levels;
    return *this;
}

//------------------------------------------------------------------------------
ImageResourceCreateInfo& ImageResourceCreateInfo::SetNativeObjectArrayLength_(
    const int arrayLength)
{
    AE_BASE_ASSERT_LESS_EQUALS(1, arrayLength);
    nativeObjectArrayLength_ = arrayLength;
    return *this;
}

//------------------------------------------------------------------------------
::vk::ImageCreateInfo ImageResourceCreateInfo::NativeCreateInfo_() const
{
    const bool isCubeImage = specInfo_.Kind() == ImageResourceKind::ImageCube;
    return ::vk::ImageCreateInfo()
        .setImageType(InternalEnumUtil::ToImageType(specInfo_.Kind()))
        .setFormat(InternalEnumUtil::ToFormat(specInfo_.Format()))
        .setExtent({ uint32_t(specInfo_.Extent().width),
            uint32_t(specInfo_.Extent().height),
            uint32_t(specInfo_.Extent().depth) })
        .setMipLevels(uint32_t(specInfo_.MipLevels()))
        .setArrayLayers(
            uint32_t(specInfo_.ArrayLength()) * (isCubeImage ? 6 : 1))
        .setSamples(::vk::SampleCountFlagBits::e1)
        .setTiling(InternalEnumUtil::ToImageTiling(specInfo_.Tiling()))
        .setUsage(InternalEnumUtil::ToImageUsageFlags(specInfo_.UsageBitSet()))
        .setSharingMode(::vk::SharingMode::eExclusive)
        .setQueueFamilyIndexCount(0)
        .setPQueueFamilyIndices(nullptr)
        .setInitialLayout(::vk::ImageLayout::eUndefined)
        .setFlags(
            isCubeImage ? ::vk::ImageCreateFlagBits::eCubeCompatible
                        : ::vk::ImageCreateFlagBits(0));
}

} // namespace ae::gfx_low
// EOF
