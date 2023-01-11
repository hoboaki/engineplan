// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_RUNTIMEASSERT_HPP)
#else
#define AE_BASE_INCLUDED_RUNTIMEASSERT_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/Console.hpp>
#include <ae/base/PointerCheck.hpp>
#include <ae/base/RuntimeError.hpp>
#include <ae/base/ShortString.hpp>
#include <ae/base/ToShortString.hpp>
#include <ae/base/ValueInRange.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

// 実行時Assertを扱う空間。
struct RuntimeAssert
{
    static const char* const Separator; // 分離する文字列。
    static const char* const Header; // ヘッダ。
    static const char* const FileLineFmt; // ファイルと行数。
    static const char* const LabelCondition; // ラベル:Condition。
    static const char* const LabelMessage; // ラベル:Message。
};

} // namespace ae::base

// 実行時Assertの本体。AE_BASE_CONFIG_ENABLE_RUNTIME_ERRORが定義されているときに動作。
#if defined(AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR)
#define AE_BASE_RUNTIME_ASSERT(cond, ...)                                   \
    do {                                                                    \
        if (!(cond)) {                                                      \
            AE_BASE_COUT_LINE(::ae::base::RuntimeAssert::Separator);        \
            AE_BASE_COUT_LINE_WITH_TIME(::ae::base::RuntimeAssert::Header); \
            AE_BASE_COUTFMT_LINE(                                           \
                ::ae::base::RuntimeAssert::FileLineFmt,                     \
                __FILE__,                                                   \
                __LINE__);                                                  \
            AE_BASE_COUT(::ae::base::RuntimeAssert::LabelCondition);        \
            AE_BASE_COUT_LINE(#cond);                                       \
            AE_BASE_COUT(::ae::base::RuntimeAssert::LabelMessage);          \
            AE_BASE_COUTFMT_LINE(__VA_ARGS__, #cond);                       \
            AE_BASE_COUT_LINE(::ae::base::RuntimeAssert::Separator);        \
            ::ae::base::RuntimeError::OnError();                            \
            while (1) {                                                     \
            }                                                               \
        }                                                                   \
    } while (0)

#else
#define AE_BASE_RUNTIME_ASSERT(cond, ...) \
    do {                                  \
    } while (false)
#endif
//@}

/// @addtogroup AeBase-Debug
//@{
/// @name 実行時アサート
//@{

/// @brief メッセージ付きアサート。指定の条件式がtrueであることをチェックする。
/// @param cond 条件式。
/// @param msg メッセージ文字列。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_MSG(cond, msg) AE_BASE_RUNTIME_ASSERT(cond, "%s", msg)

/// @brief
/// printfフォーマットのメッセージ付きアサート。指定の条件式がtrueであることをチェックする。
/// @param cond 条件式。
/// @param format printfフォーマット文字列。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_MSGFMT(cond, format, ...) \
    AE_BASE_RUNTIME_ASSERT(cond, format, __VA_ARGS__)

/// @brief 指定の条件式がtrueであることをチェックする。
/// @param cond 条件式。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT(cond) AE_BASE_ASSERT_MSG(cond, #cond)

/// @brief NULLであるべき値をチェックする。
/// @param val チェックする値。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_SHOULD_NULL(val) \
    AE_BASE_ASSERT_MSG(                 \
        (val) == 0,                     \
        "Value is not Null (%s)\n",     \
        AE_BASE_TO_SHORT_STRING(val).ReadPtr())

/// @brief NULLじゃない値をさしているかチェックする。
/// @param val チェックする値。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_NOT_NULL(val) \
    AE_BASE_ASSERT_MSG((val) != 0, "Value is Null\n")

/// @briefポインタとして有効な値であることをチェックする。
/// @param val チェックする値。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_POINTER(val)                          \
    do {                                                     \
        if (!::ae::base::PointerCheck::IsValid(val)) {       \
            AE_BASE_ERROR_INVALID_VALUE(                     \
                reinterpret_cast<::ae::base::pword_t>(val)); \
        }                                                    \
    } while (false)

/// @brief 到達したらエラーにする。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// 第1引数以降にprintfの書式でメッセージを指定してください。@n
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_NOT_REACHED_MSGFMT(format, ...) \
    AE_BASE_ASSERT_MSGFMT(false, format, __VA_ARGS__)
#define AE_BASE_ASSERT_NOT_REACHED_MSG(msg) AE_BASE_ASSERT_MSG(false, msg)

/// @brief 到達したらエラーにする。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_NOT_REACHED() \
    AE_BASE_ASSERT_NOT_REACHED_MSG("Should nod reach here.\n")

/// @brief 不正な値としてその値をコンソールにダンプしつつエラーにする。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ERROR_INVALID_VALUE(val) \
    AE_BASE_ASSERT_NOT_REACHED_MSGFMT(   \
        "%s is invalid Value(%s)\n",     \
        #val,                            \
        AE_BASE_TO_SHORT_STRING(val).ReadPtr())

/// @brief AE_BASE_ERROR_INVALID_VALUE のenum版。
/// @see AE_BASE_ERROR_INVALID_VALUE
#define AE_BASE_ERROR_INVALID_ENUM(val) AE_BASE_ERROR_INVALID_VALUE(int(val))

/// @brief ２つの値が等しいことをチェックする。
/// @param val1 チェックする値。
/// @param val2 チェックする値。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_EQUALS(val1, val2)        \
    AE_BASE_ASSERT_MSGFMT(                       \
        val1 == val2,                            \
        "%s(%s) is not equals %s(%s).\n",        \
        #val1,                                   \
        AE_BASE_TO_SHORT_STRING(val1).ReadPtr(), \
        #val2,                                   \
        AE_BASE_TO_SHORT_STRING(val2).ReadPtr())

/// @brief ２つの値が等しくないことをチェックする。
/// @param val1 チェックする値。
/// @param val2 チェックする値。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_NOT_EQUALS(val1, val2)    \
    AE_BASE_ASSERT_MSGFMT(                       \
        val1 != val2,                            \
        "%s(%s) is quals %s(%s).\n",             \
        #val1,                                   \
        AE_BASE_TO_SHORT_STRING(val1).ReadPtr(), \
        #val2,                                   \
        AE_BASE_TO_SHORT_STRING(val2).ReadPtr())

/// @def AE_BASE_TEST
/// @brief テストコマンドを実行する。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#if defined(AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR)
#define AE_BASE_TEST(cond) (cond)
#else
#define AE_BASE_TEST(cond) \
    do {                   \
    } while (false)
#endif

/// @brief val < termValであることをチェックする。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_LESS(val, termVal) \
    AE_BASE_ASSERT_RANGE_CORE2(AE_BASE_VALUE_IN_RANGE_LESS, val, termVal)

/// @brief val <= maxValであることをチェックする。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @copydetails AE_BASE_ASSERT_MSG
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_LESS_EQUALS(val, maxVal) \
    AE_BASE_ASSERT_RANGE_CORE2(AE_BASE_VALUE_IN_RANGE_LESS_EQUALS, val, maxVal)

/// @brief minVal <= val <= maxValであることをチェックする。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_MIN_MAX(val, minVal, maxVal) \
    AE_BASE_ASSERT_RANGE_CORE3(                     \
        AE_BASE_VALUE_IN_RANGE_MIN_MAX,             \
        minVal,                                     \
        val,                                        \
        maxVal)

/// @brief minVal <= val < termValであることをチェックする。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_MIN_TERM(val, minVal, termVal) \
    AE_BASE_ASSERT_RANGE_CORE3(                       \
        AE_BASE_VALUE_IN_RANGE_MIN_TERM,              \
        minVal,                                       \
        val,                                          \
        termVal)

/// @brief enumValueが 0 <= enumValue < TERMであることをチェックする。
/// @details
/// 調査するEnumにTERMが定義されている必要があります。
#define AE_BASE_ASSERT_ENUM(enumValue, enumType) \
    AE_BASE_ASSERT_MIN_TERM(int(enumValue), int(0), int(enumType::TERM))

//@}
//@}

// 範囲チェックアサートの実装。
#define AE_BASE_ASSERT_RANGE_CORE2(func, val1, val2) \
    AE_BASE_ASSERT_MSGFMT(                           \
        func(val1, val2),                            \
        "Value is not in range.\n"                   \
        "val1 : %s \naVal2 : %s\n",                  \
        AE_BASE_TO_SHORT_STRING(val1).ReadPtr(),     \
        AE_BASE_TO_SHORT_STRING(val2).ReadPtr())
#define AE_BASE_ASSERT_RANGE_CORE3(func, val1, val2, val3) \
    AE_BASE_ASSERT_MSGFMT(                                 \
        func(val1, val2, val3),                            \
        "Value is not in range.\n"                         \
        "val1 : %s \naVal2 : %s \naVal3 : %s\n",           \
        AE_BASE_TO_SHORT_STRING(val1).ReadPtr(),           \
        AE_BASE_TO_SHORT_STRING(val2).ReadPtr(),           \
        AE_BASE_TO_SHORT_STRING(val3).ReadPtr())

#endif
// EOF
