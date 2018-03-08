// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_CONFIG_HPP)
#else
#define AE_BASE_INCLUDED_CONFIG_HPP

/// @addtogroup AeBase-Env
//@{

// ビルドバージョンレベルの定義。
// FINAL版に向けて1ずつ大きくなる。
// ・DEBUG     = 0
// ・DEVELOP   = 1
// ・SEMIFINAL = 2
// ・FINAL     = 3
#define AE_BASE_BUILD_VERSION_LEVEL_DEBUG     (0)
#define AE_BASE_BUILD_VERSION_LEVEL_DEVELOP   (1)
#define AE_BASE_BUILD_VERSION_LEVEL_SEMIFINAL (2)
#define AE_BASE_BUILD_VERSION_LEVEL_FINAL     (3)

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
// semifinal
#if defined(AE_LIBRARY_SEMIFINAL)
    #if defined(AE_BASE_BUILD_VERSION_LEVEL)
        #error Already defined 'AE_BASE_BUILD_VERSION_LEVEL'.
    #endif
    #define AE_BASE_BUILD_VERSION_LEVEL (AE_BASE_BUILD_VERSION_LEVEL_SEMIFINAL)
#endif
// final
#if defined(AE_LIBRARY_FINAL)
    #if defined(AE_BASE_BUILD_VERSION_LEVEL)
        #error Already defined 'AE_BASE_BUILD_VERSION_LEVEL'.
    #endif
    #define AE_BASE_BUILD_VERSION_LEVEL (AE_BASE_BUILD_VERSION_LEVEL_FINAL)
#endif
// 未定義は警告しDEBUGに設定。
#if !defined(AE_BASE_BUILD_VERSION_LEVEL)
    #warning "Not defined build version. Please defined 'XLIBRARY_DEBUG','XLIBRARY_DEVELOP','XLIBRARY_SEMIFINAL','XLIBRARY_FINAL'."
    #define AE_BASE_BUILD_VERSION_LEVEL (AE_BASE_BUILD_VERSION_LEVEL_DEBUG)
#endif

/// @name ビルド環境
//@{

// 実行時エラーの有効・無効。DEVELOPまでなら有効。
#if (AE_BASE_BUILD_VERSION_LEVEL <= AE_BASE_BUILD_VERSION_LEVEL_DEVELOP)
    /// 実行時エラーが有効なときに定義されるプリプロセッサ。
    #define AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
#endif

// ログ文字列の有効・無効。SEMIFINALまでなら有効。
#if (AE_BASE_BUILD_VERSION_LEVEL <= AE_BASE_BUILD_VERSION_LEVEL_SEMIFINAL)
    /// ログ文字列が有効なときに定義されるプリプロセッサ。
    #define AE_BASE_CONFIG_ENABLE_LOGSTR
#endif

//@}
//@}
#endif
// EOF
