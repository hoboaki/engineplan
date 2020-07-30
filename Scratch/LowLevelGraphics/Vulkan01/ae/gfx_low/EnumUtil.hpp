// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/AttachmentLoadOp.hpp>
#include <ae/gfx_low/AttachmentStoreOp.hpp>
#include <ae/gfx_low/ImageResourceState.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// Enum に関する便利関数郡。
struct EnumUtil {
    static ::vk::AttachmentLoadOp ToNative(AttachmentLoadOp loadOp);
    static ::vk::AttachmentStoreOp ToNative(AttachmentStoreOp storeOp);
    static ::vk::ImageLayout ToImageLayoutForColorAttachment(
        ImageResourceState state);
};

} // namespace gfx_low
} // namespace ae
// EOF
