// 文字コード：UTF-8
#include <ae/base/Console.hpp>

#include <ae/base/Calendar.hpp>
#include <ae/base/FunctionAttribute.hpp>
#include <ae/base/IConsoleCallback.hpp>
#include <ae/base/NewLine.hpp>
#include <ae/base/Os.hpp>
#include <ae/base/PointerCheck.hpp>
#include <ae/base/SdkHeader.hpp>
#include <ae/base/Time.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {
//------------------------------------------------------------------------------
namespace {

IConsoleCallback* tCallbackPtr = 0;
ShortString tTimeFormatString;
ShortString* tTimeFormatStringPtr = 0;
IConsoleCallback& tCallbackObj()
{
    if (tCallbackPtr == 0
        || PointerCheck::InvalidCheck(tCallbackPtr)
        )
    {
        return Console::DefaultCallback();
    }
    return *tCallbackPtr;
}
const char* const tTimeFormat()
{
    if (tTimeFormatStringPtr == 0
        || PointerCheck::InvalidCheck(tTimeFormatStringPtr)
        )
    {
        return Console::DefaultTimeFormatString();
    }
    return tTimeFormatStringPtr->readPtr();
}
}

//------------------------------------------------------------------------------
const char* const Console::DefaultTimeFormatString()
{
    static const char* const formatString = "[%04u/%02u/%02u %02u:%02u:%02u(%03u)]";
    return formatString;
}

//------------------------------------------------------------------------------
void Console::SetTimeFormatString(const char* aFormat)
{
    if (PointerCheck::InvalidCheck(aFormat)) {
        return;
    }
    tTimeFormatString = aFormat;
    tTimeFormatStringPtr = &tTimeFormatString;
}

//------------------------------------------------------------------------------
IConsoleCallback& Console::DefaultCallback()
{
    // 実装
    class Callback : public IConsoleCallback
    {
    public:
        AE_BASE_OVERRIDE(void onWrite(const char* aFormat, va_list aArg))
        {
#if defined(AE_BASE_OS_WINDOWS)
            char buff[256];
            std::vsnprintf(buff, sizeof(buff), aFormat, aArg);
            buff[sizeof(buff) - 1] = '\0';
            OutputDebugStringA(buff);
#else
            ::std::vprintf(aFormat, aArg);
#endif
        }
    };
    static Callback obj;
    return obj;
}

//------------------------------------------------------------------------------
void Console::SetCallback(IConsoleCallback& aCallback)
{
    tCallbackPtr = &aCallback;
}

//------------------------------------------------------------------------------
void Console::WriteF(const char* aFormat, ...)
{
    va_list arg;
    va_start(arg, aFormat);
    WriteVF(aFormat, arg);
    va_end(arg);
}

//------------------------------------------------------------------------------
void Console::WriteVF(const char* aFormat, va_list aArg)
{
    tCallbackObj().onWrite(aFormat, aArg);
}

//------------------------------------------------------------------------------
void Console::WriteLineF(const char* aFormat, ...)
{
    va_list arg;
    va_start(arg, aFormat);
    WriteLineVF(aFormat, arg);
    va_end(arg);
}

//------------------------------------------------------------------------------
void Console::WriteLineVF(const char* aFormat, va_list aArg)
{
    WriteVF(aFormat, aArg);
    WriteF("%s", AE_BASE_NEWLINE);
}

//------------------------------------------------------------------------------
void Console::WriteTime()
{
    Calendar calendar = Time::LocalTime().toCalendar();
    WriteF(tTimeFormat(),
        uint(calendar.year + 1),
        uint(calendar.month + 1),
        uint(calendar.dayOfMonth + 1),
        uint(calendar.hour),
        uint(calendar.min),
        uint(calendar.sec),
        uint(calendar.msec),
        uint(calendar.usec)
        );
}

//------------------------------------------------------------------------------
void Console::TimeWriteLineF(const char* aFormat, ...)
{
    va_list arg;
    va_start(arg, aFormat);
    TimeWriteLineVF(aFormat, arg);
    va_end(arg);
}

//------------------------------------------------------------------------------
void Console::TimeWriteLineVF(const char* aFormat, va_list aArg)
{
    // まず時間
    WriteTime();

    // 本文
    WriteLineVF(aFormat, aArg);
}

}} // namespace
// EOF
