// 文字コード：UTF-8
#include <ae/gfx_low/CommandBufferCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
CommandBufferCreateInfo& CommandBufferCreateInfo::SetLevel(
    const CommandBufferLevel level)
{
    AE_BASE_ASSERT_ENUM(level, CommandBufferLevel);
    AE_BASE_ASSERT(level != CommandBufferLevel::Invalid);
    level_ = level;
    return *this;
}

//------------------------------------------------------------------------------
CommandBufferCreateInfo& CommandBufferCreateInfo::SetRenderPassCountMax(
    const int count)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    renderPassCountMax_ = count;
    return *this;
}

} // namespace ae::gfx_low
// EOF
