// 文字コード：UTF-8
#include <ae/base/Thread.hpp>

// includes
#include <ae/base/Math.hpp>
#include <ae/base/Os.hpp>
#include <ae/base/TimeSpan.hpp>

#if defined(AE_BASE_OS_WINDOWS)
#include <ae/base/SdkHeader.hpp>
#else
#include <unistd.h>
#endif

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
void Thread::Sleep(const TimeSpanPod& timeSpan)
{
#if defined(AE_BASE_OS_WINDOWS)
    ::Sleep(DWORD(::ae::base::Math::Max(s64(1), timeSpan.Milliseconds())));
#else
    usleep(useconds_t(::ae::base::Math::Max(s64(1), timeSpan.Microseconds())));
#endif
}

} // namespace ae::base
// EOF
