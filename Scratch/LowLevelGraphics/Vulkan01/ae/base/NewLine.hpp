// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_NEWLINE_HPP)
#else
#define AE_BASE_INCLUDED_NEWLINE_HPP

#include <ae/base/Os.hpp>

/// @addtogroup AeBase-Env
//@{

/// @def AE_BASE_NEWLINE
/// @brief 環境に合った改行コード文字列を定義するマクロ。
#if defined(AE_BASE_OS_WINDOWS)
    #define AE_BASE_NEWLINE ("\r\n")
#else
    // デフォルトは\n
    #define AE_BASE_NEWLINE ("\n")
#endif

//@}
#endif
// EOF
