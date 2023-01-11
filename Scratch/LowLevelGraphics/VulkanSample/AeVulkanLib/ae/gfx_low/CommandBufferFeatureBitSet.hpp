// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumBitSet.hpp>
#include <ae/gfx_low/CommandBufferFeature.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// CommandBufferFeature を扱う BitSet。
using CommandBufferFeatureBitSet = base::EnumBitSet32<CommandBufferFeature>;

} // namespace ae::gfx_low
// EOF
