// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_CONFIG_HPP)
#else
#define AE_BASE_INCLUDED_CONFIG_HPP

/// @addtogroup AeBase-Env
//@{

// ビルドバージョンレベルの定義。
// RELEASE版に向けて1ずつ大きくなる。
// ・DEBUG     = 0
// ・DEVELOP   = 1
// ・INSPECT   = 2
// ・PREVIEW   = 3
// ・RELEASE   = 4
#define AE_BASE_BUILD_VERSION_LEVEL_DEBUG     (0)
#define AE_BASE_BUILD_VERSION_LEVEL_DEVELOP   (1)
#define AE_BASE_BUILD_VERSION_LEVEL_INSPECT   (2)
#define AE_BASE_BUILD_VERSION_LEVEL_PREVIEW   (3)
#define AE_BASE_BUILD_VERSION_LEVEL_RELEASE   (4)

// 現在のビルドバージョンレベルの指定。
// AE_BASE_BUILD_VERSION_LEVELにビルドバージョンレベルが定義される。

// debug
#if defined(AE_LIBRARY_DEBUG)
    #if defined(AE_BASE_BUILD_VERSION_LEVEL)
        #error Already defined 'AE_BASE_BUILD_VERSION_LEVEL'.
    #endif
    #define AE_BASE_BUILD_VERSION_LEVEL (AE_BASE_BUILD_VERSION_LEVEL_DEBUG)
#endif
// develop
#if defined(AE_LIBRARY_DEVELOP)
    #if defined(AE_BASE_BUILD_VERSION_LEVEL)
        #error Already defined 'AE_BASE_BUILD_VERSION_LEVEL'.
    #endif
    #define AE_BASE_BUILD_VERSION_LEVEL (AE_BASE_BUILD_VERSION_LEVEL_DEVELOP)
#endif
// inspect
#if defined(AE_LIBRARY_INSPECT)
    #if defined(AE_BASE_BUILD_VERSION_LEVEL)
        #error Already defined 'AE_BASE_BUILD_VERSION_LEVEL'.
    #endif
    #define AE_BASE_BUILD_VERSION_LEVEL (AE_BASE_BUILD_VERSION_LEVEL_INSPECT)
#endif
// preview
#if defined(AE_LIBRARY_PREVIEW)
    #if defined(AE_BASE_BUILD_VERSION_LEVEL)
        #error Already defined 'AE_BASE_BUILD_VERSION_LEVEL'.
    #endif
    #define AE_BASE_BUILD_VERSION_LEVEL (AE_BASE_BUILD_VERSION_LEVEL_PREVIEW)
#endif
// release
#if defined(AE_LIBRARY_RELEASE)
    #if defined(AE_BASE_BUILD_VERSION_LEVEL)
        #error Already defined 'AE_BASE_BUILD_VERSION_LEVEL'.
    #endif
    #define AE_BASE_BUILD_VERSION_LEVEL (AE_BASE_BUILD_VERSION_LEVEL_RELEASE)
#endif
// 未定義は警告しDEBUGに設定。
#if !defined(AE_BASE_BUILD_VERSION_LEVEL)
    #warning "Not defined build version. Please defined 'AE_LIBRARY_DEBUG','AE_LIBRARY_DEVELOP','AE_LIBRARY_INSPECT','AE_LIBRARY_PREVIEW','AE_LIBRARY_RELEASE'."
    #define AE_BASE_BUILD_VERSION_LEVEL (AE_BASE_BUILD_VERSION_LEVEL_DEBUG)
#endif

/// @name ビルド環境
//@{

// 実行時エラーの有効・無効。INSPECTまでなら有効。
#if (AE_BASE_BUILD_VERSION_LEVEL <= AE_BASE_BUILD_VERSION_LEVEL_INSPECT)
    /// 実行時エラーが有効なときに定義されるプリプロセッサ。
    #define AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
#endif

// ログ文字列の有効・無効。PREVIEWまでなら有効。
#if (AE_BASE_BUILD_VERSION_LEVEL <= AE_BASE_BUILD_VERSION_LEVEL_PREVIEW)
    /// ログ文字列が有効なときに定義されるプリプロセッサ。
    #define AE_BASE_CONFIG_ENABLE_LOGSTR
#endif

//@}
//@}
#endif
// EOF
