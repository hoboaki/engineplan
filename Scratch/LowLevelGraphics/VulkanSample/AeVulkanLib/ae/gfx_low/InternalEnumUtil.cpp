// 文字コード：UTF-8
#include <ae/gfx_low/InternalEnumUtil.hpp>

// includes
#include <ae/base/ArrayLength.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/StaticAssert.hpp>
#include <ae/gfx_low/EnumUtil.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
::vk::AttachmentLoadOp InternalEnumUtil::ToAttachmentLoadOp(
    const AttachmentLoadOp loadOp)
{
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
    const AttachmentStoreOp storeOp)
{
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
    const BlendFactor factor)
{
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
    const BlendFactor factor)
{
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
::vk::BlendOp InternalEnumUtil::ToBlendOp(const BlendOp op)
{
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
::vk::BorderColor InternalEnumUtil::ToBorderColor(
    const SamplerBorderColor color)
{
    AE_BASE_ASSERT_ENUM(color, SamplerBorderColor);
    AE_BASE_ASSERT(color != SamplerBorderColor::Invalid);
    const ::vk::BorderColor table[] = {
        ::vk::BorderColor(-1), // Invalid,
        ::vk::BorderColor::eFloatTransparentBlack,
        ::vk::BorderColor::eFloatOpaqueBlack,
        ::vk::BorderColor::eFloatOpaqueWhite,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(SamplerBorderColor::TERM));
    const auto result = table[int(color)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::BufferUsageFlags InternalEnumUtil::ToBufferUsageFlags(
    const BufferResourceUsageBitSet& usageBitSet)
{
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
         i < int(BufferResourceUsage::TERM);
         ++i) {
        if (usageBitSet.Get(BufferResourceUsage(i))) {
            result |= table[i];
        }
    }
    AE_BASE_ASSERT_NOT_EQUALS(uint32_t(result), 0);
    return result;
}

//------------------------------------------------------------------------------
::vk::ColorComponentFlags InternalEnumUtil::ToColorComponentFlags(
    const RenderTargetComponentBitSet& componentBitSet)
{
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
         i < int(RenderTargetComponent::TERM);
         ++i) {
        if (componentBitSet.Get(RenderTargetComponent(i))) {
            result |= table[i];
        }
    }
    return result;
}

//------------------------------------------------------------------------------
::vk::CommandBufferLevel InternalEnumUtil::ToCommandBufferLevel(
    const CommandBufferLevel level)
{
    AE_BASE_ASSERT_ENUM(level, CommandBufferLevel);
    AE_BASE_ASSERT(level != CommandBufferLevel::Invalid);
    const ::vk::CommandBufferLevel table[] = {
        ::vk::CommandBufferLevel(-1), // Invalid,
        ::vk::CommandBufferLevel::ePrimary,
        ::vk::CommandBufferLevel::eSecondary,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(CommandBufferLevel::TERM));
    const auto result = table[int(level)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::CompareOp InternalEnumUtil::ToCompareOp(const CompareOp op)
{
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
::vk::CullModeFlags InternalEnumUtil::ToCullModeFlags(
    const RasterizeCullMode mode)
{
    AE_BASE_ASSERT_ENUM(mode, RasterizeCullMode);
    AE_BASE_ASSERT(mode != RasterizeCullMode::Invalid);
    // Vulkan は BitFlag だが gfx_low の仕様は enum
    // なので複数ビット返すことはない
    const ::vk::CullModeFlags table[] = {
        ::vk::CullModeFlags(-1), // Invalid,
        ::vk::CullModeFlagBits::eNone,
        ::vk::CullModeFlagBits::eFront,
        ::vk::CullModeFlagBits::eBack,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(RasterizeCullMode::TERM));
    const auto result = table[int(mode)];
    AE_BASE_ASSERT(result != ::vk::CullModeFlags(-1));
    return result;
}

//------------------------------------------------------------------------------
::vk::Filter InternalEnumUtil::ToFilter(const SamplerMinMagFilter filter)
{
    AE_BASE_ASSERT_ENUM(filter, SamplerMinMagFilter);
    AE_BASE_ASSERT(filter != SamplerMinMagFilter::Invalid);
    const ::vk::Filter table[] = {
        ::vk::Filter(-1), // Invalid,
        ::vk::Filter::eNearest,
        ::vk::Filter::eLinear,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(SamplerMinMagFilter::TERM));
    const auto result = table[int(filter)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::Format InternalEnumUtil::ToFormat(const ImageFormat format)
{
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
        ::vk::Format::eR32Sfloat, // R32Sfloat
        ::vk::Format::eR32Sint, // R32Sint
        ::vk::Format::eR32Uint, // R32Uint

        ::vk::Format::eR8G8Sint, // R8G8Sint
        ::vk::Format::eR8G8Snorm, // R8G8Snorm
        ::vk::Format::eR8G8Uint, // R8G8Uint
        ::vk::Format::eR8G8Unorm, // R8G8Unorm
        ::vk::Format::eR16G16Sfloat, // R16G16Sfloat
        ::vk::Format::eR16G16Sint, // R16G16Sint
        ::vk::Format::eR16G16Snorm, // R16G16Snorm
        ::vk::Format::eR16G16Uint, // R16G16Uint
        ::vk::Format::eR16G16Unorm, // R16G16Unorm
        ::vk::Format::eR32G32Sfloat, // R32G32Sfloat
        ::vk::Format::eR32G32Sint, // R32G32Sint
        ::vk::Format::eR32G32Uint, // R32G32Uint

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
        ::vk::Format::eR32G32B32A32Sfloat, // R32G32B32A32Sfloat
        ::vk::Format::eR32G32B32A32Sint, // R32G32B32A32Sint
        ::vk::Format::eR32G32B32A32Uint, // R32G32B32A32Uint

        ::vk::Format::eD16Unorm, // D16Unorm
        ::vk::Format::eD32Sfloat, // D32Sfloat

        ::vk::Format::eD16UnormS8Uint, // D16UnormS8Uint
        ::vk::Format::eD24UnormS8Uint, // D24UnormS8Uint
        ::vk::Format::eD32SfloatS8Uint, // D32SfloatS8Uint

        ::vk::Format::eS8Uint, // S8Uint

        ::vk::Format::eBc1RgbUnormBlock, // Bc1RgbUnormBlock
        ::vk::Format::eBc1RgbSrgbBlock, // Bc1RgbUnormSrgbBlock
        ::vk::Format::eBc1RgbaUnormBlock, // Bc1RgbaUnormBlock
        ::vk::Format::eBc1RgbaSrgbBlock, // Bc1RgbaUnormSrgbBlock
        ::vk::Format::eBc2UnormBlock, // Bc2UnormBlock
        ::vk::Format::eBc2UnormBlock, // Bc2UnormSrgbBlock
        ::vk::Format::eBc3UnormBlock, // Bc3UnormBlock
        ::vk::Format::eBc3SrgbBlock, // Bc3UnormSrgbBlock
        ::vk::Format::eBc4SnormBlock, // Bc4SnormBlock
        ::vk::Format::eBc4UnormBlock, // Bc4UnormBlock
        ::vk::Format::eBc5SnormBlock, // Bc5SnormBlock
        ::vk::Format::eBc5UnormBlock, // Bc5UnormBlock
        ::vk::Format::eBc6HSfloatBlock, // Bc6SfloatBlock
        ::vk::Format::eBc6HUfloatBlock, // Bc6UfloatBlock
        ::vk::Format::eBc7UnormBlock, // Bc7SnormBlock
        ::vk::Format::eBc7SrgbBlock, // Bc7UnormBlock
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(ImageFormat::TERM));
    return table[int(format)];
}

//------------------------------------------------------------------------------
::vk::Format InternalEnumUtil::ToFormat(const VertexFormat format)
{
    AE_BASE_ASSERT_ENUM(format, VertexFormat);
    AE_BASE_ASSERT(format != VertexFormat::Invalid);
    const ::vk::Format table[] = {
        ::vk::Format::eUndefined, // Invalid

        ::vk::Format::eR8Sint, // Sint8x1
        ::vk::Format::eR8G8Sint, // Sint8x2
        ::vk::Format::eR8G8B8Sint, // Sint8x3
        ::vk::Format::eR8G8B8A8Sint, // Sint8x4

        ::vk::Format::eR8Snorm, // Snorm8x1
        ::vk::Format::eR8G8Snorm, // Snorm8x2
        ::vk::Format::eR8G8B8Snorm, // Snorm8x3
        ::vk::Format::eR8G8B8A8Snorm, // Snorm8x4

        ::vk::Format::eR8Uint, // Uint8x1
        ::vk::Format::eR8G8Uint, // Uint8x2
        ::vk::Format::eR8G8B8Uint, // Uint8x3
        ::vk::Format::eR8G8B8A8Uint, // Uint8x4

        ::vk::Format::eR8Unorm, // Unorm8x1
        ::vk::Format::eR8G8Unorm, // Unorm8x2
        ::vk::Format::eR8G8B8Unorm, // Unorm8x3
        ::vk::Format::eR8G8B8A8Unorm, // Unorm8x4

        ::vk::Format::eR16Sfloat, // Sfloat16x1
        ::vk::Format::eR16G16Sfloat, // Sfloat16x2
        ::vk::Format::eR16G16B16Sfloat, // Sfloat16x3
        ::vk::Format::eR16G16B16A16Sfloat, // Sfloat16x4

        ::vk::Format::eR16Sint, // Sint16x1
        ::vk::Format::eR16G16Sint, // Sint16x2
        ::vk::Format::eR16G16B16Sint, // Sint16x3
        ::vk::Format::eR16G16B16A16Sint, // Sint16x4

        ::vk::Format::eR16Snorm, // Snorm16x1
        ::vk::Format::eR16G16Snorm, // Snorm16x2
        ::vk::Format::eR16G16B16Snorm, // Snorm16x3
        ::vk::Format::eR16G16B16A16Snorm, // Snorm16x4

        ::vk::Format::eR16Uint, // Uint16x1
        ::vk::Format::eR16G16Uint, // Uint16x2
        ::vk::Format::eR16G16B16Uint, // Uint16x3
        ::vk::Format::eR16G16B16A16Uint, // Uint16x4

        ::vk::Format::eR16Unorm, // Unorm16x1
        ::vk::Format::eR16G16Unorm, // Unorm16x2
        ::vk::Format::eR16G16B16Unorm, // Unorm16x3
        ::vk::Format::eR16G16B16A16Unorm, // Unorm16x4

        ::vk::Format::eR32Sfloat, // Sfloat32x1
        ::vk::Format::eR32G32Sfloat, // Sfloat32x2
        ::vk::Format::eR32G32B32Sfloat, // Sfloat32x3
        ::vk::Format::eR32G32B32A32Sfloat, // Sfloat32x4

        ::vk::Format::eR32Sint, // Sint32x1
        ::vk::Format::eR32G32Sint, // Sint32x2
        ::vk::Format::eR32G32B32Sint, // Sint32x3
        ::vk::Format::eR32G32B32A32Sint, // Sint32x4

        ::vk::Format::eR32Uint, // Uint32x1
        ::vk::Format::eR32G32Uint, // Uint32x2
        ::vk::Format::eR32G32B32Uint, // Uint32x3
        ::vk::Format::eR32G32B32A32Uint, // Uint32x4

        ::vk::Format::eB4G4R4A4UnormPack16, // UnormB4G4R4A4

        ::vk::Format::eA2R10G10B10SnormPack32, // SnormR10G10B10A2
        ::vk::Format::eA2R10G10B10UnormPack32, // UnormR10G10B10A2
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(VertexFormat::TERM));
    return table[int(format)];
}

//------------------------------------------------------------------------------
::vk::FrontFace InternalEnumUtil::ToFrontFace(const PolygonFrontFace face)
{
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
::vk::ImageAspectFlags InternalEnumUtil::ToImageAspectFlags(
    const ::vk::Format format)
{
    switch (format) {
    case ::vk::Format::eD16Unorm:
    case ::vk::Format::eD32Sfloat:
        return ::vk::ImageAspectFlags(::vk::ImageAspectFlagBits::eDepth);

    case ::vk::Format::eD16UnormS8Uint:
    case ::vk::Format::eD24UnormS8Uint:
    case ::vk::Format::eD32SfloatS8Uint:
        return ::vk::ImageAspectFlags(
            ::vk::ImageAspectFlagBits::eDepth |
            ::vk::ImageAspectFlagBits::eStencil);

    case ::vk::Format::eS8Uint:
        return ::vk::ImageAspectFlags(::vk::ImageAspectFlagBits::eStencil);

    default: return ::vk::ImageAspectFlags(::vk::ImageAspectFlagBits::eColor);
    }
}

//------------------------------------------------------------------------------
::vk::ImageLayout InternalEnumUtil::ToImageLayout(
    const ImageResourceState state)
{
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);
    AE_BASE_ASSERT(state != ImageResourceState::Invalid);
    const ::vk::ImageLayout table[] = {
        ::vk::ImageLayout(-1), // Invalid
        ::vk::ImageLayout::eUndefined, // Unknown
        ::vk::ImageLayout::eColorAttachmentOptimal, // RenderTarget
        ::vk::ImageLayout::ePresentSrcKHR, // PresentSrc
        ::vk::ImageLayout::eDepthStencilAttachmentOptimal, // DepthStencil
        ::vk::ImageLayout::eDepthStencilReadOnlyOptimal, // DepthStencilReadOnly
        ::vk::ImageLayout::eGeneral, // ShaderResource
        ::vk::ImageLayout::eShaderReadOnlyOptimal, // ShaderResourceReadOnly
        ::vk::ImageLayout::eTransferSrcOptimal, // CopySrc
        ::vk::ImageLayout::eTransferDstOptimal, // CopyDst
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(ImageResourceState::TERM));
    const auto result = table[int(state)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::ImageLayout InternalEnumUtil::ToImageLayoutForColorAttachment(
    const ImageResourceState state)
{
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);
    AE_BASE_ASSERT(state != ImageResourceState::Invalid);
    const ::vk::ImageLayout table[] = {
        ::vk::ImageLayout(-1), // Invalid
        ::vk::ImageLayout::eUndefined, // Unknown
        ::vk::ImageLayout::eColorAttachmentOptimal, // RenderTarget
        ::vk::ImageLayout::ePresentSrcKHR, // PresentSrc
        ::vk::ImageLayout(-1), // DepthStencil
        ::vk::ImageLayout(-1), // DepthStencilReadOnly
        ::vk::ImageLayout::eGeneral, // ShaderResource
        ::vk::ImageLayout::eShaderReadOnlyOptimal, // ShaderResourceReadOnly
        ::vk::ImageLayout::eTransferSrcOptimal, // CopySrc
        ::vk::ImageLayout::eTransferDstOptimal, // CopyDst
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(ImageResourceState::TERM));
    const auto result = table[int(state)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::ImageLayout InternalEnumUtil::ToImageLayoutForDepthStencilAttachment(
    const ImageResourceState state,
    const ImageFormat format)
{
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);
    AE_BASE_ASSERT(state != ImageResourceState::Invalid);
    const ::vk::ImageLayout table[] = {
        ::vk::ImageLayout(-1), // Invalid
        ::vk::ImageLayout::eUndefined, // Unknown
        ::vk::ImageLayout(-1), // RenderTarget
        ::vk::ImageLayout(-1), // PresentSrc
        ::vk::ImageLayout::eDepthStencilAttachmentOptimal, // DepthStencil
        ::vk::ImageLayout::eDepthStencilReadOnlyOptimal, // DepthStencilReadOnly
        ::vk::ImageLayout::eGeneral, // ShaderResource
        ::vk::ImageLayout::eShaderReadOnlyOptimal, // ShaderResourceReadOnly
        ::vk::ImageLayout::eTransferSrcOptimal, // CopySrc
        ::vk::ImageLayout::eTransferDstOptimal, // CopyDst
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(ImageResourceState::TERM));
    const auto result = table[int(state)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::ImageType InternalEnumUtil::ToImageType(const ImageResourceKind kind)
{
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
    const ImageResourceTiling tiling)
{
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
    const ImageResourceUsageBitSet& usageBitSet)
{
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
    const ImageViewKind kind)
{
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
::vk::IndexType InternalEnumUtil::ToIndexType(const IndexFormat format)
{
    AE_BASE_ASSERT_ENUM(format, IndexFormat);
    AE_BASE_ASSERT(format != IndexFormat::Invalid);
    const ::vk::IndexType table[] = {
        ::vk::IndexType(-1), // Invalid
        ::vk::IndexType::eUint16, // Uint16
        ::vk::IndexType::eUint32, // Uint32
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(IndexFormat::TERM));
    const auto result = table[int(format)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::PolygonMode InternalEnumUtil::ToPolygonMode(
    const RasterizeFillMode kind)
{
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
    const PrimitiveTopologyKind kind)
{
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
::vk::SamplerAddressMode InternalEnumUtil::ToSamplerAddressMode(
    const SamplerAddressMode mode)
{
    AE_BASE_ASSERT_ENUM(mode, SamplerAddressMode);
    AE_BASE_ASSERT(mode != SamplerAddressMode::Invalid);
    const ::vk::SamplerAddressMode table[] = {
        ::vk::SamplerAddressMode(-1), // Invalid,
        ::vk::SamplerAddressMode::eRepeat,
        ::vk::SamplerAddressMode::eMirroredRepeat,
        ::vk::SamplerAddressMode::eClampToEdge,
        ::vk::SamplerAddressMode::eClampToBorder,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(SamplerAddressMode::TERM));
    const auto result = table[int(mode)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::SamplerMipmapMode InternalEnumUtil::ToSamplerMipmapMode(
    const SamplerMipmapMode mode)
{
    AE_BASE_ASSERT_ENUM(mode, SamplerMipmapMode);
    AE_BASE_ASSERT(mode != SamplerMipmapMode::Invalid);
    const ::vk::SamplerMipmapMode table[] = {
        ::vk::SamplerMipmapMode(-1), // Invalid,
        ::vk::SamplerMipmapMode::eNearest,
        ::vk::SamplerMipmapMode::eLinear,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(SamplerMipmapMode::TERM));
    const auto result = table[int(mode)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

//------------------------------------------------------------------------------
::vk::ShaderStageFlagBits InternalEnumUtil::ToShaderStageFlagBits(
    const RenderPipelineShaderStage stage)
{
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
::vk::ShaderStageFlags InternalEnumUtil::ToShaderStageFlags(
    const ShaderBindingStageBitSet& stages)
{
    const ::vk::ShaderStageFlagBits table[] = {
        ::vk::ShaderStageFlagBits(0), // Invalid
        ::vk::ShaderStageFlagBits::eVertex,
        ::vk::ShaderStageFlagBits::eGeometry,
        ::vk::ShaderStageFlagBits::eFragment,
        ::vk::ShaderStageFlagBits::eCompute,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(ShaderBindingStage::TERM));
    auto result = ::vk::ShaderStageFlags();
    for (int i = 0; i < int(ShaderBindingStage::TERM); ++i) {
        if (stages.Get(ShaderBindingStage(i))) {
            result |= table[i];
        }
    }
    AE_BASE_ASSERT_NOT_EQUALS(uint32_t(result), 0);
    return result;
}

//------------------------------------------------------------------------------
::vk::StencilOp InternalEnumUtil::ToStencilOp(const StencilOp op)
{
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

//------------------------------------------------------------------------------
::vk::VertexInputRate InternalEnumUtil::ToVertexInputRate(
    const VertexStepRate stepRate)
{
    AE_BASE_ASSERT_ENUM(stepRate, VertexStepRate);
    AE_BASE_ASSERT(stepRate != VertexStepRate::Invalid);
    const ::vk::VertexInputRate table[] = {
        ::vk::VertexInputRate(-1), // Invalid,
        ::vk::VertexInputRate::eVertex,
        ::vk::VertexInputRate::eInstance,
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(VertexStepRate::TERM));
    const auto result = table[int(stepRate)];
    AE_BASE_ASSERT_NOT_EQUALS(int(result), -1);
    return result;
}

} // namespace ae::gfx_low
// EOF
