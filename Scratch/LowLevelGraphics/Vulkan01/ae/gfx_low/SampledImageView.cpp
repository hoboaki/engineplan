// 文字コード：UTF-8
#include <ae/gfx_low/SampledImageView.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/ImageResource.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/SampledImageViewCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
SampledImageView::SampledImageView(const SampledImageViewCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, nativeObject_() {
    const auto nativeFormat = InternalEnumUtil::ToFormat(createInfo.Format());
    const auto imageViewCreateInfo =
        ::vk::ImageViewCreateInfo()
            .setImage(base::PtrToRef(createInfo.Resource()).NativeObject_())
            .setViewType(InternalEnumUtil::ToImageViewType(createInfo.Kind()))
            .setFormat(nativeFormat)
            .setSubresourceRange(::vk::ImageSubresourceRange(
                InternalEnumUtil::ToImageAspectFlags(nativeFormat), 0, 1, 0,
                1));
    const auto result = device_.NativeObject_().createImageView(
        &imageViewCreateInfo, nullptr, &nativeObject_);
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
}

//------------------------------------------------------------------------------
SampledImageView::~SampledImageView() {
    device_.NativeObject_().destroyImageView(nativeObject_, nullptr);
}

} // namespace gfx_low
} // namespace ae
// EOF
