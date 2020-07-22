// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_POINTERCHECK_HPP)
#else
#define AE_BASE_INCLUDED_POINTERCHECK_HPP

#include <ae/base/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Debug
//@{
/// ポインタについて調べる処理を扱う空間。
struct PointerCheck
{
    /// @brief 有効なポインタか。
    /// @return nullや無効なポインタならfalseを返す。
    static bool IsValid(const_anyptr_t aPtr);

    /// @brief 指定したポインタが無効かどうかAssertでチェックする。
    /// @return 無効な場合trueが返る。trueが返ってきたらfail safe code用の処理を書くことを想定。
    static bool InvalidCheck(const_anyptr_t aPtr);
};
//@}

}} // namespace
#endif
// EOF
