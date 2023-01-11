// 文字コード：UTF-8
#include <ae/gfx_low/EnumUtil.hpp>

// includes
#include <ae/base/ArrayLength.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/StaticAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
ResourceMemoryUsageBitSet EnumUtil::ToResourceMemoryUsageBitSet(
    const ImageResourceUsageBitSet& usageBitSet)
{
    const ResourceMemoryUsage table[] = {
        ResourceMemoryUsage(0), // Invalid
        ResourceMemoryUsage::CopySrc, // CopySrc
        ResourceMemoryUsage::CopyDst, // CopyDst
        ResourceMemoryUsage::SampledImage, // SampledImage
        ResourceMemoryUsage::StorageImage, // StorageImage
        ResourceMemoryUsage::RenderTargetImage, // RenderTargetImage
        ResourceMemoryUsage::DepthStencilImage, // DepthStencilImage
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(ImageResourceUsage::TERM));
    ResourceMemoryUsageBitSet result;
    for (int i = 0; i < int(ImageResourceUsage::TERM); ++i) {
        if (i == int(ImageResourceUsage::Invalid)) {
            continue;
        }
        if (usageBitSet.Get(ImageResourceUsage(i))) {
            result.Set(table[i], true);
        }
    }
    return result;
}

//------------------------------------------------------------------------------
ResourceMemoryUsageBitSet EnumUtil::ToResourceMemoryUsageBitSet(
    const BufferResourceUsageBitSet& usageBitSet)
{
    const ResourceMemoryUsage table[] = {
        ResourceMemoryUsage(0), // Invalid
        ResourceMemoryUsage::CopySrc, // CopySrc
        ResourceMemoryUsage::CopyDst, // CopyDst
        ResourceMemoryUsage::UniformBuffer, // UniformBuffer
        ResourceMemoryUsage::StorageBuffer, // StorageBuffer
        ResourceMemoryUsage::IndexBuffer, // IndexBuffer
        ResourceMemoryUsage::VertexBuffer, // VertexBuffer
        ResourceMemoryUsage::IndirectBuffer, // IndirectBuffer
    };
    AE_BASE_ARRAY_LENGTH_CHECK(table, int(BufferResourceUsage::TERM));
    ResourceMemoryUsageBitSet result;
    for (int i = 0; i < int(BufferResourceUsage::TERM); ++i) {
        if (i == int(BufferResourceUsage::Invalid)) {
            continue;
        }
        if (usageBitSet.Get(BufferResourceUsage(i))) {
            result.Set(table[i], true);
        }
    }
    return result;
}

} // namespace ae::gfx_low
// EOF
