// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_VALUEINRANGE_HPP)
#else
#define AE_BASE_INCLUDED_VALUEINRANGE_HPP

/// @addtogroup AeBase-Util
//@{
/// @name 値範囲チェック
//@{

/// @brief aVal < aTermVal な値か調べる。
/// @return 条件に当てはまればtrueを返し、そうでなければfalseを返す。
#define AE_BASE_VALUE_IN_RANGE_LESS(aVal, aTermVal) (aVal < aTermVal)

/// @brief aVal <= aMaxVal な値か調べる。
/// @return 条件に当てはまればtrueを返し、そうでなければfalseを返す。
#define AE_BASE_VALUE_IN_RANGE_LESS_EQUALS(aVal, aMaxVal) (aVal <= aMaxVal)

/// @brief aMinVal <= aVal < aTermVal な値か調べる。
/// @return 条件に当てはまればtrueを返し、そうでなければfalseを返す。
#define AE_BASE_VALUE_IN_RANGE_MIN_TERM(aMinVal, aVal, aTermVal) (aMinVal <= aVal && aVal < aTermVal)

/// @brief aMinVal <= aVal <= aMaxVal な値か調べる。
/// @return 条件に当てはまればtrueを返し、そうでなければfalseを返す。
#define AE_BASE_VALUE_IN_RANGE_MIN_MAX(aMinVal, aVal, aMaxVal) (aMinVal <= aVal && aVal <= aMaxVal)

//@}
//@}
#endif
// EOF
