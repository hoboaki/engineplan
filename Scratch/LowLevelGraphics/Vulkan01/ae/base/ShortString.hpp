// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_SHORTSTRING_HPP)
#else
#define AE_BASE_INCLUDED_SHORTSTRING_HPP

#include <ae/base/FixedString.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-String
//@{
typedef FixedString< char, 64 > ShortString;  ///< char版ShortString。短い固定長文字列。
typedef FixedString< wchar_t, 64 > ShortWString; ///< wchar_t版ShortString。短い固定長文字列。
//@}

}} // namespace
#endif
// EOF
