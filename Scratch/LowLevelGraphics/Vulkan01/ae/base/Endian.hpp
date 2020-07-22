// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_ENDIAN_HPP)
#else
#define AE_BASE_INCLUDED_ENDIAN_HPP

#include <ae/base/Os.hpp>

/// @addtogroup AeBase-Env
//@{
/// @name エンディアン
//@{

/// BigEndian環境時に定義されるプリプロセッサ。
#define AE_BASE_BIG_ENDIAN
#undef  AE_BASE_BIG_ENDIAN

/// LittleEndian環境時に定義されるプリプロセッサ。
#define AE_BASE_LITTLE_ENDIAN
#undef  AE_BASE_LITTLE_ENDIAN

// 選択
#if defined(AE_BASE_OS_MACOSX) && defined(__BIG_ENDIAN__)
    #define AE_BASE_BIG_ENDIAN
#else
    #define AE_BASE_LITTLE_ENDIAN
#endif

/// @def AE_BASE_IS_BIG_ENDIAN
/// @brief BigEndianならtrue。LittleEndianならfalseが入る。
#if defined(AE_BASE_BIG_ENDIAN)
    #define AE_BASE_IS_BIG_ENDIAN (true)
#else
    #define AE_BASE_IS_BIG_ENDIAN (false)
#endif

/// @def AE_BASE_IS_LITTLE_ENDIAN
/// @brief LittleEndianならtrue。BigEndianならfalseが入る。
#if defined(AE_BASE_LITTLE_ENDIAN)
    #define AE_BASE_IS_LITTLE_ENDIAN (true)
#else
    #define AE_BASE_IS_LITTLE_ENDIAN (false)
#endif

//@}
//@}
#endif
// EOF
