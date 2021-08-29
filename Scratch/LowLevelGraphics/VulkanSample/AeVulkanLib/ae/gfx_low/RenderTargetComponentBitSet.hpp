// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumBitSet.hpp>
#include <ae/gfx_low/RenderTargetComponent.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// ColorComponent を扱う BitSet。
using RenderTargetComponentBitSet =
    ::ae::base::EnumBitSet32<RenderTargetComponent>;

} // namespace gfx_low
} // namespace ae
// EOF
