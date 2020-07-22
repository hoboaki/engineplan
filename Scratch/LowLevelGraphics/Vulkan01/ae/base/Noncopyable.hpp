// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_NONCOPYABLE_HPP)
#else
#define AE_BASE_INCLUDED_NONCOPYABLE_HPP

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Util
//@{
/// @brief 誤ってコピーできないようにする継承専用クラス。
/// @code
/// // 例
/// class Hoge : private Noncopyable<Hoge>
/// {
/// };
/// Hoge a;
/// Hoge b = a; // コピーできないのでコンパイルエラー。
/// @endcode
template <class T>
struct Noncopyable {
    Noncopyable() = default;
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;
};
//@}

}} // namespace
#endif
// EOF
