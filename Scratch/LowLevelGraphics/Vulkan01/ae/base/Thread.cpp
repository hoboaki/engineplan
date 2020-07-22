// 文字コード：UTF-8
#include <ae/base/Thread.hpp>

#include <ae/base/Math.hpp>
#include <ae/base/Os.hpp>
#include <ae/base/TimeSpan.hpp>

#if defined(AE_BASE_OS_WINDOWS)
    #include <ae/base/SdkHeader.hpp>
#else
    #include <unistd.h>
#endif

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
void Thread::Sleep(const TimeSpanPod& aTimeSpan)
{
#if defined(AE_BASE_OS_WINDOWS)
    ::Sleep(DWORD(::ae::base::Math::Max(s64(1), aTimeSpan.milliseconds())));
#else    
    usleep(useconds_t(::ae::base::Math::Max(s64(1), aTimeSpan.microseconds())));
#endif
}

}} // namespace
// EOF
