// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_TIMESPAN_HPP)
#else
#define AE_BASE_INCLUDED_TIMESPAN_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/PodInheritClass.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-DateTime
//@{
/// @brief 時間間隔を表現する構造体。
/// @details
/// 最小単位(1チック)は100ナノ秒です。@n
/// 加算・減算に関してオーバーフロー対策は何もしていないためオーバーフローしてもエラーにはなりません。
/// @n
struct TimeSpanPod
{
    /// @brief チック数から作成する。
    /// @return 作成された時間間隔。
    /// @param ticks チック数。
    static const TimeSpanPod FromTicks(s64 ticks);

    /// @brief マイクロ秒数から作成する。
    /// @return 作成された時間間隔。
    /// @param usecs マイクロ秒数。
    static const TimeSpanPod FromMicroseconds(s64 usecs);

    /// @brief ミリ秒数から作成する。
    /// @return 作成された時間間隔。
    /// @param msecs ミリ秒数。
    static const TimeSpanPod FromMilliseconds(s64 msecs);

    /// @brief 秒数から作成する。
    /// @return 作成された時間間隔。
    /// @param secs 秒数。
    static const TimeSpanPod FromSeconds(s64 secs);

    /// @brief 分数から作成する。
    /// @return 作成された時間間隔。
    /// @param minutes 分数。
    static const TimeSpanPod FromMinnutes(s64 minutes);

    /// @brief 時数から作成する。
    /// @return 作成された時間間隔。
    /// @param hours 時数。
    static const TimeSpanPod FromHours(s64 hours);

    /// @brief 日数から作成する。
    /// @return 作成された時間間隔。
    /// @param days 日数。
    static const TimeSpanPod FromDays(s64 days);

    /// @brief チック数として取得する。
    /// @return チック数。
    s64 Ticks() const;

    /// @brief マイクロ秒数として取得する。
    /// @return マイクロ秒数。小数点以下は切り捨て。
    s64 Microseconds() const;

    /// @brief ミリ秒数として取得する。
    /// @return ミリ秒数。小数点以下は切り捨て。
    s64 Milliseconds() const;

    /// @brief 秒数として取得する。
    /// @return 秒数。小数点以下は切り捨て。
    s64 Seconds() const;

    /// @brief 分数として取得する。
    /// @return 分数。小数点以下は切り捨て。
    s64 Minutes() const;

    /// @brief 時数として取得する。
    /// @return 時数。小数点以下は切り捨て。
    s64 Hours() const;

    /// @brief 日数として取得する。
    /// @return 日数。小数点以下は切り捨て。
    s64 Days() const;

    /// @brief 加算された時間間隔を取得する。
    /// @param timeSpan 加算する時間間隔。
    /// @return 求められた時間間隔。
    const TimeSpanPod Add(const TimeSpanPod& timeSpan) const;
    const TimeSpanPod operator+(
        const TimeSpanPod& timeSpan) const; ///< @copydoc add

    /// @brief 時間間隔を加算する。
    /// @return 加算された自分自身の参照。
    /// @param timeSpan 加算する時間間隔。
    TimeSpanPod& AddAssign(const TimeSpanPod& timeSpan);
    TimeSpanPod& operator+=(
        const TimeSpanPod& timeSpan); ///< @copydoc addAssign

    /// @brief 減算された時間間隔を取得する。
    /// @param timeSpan 減算する時間間隔。
    /// @return 求められた時間間隔。
    const TimeSpanPod Sub(const TimeSpanPod& timeSpan) const;
    const TimeSpanPod operator-(
        const TimeSpanPod& timeSpan) const; ///< @copydoc sub

    /// @brief 時間間隔を減算する。
    /// @return 減算された自分自身の参照。
    /// @param timeSpan 減算する時間間隔。
    TimeSpanPod& SubAssign(const TimeSpanPod& timeSpan);
    TimeSpanPod& operator-=(
        const TimeSpanPod& timeSpan); ///< @copydoc subAssign

    // 値。直接アクセスすることは想定していない。
    s64 ticks_;
};

/// TimeSpanPod のクラス版。
typedef PodInheritClass<TimeSpanPod> TimeSpan;
//@}

} // namespace ae::base
#endif
// EOF
