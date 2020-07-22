// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_COMPILER_HPP)
#else
#define AE_BASE_INCLUDED_COMPILER_HPP

/// @addtogroup AeBase-Env
//@{
/// @name コンパイラ
//@{

/// MicrosoftVisualC使用時に定義されるプリプロセッサ。
#define AE_BASE_COMPILER_MSVC
#undef  AE_BASE_COMPILER_MSVC

/// GNUC使用時に定義されるプリプロセッサ。
#define AE_BASE_COMPILER_GNUC
#undef  AE_BASE_COMPILER_GNUC

// 選択
#if defined(_MSC_VER)
    #define AE_BASE_COMPILER_MSVC
#elif defined(__GNUC__)
    #define AE_BASE_COMPILER_GNUC
#else
    #error Unknown Compiler.
#endif

//@}
//@}
#endif
// EOF
