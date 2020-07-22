// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_CALENDAR_HPP)
#else
#define AE_BASE_INCLUDED_CALENDAR_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/PodInheritClass.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-DateTime
//@{
/// @brief カレンダー情報を扱う構造体。
/// @details グレゴリアン歴を使っています。
struct CalendarPod
{
    /// @name 定数
    //@{
    enum
    {
        YearMin = 0,       ///< 年の最小値。
        YearMax = 9998,    ///< 年の最大値。
        MonthMin = 0,       ///< 月の最小値。
        MonthMax = 11,      ///< 月の最大値。
        DayOfYearMin = 0,   ///< 日の最小値
        DayOfYearMax = 365, ///< 日の最大値。
        DayOfMonthMin = 0,  ///< 月の中の日の最小値。
        DayOfMonthMax = 30, ///< 月の中の日の最大値。
        DayOfWeekMin = 0,   ///< 週の中の日の最小値。
        DayOfWeekMax = 6,   ///< 週の中の日の最大値。
        HourMin = 0,        ///< 時の最小値。
        HourMax = 23,       ///< 時の最大値。
        MinuteMin = 0,      ///< 分の最小値。
        MinuteMax = 59,     ///< 分の最大値。
        SecondMin = 0,      ///< 秒の最小値。
        SecondMax = 59,     ///< 秒の最大値。
        MillisecondMin = 0,     ///< ミリ秒の最小値。
        MillisecondMax = 999,   ///< ミリ秒の最大値。
        MicrosecondMin = 0,     ///< マイクロ秒の最小値。
        MicrosecondMax = 999,   ///< マイクロ秒の最大値。
        NanosecondsMin = 0,     ///< ナノ秒の最小値。
        NanosecondsMax = 999,   ///< ナノ秒の最大値。
        FirstDayOfWeek = 1      ///< 西暦1年1月1日の曜日。
    };
    //@}

    /// @brief 指定の年が閏年かどうか取得する。
    /// @return 閏年ならtrue。
    /// @param aYear 年。値の意味は CalendarPod::year と同じ。
    static bool IsLeapYear(int aYear);

    /// @brief 西暦1年1月1日から指定の年・月・日まで何日あるか取得する。
    /// @return 日数。
    /// @param aYear 年。値の意味は CalendarPod::year と同じ。
    /// @param aMonth 月。値の意味は CalendarPod::month と同じ。
    /// @param aDayOfMonth 日。値の意味は CalendarPod::dayOfMonth と同じ。
    static int DaysToDate(int aYear, int aMonth, int aDayOfMonth);

    /// @brief 西暦1年1月1日から指定した日数が経過した日の0:0:0.0.0.0を取得する。
    /// @return カレンダー。
    /// @param aDays 日数。
    static const CalendarPod FromDays(int aDays);

    /// @brief 指定の年の総日数を取得する。
    /// @return 総日数。
    /// @param aYear 年。値の意味は CalendarPod::year と同じ。
    static int  DaysInYear(int aYear);

    /// @brief 指定の年・月の総日数を取得する。
    /// @return 総日数。
    /// @param aYear 月が所属する年。値の意味は CalendarPod::year と同じ。
    /// @param aMonth 月。値の意味は CalendarPod::month と同じ。
    static int  DaysInMonth(int aYear, int aMonth);

    u16 year;       ///< 年。 CalendarPod::YearMin <= val <= CalendarPod::YearMax 。0は西暦1年を示す。
    u16 month;      ///< 月。 CalendarPod::MonthMin <= val <= CalendarPod::MonthMax 。0は1月を示す。
    u16 dayOfYear;  ///< 日。 CalendarPod::DayOfYearMin <= val <= CalendarPod::DayOfYearMax 。0は1月1日を示す。
    u16 dayOfMonth; ///< 月の中の日。 CalendarPod::DayOfMonthMin <= val <= CalendarPod::DayOfMonthMax 。0は1日を示す。
    u16 dayOfWeek;  ///< 週の中の日。 CalendarPod::DayOfWeekMin <= val <= CalendarPod::DayOfWeekMax 。0は日曜日を示す。
    u16 hour;       ///< 時。 CalendarPod::HourMin <= val <= CalendarPod::HourMax 。
    u16 min;        ///< 分。 CalendarPod::MinuteMin <= val <= CalendarPod::MinuteMax 。
    u16 sec;        ///< 秒。 CalendarPod::SecondMin <= val <= CalendarPod::SecondMax 。
    u16 msec;       ///< ミリ秒。 CalendarPod::MillisecondMin <= val <= CalendarPod::MillisecondMax 。
    u16 usec;       ///< マイクロ秒。 CalendarPod::MicrosecondMin <= val <= CalendarPod::MicrosecondMax 。
    u16 nsec;       ///< ナノ秒。 CalendarPod::NanosecondsMin <= val <= CalendarPod::NanosecondsMax 。
};

/// CalendarPod のクラス版。
typedef PodInheritClass< CalendarPod > Calendar;
//@}

}} // namespace
#endif
// EOF
