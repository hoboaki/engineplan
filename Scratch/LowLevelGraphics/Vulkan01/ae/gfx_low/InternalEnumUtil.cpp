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
    const auto result = table[int(loadOp)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
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
    const auto result = table[int(storeOp)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::BlendFactor InternalEnumUtil::ToBlendFactorForColor(
    const BlendFactor factor) {
    AE_BASE_ASSERT_ENUM(factor, BlendFactor);
    AE_BASE_ASSERT(factor != BlendFactor::Invalid);
    const ::vk::BlendFactor table[] = {
        ::vk::BlendFactor(-1), // Invalid,
        ::vk::BlendFactor::eZero,
        ::vk::BlendFactor::eOne,
        ::vk::BlendFactor::eSrcColor,
        ::vk::BlendFactor::eOneMinusSrcColor,
        ::vk::BlendFactor::eDstColor,
        ::vk::BlendFactor::eOneMinusDstColor,
        ::vk::BlendFactor::eSrcAlpha,
        ::vk::BlendFactor::eOneMinusSrcAlpha,
        ::vk::BlendFactor::eDstAlpha,
        ::vk::BlendFactor::eOneMinusDstAlpha,
        ::vk::BlendFactor::eConstantColor, // Constant
        ::vk::BlendFactor::eOneMinusConstantColor, // OneMinusConstant
        ::vk::BlendFactor::eSrcAlphaSaturate,
        ::vk::BlendFactor::eSrc1Color,
        ::vk::BlendFactor::eOneMinusSrc1Color,
        ::vk::BlendFactor::eSrc1Alpha,
        ::vk::BlendFactor::eOneMinusSrc1Alpha,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(BlendFactor::TERM));
    const auto result = table[int(factor)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::BlendFactor InternalEnumUtil::ToBlendFactorForAlpha(
    const BlendFactor factor) {
    AE_BASE_ASSERT_ENUM(factor, BlendFactor);
    AE_BASE_ASSERT(factor != BlendFactor::Invalid);
    const ::vk::BlendFactor table[] = {
        ::vk::BlendFactor(-1), // Invalid,
        ::vk::BlendFactor::eZero,
        ::vk::BlendFactor::eOne,
        ::vk::BlendFactor::eSrcColor,
        ::vk::BlendFactor::eOneMinusSrcColor,
        ::vk::BlendFactor::eDstColor,
        ::vk::BlendFactor::eOneMinusDstColor,
        ::vk::BlendFactor::eSrcAlpha,
        ::vk::BlendFactor::eOneMinusSrcAlpha,
        ::vk::BlendFactor::eDstAlpha,
        ::vk::BlendFactor::eOneMinusDstAlpha,
        ::vk::BlendFactor::eConstantAlpha, // Constant
        ::vk::BlendFactor::eOneMinusConstantAlpha, // OneMinusConstant
        ::vk::BlendFactor::eSrcAlphaSaturate,
        ::vk::BlendFactor::eSrc1Color,
        ::vk::BlendFactor::eOneMinusSrc1Color,
        ::vk::BlendFactor::eSrc1Alpha,
        ::vk::BlendFactor::eOneMinusSrc1Alpha,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(BlendFactor::TERM));
    const auto result = table[int(factor)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::BlendOp InternalEnumUtil::ToBlendOp(const BlendOp op) {
    AE_BASE_ASSERT_ENUM(op, BlendOp);
    AE_BASE_ASSERT(op != BlendOp::Invalid);
    const ::vk::BlendOp table[] = {
        ::vk::BlendOp(-1), // Invalid,
        ::vk::BlendOp::eAdd,
        ::vk::BlendOp::eSubtract,
        ::vk::BlendOp::eReverseSubtract,
        ::vk::BlendOp::eMin,
        ::vk::BlendOp::eMax,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(BlendOp::TERM));
    const auto result = table[int(op)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::BufferUsageFlags InternalEnumUtil::ToBufferUsageFlags(
    const BufferResourceUsageBitSet& usageBitSet) {
    const ::vk::BufferUsageFlagBits table[] = {
        ::vk::BufferUsageFlagBits(0), // Invalid
        ::vk::BufferUsageFlagBits::eTransferSrc, // CopySrc
        ::vk::BufferUsageFlagBits::eTransferDst, // CopyDst
        ::vk::BufferUsageFlagBits::eUniformBuffer, // UniformBuffer
        ::vk::BufferUsageFlagBits::eStorageBuffer, // StorageBuffer
        ::vk::BufferUsageFlagBits::eIndexBuffer, // IndexBuffer
        ::vk::BufferUsageFlagBits::eVertexBuffer, // VertexBuffer
        ::vk::BufferUsageFlagBits::eIndirectBuffer, // IndirectBuffer
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(BufferResourceUsage::TERM));
    auto result = ::vk::BufferUsageFlags();
    for (int i = int(BufferResourceUsage::Invalid) + 1;
         i < int(BufferResourceUsage::TERM); ++i) {
        if (usageBitSet.Get(BufferResourceUsage(i))) {
            result |= table[i];
        }
    }
    AE_BASE_ASSERT_NOT_EQUALS(uint32_t(result), 0);
    return result;
}

//------------------------------------------------------------------------------
::vk::ColorComponentFlags InternalEnumUtil::ToColorComponentFlags(
    const RenderTargetComponentBitSet& componentBitSet) {
    const ::vk::ColorComponentFlagBits table[] = {
        ::vk::ColorComponentFlagBits(0), // Invalid
        ::vk::ColorComponentFlagBits::eR,
        ::vk::ColorComponentFlagBits::eG,
        ::vk::ColorComponentFlagBits::eB,
        ::vk::ColorComponentFlagBits::eA,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(RenderTargetComponent::TERM));
    auto result = ::vk::ColorComponentFlags();
    for (int i = int(RenderTargetComponent::Invalid) + 1;
         i < int(RenderTargetComponent::TERM); ++i) {
        if (componentBitSet.Get(RenderTargetComponent(i))) {
            result |= table[i];
        }
    }
    AE_BASE_ASSERT_NOT_EQUALS(uint32_t(result), 0);
    return result;
}

//------------------------------------------------------------------------------
::vk::CompareOp InternalEnumUtil::ToCompareOp(const CompareOp op) {
    AE_BASE_ASSERT_ENUM(op, CompareOp);
    AE_BASE_ASSERT(op != CompareOp::Invalid);
    const ::vk::CompareOp table[] = {
        ::vk::CompareOp(-1), // Invalid,
        ::vk::CompareOp::eNever,
        ::vk::CompareOp::eLess,
        ::vk::CompareOp::eEqual,
        ::vk::CompareOp::eLessOrEqual,
        ::vk::CompareOp::eGreater,
        ::vk::CompareOp::eNotEqual,
        ::vk::CompareOp::eGreaterOrEqual,
        ::vk::CompareOp::eAlways,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(CompareOp::TERM));
    const auto result = table[int(op)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::CullModeFlags InternalEnumUtil::ToCullModeFlags(const RasterizeCullMode mode) {
    AE_BASE_ASSERT_ENUM(mode, RasterizeCullMode);
    AE_BASE_ASSERT(mode != RasterizeCullMode::Invalid);
    // Vulkan は BitFlag だが gfx_low の仕様は enum なので複数ビット返すことはない
    const ::vk::CullModeFlags table[] = {
        ::vk::CullModeFlags(-1), // Invalid,
        ::vk::CullModeFlagBits::eNone,
        ::vk::CullModeFlagBits::eFront,
        ::vk::CullModeFlagBits::eBack,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(RasterizeCullMode::TERM));
    const auto result = table[int(mode)];
    return table[int(mode)];
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
::vk::FrontFace InternalEnumUtil::ToFrontFace(const PolygonFrontFace face) {
    AE_BASE_ASSERT_ENUM(face, PolygonFrontFace);
    AE_BASE_ASSERT(face != PolygonFrontFace::Invalid);
    const ::vk::FrontFace table[] = {
        ::vk::FrontFace(-1), // Invalid,
        ::vk::FrontFace::eClockwise,
        ::vk::FrontFace::eCounterClockwise,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(PolygonFrontFace::TERM));
    const auto result = table[int(face)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
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
    const ::vk::ImageLayout table[] = {
        ::vk::ImageLayout(-1), // Invalid
        ::vk::ImageLayout::eUndefined, // Unknown
        ::vk::ImageLayout(-1), // RenderTarget
        ::vk::ImageLayout(-1), // PresentSrc
        ::vk::ImageLayout::eDepthStencilAttachmentOptimal, // DepthStencil
        ::vk::ImageLayout::eDepthStencilReadOnlyOptimal, // DepthStencilReadOnly
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(ImageResourceState::TERM));
    const auto result = table[int(state)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
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
    const auto result = table[int(kind)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
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
    const auto result = table[int(tiling)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
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
    AE_BASE_ASSERT_NOT_EQUALS(uint32_t(result), 0);
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
    const auto result = table[int(kind)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::PolygonMode InternalEnumUtil::ToPolygonMode(
    const RasterizeFillMode kind) {
    AE_BASE_ASSERT_ENUM(kind, RasterizeFillMode);
    AE_BASE_ASSERT(kind != RasterizeFillMode::Invalid);
    const ::vk::PolygonMode table[] = {
        ::vk::PolygonMode(-1), // Invalid
        ::vk::PolygonMode::eLine, // Wireframe,
        ::vk::PolygonMode::eFill, // Solid,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(RasterizeFillMode::TERM));
    const auto result = table[int(kind)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::PrimitiveTopology InternalEnumUtil::ToPrimitiveTopology(
    const PrimitiveTopologyKind kind) {
    AE_BASE_ASSERT_ENUM(kind, PrimitiveTopologyKind);
    AE_BASE_ASSERT(kind != PrimitiveTopologyKind::Invalid);
    const ::vk::PrimitiveTopology table[] = {
        ::vk::PrimitiveTopology(-1), // Invalid
        ::vk::PrimitiveTopology::ePointList,
        ::vk::PrimitiveTopology::eLineList,
        ::vk::PrimitiveTopology::eLineStrip,
        ::vk::PrimitiveTopology::eTriangleList,
        ::vk::PrimitiveTopology::eTriangleStrip,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(PrimitiveTopologyKind::TERM));
    const auto result = table[int(kind)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::ShaderStageFlagBits InternalEnumUtil::ToShaderStageFlagBits(
    const RenderPipelineShaderStage stage) {
    AE_BASE_ASSERT_ENUM(stage, RenderPipelineShaderStage);
    AE_BASE_ASSERT(stage != RenderPipelineShaderStage::Invalid);
    const ::vk::ShaderStageFlagBits table[] = {
        ::vk::ShaderStageFlagBits(-1), // Invalid
        ::vk::ShaderStageFlagBits::eVertex,
        ::vk::ShaderStageFlagBits::eGeometry,
        ::vk::ShaderStageFlagBits::eFragment,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(RenderPipelineShaderStage::TERM));
    const auto result = table[int(stage)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::StencilOp InternalEnumUtil::ToStencilOp(const StencilOp op) {
    AE_BASE_ASSERT_ENUM(op, StencilOp);
    AE_BASE_ASSERT(op != StencilOp::Invalid);
    const ::vk::StencilOp table[] = {
        ::vk::StencilOp(-1), // Invalid,
        ::vk::StencilOp::eKeep,
        ::vk::StencilOp::eZero,
        ::vk::StencilOp::eReplace,
        ::vk::StencilOp::eIncrementAndClamp,
        ::vk::StencilOp::eDecrementAndClamp,
        ::vk::StencilOp::eInvert,
        ::vk::StencilOp::eIncrementAndWrap,
        ::vk::StencilOp::eDecrementAndWrap,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(StencilOp::TERM));
    const auto result = table[int(op)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

} // namespace gfx_low
} // namespace ae
// EOF
