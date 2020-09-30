// 文字コード：UTF-8
#include <ae/gfx_low/RenderTargetImageView.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/ImageResource.hpp>
#include <ae/gfx_low/InternalUtility.hpp>
#include <ae/gfx_low/RenderTargetImageViewCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
RenderTargetImageView::RenderTargetImageView(
    const RenderTargetImageViewCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, nativeObject_() {
    // 今は RawFormat しか対応しない
    const auto imageFormat = createInfo.RawFormat_();
    AE_BASE_ASSERT(imageFormat != ::vk::Format::eUndefined);

    const auto imageViewCreateInfo =
        ::vk::ImageViewCreateInfo()
            .setImage(base::PtrToRef(createInfo.Resource()).NativeObject_())
            .setViewType(::vk::ImageViewType::e2D)
            .setFormat(imageFormat)
            .setSubresourceRange(InternalUtility::ToImageSubresourceRange(
                base::PtrToRef(createInfo.Resource()),
                createInfo.SubresouceLocation(),
                ::vk::ImageAspectFlagBits::eColor));
    const auto result = device_.NativeObject_().createImageView(
        &imageViewCreateInfo, nullptr, &nativeObject_);
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
}

//------------------------------------------------------------------------------
RenderTargetImageView::~RenderTargetImageView() {
    device_.NativeObject_().destroyImageView(nativeObject_, nullptr);
}

} // namespace gfx_low
} // namespace ae
// EOF
