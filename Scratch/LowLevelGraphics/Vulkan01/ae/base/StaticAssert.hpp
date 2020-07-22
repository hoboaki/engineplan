// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_STATICASSERT_HPP)
#else
#define AE_BASE_INCLUDED_STATICASSERT_HPP

#include <ae/base/Compiler.hpp>

/// @addtogroup AeBase-Debug
//@{
/// @name コンパイル時アサート
//@{

/// @brief メッセージ付きコンパイル時アサート。
/// @param aCond チェックする条件。これがfalseならコンパイルエラー。
/// @param aMsg エラー時に出力するメッセージ。
#if defined(AE_BASE_COMPILER_MSVC)
    #define AE_BASE_STATIC_ASSERT_MSG( aCond , aMsg )  static_assert( aCond , aMsg )
#else
    #define AE_BASE_STATIC_ASSERT_MSG( aCond , aMsg )
#endif

/// @brief コンパイル時アサート。
/// @param aCond チェックする条件。これがfalseならコンパイルエラー。
#define AE_BASE_STATIC_ASSERT( aCond )  AE_BASE_STATIC_ASSERT_MSG( aCond , "Static assert failure." )

/// コンパイルを止めるアサート。
#define AE_BASE_STATIC_ASSERT_FAILURE   AE_BASE_STATIC_ASSERT_MSG( false )

//@}
//@}
#endif
// EOF

