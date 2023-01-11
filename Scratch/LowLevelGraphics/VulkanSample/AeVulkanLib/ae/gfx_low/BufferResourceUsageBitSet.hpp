// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumBitSet.hpp>
#include <ae/gfx_low/BufferResourceUsage.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// BufferResourceUsage を扱う BitSet。
using BufferResourceUsageBitSet = ::ae::base::EnumBitSet32<BufferResourceUsage>;

} // namespace ae::gfx_low
// EOF
