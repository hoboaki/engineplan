// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_CHARTRAITS_HPP)
#else
#define AE_BASE_INCLUDED_CHARTRAITS_HPP

#include <ae/base/Bool.hpp>
#include <ae/base/BuiltInTypes.hpp>
#include <cstdarg>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-String
//@{
/// @brief 文字列に関する関数群。
/// @details テンプレート引数に char/wchar_t を入れて使ってください。
/// @code
/// // 例
/// ::ae::base::pword_t charLength = ::ae::base::StringTraits< char >::Length(
/// "abc" );
/// ::ae::base::pword_t wcharLength = ::ae::base::StringTraits< wchar_t
/// >::Length( L"abc" );
/// @endcode
template <typename CharType>
struct StringTraits
{
    /// Write系の結果。
    struct WriteResult
    {
        BoolPod32 isSuccess; ///< 成功したか。
        pword_t length; ///< 書き込んだ文字数。終端文字は含めない。
    };

    /// @brief 指定の文字列の長さを取得する。
    /// @return 文字数(バイト長ではない)。終端文字は含めない。
    static pword_t Length(const CharType* str);

    /// @brief ２つの文字列の内容が一致するか。
    /// @return 一致する場合true。
    static bool Equals(const CharType* strA, const CharType* strB);

    /// @brief 文字列を指定のバッファにコピーする。
    /// @param buffer       格納先バッファ。
    /// @param bufferLength 格納先バッファの配列長。バイト長ではない。
    /// @param str          コピーする文字列。
    /// @see NCopy
    /// @details NCopyを使って良いケースならそちらを使うことを薦めます。
    static const WriteResult NCopyStrict(
        CharType* buffer,
        pword_t bufferLength,
        const CharType* str);

    /// @brief NCopyと同様の処理を行い追加でエラーチェックをする。
    /// @param buffer       格納先バッファ。
    /// @param bufferLength 格納先バッファの配列長。バイト長ではない。1 <=
    /// bufferLength。
    /// @param str          コピーする文字列。
    /// @see NCopy
    /// @details
    /// バッファ長が不足した場合はAssertで落とします。@n
    /// Assertが無効な場合は終端文字を0バイト目に設定します。
    static const WriteResult NCopy(
        CharType* buffer,
        pword_t bufferLength,
        const CharType* str);

    /// @brief 指定のバッファにPrintfフォーマットで作成された文字列を格納する。
    /// @param buffer       格納先バッファ。
    /// @param bufferLength 格納先バッファの配列長。バイト長ではない。
    /// @param format       出力する文字列のフォーマット文字列。
    /// @see SNPrintf
    /// @details SNPrintfを使って良いケースならそちらを使うことを勧めます。
    static const WriteResult SNPrintfStrict(
        CharType* buffer,
        pword_t bufferLength,
        const CharType* format,
        ...);

    /// @brief SNPrintfStrictと同様の処理を行い追加でエラーチェックをする。
    /// @param buffer       格納先バッファ。
    /// @param bufferLength 格納先バッファの配列長。バイト長ではない。1 <=
    /// bufferLength。
    /// @param format       出力する文字列のフォーマット文字列。
    /// @see SNPrintfStrict
    /// @details
    /// バッファ長が不足した場合はAssertで落とします。@n
    /// Assertが無効な場合は終端文字を0バイト目に設定します。
    static const WriteResult SNPrintf(
        CharType* buffer,
        pword_t bufferLength,
        const CharType* format,
        ...);

    /// @brief 指定のバッファにPrintfフォーマットで作成された文字列を格納する。
    /// @param buffer       格納先バッファ。
    /// @param bufferLength 格納先バッファの配列長。バイト長ではない。
    /// @param format       出力する文字列のフォーマット文字列。
    /// @param arg          フォーマット文字列に対する引数。
    /// @see VSNPrintf
    /// @details VSNPrintfを使って良いケースならそちらを使うことを勧めます。
    static const WriteResult VSNPrintfStrict(
        CharType* buffer,
        pword_t bufferLength,
        const CharType* format,
        va_list arg);

    /// @brief VSNPrintfStrictと同様の処理を行い追加でエラーチェックをする。
    /// @param buffer       格納先バッファ。
    /// @param bufferLength 格納先バッファの配列長。バイト長ではない。1 <=
    /// bufferLength。
    /// @param format       出力する文字列のフォーマット文字列。
    /// @param arg          フォーマット文字列に対する引数。
    /// @see VSNPrintfStrict
    /// @details
    /// バッファ長が不足した場合はAssertで落とします。@n
    /// Assertが無効な場合は終端文字を0バイト目に設定します。
    static const WriteResult VSNPrintf(
        CharType* buffer,
        pword_t bufferLength,
        const CharType* format,
        va_list arg);
};
//@}

} // namespace ae::base
#endif
// EOF
