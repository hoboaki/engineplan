// 文字コード：UTF-8
#include <ae/gfx_low/RenderTargetImageView.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/ImageResource.hpp>
#include <ae/gfx_low/RenderTargetImageViewCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
RenderTargetImageView::RenderTargetImageView(
    const RenderTargetImageViewCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, imageView_() {
    // 今は RawFormat しか対応しない
    auto imageFormat = createInfo.RawFormat_();
    AE_BASE_ASSERT(imageFormat != ::vk::Format::eUndefined);

    auto imageViewCreateInfo =
        ::vk::ImageViewCreateInfo()
            .setImage(base::PtrToRef(createInfo.ImageResource()).Instance_())
            .setViewType(::vk::ImageViewType::e2D)
            .setFormat(imageFormat)
            .setSubresourceRange(::vk::ImageSubresourceRange(
                ::vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));
    const auto result = device_.Instance_().createImageView(
        &imageViewCreateInfo, nullptr, &imageView_);
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
}

//------------------------------------------------------------------------------
RenderTargetImageView::~RenderTargetImageView() {
    device_.Instance_().destroyImageView(imageView_, nullptr);
}

} // namespace gfx_low
} // namespace ae
// EOF
