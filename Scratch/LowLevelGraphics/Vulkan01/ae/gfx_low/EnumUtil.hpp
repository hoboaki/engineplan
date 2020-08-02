// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/ImageResourceUsageBitSet.hpp>
#include <ae/gfx_low/ResourceMemoryUsageBitSet.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// Enum に関する便利関数郡。
struct EnumUtil {
    static ResourceMemoryUsageBitSet ToResourceMemoryUsageBitSet(
        const ImageResourceUsageBitSet& usageBitSet);
};

} // namespace gfx_low
} // namespace ae
// EOF
