// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_OSTYPE_HPP)
#else
#define AE_BASE_INCLUDED_OSTYPE_HPP

#include <ae/base/Os.hpp>

/// @addtogroup AeBase-Env 
//@{

/// @name オペレーティングシステムの種類
//@{

/// WindowSystem型OS使用時に定義されるプリプロセッサ。
#define AE_BASE_OSTYPE_WINDOWSYSTEM
#undef  AE_BASE_OSTYPE_WINDOWSYSTEM

/// 組み込み型OS使用時に定義されるプリプロセッサ。
#define AE_BASE_OSTYPE_EMBEDDEDSYSTEM
#undef  AE_BASE_OSTYPE_EMBEDDEDSYSTEM

// 選択
#if defined(AE_BASE_OS_WINDOWS) || defined(AE_BASE_OS_MACOSX)
    #define AE_BASE_OSTYPE_WINDOWSYSTEM
#elif defined(AE_BASE_OS_IOS)
    #define AE_BASE_OSTYPE_EMBEDDEDSYSTEM
#endif

//@}
//@}
#endif
// EOF
