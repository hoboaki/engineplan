// 文字コード：UTF-8
#include <ae/base/Console.hpp>

// includes
#include <ae/base/Calendar.hpp>
#include <ae/base/FunctionAttribute.hpp>
#include <ae/base/IConsoleCallback.hpp>
#include <ae/base/NewLine.hpp>
#include <ae/base/Os.hpp>
#include <ae/base/PointerCheck.hpp>
#include <ae/base/SdkHeader.hpp>
#include <ae/base/Time.hpp>

//------------------------------------------------------------------------------
namespace ae::base {
//------------------------------------------------------------------------------
namespace {

IConsoleCallback* tCallbackPtr = 0;
ShortString tTimeFormatString;
ShortString* tTimeFormatStringPtr = 0;
IConsoleCallback& tCallbackObj()
{
    if (tCallbackPtr == 0 || PointerCheck::InvalidCheck(tCallbackPtr)) {
        return Console::DefaultCallback();
    }
    return *tCallbackPtr;
}
const char* const tTimeFormat()
{
    if (tTimeFormatStringPtr == 0 ||
        PointerCheck::InvalidCheck(tTimeFormatStringPtr)) {
        return Console::DefaultTimeFormatString();
    }
    return tTimeFormatStringPtr->ReadPtr();
}
} // namespace

//------------------------------------------------------------------------------
const char* const Console::DefaultTimeFormatString()
{
    static const char* const formatString =
        "[%04u/%02u/%02u %02u:%02u:%02u(%03u)]";
    return formatString;
}

//------------------------------------------------------------------------------
void Console::SetTimeFormatString(const char* format)
{
    if (PointerCheck::InvalidCheck(format)) {
        return;
    }
    tTimeFormatString = format;
    tTimeFormatStringPtr = &tTimeFormatString;
}

//------------------------------------------------------------------------------
IConsoleCallback& Console::DefaultCallback()
{
    // 実装
    class Callback : public IConsoleCallback {
    public:
        AE_BASE_OVERRIDE(void OnWrite(const char* format, va_list arg))
        {
#if defined(AE_BASE_OS_WINDOWS)
            char buff[256];
            std::vsnprintf(buff, sizeof(buff), format, arg);
            buff[sizeof(buff) - 1] = '\0';
            OutputDebugStringA(buff);
#else
            ::std::vprintf(format, arg);
#endif
        }
    };
    static Callback obj;
    return obj;
}

//------------------------------------------------------------------------------
void Console::SetCallback(IConsoleCallback& callback)
{
    tCallbackPtr = &callback;
}

//------------------------------------------------------------------------------
void Console::WriteF(const char* format, ...)
{
    va_list arg;
    va_start(arg, format);
    WriteVF(format, arg);
    va_end(arg);
}

//------------------------------------------------------------------------------
void Console::WriteVF(const char* format, va_list arg)
{
    tCallbackObj().OnWrite(format, arg);
}

//------------------------------------------------------------------------------
void Console::WriteLineF(const char* format, ...)
{
    va_list arg;
    va_start(arg, format);
    WriteLineVF(format, arg);
    va_end(arg);
}

//------------------------------------------------------------------------------
void Console::WriteLineVF(const char* format, va_list arg)
{
    WriteVF(format, arg);
    WriteF("%s", AE_BASE_NEWLINE);
}

//------------------------------------------------------------------------------
void Console::WriteTime()
{
    Calendar calendar = Time::LocalTime().ToCalendar();
    WriteF(
        tTimeFormat(),
        uint(calendar.year + 1),
        uint(calendar.month + 1),
        uint(calendar.dayOfMonth + 1),
        uint(calendar.hour),
        uint(calendar.min),
        uint(calendar.sec),
        uint(calendar.msec),
        uint(calendar.usec));
}

//------------------------------------------------------------------------------
void Console::TimeWriteLineF(const char* format, ...)
{
    va_list arg;
    va_start(arg, format);
    TimeWriteLineVF(format, arg);
    va_end(arg);
}

//------------------------------------------------------------------------------
void Console::TimeWriteLineVF(const char* format, va_list arg)
{
    // まず時間
    WriteTime();

    // 本文
    WriteLineVF(format, arg);
}

} // namespace ae::base
// EOF
