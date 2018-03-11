// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_ENTRYPOINT_HPP)
#else
#define AE_BASE_INCLUDED_ENTRYPOINT_HPP

//------------------------------------------------------------------------------
namespace ae {
namespace base {
class Application;
}}

/// @addtogroup AeBase-System
//@{

/// @brief メイン関数の宣言。
/// @return リターンコード。
/// @details アプリケーションはこれを実装してアプリケーションを開始してください。
/// @code
/// // 例
/// int xmain( const ::ae::base::Application& )
/// {
///     // 何もせずにアプリケーションを終了するコード。
///     return 0;
/// }
/// @endcode
extern int xmain(::ae::base::Application& aApp);

//@}
#endif
// EOF
