// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumBitSet.hpp>
#include <ae/gfx_low/ResourceMemoryUsage.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ResourceMemoryUsage を扱う BitSet。
using ResourceMemoryUsageBitSet = ::ae::base::EnumBitSet32<ResourceMemoryUsage>;

} // namespace ae::gfx_low
// EOF
