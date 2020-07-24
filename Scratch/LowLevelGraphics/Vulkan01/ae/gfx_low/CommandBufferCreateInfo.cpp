// 文字コード：UTF-8
#include <ae/gfx_low/CommandBufferCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
CommandBufferCreateInfo& CommandBufferCreateInfo::SetLevel(const CommandBufferLevel level) {
    AE_BASE_ASSERT_ENUM(level, CommandBufferLevel);
    AE_BASE_ASSERT(level != CommandBufferLevel::Invalid);
    level_ = level;
    return *this;
}

}  // namespace gfx_low
}  // namespace ae
// EOF
