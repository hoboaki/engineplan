// 文字コード：UTF-8
#include <ae/gfx_low/DepthStencilImageView.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/DepthStencilImageViewCreateInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/ImageResource.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/InternalUtility.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
DepthStencilImageView::DepthStencilImageView(
    const DepthStencilImageViewCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, nativeObject_()
{
    const auto imageViewCreateInfo =
        ::vk::ImageViewCreateInfo()
            .setImage(base::PtrToRef(createInfo.Resource()).NativeObject_())
            .setViewType(::vk::ImageViewType::e2D)
            .setFormat(InternalEnumUtil::ToFormat(createInfo.Format()))
            .setSubresourceRange(InternalUtility::ToImageSubresourceRange(
                base::PtrToRef(createInfo.Resource()),
                createInfo.SubresouceLocation(),
                ::vk::ImageAspectFlagBits::eDepth));
    const auto result = device_.NativeObject_().createImageView(
        &imageViewCreateInfo,
        nullptr,
        &nativeObject_);
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
}

//------------------------------------------------------------------------------
DepthStencilImageView::~DepthStencilImageView()
{
    device_.NativeObject_().destroyImageView(nativeObject_, nullptr);
}

} // namespace ae::gfx_low
// EOF
