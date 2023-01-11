// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_CONSOLE_HPP)
#else
#define AE_BASE_INCLUDED_CONSOLE_HPP

#include <ae/base/Config.hpp>
#include <ae/base/ToShortString.hpp>
#include <cstdarg>

namespace ae::base {
class IConsoleCallback;
}

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Debug
//@{
/// コンソールに関する関数を定義する空間。
struct Console
{
    /// @brief デフォルトの時間フォーマット文字列を取得する。
    /// @return フォーマット文字列。
    /// @see SetTimeFormatString
    static const char* const DefaultTimeFormatString();

    /// @brief 時間フォーマット文字列を設定する。
    /// @param format フォーマット文字列。文字列長は終端文字を含めて64文字まで。
    /// @details
    /// printf形式で「年,月,日,時,分,秒,ミリ秒,マイクロ秒」(全てuint型)がフォーマット文字列の後に続きます。
    /// それを処理するような文字列を設定してください。 @n
    /// 出力結果が終端文字を含めて64文字以内になるようにしてください。もしそれを超える場合の動作は不定です。
    /// @n format は内部バッファにコピーされます。
    static void SetTimeFormatString(const char* format);

    /// @brief デフォルトのコールバッククラスを取得する。
    /// @return デフォルトのコールバッククラス。
    /// @details
    /// デフォルトのコールバッククラスは改行を'\n'、現在時刻を""としてstd::vprintfを呼ぶ実装になっています。
    static IConsoleCallback& DefaultCallback();

    /// @brief コールバッククラスを設定する。
    /// @param callback 設定するコールバック。
    static void SetCallback(IConsoleCallback& callback);

    /// @brief printf形式で文字列をコンソールに書き込む。
    /// @param format printfフォーマット文字列。
    static void WriteF(const char* format, ...);

    /// @brief vprintf形式で文字列をコンソールに書き込む。
    /// @param format printfフォーマット文字列。
    static void WriteVF(const char* format, va_list);

    /// @brief printf形式で文字列をコンソールに改行書き込みする。
    /// @param format printfフォーマット文字列。
    static void WriteLineF(const char* format, ...);

    /// @brief vprintf形式で文字列をコンソールに改行書き込みする。
    /// @param format printfフォーマット文字列。
    static void WriteLineVF(const char* format, va_list);

    /// 現在時間をコンソールに書き込む。
    static void WriteTime();

    /// @brief 現在時間と共にprintf形式で文字列をコンソールに改行書き込みする。
    /// @param format printfフォーマット文字列。
    static void TimeWriteLineF(const char* format, ...);

    /// @brief 現在時間と共にvprintf形式で文字列をコンソールに改行書き込みする。
    /// @param format printfフォーマット文字列。
    static void TimeWriteLineVF(const char* format, va_list);
};
//@}

} // namespace ae::base

// 準備
#if defined(AE_BASE_CONFIG_ENABLE_LOGSTR)
#define AE_BASE_COUT_CORE(fmt, ...) \
    ::ae::base::Console::WriteF(fmt, __VA_ARGS__)
#else
#define AE_BASE_COUT_CORE(fmt, ...) \
    do {                            \
    } while (0)
#endif

/// @addtogroup AeBase-Debug
//@{
/// @name コンソール出力
//@{

/// @brief 文字列をコンソールに書き込む。
/// @see AE_BASE_CONFIG_ENABLE_LOGSTR
/// @details ログ文字列が無効な時は何もしません。
#define AE_BASE_COUT(str) AE_BASE_COUT_CORE("%s", str)

/// @brief printfフォーマットの文字列をコンソールに書き込む。
/// @see AE_BASE_CONFIG_ENABLE_LOGSTR
/// @details ログ文字列が無効な時は何もしません。
#define AE_BASE_COUTFMT(fmt, ...) AE_BASE_COUT_CORE(fmt, __VA_ARGS__)

/// @def AE_BASE_COUT_TIME
/// @brief 現在時刻をコンソールに書き込む。
/// @see AE_BASE_CONFIG_ENABLE_LOGSTR
/// @details ログ文字列が無効な時は何もしません。
#if defined(AE_BASE_CONFIG_ENABLE_LOGSTR)
#define AE_BASE_COUT_TIME() ::ae::base::Console::WriteTime()
#else
#define AE_BASE_COUT_TIME() \
    do {                    \
    } while (false)
#endif

/// @def AE_BASE_COUT_END_LINE
/// @brief 改行コードをコンソールに書き込む。
/// @see AE_BASE_CONFIG_ENABLE_LOGSTR
/// @details ログ文字列が無効な時は何もしません。
#if defined(AE_BASE_CONFIG_ENABLE_LOGSTR)
#define AE_BASE_COUT_END_LINE() ::ae::base::Console::WriteLineF("%s", "")
#else
#define AE_BASE_COUT_END_LINE() \
    do {                        \
    } while (false)
#endif

/// @brief 文字列をコンソールに改行書き込みする。
/// @see AE_BASE_CONFIG_ENABLE_LOGSTR
/// @details ログ文字列が無効な時は何もしません。
#define AE_BASE_COUT_LINE(str)   \
    do {                         \
        AE_BASE_COUT(str);       \
        AE_BASE_COUT_END_LINE(); \
    } while (0)

/// @brief printfフォーマットの文字列をコンソールに改行書き込みする。
/// @see AE_BASE_CONFIG_ENABLE_LOGSTR
/// @details ログ文字列が無効な時は何もしません。
#define AE_BASE_COUTFMT_LINE(...)     \
    do {                              \
        AE_BASE_COUTFMT(__VA_ARGS__); \
        AE_BASE_COUT_END_LINE();      \
    } while (0)

/// @brief 現在時間と共にprintfフォーマットの文字列をコンソールに書き込む。
/// @see AE_BASE_CONFIG_ENABLE_LOGSTR
/// @details ログ文字列が無効な時は何もしません。
#define AE_BASE_COUT_WITH_TIME(str) \
    do {                            \
        AE_BASE_COUT_TIME();        \
        AE_BASE_COUT(str);          \
    } while (0)

/// @brief 現在時間と共にprintfフォーマットの文字列をコンソールに書き込む。
/// @see AE_BASE_CONFIG_ENABLE_LOGSTR
/// @details ログ文字列が無効な時は何もしません。
#define AE_BASE_COUTFMT_WITH_TIME(...) \
    do {                               \
        AE_BASE_COUT_TIME();           \
        AE_BASE_COUTFMT(__VA_ARGS__);  \
    } while (0)

/// @brief 現在時間と共に文字列をコンソールに改行書き込みする。
/// @see AE_BASE_CONFIG_ENABLE_LOGSTR
/// @details ログ文字列が無効な時は何もしません。
#define AE_BASE_COUT_LINE_WITH_TIME(str) \
    do {                                 \
        AE_BASE_COUT_WITH_TIME(str);     \
        AE_BASE_COUT_END_LINE();         \
    } while (0)

/// @brief
/// 現在時間と共にprintfフォーマットの文字列をコンソールに改行書き込みする。
/// @see AE_BASE_CONFIG_ENABLE_LOGSTR
/// @details ログ文字列が無効な時は何もしません。
#define AE_BASE_COUTFMT_LINE_WITH_TIME(...)     \
    do {                                        \
        AE_BASE_COUTFMT_WITH_TIME(__VA_ARGS__); \
        AE_BASE_COUT_END_LINE();                \
    } while (0)

/// @brief 現在時刻と共にファイル名と行番号をコンソールに改行書き込みする。
/// @see AE_BASE_CONFIG_ENABLE_LOGSTR
/// @details ログ文字列が無効な時は何もしません。
#define AE_BASE_CHECKPOINT() \
    AE_BASE_COUTFMT_LINE_WITH_TIME("%s at %lu\n", __FILE__, __LINE__)

/// @brief 現在時刻と共に変数の名前・値をコンソールに改行書き込みする。
/// @param val ダンプする値。ShortString変換に対応していないとエラーになる。
/// @see AE_BASE_CONFIG_ENABLE_LOGSTR
/// @details ログ文字列が無効な時は何もしません。
#define AE_BASE_DUMP(val)           \
    AE_BASE_COUTFMT_LINE_WITH_TIME( \
        "%s : %s\n",                \
        #val,                       \
        AE_BASE_TO_SHORT_STRING(val).ReadPtr())

//@}
//@}
#endif
// EOF
