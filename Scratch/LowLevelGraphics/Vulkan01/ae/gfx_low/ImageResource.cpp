// 文字コード：UTF-8
#include <ae/gfx_low/ImageResource.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/ImageResourceCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
ImageResource::ImageResource(const ImageResourceCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, image_() {
    // 今は ImagePtr を使った方法しか対応しない
    AE_BASE_ASSERT(createInfo.PrvImagePtr() != nullptr);
    image_ = base::PtrToRef(createInfo.PrvImagePtr());
}

//------------------------------------------------------------------------------
ImageResource::~ImageResource() {}

}  // namespace gfx_low
}  // namespace ae
// EOF
