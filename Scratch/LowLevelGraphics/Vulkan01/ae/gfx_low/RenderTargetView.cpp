// 文字コード：UTF-8
#include <ae/gfx_low/RenderTargetView.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/ImageResource.hpp>
#include <ae/gfx_low/RenderTargetViewCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
RenderTargetView::RenderTargetView(const RenderTargetViewCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, imageView_() {
    // 今は RawFormat しか対応しない
    auto imageFormat = createInfo.InternalRawFormat();
    AE_BASE_ASSERT(imageFormat != ::vk::Format::eUndefined);

    auto imageViewCreateInfo =
        ::vk::ImageViewCreateInfo()
            .setImage(
                base::PtrToRef(createInfo.ImageResource()).InternalInstance())
            .setViewType(::vk::ImageViewType::e2D)
            .setFormat(imageFormat)
            .setSubresourceRange(::vk::ImageSubresourceRange(
                ::vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));
    const auto result = device_.InternalInstance().createImageView(
        &imageViewCreateInfo, nullptr, &imageView_);
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
}

//------------------------------------------------------------------------------
RenderTargetView::~RenderTargetView() {
    device_.InternalInstance().destroyImageView(imageView_, nullptr);
}

}  // namespace gfx_low
}  // namespace ae
// EOF
