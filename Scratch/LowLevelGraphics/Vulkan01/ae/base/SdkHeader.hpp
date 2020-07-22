// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_SDKHEADER_HPP)
#else
#define AE_BASE_INCLUDED_SDKHEADER_HPP

#include <ae/base/Os.hpp>

#if defined(AE_BASE_OS_WINDOWS)
    #include <windows.h>
    #undef min
    #undef max
#endif

#endif
// EOF
