// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumBitSet.hpp>
#include <ae/gfx_low/ShaderBindingStage.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ShaderBindingStage を扱う BitSet。
using ShaderBindingStageBitSet = ::ae::base::EnumBitSet32<ShaderBindingStage>;

} // namespace ae::gfx_low
// EOF
