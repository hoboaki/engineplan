// 文字コード：UTF-8
#include <ae/gfx_low/ImageResource.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/ImageResourceCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
ImageResource::ImageResource(const ImageResourceCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, image_()
, isCreatedByImagePtr_(false) {
    // ImagePtr からの作成
    if (createInfo.ImagePtr_() != nullptr) {
        AE_BASE_ASSERT(createInfo.ImagePtr_() != nullptr);
        image_ = base::PtrToRef(createInfo.ImagePtr_());
        isCreatedByImagePtr_ = true;
        return;    
    }
    
    // VkImage の作成
    { 
        const auto nativeCreateInfo = createInfo.NativeCreateInfo_();
        const auto result = device_.Instance_().createImage(
                &nativeCreateInfo, nullptr, &image_);
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }

    // メモリ割り当て
    {
        AE_BASE_ASSERT(createInfo.DataAddress().Memory().IsValid());
        const auto result = device_.Instance_().bindImageMemory(
            image_,
            createInfo.DataAddress().Memory().Instance_(),
            createInfo.DataAddress().Offset()
            );
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }
}

//------------------------------------------------------------------------------
ImageResource::~ImageResource() {
    // ImagePtr から作った場合は何もしない
    if (isCreatedByImagePtr_) {
        image_ = ::vk::Image();
        return;
    }

    device_.Instance_().destroyImage(image_, nullptr);
    image_ = ::vk::Image();
}

} // namespace gfx_low
} // namespace ae
// EOF
