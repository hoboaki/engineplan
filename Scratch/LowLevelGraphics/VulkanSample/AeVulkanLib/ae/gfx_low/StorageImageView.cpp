// 文字コード：UTF-8
#include <ae/gfx_low/StorageImageView.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/ImageResource.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/StorageImageViewCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
StorageImageView::StorageImageView(const StorageImageViewCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, nativeObject_()
{
    const auto nativeFormat = InternalEnumUtil::ToFormat(createInfo.Format());
    const auto viewType = InternalEnumUtil::ToImageViewType(createInfo.Kind());
    const bool isCubeImageViewType =
        viewType == ::vk::ImageViewType::eCube ||
        viewType == ::vk::ImageViewType::eCubeArray;
    const auto& resource = base::PtrToRef(createInfo.Resource());

    // CubeImage のとき用エラーチェック
    if (isCubeImageViewType) {
        AE_BASE_ASSERT_EQUALS(
            createInfo.SubresourceRange().BaseLocation().FaceIndex(),
            0);
    }
    const uint32_t imageCountPerCubeImageLayer = 6;
    const uint32_t perLayerImageCountOnResource =
        resource.IsCubeMapImage_() ? imageCountPerCubeImageLayer : 1;
    const uint32_t perLayerImageCountOnView =
        isCubeImageViewType ? imageCountPerCubeImageLayer : 1;

    const auto imageViewCreateInfo =
        ::vk::ImageViewCreateInfo()
            .setImage(resource.NativeObject_())
            .setViewType(viewType)
            .setFormat(nativeFormat)
            .setSubresourceRange(::vk::ImageSubresourceRange(
                InternalEnumUtil::ToImageAspectFlags(nativeFormat),
                createInfo.SubresourceRange().BaseLocation().MipLevel(),
                createInfo.SubresourceRange().MipLevels(),
                perLayerImageCountOnResource * createInfo.SubresourceRange()
                                                   .BaseLocation()
                                                   .ArrayIndex() +
                    createInfo.SubresourceRange().BaseLocation().FaceIndex(),
                createInfo.SubresourceRange().ArrayLength() *
                    perLayerImageCountOnView));
    const auto result = device_.NativeObject_().createImageView(
        &imageViewCreateInfo,
        nullptr,
        &nativeObject_);
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
}

//------------------------------------------------------------------------------
StorageImageView::~StorageImageView()
{
    device_.NativeObject_().destroyImageView(nativeObject_, nullptr);
}

} // namespace ae::gfx_low
// EOF
