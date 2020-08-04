// 文字コード：UTF-8
#include <ae/gfx_low/InternalEnumUtil.hpp>

// includes
#include <ae/base/ArrayLength.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/StaticAssert.hpp>
#include <ae/gfx_low/EnumUtil.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
::vk::AttachmentLoadOp InternalEnumUtil::ToAttachmentLoadOp(
    const AttachmentLoadOp loadOp) {
    AE_BASE_ASSERT_ENUM(loadOp, AttachmentLoadOp);
    AE_BASE_ASSERT(loadOp != AttachmentLoadOp::Invalid);
    const ::vk::AttachmentLoadOp table[] = {
        ::vk::AttachmentLoadOp(-1), // Invalid
        ::vk::AttachmentLoadOp::eDontCare, // DontCare
        ::vk::AttachmentLoadOp::eLoad, // Load
        ::vk::AttachmentLoadOp::eClear, // Clear
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(AttachmentLoadOp::TERM));
    return table[int(loadOp)];
}

//------------------------------------------------------------------------------
::vk::AttachmentStoreOp InternalEnumUtil::ToAttachmentStoreOp(
    const AttachmentStoreOp storeOp) {
    AE_BASE_ASSERT_ENUM(storeOp, AttachmentStoreOp);
    AE_BASE_ASSERT(storeOp != AttachmentStoreOp::Invalid);
    const ::vk::AttachmentStoreOp table[] = {
        ::vk::AttachmentStoreOp(-1), // Invalid
        ::vk::AttachmentStoreOp::eDontCare, // DontCare
        ::vk::AttachmentStoreOp::eStore, // Store
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(AttachmentStoreOp::TERM));
    return table[int(storeOp)];
}

//------------------------------------------------------------------------------
::vk::Format InternalEnumUtil::ToFormat(const ImageFormat format) {
    AE_BASE_ASSERT_ENUM(format, ImageFormat);
    AE_BASE_ASSERT(format != ImageFormat::Invalid);
    const ::vk::Format table[] = {
        ::vk::Format::eUndefined, // Invalid

        ::vk::Format::eR8Sint, // R8Sint
        ::vk::Format::eR8Snorm, // R8Snorm
        ::vk::Format::eR8Uint, // R8Uint
        ::vk::Format::eR8Unorm, // R8Unorm
        ::vk::Format::eR16Sfloat, // R16Sfloat
        ::vk::Format::eR16Sint, // R16Sint
        ::vk::Format::eR16Snorm, // R16Snorm
        ::vk::Format::eR16Uint, // R16Uint
        ::vk::Format::eR16Unorm, // R16Unorm

        ::vk::Format::eR8G8Sint, // R8G8Sint
        ::vk::Format::eR8G8Snorm, // R8G8Snorm
        ::vk::Format::eR8G8Uint, // R8G8Uint
        ::vk::Format::eR8G8Unorm, // R8G8Unorm
        ::vk::Format::eR16G16Sfloat, // R16G16Sfloat
        ::vk::Format::eR16G16Sint, // R16G16Sint
        ::vk::Format::eR16G16Snorm, // R16G16Snorm
        ::vk::Format::eR16G16Uint, // R16G16Uint
        ::vk::Format::eR16G16Unorm, // R16G16Unorm

        ::vk::Format::eB10G11R11UfloatPack32, // R11G11B10Ufloat

        ::vk::Format::eR8G8B8A8Uint, // R8G8B8A8Uint
        ::vk::Format::eR8G8B8A8Unorm, // R8G8B8A8Unorm
        ::vk::Format::eR8G8B8A8Srgb, // R8G8B8A8UnormSrgb
        ::vk::Format::eA2R10G10B10UintPack32, // R10G10B10A2Uint
        ::vk::Format::eA2R10G10B10UnormPack32, // R10G10B10A2Unorm
        ::vk::Format::eR16G16B16A16Sfloat, // R16G16B16A16Sfloat
        ::vk::Format::eR16G16B16A16Sint, // R16G16B16A16Sint
        ::vk::Format::eR16G16B16A16Snorm, // R16G16B16A16Snorm
        ::vk::Format::eR16G16B16A16Uint, // R16G16B16A16Uint
        ::vk::Format::eR16G16B16A16Unorm, // R16G16B16A16Unorm

        ::vk::Format::eD16Unorm, // D16Unorm
        ::vk::Format::eD32Sfloat, // D32Sfloat

        ::vk::Format::eD16UnormS8Uint, // D16UnormS8Uint
        ::vk::Format::eD24UnormS8Uint, // D24UnormS8Uint
        ::vk::Format::eD32SfloatS8Uint, // D32SfloatS8Uint

        ::vk::Format::eS8Uint, // S8Uint
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(ImageFormat::TERM));
    return table[int(format)];
}

//------------------------------------------------------------------------------
::vk::ImageLayout InternalEnumUtil::ToImageLayoutForColorAttachment(
    const ImageResourceState state) {
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);
    AE_BASE_ASSERT(state != ImageResourceState::Invalid);
    const ::vk::ImageLayout table[] = {
        ::vk::ImageLayout(-1), // Invalid
        ::vk::ImageLayout::eUndefined, // Unknown
        ::vk::ImageLayout::eColorAttachmentOptimal, // RenderTarget
        ::vk::ImageLayout::ePresentSrcKHR, // PresentSrc
        ::vk::ImageLayout(-1), // DepthStencil
        ::vk::ImageLayout(-1), // DepthStencilReadOnly
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(ImageResourceState::TERM));
    const auto result = table[int(state)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::ImageLayout InternalEnumUtil::ToImageLayoutForDepthStencilAttachment(
    const ImageResourceState state, const ImageFormat format) {
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);
    AE_BASE_ASSERT(state != ImageResourceState::Invalid);
    const bool hasDepth = EnumUtil::HasDepthComponent(format);
    const bool hasStencil = EnumUtil::HasStencilComponent(format);
    AE_BASE_ASSERT(hasDepth || hasStencil);
    switch (state) {
    case ImageResourceState::Unknown: return ::vk::ImageLayout::eUndefined;
    case ImageResourceState::DepthStencil: 
        if (hasDepth && hasStencil) {
            return ::vk::ImageLayout::eDepthStencilAttachmentOptimal;
        } else if (hasDepth) {
            return ::vk::ImageLayout::eDepthStencilAttachmentOptimal;
        } else if (hasStencil) {
            return ::vk::ImageLayout::eDepthStencilAttachmentOptimal;
        }
        AE_BASE_ASSERT_NOT_REACHED();
        break;
    case ImageResourceState::DepthStencilReadOnly:
        if (hasDepth && hasStencil) {
            return ::vk::ImageLayout::eDepthStencilReadOnlyOptimal;
        } else if (hasDepth) {
            return ::vk::ImageLayout::eDepthStencilReadOnlyOptimal;
        } else if (hasStencil) {
            return ::vk::ImageLayout::eDepthStencilReadOnlyOptimal;
        }
        AE_BASE_ASSERT_NOT_REACHED();
        break;
    default: 
        AE_BASE_ASSERT_NOT_REACHED_MSGFMT(
            "Invalid state(%d) for depth stencil attachment.", int(state));
        break;
    }
    return ::vk::ImageLayout(-1);
}

//------------------------------------------------------------------------------
::vk::ImageType InternalEnumUtil::ToImageType(const ImageResourceKind kind) {
    AE_BASE_ASSERT_ENUM(kind, ImageResourceKind);
    AE_BASE_ASSERT(kind != ImageResourceKind::Invalid);
    const ::vk::ImageType table[] = {
        ::vk::ImageType(-1), // Invalid
        ::vk::ImageType::e1D, // Image1d
        ::vk::ImageType::e2D, // Image2d
        ::vk::ImageType::e3D, // Image3d
        ::vk::ImageType::e2D, // ImageCube
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(ImageResourceKind::TERM));
    return table[int(kind)];
}

//------------------------------------------------------------------------------
::vk::ImageTiling InternalEnumUtil::ToImageTiling(
    const ImageResourceTiling tiling) {
    AE_BASE_ASSERT_ENUM(tiling, ImageResourceTiling);
    AE_BASE_ASSERT(tiling != ImageResourceTiling::Invalid);
    const ::vk::ImageTiling table[] = {
        ::vk::ImageTiling(-1), // Invalid
        ::vk::ImageTiling::eLinear, // Linear
        ::vk::ImageTiling::eOptimal, // Optimal
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(ImageResourceTiling::TERM));
    return table[int(tiling)];
}

//------------------------------------------------------------------------------
::vk::ImageUsageFlags InternalEnumUtil::ToImageUsageFlags(
    const ImageResourceUsageBitSet& usageBitSet) {
    const ::vk::ImageUsageFlagBits table[] = {
        ::vk::ImageUsageFlagBits(0), // Invalid
        ::vk::ImageUsageFlagBits::eTransferSrc, // CopySrc
        ::vk::ImageUsageFlagBits::eTransferDst, // CopyDst
        ::vk::ImageUsageFlagBits::eSampled, // SampledImage
        ::vk::ImageUsageFlagBits::eStorage, // StorageImage
        ::vk::ImageUsageFlagBits::eColorAttachment, // RenderTargetImage
        ::vk::ImageUsageFlagBits::eDepthStencilAttachment, // DepthStencilImage
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(ImageResourceUsage::TERM));
    auto result = ::vk::ImageUsageFlags();
    for (int i = 0; i < int(ImageResourceUsage::TERM); ++i) {
        if (usageBitSet.Get(ImageResourceUsage(i))) {
            result |= table[i];
        }
    }
    return result;
}

//------------------------------------------------------------------------------
::vk::ImageViewType InternalEnumUtil::ToImageViewType(
    const ImageViewKind kind) {
    AE_BASE_ASSERT_ENUM(kind, ImageViewKind);
    AE_BASE_ASSERT(kind != ImageViewKind::Invalid);
    const ::vk::ImageViewType table[] = {
        ::vk::ImageViewType(-1), // Invalid
        ::vk::ImageViewType::e1D, // Image1d
        ::vk::ImageViewType::e2D, // Image2d
        ::vk::ImageViewType::e3D, // Image3d
        ::vk::ImageViewType::eCube, // ImageCube
        ::vk::ImageViewType::e1DArray, // Image1dArray
        ::vk::ImageViewType::e2DArray, // Image2dArray
        ::vk::ImageViewType::eCubeArray, // ImageCubeArray
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(ImageViewKind::TERM));
    return table[int(kind)];
}

} // namespace gfx_low
} // namespace ae
// EOF
