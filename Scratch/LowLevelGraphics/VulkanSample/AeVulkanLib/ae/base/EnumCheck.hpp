// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_ENUMCHECK_HPP)
#else
#define AE_BASE_INCLUDED_ENUMCHECK_HPP

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Debug
//@{

/// @brief Enumの値が 0以上 TERM　未満であることをチェックするマクロ。
/// @return bool値。範囲内ならtrue。
/// @details
/// 調査するEnumにTERMが定義されている必要があります。
#define AE_BASE_ENUM_IS_VALID(enumType, enumValue) \
    (0 <= int(enumValue) && int(enumValue) <= enumType::TERM)

/// @brief Enumの値が 0以上 TERM　未満であることをチェックするマクロ。
/// @return bool値。範囲外ならtrue。
/// @details
/// 調査するEnumにTERMが定義されている必要があります。
#define AE_BASE_ENUM_IS_INVALID(enumType, enumValue) \
    (AE_BASE_ENUM_IS_VALID(enumType, enumValue) == false)
//@}

} // namespace ae::base
#endif
// EOF
