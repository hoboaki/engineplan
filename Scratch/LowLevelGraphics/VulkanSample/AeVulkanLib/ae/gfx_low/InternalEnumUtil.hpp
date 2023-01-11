// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/AttachmentLoadOp.hpp>
#include <ae/gfx_low/AttachmentStoreOp.hpp>
#include <ae/gfx_low/BlendFactor.hpp>
#include <ae/gfx_low/BlendOp.hpp>
#include <ae/gfx_low/BufferResourceUsageBitSet.hpp>
#include <ae/gfx_low/CommandBufferLevel.hpp>
#include <ae/gfx_low/CompareOp.hpp>
#include <ae/gfx_low/ImageFormat.hpp>
#include <ae/gfx_low/ImageResourceKind.hpp>
#include <ae/gfx_low/ImageResourceState.hpp>
#include <ae/gfx_low/ImageResourceTiling.hpp>
#include <ae/gfx_low/ImageResourceUsageBitSet.hpp>
#include <ae/gfx_low/ImageViewKind.hpp>
#include <ae/gfx_low/IndexFormat.hpp>
#include <ae/gfx_low/PolygonFrontFace.hpp>
#include <ae/gfx_low/PrimitiveTopologyKind.hpp>
#include <ae/gfx_low/RasterizeCullMode.hpp>
#include <ae/gfx_low/RasterizeFillMode.hpp>
#include <ae/gfx_low/RenderPipelineShaderStage.hpp>
#include <ae/gfx_low/RenderTargetComponentBitSet.hpp>
#include <ae/gfx_low/SamplerAddressMode.hpp>
#include <ae/gfx_low/SamplerBorderColor.hpp>
#include <ae/gfx_low/SamplerMinMagFilter.hpp>
#include <ae/gfx_low/SamplerMipmapMode.hpp>
#include <ae/gfx_low/SdkHeader.hpp>
#include <ae/gfx_low/ShaderBindingStageBitSet.hpp>
#include <ae/gfx_low/StencilOp.hpp>
#include <ae/gfx_low/VertexFormat.hpp>
#include <ae/gfx_low/VertexStepRate.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// 内部実装用 Enum に関する便利関数郡。
struct InternalEnumUtil
{
    static ::vk::AttachmentLoadOp ToAttachmentLoadOp(AttachmentLoadOp loadOp);
    static ::vk::AttachmentStoreOp ToAttachmentStoreOp(
        AttachmentStoreOp storeOp);
    static ::vk::BlendFactor ToBlendFactorForColor(BlendFactor factor);
    static ::vk::BlendFactor ToBlendFactorForAlpha(BlendFactor factor);
    static ::vk::BlendOp ToBlendOp(BlendOp op);
    static ::vk::BorderColor ToBorderColor(SamplerBorderColor color);
    static ::vk::BufferUsageFlags ToBufferUsageFlags(
        const BufferResourceUsageBitSet& usageBitSet);
    static ::vk::ColorComponentFlags ToColorComponentFlags(
        const RenderTargetComponentBitSet& componentBitSet);
    static ::vk::CommandBufferLevel ToCommandBufferLevel(
        CommandBufferLevel level);
    static ::vk::CompareOp ToCompareOp(CompareOp op);
    static ::vk::CullModeFlags ToCullModeFlags(RasterizeCullMode mode);
    static ::vk::Filter ToFilter(SamplerMinMagFilter filter);
    static ::vk::Format ToFormat(ImageFormat format);
    static ::vk::Format ToFormat(VertexFormat format);
    static ::vk::FrontFace ToFrontFace(PolygonFrontFace face);
    static ::vk::ImageAspectFlags ToImageAspectFlags(::vk::Format format);
    static ::vk::ImageLayout ToImageLayout(ImageResourceState state);
    static ::vk::ImageLayout ToImageLayoutForColorAttachment(
        ImageResourceState state);
    static ::vk::ImageLayout ToImageLayoutForDepthStencilAttachment(
        ImageResourceState state,
        ImageFormat format);
    static ::vk::ImageTiling ToImageTiling(ImageResourceTiling tiling);
    static ::vk::ImageType ToImageType(ImageResourceKind kind);
    static ::vk::ImageUsageFlags ToImageUsageFlags(
        const ImageResourceUsageBitSet& usageBitSet);
    static ::vk::ImageViewType ToImageViewType(ImageViewKind kind);
    static ::vk::IndexType ToIndexType(IndexFormat format);
    static ::vk::PolygonMode ToPolygonMode(RasterizeFillMode mode);
    static ::vk::PrimitiveTopology ToPrimitiveTopology(
        PrimitiveTopologyKind kind);
    static ::vk::SamplerAddressMode ToSamplerAddressMode(
        SamplerAddressMode mode);
    static ::vk::SamplerMipmapMode ToSamplerMipmapMode(SamplerMipmapMode mode);
    static ::vk::ShaderStageFlagBits ToShaderStageFlagBits(
        RenderPipelineShaderStage stage);
    static ::vk::ShaderStageFlags ToShaderStageFlags(
        const ShaderBindingStageBitSet& stages);
    static ::vk::StencilOp ToStencilOp(StencilOp op);
    static ::vk::VertexInputRate ToVertexInputRate(VertexStepRate stepRate);
};

} // namespace ae::gfx_low
// EOF
