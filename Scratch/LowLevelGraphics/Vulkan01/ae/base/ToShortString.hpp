// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_TOSHORTSTRING_HPP)
#else
#define AE_BASE_INCLUDED_TOSHORTSTRING_HPP

#include <ae/base/ShortStringFactory.hpp>

/// @addtogroup AeBase-String
//@{

/// @brief 引数の値をShortStringに変換するマクロ。
/// @return 変換された文字列。
#define AE_BASE_TO_SHORT_STRING(val) \
    (::ae::base::ShortStringFactory::Create(val))

//@}
#endif
// EOF
