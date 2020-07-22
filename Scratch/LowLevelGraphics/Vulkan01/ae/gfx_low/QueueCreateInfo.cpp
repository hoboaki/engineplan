// 文字コード：UTF-8
#include <ae/gfx_low/QueueCreateInfo.hpp>

#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
QueueCreateInfo& QueueCreateInfo::SetKind(const QueueKind type) {
    AE_BASE_ASSERT_ENUM(type, QueueKind);
    AE_BASE_ASSERT(type != QueueKind::Invalid);
    type_ = type;
    return *this;
}

//------------------------------------------------------------------------------
QueueCreateInfo& QueueCreateInfo::SetPriority(const QueuePriority priority) {
    AE_BASE_ASSERT_ENUM(priority, QueuePriority);
    AE_BASE_ASSERT(priority != QueuePriority::Invalid);
    priority_ = priority;
    return *this;
}

}  // namespace gfx_low
}  // namespace ae
// EOF
