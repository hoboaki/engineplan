// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_FUNCTIONATTRIBUTE_HPP)
#else
#define AE_BASE_INCLUDED_FUNCTIONATTRIBUTE_HPP

#include <ae/base/Compiler.hpp>

/// @addtogroup AeBase-Debug
//@{
/// @name 関数属性
//@{

/// @def AE_BASE_OVERRIDE
/// @brief オーバーライドチェック。
/// @details 指定の関数がオーバーライドしていなければコンパイルエラーにします。
/// @code
///  // [例]
///  // 継承元。
///  class Base
///  {
///  public:
///      virtual void func();
///  };
///  // 派生クラス。
///  class Inherit : public Base
///  {
///  public:
///      AE_BASE_OVERRIDE( void func() ); // オーバーライドしているのでOK。
///      AE_BASE_OVERRIDE( void foo() );  // オーバーライドしていないのでエラー。
///  };
/// @endcode
#if defined(AE_BASE_COMPILER_MSVC)
#define AE_BASE_OVERRIDE( ... ) virtual __VA_ARGS__ override
#else
#define AE_BASE_OVERRIDE( ... ) __VA_ARGS__
#endif

/// @def AE_BASE_FINAL
/// @brief オーバーライド禁止チェック。
/// @details 指定の関数が派生クラスでオーバーライドしていればコンパイルエラーにします。
/// @code
///  // [例]
///  // 継承元。
///  class Base
///  {
///  public:
///      AE_BASE_FINAL( void func() );
///  };
///  // 派生クラス。
///  class Inherit : public Base
///  {
///  public:
///      virtual void func(); // オーバーライドしようとしたのでエラー。
///  };
/// @endcode
#if defined(AE_BASE_COMPILER_MSVC)
#define AE_BASE_FINAL( ... ) virtual __VA_ARGS__ sealed
#else
#define AE_BASE_FINAL( ... ) __VA_ARGS__
#endif

//@}
//@}
#endif
// EOF
