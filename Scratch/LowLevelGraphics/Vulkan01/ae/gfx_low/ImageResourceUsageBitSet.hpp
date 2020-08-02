// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumBitSet.hpp>
#include <ae/gfx_low/ImageResourceUsage.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// ImageResourceUsage を扱う BitSet。
using ImageResourceUsageBitSet = ::ae::base::EnumBitSet32<ImageResourceUsage>;

} // namespace gfx_low
} // namespace ae
// EOF
