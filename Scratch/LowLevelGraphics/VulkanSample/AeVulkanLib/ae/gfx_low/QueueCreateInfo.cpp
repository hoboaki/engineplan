// 文字コード：UTF-8
#include <ae/gfx_low/QueueCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
QueueCreateInfo& QueueCreateInfo::SetKind(const QueueKind type)
{
    AE_BASE_ASSERT_ENUM(type, QueueKind);
    AE_BASE_ASSERT(type != QueueKind::Invalid);
    type_ = type;
    return *this;
}

//------------------------------------------------------------------------------
QueueCreateInfo& QueueCreateInfo::SetPriority(const QueuePriority priority)
{
    AE_BASE_ASSERT_ENUM(priority, QueuePriority);
    AE_BASE_ASSERT(priority != QueuePriority::Invalid);
    priority_ = priority;
    return *this;
}

//------------------------------------------------------------------------------
QueueCreateInfo& QueueCreateInfo::SetOperationCountMax(
    const int operationCountMax)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, operationCountMax);
    operationCountMax_ = operationCountMax;
    return *this;
}

} // namespace ae::gfx_low
// EOF
