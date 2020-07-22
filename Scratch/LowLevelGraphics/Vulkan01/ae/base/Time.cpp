// 文字コード：UTF-8
#include <ae/base/Time.hpp>

#include <ctime>
#include <ae/base/Calendar.hpp>
#include <ae/base/Os.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/TimeSpan.hpp>

// for LocalTime() UniversalTime()
#if defined(AE_BASE_OS_WINDOWS)
#pragma warning(disable: 4996) // for gmtime,localtime
#include <ae/base/SdkHeader.hpp>
#elif defined(AE_BASE_OS_MACOSX)
#include <sys/time.h>
#endif

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
namespace {

// 時間変換関数のポインタ。
typedef std::tm* (*tTimeConverter)(const std::time_t*, std::tm*);

// 現在時間を作成。
const TimePod tCurrentTime(tTimeConverter aConverter)
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
            const u64 shift = 116444736000000000ULL; // (27111902 << 32) + 3577643008

            union
            {
                FILETIME as_file_time;
                u64 as_integer; // 100-nanos since 1601-Jan-01
            } caster;
            caster.as_file_time = ft;

            caster.as_integer -= shift; // filetime is now 100-nanos since 1970-Jan-01

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
    const std::tm* tmPtr = aConverter(&secFrom1970, &safeTM);
    if (PointerCheck::InvalidCheck(tmPtr)) {
        AE_BASE_ASSERT_NOT_REACHED();
    }
    else
    {
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
            calendar.usec
            );
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
        static std::tm* func(const std::time_t* aTime, std::tm* aSafePtr)
        {
            std::tm* result = std::localtime(aTime);
            if (PointerCheck::InvalidCheck(result)) {
                result = aSafePtr;
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
        static std::tm* func(const std::time_t* aTime, std::tm* aSafePtr)
        {
            std::tm* result = std::gmtime(aTime);
            if (PointerCheck::InvalidCheck(result)) {
                result = aSafePtr;
            }
            return result;
        }
    };
    return tCurrentTime(Converter::func);
}

//------------------------------------------------------------------------------
const TimePod TimePod::FromDate(
    const int aYear,
    const int aMonth,
    const int aDayOfMonth,
    const int aHour,
    const int aMin,
    const int aSec,
    const int aMsec,
    const int aUsec
    )
{
    const u64 days = Calendar::DaysToDate(aYear, aMonth, aDayOfMonth);
    Time obj;
    obj.ticks_ =
        days * u64(u64(24) * 60 * 60 * 1000 * 1000 * 10)
        + aHour * u64(u64(60) * 60 * 1000 * 1000 * 10)
        + aMin  * u64(u64(60) * 1000 * 1000 * 10)
        + aSec  * u64(1000 * 1000 * 10)
        + aMsec * u64(1000 * 10)
        + aUsec * u64(10);
    return obj;
}

//------------------------------------------------------------------------------
namespace {

    // 1日の総チック数。
const u64 tUnitTickOfDay = (u64(24) * 60 * 60 * 1000 * 1000 * 10);
}
const CalendarPod TimePod::toCalendar()const
{
    // 変数準備
    Calendar calendar;

    // マイナスの値はサポートしない
    if (ticks_ < 0) {
        AE_BASE_ERROR_INVALID_VALUE(ticks_);
        return calendar;
    }


    {// 時間
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

    {// 日付
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
const TimePod TimePod::add(const TimeSpanPod& aTimeSpan)const
{
    TimePod obj = *this;
    obj += aTimeSpan;
    return obj;
}

//------------------------------------------------------------------------------
const TimePod TimePod::operator+(const TimeSpanPod& aTimeSpan)const
{
    return add(aTimeSpan);
}

//------------------------------------------------------------------------------
TimePod& TimePod::addAssign(const TimeSpanPod& aTimeSpan)
{
    ticks_ += aTimeSpan.ticks();
    return *this;
}

//------------------------------------------------------------------------------
TimePod& TimePod::operator+=(const TimeSpanPod& aTimeSpan)
{
    return addAssign(aTimeSpan);
}

//------------------------------------------------------------------------------
const TimePod TimePod::sub(const TimeSpanPod& aTimeSpan)const
{
    TimePod obj = *this;
    obj -= aTimeSpan;
    return obj;
}

//------------------------------------------------------------------------------
const TimePod TimePod::operator-(const TimeSpanPod& aTimeSpan)const
{
    return sub(aTimeSpan);
}

//------------------------------------------------------------------------------
TimePod& TimePod::subAssign(const TimeSpanPod& aTimeSpan)
{
    ticks_ -= aTimeSpan.ticks();
    return *this;
}

//------------------------------------------------------------------------------
TimePod& TimePod::operator-=(const TimeSpanPod& aTimeSpan)
{
    return subAssign(aTimeSpan);
}

//------------------------------------------------------------------------------
s64 TimePod::ticks()const
{
    return ticks_;
}

}} // namespace
// EOF
