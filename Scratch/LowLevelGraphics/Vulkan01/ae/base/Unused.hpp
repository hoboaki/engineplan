// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_UNUSED_HPP)
#else
#define AE_BASE_INCLUDED_UNUSED_HPP

/// @addtogroup AeBase-Util
//@{
/// @name 変数未使用警告対応
//@{

/// @brief 変数を使用しないことを示すマクロ。
/// @details 関数の実装時に引数を使用しないときにこのマクロを使う。
/// @code
/// // 例
/// void func( int aArg )
/// {
///     AE_BASE_UNUSED( aArg ); // 変数未使用警告を回避できる。
/// }
/// @endcode
#define AE_BASE_UNUSED( aVar ) ((void)aVar)

//@}
//@}
#endif
// EOF
