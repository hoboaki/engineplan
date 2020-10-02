// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumBitSet.hpp>
#include <ae/gfx_low/BufferResourceUsage.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// BufferResourceUsage を扱う BitSet。
using BufferResourceUsageBitSet = ::ae::base::EnumBitSet32<BufferResourceUsage>;

} // namespace gfx_low
} // namespace ae
// EOF
