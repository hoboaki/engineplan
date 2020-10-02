// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_VALUEINRANGE_HPP)
#else
#define AE_BASE_INCLUDED_VALUEINRANGE_HPP

/// @addtogroup AeBase-Util
//@{
/// @name 値範囲チェック
//@{

/// @brief val < termVal な値か調べる。
/// @return 条件に当てはまればtrueを返し、そうでなければfalseを返す。
#define AE_BASE_VALUE_IN_RANGE_LESS(val, termVal) (val < termVal)

/// @brief val <= maxVal な値か調べる。
/// @return 条件に当てはまればtrueを返し、そうでなければfalseを返す。
#define AE_BASE_VALUE_IN_RANGE_LESS_EQUALS(val, maxVal) (val <= maxVal)

/// @brief minVal <= val < termVal な値か調べる。
/// @return 条件に当てはまればtrueを返し、そうでなければfalseを返す。
#define AE_BASE_VALUE_IN_RANGE_MIN_TERM(minVal, val, termVal) \
    (minVal <= val && val < termVal)

/// @brief minVal <= val <= maxVal な値か調べる。
/// @return 条件に当てはまればtrueを返し、そうでなければfalseを返す。
#define AE_BASE_VALUE_IN_RANGE_MIN_MAX(minVal, val, maxVal) \
    (minVal <= val && val <= maxVal)

//@}
//@}
#endif
// EOF
