// 文字コード：UTF-8
#include <ae/gfx_low/SystemCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
SystemCreateInfo::SystemCreateInfo() {
}

//------------------------------------------------------------------------------
SystemCreateInfo& SystemCreateInfo::SetDebugLevel(
    const SystemDebugLevel level) {
    AE_BASE_ASSERT_ENUM(level, SystemDebugLevel);
    debugLevel_ = level;
    return *this;
}

} // namespace gfx_low
} // namespace ae
// EOF
