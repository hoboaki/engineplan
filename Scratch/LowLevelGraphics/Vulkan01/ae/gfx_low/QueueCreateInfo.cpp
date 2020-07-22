// 文字コード：UTF-8
#include <ae/gfx_low/QueueCreateInfo.hpp>

#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
QueueCreateInfo& QueueCreateInfo::SetType(const QueueType type) {
    AE_BASE_ASSERT_ENUM(type, QueueType);
    type_ = type;
    return *this;
}

//------------------------------------------------------------------------------
QueueCreateInfo& QueueCreateInfo::SetPriority(const QueuePriority priority) {
    AE_BASE_ASSERT_ENUM(priority, QueuePriority);
    priority_ = priority;
    return *this;
}

}  // namespace gfx_low
}  // namespace ae
// EOF
