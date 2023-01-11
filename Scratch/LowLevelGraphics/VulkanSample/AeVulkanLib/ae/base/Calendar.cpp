// 文字コード：UTF-8
#include <ae/base/Calendar.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
namespace {

// 範囲チェックをしつつ範囲外なら最小値を返す。
int tYearCheck(const int year)
{
    if (year < Calendar::YearMin || Calendar::YearMax < year) {
        AE_BASE_ERROR_INVALID_VALUE(year);
        return Calendar::YearMin;
    }
    return year;
}
int tMonthCheck(const int month)
{
    if (month < Calendar::MonthMin || Calendar::MonthMax < month) {
        AE_BASE_ERROR_INVALID_VALUE(month);
        return Calendar::MonthMin;
    }
    return month;
}

} // namespace

//------------------------------------------------------------------------------
bool CalendarPod::IsLeapYear(const int year)
{
    // 閏年の定義
    // 1. 西暦年が4で割り切れる年は閏年
    // 2. ただし、西暦年が100で割り切れる年は平年
    // 3. ただし、西暦年が400で割り切れる年は閏年
    // 西暦4年は閏年と扱わなかったらしいという話もあるが
    // .Net4.0 の実装では西暦4年が閏年となっていたためそれに合わせる。
    const int localYear = 1 + tYearCheck(year);

    if ((localYear % 4) != 0 // 4で割り切れないので平年
        || ((localYear % 100) == 0 &&
               (localYear % 400) != 0) // 100 で割り切れ 400 で割り切れない年は平年
    ) {
        return false;
    }

    // 閏年
    return true;
}

//------------------------------------------------------------------------------
int CalendarPod::DaysToDate(
    const int year,
    const int month,
    const int dayOfMonth)
{
    int days = 0;

    // 年
    {
        // 平年
        days += year * 365;

        // 閏年補正
        int addDays = year / 4;
        addDays -= year / 100;
        addDays += year / 400;
        days += addDays;
    }

    // 月
    for (int i = 0; i < month; ++i) {
        days += DaysInMonth(year, i);
    }

    // 日
    days += dayOfMonth;

    return days;
}

//------------------------------------------------------------------------------
const CalendarPod CalendarPod::FromDays(const int days)
{
    Calendar calendar;
    int localDays = days;
    { // 年
        int year = 0;
        while (true) {
            // その年の総日数を取得
            const int totalDayOfYear = Calendar::DaysInYear(year);

            // 年を越すか計算
            if (localDays < totalDayOfYear) {
                // 年は越さないので終了
                calendar.year = u16(year);
                calendar.dayOfYear = u16(localDays);
                break;
            }

            // 次の年へ
            ++year;
            localDays -= totalDayOfYear;
        }
    }

    { // 月・曜日・日
        int month = 0;
        while (true) {
            // その月の総日数を取得
            const int totalDayOfMonth =
                Calendar::DaysInMonth(calendar.year, month);

            // 月を越すか計算
            if (localDays < totalDayOfMonth) {
                // 月は越さないので終了
                calendar.month = u16(month);
                calendar.dayOfMonth = u16(localDays);
                calendar.dayOfWeek =
                    u16((FirstDayOfWeek + localDays) % (DayOfWeekMax + 1));
                break;
            }

            // 次の月へ
            ++month;
            localDays -= totalDayOfMonth;
        }
    }

    return calendar;
}

//------------------------------------------------------------------------------
int CalendarPod::DaysInYear(const int year)
{
    const int localYear = tYearCheck(year);
    return uint(IsLeapYear(localYear) ? 366 : 365);
}

//------------------------------------------------------------------------------
int CalendarPod::DaysInMonth(const int year, const int month)
{
    const int localMonth = tMonthCheck(month);
    switch (localMonth + 1) { // 直感的になるように+1
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12: return 31;

    case 4:
    case 6:
    case 9:
    case 11: return 30;

    case 2: return IsLeapYear(tYearCheck(year)) ? 29 : 28;

    default:
        AE_BASE_ERROR_INVALID_VALUE(localMonth);
        return 28; // fail safe code
    }
}

} // namespace ae::base
// EOF
