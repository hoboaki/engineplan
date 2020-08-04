// 文字コード：UTF-8
#include <ae/gfx_low/DepthStencilImageView.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/DepthStencilImageViewCreateInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/ImageResource.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
DepthStencilImageView::DepthStencilImageView(
    const DepthStencilImageViewCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, imageView_() {
    auto imageViewCreateInfo =
        ::vk::ImageViewCreateInfo()
            .setImage(base::PtrToRef(createInfo.Resource()).Instance_())
            .setViewType(InternalEnumUtil::ToImageViewType(createInfo.Kind()))
            .setFormat(InternalEnumUtil::ToFormat(createInfo.Format()))
            .setSubresourceRange(::vk::ImageSubresourceRange(
                ::vk::ImageAspectFlagBits::eDepth, 0, 1, 0, 1));
    const auto result = device_.Instance_().createImageView(
        &imageViewCreateInfo, nullptr, &imageView_);
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
}

//------------------------------------------------------------------------------
DepthStencilImageView::~DepthStencilImageView()
{
    device_.Instance_().destroyImageView(imageView_, nullptr);
}

} // namespace gfx_low
} // namespace ae
// EOF