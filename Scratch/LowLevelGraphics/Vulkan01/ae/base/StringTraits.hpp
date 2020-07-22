// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_CHARTRAITS_HPP)
#else
#define AE_BASE_INCLUDED_CHARTRAITS_HPP

#include <cstdarg>
#include <ae/base/Bool.hpp>
#include <ae/base/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-String
//@{
    /// @brief 文字列に関する関数群。
    /// @details テンプレート引数に char/wchar_t を入れて使ってください。
    /// @code
    /// // 例
    /// ::ae::base::pword_t charLength = ::ae::base::StringTraits< char >::Length( "abc" );
    /// ::ae::base::pword_t wcharLength = ::ae::base::StringTraits< wchar_t >::Length( L"abc" );
    /// @endcode
template< typename CharType >
struct StringTraits
{
    /// Write系の結果。
    struct WriteResult
    {
        BoolPod32 isSuccess; ///< 成功したか。
        pword_t   length;    ///< 書き込んだ文字数。終端文字は含めない。
    };

    /// @brief 指定の文字列の長さを取得する。
    /// @return 文字数(バイト長ではない)。終端文字は含めない。
    static pword_t Length(const CharType* aStr);

    /// @brief ２つの文字列の内容が一致するか。
    /// @return 一致する場合true。
    static bool Equals(const CharType* aStrA, const CharType* aStrB);

    /// @brief 文字列を指定のバッファにコピーする。
    /// @param aBuffer       格納先バッファ。
    /// @param aBufferLength 格納先バッファの配列長。バイト長ではない。
    /// @param aStr          コピーする文字列。
    /// @see NCopy
    /// @details NCopyを使って良いケースならそちらを使うことを薦めます。
    static const WriteResult NCopyStrict(CharType* aBuffer, pword_t aBufferLength, const CharType* aStr);

    /// @brief NCopyと同様の処理を行い追加でエラーチェックをする。
    /// @param aBuffer       格納先バッファ。
    /// @param aBufferLength 格納先バッファの配列長。バイト長ではない。1 <= aBufferLength。
    /// @param aStr          コピーする文字列。
    /// @see NCopy
    /// @details 
    /// バッファ長が不足した場合はAssertで落とします。@n
    /// Assertが無効な場合は終端文字を0バイト目に設定します。
    static const WriteResult NCopy(CharType* aBuffer, pword_t aBufferLength, const CharType* aStr);

    /// @brief 指定のバッファにPrintfフォーマットで作成された文字列を格納する。
    /// @param aBuffer       格納先バッファ。
    /// @param aBufferLength 格納先バッファの配列長。バイト長ではない。
    /// @param aFormat       出力する文字列のフォーマット文字列。
    /// @see SNPrintf
    /// @details SNPrintfを使って良いケースならそちらを使うことを勧めます。
    static const WriteResult SNPrintfStrict(CharType* aBuffer, pword_t aBufferLength, const CharType* aFormat, ...);

    /// @brief SNPrintfStrictと同様の処理を行い追加でエラーチェックをする。
    /// @param aBuffer       格納先バッファ。
    /// @param aBufferLength 格納先バッファの配列長。バイト長ではない。1 <= aBufferLength。
    /// @param aFormat       出力する文字列のフォーマット文字列。
    /// @see SNPrintfStrict
    /// @details 
    /// バッファ長が不足した場合はAssertで落とします。@n
    /// Assertが無効な場合は終端文字を0バイト目に設定します。
    static const WriteResult SNPrintf(CharType* aBuffer, pword_t aBufferLength, const CharType* aFormat, ...);

    /// @brief 指定のバッファにPrintfフォーマットで作成された文字列を格納する。
    /// @param aBuffer       格納先バッファ。
    /// @param aBufferLength 格納先バッファの配列長。バイト長ではない。
    /// @param aFormat       出力する文字列のフォーマット文字列。
    /// @param aArg          フォーマット文字列に対する引数。
    /// @see VSNPrintf
    /// @details VSNPrintfを使って良いケースならそちらを使うことを勧めます。
    static const WriteResult VSNPrintfStrict(CharType* aBuffer, pword_t aBufferLength, const CharType* aFormat, va_list aArg);

    /// @brief VSNPrintfStrictと同様の処理を行い追加でエラーチェックをする。
    /// @param aBuffer       格納先バッファ。
    /// @param aBufferLength 格納先バッファの配列長。バイト長ではない。1 <= aBufferLength。
    /// @param aFormat       出力する文字列のフォーマット文字列。
    /// @param aArg          フォーマット文字列に対する引数。
    /// @see VSNPrintfStrict
    /// @details 
    /// バッファ長が不足した場合はAssertで落とします。@n
    /// Assertが無効な場合は終端文字を0バイト目に設定します。
    static const WriteResult VSNPrintf(CharType* aBuffer, pword_t aBufferLength, const CharType* aFormat, va_list aArg);
};
//@}

}} // namespace
#endif
// EOF
