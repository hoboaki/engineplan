// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/AttachmentLoadOp.hpp>
#include <ae/gfx_low/AttachmentStoreOp.hpp>
#include <ae/gfx_low/ImageFormat.hpp>
#include <ae/gfx_low/ImageKind.hpp>
#include <ae/gfx_low/ImageResourceState.hpp>
#include <ae/gfx_low/ImageResourceTiling.hpp>
#include <ae/gfx_low/ImageResourceUsageBitSet.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// Enum に関する便利関数郡。
struct EnumUtil {
    static ::vk::AttachmentLoadOp ToNative(AttachmentLoadOp loadOp);
    static ::vk::AttachmentStoreOp ToNative(AttachmentStoreOp storeOp);
    static ::vk::Format ToFormat(ImageFormat format);
    static ::vk::ImageLayout ToImageLayoutForColorAttachment(
        ImageResourceState state);
    static ::vk::ImageTiling ToImageTiling(ImageResourceTiling tiling);
    static ::vk::ImageType ToImageType(ImageKind kind);
    static ::vk::ImageUsageFlags ToImageUsageFlags(
        const ImageResourceUsageBitSet& usageBitSet);
};

} // namespace gfx_low
} // namespace ae
// EOF
