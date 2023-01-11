// 文字コード：UTF-8
#include <ae/base/Time.hpp>

// includes
#include <ae/base/Calendar.hpp>
#include <ae/base/Os.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/TimeSpan.hpp>
#include <ctime>

// for LocalTime() UniversalTime()
#if defined(AE_BASE_OS_WINDOWS)
#pragma warning(disable : 4996) // for gmtime,localtime
#include <ae/base/SdkHeader.hpp>
#elif defined(AE_BASE_OS_MACOSX)
#include <sys/time.h>
#endif

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
namespace {

// 時間変換関数のポインタ。
typedef std::tm* (*tTimeConverter)(const std::time_t*, std::tm*);

// 現在時間を作成。
const TimePod tCurrentTime(tTimeConverter converter)
{
    // 結果用変数の用意
    TimePod obj = {};

    // 1970/01/01 00:00からの秒数とチック(100ナノ秒)数を求める
    std::time_t secFrom1970 = std::time_t();
    u64 subTick = u64();
#if defined(AE_BASE_OS_WINDOWS)
    {
        // 1601/01/01 12:00 の時間
        FILETIME ft = {};
        GetSystemTimeAsFileTime(&ft);

        // 1970/01/01 00:00 に変換
        {
            /* shift is difference between 1970-Jan-01 & 1601-Jan-01
             * in 100-nanosecond intervals */
            const u64 shift =
                116444736000000000ULL; // (27111902 << 32) + 3577643008

            union
            {
                FILETIME as_file_time;
                u64 as_integer; // 100-nanos since 1601-Jan-01
            } caster;
            caster.as_file_time = ft;

            caster.as_integer -=
                shift; // filetime is now 100-nanos since 1970-Jan-01

            secFrom1970 = caster.as_integer / 10000000;
            subTick = caster.as_integer % 10000000;
        }
    }
#elif defined(AE_BASE_OS_MACOSX)
    {
        timeval tv;
        gettimeofday(&tv, 0);
        secFrom1970 = tv.tv_sec;
        subTick = u64(tv.tv_usec) * 10;
    }
#else
    // 標準関数で実装。ミリ秒以下は無し。
    std::time(&secFrom1970);
#endif

    // 変換したtmを取得
    std::tm safeTM = {};
    const std::tm* tmPtr = converter(&secFrom1970, &safeTM);
    if (PointerCheck::InvalidCheck(tmPtr)) {
        AE_BASE_ASSERT_NOT_REACHED();
    } else {
        // カレンダー用意
        Calendar calendar;
        calendar.year = u16(tmPtr->tm_year + 1900 - 1);
        calendar.month = u16(tmPtr->tm_mon);
        calendar.dayOfMonth = u16(tmPtr->tm_mday - 1);
        calendar.hour = u16(tmPtr->tm_hour);
        calendar.min = u16(tmPtr->tm_min);
        calendar.sec = u16(tmPtr->tm_sec);
        {
            u64 tmpVal = subTick;
            calendar.nsec = u16(100 * (tmpVal % 10));
            tmpVal /= 10;
            calendar.usec = u16(tmpVal % 1000);
            tmpVal /= 1000;
            calendar.msec = u16(tmpVal % 1000);
        }

        // 日時から作成
        obj = TimePod::FromDate(
            calendar.year,
            calendar.month,
            calendar.dayOfMonth,
            calendar.hour,
            calendar.min,
            calendar.sec,
            calendar.msec,
            calendar.usec);
        obj.ticks_ += calendar.nsec / 100;
    }

    return obj;
}

} // namespace

//------------------------------------------------------------------------------
const TimePod TimePod::LocalTime()
{
    struct Converter
    {
        static std::tm* func(const std::time_t* time, std::tm* safePtr)
        {
            std::tm* result = std::localtime(time);
            if (PointerCheck::InvalidCheck(result)) {
                result = safePtr;
            }
            return result;
        }
    };
    return tCurrentTime(Converter::func);
}

//------------------------------------------------------------------------------
const TimePod TimePod::UniversalTime()
{
    struct Converter
    {
        static std::tm* func(const std::time_t* time, std::tm* safePtr)
        {
            std::tm* result = std::gmtime(time);
            if (PointerCheck::InvalidCheck(result)) {
                result = safePtr;
            }
            return result;
        }
    };
    return tCurrentTime(Converter::func);
}

//------------------------------------------------------------------------------
const TimePod TimePod::FromDate(
    const int year,
    const int month,
    const int dayOfMonth,
    const int hour,
    const int min,
    const int sec,
    const int msec,
    const int usec)
{
    const u64 days = Calendar::DaysToDate(year, month, dayOfMonth);
    Time obj;
    obj.ticks_ = days * u64(u64(24) * 60 * 60 * 1000 * 1000 * 10) +
                 hour * u64(u64(60) * 60 * 1000 * 1000 * 10) +
                 min * u64(u64(60) * 1000 * 1000 * 10) +
                 sec * u64(1000 * 1000 * 10) + msec * u64(1000 * 10) +
                 usec * u64(10);
    return obj;
}

//------------------------------------------------------------------------------
namespace {

// 1日の総チック数。
const u64 tUnitTickOfDay = (u64(24) * 60 * 60 * 1000 * 1000 * 10);
} // namespace
const CalendarPod TimePod::ToCalendar() const
{
    // 変数準備
    Calendar calendar;

    // マイナスの値はサポートしない
    if (ticks_ < 0) {
        AE_BASE_ERROR_INVALID_VALUE(ticks_);
        return calendar;
    }

    { // 時間
        // 1日単位で切り捨てられるusecに変換
        u64 val = ticks_ % tUnitTickOfDay;

        calendar.nsec = 100 * (val % 10);

        val /= 10;
        calendar.usec = val % 1000;

        val /= 1000;
        calendar.msec = val % 1000;

        val /= 1000;
        calendar.sec = val % 60;

        val /= 60;
        calendar.min = val % 60;

        val /= 60;
        calendar.hour = val % 24;
    }

    { // 日付
        // 西暦1年からの日数に変換
        const int days = u32(ticks_ / tUnitTickOfDay);

        // その日の0時のカレンダーを取得
        const Calendar theDay = Calendar::FromDays(days);

        // 上書き
        calendar.year = theDay.year;
        calendar.month = theDay.month;
        calendar.dayOfYear = theDay.dayOfYear;
        calendar.dayOfMonth = theDay.dayOfMonth;
        calendar.dayOfWeek = theDay.dayOfWeek;
    }

    // 結果を返す
    return calendar;
}

//------------------------------------------------------------------------------
const TimePod TimePod::Add(const TimeSpanPod& timeSpan) const
{
    TimePod obj = *this;
    obj += timeSpan;
    return obj;
}

//------------------------------------------------------------------------------
const TimePod TimePod::operator+(const TimeSpanPod& timeSpan) const
{
    return Add(timeSpan);
}

//------------------------------------------------------------------------------
TimePod& TimePod::AddAssign(const TimeSpanPod& timeSpan)
{
    ticks_ += timeSpan.Ticks();
    return *this;
}

//------------------------------------------------------------------------------
TimePod& TimePod::operator+=(const TimeSpanPod& timeSpan)
{
    return AddAssign(timeSpan);
}

//------------------------------------------------------------------------------
const TimePod TimePod::Sub(const TimeSpanPod& timeSpan) const
{
    TimePod obj = *this;
    obj -= timeSpan;
    return obj;
}

//------------------------------------------------------------------------------
const TimePod TimePod::operator-(const TimeSpanPod& timeSpan) const
{
    return Sub(timeSpan);
}

//------------------------------------------------------------------------------
TimePod& TimePod::SubAssign(const TimeSpanPod& timeSpan)
{
    ticks_ -= timeSpan.Ticks();
    return *this;
}

//------------------------------------------------------------------------------
TimePod& TimePod::operator-=(const TimeSpanPod& timeSpan)
{
    return SubAssign(timeSpan);
}

//------------------------------------------------------------------------------
s64 TimePod::Ticks() const
{
    return ticks_;
}

} // namespace ae::base
// EOF
