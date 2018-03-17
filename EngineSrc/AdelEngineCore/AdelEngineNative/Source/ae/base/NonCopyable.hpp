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
/// class Hoge : private NonCopyable
/// {
/// };
/// Hoge a;
/// Hoge b = a; // コピーできないのでコンパイルエラー。
/// @endcode
class NonCopyable
{
protected:
    NonCopyable() {}
private:
    NonCopyable(const NonCopyable&);
    void operator=(const NonCopyable&);
};
//@}

}} // namespace
#endif
// EOF
