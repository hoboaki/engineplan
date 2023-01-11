// 文字コード：UTF-8
#include <ae/gfx_low/InternalUtility.hpp>

// includes
#include <ae/gfx_low/ImageResource.hpp>
#include <ae/gfx_low/ImageSubresourceLocation.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
::vk::ImageSubresourceRange InternalUtility::ToImageSubresourceRange(
    const ImageResource& resource,
    const ImageSubresourceLocation& location,
    const ::vk::ImageAspectFlags& aspectFlagsHint)
{
    const ::vk::ImageAspectFlags aspectFlags =
        aspectFlagsHint
            ? aspectFlagsHint
            : InternalEnumUtil::ToImageAspectFlags(resource.NativeFormat_());
    const uint32_t perLayerImageCount = resource.IsCubeMapImage_() ? 6 : 1;
    return ::vk::ImageSubresourceRange(
        aspectFlags,
        location.MipLevel(), // baseMipLevel
        1, // levelCount
        perLayerImageCount * location.ArrayIndex() +
            location.FaceIndex(), // baseArrayLayer
        1 // layerCount
    );
}

} // namespace ae::gfx_low
// EOF
