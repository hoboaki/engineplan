// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_MATH_HPP)
#else
#define AE_BASE_INCLUDED_MATH_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/RuntimeAssert.hpp>

namespace ae {
namespace base {
class Angle;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

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
    template< typename T >
    static const T Min(const T aA1, const T aA2)
    {
        return aA1 < aA2 ? aA1 : aA2;
    }

    /// 最大値を取得する。
    template< typename T >
    static const T Max(const T aA1, const T aA2)
    {
        return aA1 < aA2 ? aA2 : aA1;
    }

    //@}

    //============================================================
    /// @name 符号操作
    //@{
    /// 絶対値を取得する。
    static f32 AbsF32(f32 aVal)
    {
        return aVal < 0 ? -1.0f * aVal : aVal;
    }
    /// 絶対値を取得する。
    static s32 AbsS32(s32 aVal)
    {
        return aVal < 0 ? -1 * aVal : aVal;
    }
    //@}

    //============================================================
    /// @name 範囲
    //@{
    /// @brief クランプする。
    /// @return aMin <= result <= aMax
    /// @param aMin 最小値。
    /// @param aMax 最大値。
    /// @param aValue 対象となる値。
    static f32 ClampF32(f32 aMin, f32 aValue, f32 aMax);

    /// @brief 範囲内の値か。
    /// @return aMin <= aValue <= aMax ならtrue。
    static bool IsInRangeF32(f32 aMin, f32 aValue, f32 aMax);
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
    static f32 CecF32(const Angle&); ///< cosecant(1/sin)を求める。
    static f32 SecF32(const Angle&); ///< secant(1/cos)を求める。
    static f32 CotF32(const Angle&); ///< cotangent(1/tan)を求める。
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
    /// @param aVal1 aRate == 0.0f のときに100%で返される値。
    /// @param aVal2 aRate == 1.0f のときに100%で返される値。
    /// @param aRate レート値。0.0f <= aRate <= 1.0f。
    template< typename T >
    static const T Interpolation(const T& aVal1, const T& aVal2, const f32 aRate)
    {
        AE_BASE_ASSERT_MIN_MAX(aRate, 0.0f, 1.0f);
        return aVal1 + (aVal2 - aVal1) * aRate;
    }
    //@}
};
//@}
//@}

}} // namespace
#endif
// EOF
