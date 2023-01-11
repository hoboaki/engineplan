// 文字コード：UTF-8
#include <ae/gfx_low/ImageResource.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/ImageResourceCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
ImageResource::ImageResource(const ImageResourceCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, nativeObject_()
, nativeFormat_()
, mipLevels_()
, arrayLength_()
, isCreatedByNativeObjectPtr_(false)
, isCubeMapImage_()
{
    // NativeObjectPtr からの作成
    if (createInfo.NativeObjectPtr_() != nullptr) {
        AE_BASE_ASSERT(createInfo.NativeObjectPtr_() != nullptr);
        nativeObject_ = base::PtrToRef(createInfo.NativeObjectPtr_());
        nativeFormat_ = createInfo.NativeFormat_();
        mipLevels_ = createInfo.NativeObjectMipLevels_();
        arrayLength_ = createInfo.NativeObjectArrayLength_();
        isCubeMapImage_ = createInfo.IsNativeObjectCubeImage_();
        isCreatedByNativeObjectPtr_ = true;
        return;
    }

    // VkImage の作成
    {
        const auto nativeCreateInfo = createInfo.NativeCreateInfo_();
        const auto result = device_.NativeObject_().createImage(
            &nativeCreateInfo,
            nullptr,
            &nativeObject_);
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
        nativeFormat_ = nativeCreateInfo.format;
        mipLevels_ = createInfo.NativeObjectMipLevels_();
        arrayLength_ = createInfo.NativeObjectArrayLength_();
        isCubeMapImage_ =
            createInfo.SpecInfo().Kind() == ImageResourceKind::ImageCube;
    }

    // メモリ割り当て
    {
        AE_BASE_ASSERT(createInfo.DataAddress().Memory().IsValid());
        const auto result = device_.NativeObject_().bindImageMemory(
            nativeObject_,
            createInfo.DataAddress().Memory().NativeObject_(),
            createInfo.DataAddress().Offset());
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }
}

//------------------------------------------------------------------------------
ImageResource::~ImageResource()
{
    // NativeObjectPtr から作った場合は何もしない
    if (isCreatedByNativeObjectPtr_) {
        nativeObject_ = ::vk::Image();
        return;
    }

    device_.NativeObject_().destroyImage(nativeObject_, nullptr);
    nativeObject_ = ::vk::Image();
}

} // namespace ae::gfx_low
// EOF
