// 文字コード：UTF-8
#include <ae/gfx_low/EnumUtil.hpp>

// includes
#include <ae/base/ArrayLength.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/StaticAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
::vk::AttachmentLoadOp EnumUtil::ToNative(const AttachmentLoadOp loadOp) {
    AE_BASE_ASSERT_ENUM(loadOp, AttachmentLoadOp);
    AE_BASE_ASSERT(loadOp != AttachmentLoadOp::Invalid);
    const ::vk::AttachmentLoadOp table[] = {
        ::vk::AttachmentLoadOp::eDontCare,  // Invalid
        ::vk::AttachmentLoadOp::eDontCare,  // DontCare
        ::vk::AttachmentLoadOp::eLoad,      // Load
        ::vk::AttachmentLoadOp::eClear,     // Clear
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(AttachmentLoadOp::TERM));
    return table[int(loadOp)];
}

//------------------------------------------------------------------------------
::vk::AttachmentStoreOp EnumUtil::ToNative(const AttachmentStoreOp storeOp) {
    AE_BASE_ASSERT_ENUM(storeOp, AttachmentStoreOp);
    AE_BASE_ASSERT(storeOp != AttachmentStoreOp::Invalid);
    const ::vk::AttachmentStoreOp table[] = {
        ::vk::AttachmentStoreOp::eDontCare,  // Invalid
        ::vk::AttachmentStoreOp::eDontCare,  // DontCare
        ::vk::AttachmentStoreOp::eStore,     // Store
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(AttachmentStoreOp::TERM));
    return table[int(storeOp)];
}

//------------------------------------------------------------------------------
::vk::ImageLayout EnumUtil::ToImageLayoutForColorAttachment(
    const ImageResourceState state) {
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);
    AE_BASE_ASSERT(state != ImageResourceState::Invalid);
    const ::vk::ImageLayout table[] = { 
        ::vk::ImageLayout::eUndefined, // Invalid
        ::vk::ImageLayout::eUndefined,  // Unknown
        ::vk::ImageLayout::eColorAttachmentOptimal,  // RenderTarget
        ::vk::ImageLayout::ePresentSrcKHR,  // PresentSrc
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(ImageResourceState::TERM));
    return table[int(state)];
}

}  // namespace gfx_low
}  // namespace ae
// EOF
