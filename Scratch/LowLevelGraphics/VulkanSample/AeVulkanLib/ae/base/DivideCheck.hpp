// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_DIVIDECHECK_HPP)
#else
#define AE_BASE_INCLUDED_DIVIDECHECK_HPP

#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

// 割り算チェックで使うモノたち用空間。
struct DivideCheck
{
    // Assert用メッセージ文字列。
    static const char* const AssertionMessage;

    // アサートで止めつつ引数の値をそのまま返す。
    template <typename T>
    static T Error(const T& retVal)
    {
        AE_BASE_ASSERT_NOT_REACHED_MSG(AssertionMessage);
        return retVal;
    }
};

} // namespace ae::base

/// @addtogroup AeBase-Debug
//@{
/// @name 0除算チェック
//@{

/// @brief lhs /= rhs, operator /=の0除算チェック。
/// @details
/// 0除算しようとした場合はエラー。エラーが無効なときは除算をせずに続行する。
#define AE_BASE_DIV_ASSIGN(lhs, rhs)                        \
    do {                                                    \
        if (rhs == 0) {                                     \
            AE_BASE_ASSERT_NOT_REACHED_MSG(                 \
                ::ae::base::DivideCheck::AssertionMessage); \
        } else {                                            \
            lhs /= rhs;                                     \
        }                                                   \
    } while (0)

/// @brief lhs / rhsの0除算チェック。
/// @details
/// 0除算しようとした場合はエラー。エラーが無効なときは除算をせずに左辺を返す。
#define AE_BASE_DIV(lHS, rHS) \
    (rHS != 0 ? (lHS / rHS) : ::ae::base::DivideCheck::Error(lHS))

//@}
//@}
#endif
// EOF
