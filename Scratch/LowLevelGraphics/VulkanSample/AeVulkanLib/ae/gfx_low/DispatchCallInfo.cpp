// 文字コード：UTF-8
#include <ae/gfx_low/DispatchCallInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
DispatchCallInfo& DispatchCallInfo::SetThreadsPerThreadGroup(
    const base::Extent3i& threads)
{
    AE_BASE_ASSERT_LESS_EQUALS(1, threads.width);
    AE_BASE_ASSERT_LESS_EQUALS(1, threads.height);
    AE_BASE_ASSERT_LESS_EQUALS(1, threads.depth);
    threadsPerThreadGroup_ = threads;
    return *this;
}

//------------------------------------------------------------------------------
DispatchCallInfo& DispatchCallInfo::SetThreadGroups(
    const base::Extent3i& threadGroups)
{
    AE_BASE_ASSERT_LESS_EQUALS(1, threadGroups.width);
    AE_BASE_ASSERT_LESS_EQUALS(1, threadGroups.height);
    AE_BASE_ASSERT_LESS_EQUALS(1, threadGroups.depth);
    threadGroups_ = threadGroups;
    return *this;
}

} // namespace ae::gfx_low
// EOF
