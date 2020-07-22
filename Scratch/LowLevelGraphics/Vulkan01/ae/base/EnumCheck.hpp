// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_ENUMCHECK_HPP)
#else
#define AE_BASE_INCLUDED_ENUMCHECK_HPP

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Debug
//@{

/// @brief Enumの値が 0以上 TERM　未満であることをチェックするマクロ。
/// @return bool値。範囲内ならtrue。
/// @details
/// 調査するEnumにTERMが定義されている必要があります。
#define AE_BASE_ENUM_IS_VALID( aEnumType , aEnumValue ) ( 0 <= int( aEnumValue ) && int( aEnumValue ) <= aEnumType::TERM )

/// @brief Enumの値が 0以上 TERM　未満であることをチェックするマクロ。
/// @return bool値。範囲外ならtrue。
/// @details
/// 調査するEnumにTERMが定義されている必要があります。
#define AE_BASE_ENUM_IS_INVALID( aEnumType , aEnumValue ) ( AE_BASE_ENUM_IS_VALID( aEnumType , aEnumValue ) == false )
//@}

}} // namespace
#endif
// EOF
