// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_OS_HPP)
#else
#define AE_BASE_INCLUDED_OS_HPP

/// @addtogroup AeBase-Env 
//@{
/// @name オペレーティングシステム 
//@{

/// Windows使用時に定義されるプリプロセッサ。
#define AE_BASE_OS_WINDOWS
#undef  AE_BASE_OS_WINDOWS

/// MacOSX使用時に定義されるプリプロセッサ。
#define AE_BASE_OS_MACOSX
#undef  AE_BASE_OS_MACOSX

/// iPhone使用時に定義されるプリプロセッサ。
#define AE_BASE_OS_IPHONE
#undef  AE_BASE_OS_IPHONE

/// iPad使用時に定義されるプリプロセッサ。
#define AE_BASE_OS_IPAD
#undef  AE_BASE_OS_IPAD

/// iOS使用時に定義されるプリプロセッサ。
#define AE_BASE_OS_IOS
#undef  AE_BASE_OS_IOS

// 選択
#if defined(_WIN32)
    #define AE_BASE_OS_WINDOWS
#elif defined(__APPLE__)
    #if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
        #define AE_BASE_OS_MACOSX
    #elif defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
        #define AE_BASE_OS_IOS
        #define AE_BASE_OS_IPHONE
    #else
        #define AE_BASE_OS_IOS
        #define AE_BASE_OS_IPAD
    #endif
#else
    #error Unkonwn OS.
#endif

//@}
//@}
#endif
// EOF
