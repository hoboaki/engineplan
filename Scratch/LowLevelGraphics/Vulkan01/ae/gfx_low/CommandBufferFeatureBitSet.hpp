// 文字コード：UTF-8
#pragma once

#include <ae/base/BitSet.hpp>
#include <ae/gfx_low/CommandBufferFeature.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// CommandBufferFeature を扱う BitSet。
using CommandBufferFeatureBitSet =
    base::BitSet<static_cast<int>(CommandBufferFeature::TERM)>;

} // namespace gfx_low
} // namespace ae
// EOF
