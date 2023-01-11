// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/BufferResourceUsageBitSet.hpp>
#include <ae/gfx_low/ImageFormat.hpp>
#include <ae/gfx_low/ImageResourceUsageBitSet.hpp>
#include <ae/gfx_low/ResourceMemoryUsageBitSet.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// Enum に関する便利関数郡。
struct EnumUtil
{
    /// 指定の ImageResourceUsageBitSet に適合する
    /// ResourceMemoryUsageBitSet を取得する。
    static ResourceMemoryUsageBitSet ToResourceMemoryUsageBitSet(
        const ImageResourceUsageBitSet& usageBitSet);

    /// 指定の BufferResourceUsageBitSet に適合する
    /// ResourceMemoryUsageBitSet を取得する。
    static ResourceMemoryUsageBitSet ToResourceMemoryUsageBitSet(
        const BufferResourceUsageBitSet& usageBitSet);

    /// Depth 要素があるフォーマットか。
    static bool HasDepthComponent(ImageFormat format)
    {
        switch (format) {
        case ImageFormat::D16Unorm:
        case ImageFormat::D32Sfloat:
        case ImageFormat::D16UnormS8Uint:
        case ImageFormat::D24UnormS8Uint:
        case ImageFormat::D32SfloatS8Uint: return true;
        default: return false;
        }
    }

    /// Stencil 要素があるフォーマットか。
    static bool HasStencilComponent(ImageFormat format)
    {
        switch (format) {
        case ImageFormat::D16UnormS8Uint:
        case ImageFormat::D24UnormS8Uint:
        case ImageFormat::D32SfloatS8Uint:
        case ImageFormat::S8Uint: return true;
        default: return false;
        }
    }
};

} // namespace ae::gfx_low
// EOF
