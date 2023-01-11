// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_MATH_HPP)
#else
#define AE_BASE_INCLUDED_MATH_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/RuntimeAssert.hpp>

namespace ae::base {
class Angle;
}

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// @brief 数学系関数を集めた空間。
//@{
struct Math
{
    //============================================================
    /// @name 選択
    //@{

    /// 最小値を取得する。
    template <typename T>
    static const T Min(const T a1, const T a2)
    {
        return a1 < a2 ? a1 : a2;
    }

    /// 最大値を取得する。
    template <typename T>
    static const T Max(const T a1, const T a2)
    {
        return a1 < a2 ? a2 : a1;
    }

    //@}

    //============================================================
    /// @name 符号操作
    //@{
    /// 絶対値を取得する。
    static f32 AbsF32(f32 val) { return val < 0 ? -1.0f * val : val; }
    /// 絶対値を取得する。
    static s32 AbsS32(s32 val) { return val < 0 ? -1 * val : val; }
    //@}

    //============================================================
    /// @name 範囲
    //@{
    /// @brief 汎用的なクランプ。
    /// @return min <= result <= max
    /// @param value 対象となる値。
    /// @param min 最小値。
    /// @param max 最大値。
    template <typename T>
    static T Clamp(T value, T min, T max)
    {
        AE_BASE_ASSERT_LESS_EQUALS(min, max);
        if (value < min) {
            return min;
        } else if (max < value) {
            return max;
        }
        return value;
    }

    /// @brief クランプする。
    /// @return min <= result <= max
    /// @param value 対象となる値。
    /// @param min 最小値。
    /// @param max 最大値。
    static f32 ClampF32(f32 value, f32 min, f32 max);

    /// @brief 範囲内の値か。
    /// @return min <= value <= max ならtrue。
    static bool IsInRangeF32(f32 value, f32 min, f32 max);
    //@}

    //============================================================
    /// @name 比較（StrictがつかないF32関数は誤差を許容する）
    //@{
    static bool IsEqualsF32(f32 value1, f32 value2); ///< 値が等しいか。
    static bool IsLessEqualsF32(const f32 lhs, const f32 rhs); ///< lhs <= rhs。
    static bool IsLessF32(const f32 lhs, const f32 rhs); ///< lhs < rhs。
    static bool IsZeroF32(const f32); ///< ゼロか。
    //@}

    //============================================================
    /// @name 三角関数
    //@{
    static f32 SinF32(const Angle&); ///< sineを求める。
    static f32 CosF32(const Angle&); ///< cosineを求める。
    static f32 TanF32(const Angle&); ///< tangentを求める。
    static f32 CecF32(const Angle&); ///< Cosecant(1/sin)を求める。
    static f32 SecF32(const Angle&); ///< Secant(1/cos)を求める。
    static f32 CotF32(const Angle&); ///< Cotangent(1/tan)を求める。
    //@}

    //============================================================
    /// @name 乗算
    //@{
    static f32 SqrtF32(f32 val); ///< 平方根を求める。
    //@}

    //============================================================
    /// @name 切り上げ・切り捨て
    //@{
    static f32 CeilF32(f32 val); ///< 切り上げ。
    static f32 FloorF32(f32 val); ///< 切り捨て。
    //@}

    //============================================================
    /// @name 補間。
    //@{

    /// @brief ２つの値を指定のレートで補間する。
    /// @param val1 rate == 0.0f のときに100%で返される値。
    /// @param val2 rate == 1.0f のときに100%で返される値。
    /// @param rate レート値。0.0f <= rate <= 1.0f。
    template <typename T>
    static const T Interpolation(const T& val1, const T& val2, const f32 rate)
    {
        AE_BASE_ASSERT_MIN_MAX(rate, 0.0f, 1.0f);
        return val1 + (val2 - val1) * rate;
    }
    //@}
};
//@}
//@}

} // namespace ae::base
#endif
// EOF
