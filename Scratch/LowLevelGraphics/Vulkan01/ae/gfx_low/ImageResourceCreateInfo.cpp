// 文字コード：UTF-8
#include <ae/gfx_low/ImageResourceCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
ImageResourceCreateInfo& ImageResourceCreateInfo::SetInitialState(
    const ImageResourceState state) {
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);
    AE_BASE_ASSERT(state != ImageResourceState::Invalid);
    initialState_ = state;
    return *this;
}

//------------------------------------------------------------------------------
::vk::ImageCreateInfo ImageResourceCreateInfo::NativeCreateInfo_() const {
    return ::vk::ImageCreateInfo()
        .setImageType(vk::ImageType::e2D)
        .setFormat(InternalEnumUtil::ToFormat(specInfo_.Format()))
        .setExtent({uint32_t(specInfo_.Extent().width),
            uint32_t(specInfo_.Extent().height),
            uint32_t(specInfo_.Extent().depth)})
        .setMipLevels(uint32_t(specInfo_.MipLevels()))
        .setArrayLayers(uint32_t(specInfo_.ArrayLength()))
        .setSamples(vk::SampleCountFlagBits::e1)
        .setTiling(InternalEnumUtil::ToImageTiling(specInfo_.Tiling()))
        .setUsage(InternalEnumUtil::ToImageUsageFlags(specInfo_.UsageBitSet()))
        .setSharingMode(vk::SharingMode::eExclusive)
        .setQueueFamilyIndexCount(0)
        .setPQueueFamilyIndices(nullptr)
        .setInitialLayout(vk::ImageLayout::eUndefined);
}

} // namespace gfx_low
} // namespace ae
// EOF
