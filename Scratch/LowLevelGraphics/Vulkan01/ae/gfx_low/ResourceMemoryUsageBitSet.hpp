// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumBitSet.hpp>
#include <ae/gfx_low/ResourceMemoryUsage.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// ResourceMemoryUsage を扱う BitSet。
using ResourceMemoryUsageBitSet = ::ae::base::EnumBitSet<ResourceMemoryUsage>;

} // namespace gfx_low
} // namespace ae
// EOF
