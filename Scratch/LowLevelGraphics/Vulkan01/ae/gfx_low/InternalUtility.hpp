// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class ImageResource;
class ImageSubresourceLocation;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// 内部実装用便利機能群。
struct InternalUtility {
    /// @param aspectFlagsHint ImageAspectFlags が事前に分かっている場合は指定。（処理負荷削減目的の引数）
    static ::vk::ImageSubresourceRange ToImageSubresourceRange(
        const ImageResource& resource,
        const ImageSubresourceLocation& location,
        const ::vk::ImageAspectFlags& aspectFlagsHint = {});
};

} // namespace gfx_low
} // namespace ae
// EOF
