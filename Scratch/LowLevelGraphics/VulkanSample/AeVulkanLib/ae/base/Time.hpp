// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_TIMEPod_HPP)
#else
#define AE_BASE_INCLUDED_TIMEPod_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/PodInheritClass.hpp>

namespace ae::base {
struct CalendarPod;
struct TimeSpanPod;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-DateTime
//@{
/// @brief 時間を扱う構造体。
/// @details
/// 最小単位(1チック)は100ナノ秒です。@n
/// 0初期化時は0001/01/01 00:00:00.000.000.0を表します。@n
/// 9999/12/31 23:59:59.999.999.9までサポートされています。@n
/// 加算・減算に関してオーバーフロー対策は何もしていないためオーバーフローしてもエラーにはなりません。
/// @n
struct TimePod
{
    /// @brief 地域補正された現在時刻を取得する。
    /// @return 地域補正された現在時刻。
    /// @details
    /// マイクロ秒まで扱えるようにしてありますが環境によってはそこまで精度が出ない場合があります。
    static const TimePod LocalTime();

    /// @brief 世界標準の現在時刻を取得する。
    /// @return 世界標準の現在時刻。
    /// @details
    /// マイクロ秒まで扱えるようにしてありますが環境によってはそこまで精度が出ない場合があります。
    static const TimePod UniversalTime();

    /// @brief 指定の日時から作成する。
    /// @return 作成された時間。
    /// @param year 年。値の意味は Calendar::year と同じ。
    /// @param month 月。 値の意味は Calendar::month と同じ。
    /// @param dayOfMonth 日。値の意味は Calendar::dayOfMonth と同じ。
    /// @param hour 時。値の意味は Calendar::hour と同じ。
    /// @param min 時。値の意味は Calendar::min と同じ。
    /// @param sec 秒。値の意味は Calendar::sec と同じ。
    /// @param msec ミリ秒。値の意味は Calendar::msec と同じ。
    /// @param usec マイクロ秒。値の意味は Calendar::usec と同じ。
    /// @details
    /// ナノ秒以下は0として作成します。
    static const TimePod FromDate(
        int year,
        int month,
        int dayOfMonth,
        int hour,
        int min,
        int sec,
        int msec,
        int usec);

    /// カレンダー情報を作成する。
    const CalendarPod ToCalendar() const;

    /// @brief 加算された時間を取得する。
    /// @param timeSpan 加算する時間。
    /// @return 求められた時間。
    const TimePod Add(const TimeSpanPod& timeSpan) const;
    const TimePod operator+(
        const TimeSpanPod& timeSpan) const; ///< @copydoc add

    /// @brief 時間を加算する。
    /// @return 加算された自分自身の参照。
    /// @param timeSpan 加算する時間。
    TimePod& AddAssign(const TimeSpanPod& timeSpan);
    TimePod& operator+=(const TimeSpanPod& timeSpan); ///< @copydoc addAssign

    /// @brief 減算された時間を取得する。
    /// @param timeSpan 減算する時間。
    /// @return 求められた時間。
    const TimePod Sub(const TimeSpanPod& timeSpan) const;
    const TimePod operator-(
        const TimeSpanPod& timeSpan) const; ///< @copydoc sub

    /// @brief 時間を減算する。
    /// @return 減算された自分自身の参照。
    /// @param timeSpan 減算する時間。
    TimePod& SubAssign(const TimeSpanPod& timeSpan);
    TimePod& operator-=(const TimeSpanPod& timeSpan); ///< @copydoc subAssign

    /// チック値(1チック100ナノ秒)を取得する。
    s64 Ticks() const;

    // 値。直接アクセスすることは想定していない。
    // 実質使えるのは0 <= val <= S64::MaxValue()まで。
    s64 ticks_;
};

/// TimePod のクラス版。
typedef PodInheritClass<TimePod> Time;
//@}

} // namespace ae::base
#endif
// EOF
