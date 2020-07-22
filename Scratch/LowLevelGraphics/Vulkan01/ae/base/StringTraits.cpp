// 文字コード：UTF-8
#include <ae/base/StringTraits.hpp>

#include <cstdio>
#include <cstring>
#include <cwchar>
#include <ae/base/Compiler.hpp>
#include <ae/base/PointerCheck.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
#if defined(AE_BASE_COMPILER_MSVC)
#pragma warning(disable: 4996) // for vsnprintf
#endif

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
namespace {

// 関数実装用テンプレート構造体宣言。
template< typename CharType >
struct tImpl;

// char用。
template<>
struct tImpl< char >
{
    // 終端文字。
    static const char TERM_VALUE = '\0';

    // Lengthの実装。
    static pword_t Length(const char* aStr)
    {
        return std::strlen(aStr);
    }

    // Equalsの実装。
    static bool Equals(const char* aStrA, const char* aStrB)
    {
        return std::strcmp(aStrA, aStrB) == 0;
    }

    // NCopyの実装。
    static int NCopy(
        char* aBuffer,
        const pword_t aBufferLength,
        const char* aStr
        )
    {
        return SNPrintf(aBuffer, aBufferLength, "%s", aStr);
    }

    // SNPrintfの実装。
    static int SNPrintf(
        char* aBuffer,
        const pword_t aBufferLength,
        const char* aFormat,
        ...
        )
    {
        va_list arg;
        va_start(arg, aFormat);
        int result = VSNPrintf(aBuffer, aBufferLength, aFormat, arg);
        va_end(arg);
        return result;
    }

    // VSNPrintfの実装。
    static int VSNPrintf(
        char* aBuffer,
        const pword_t aBufferLength,
        const char* aFormat,
        va_list aArg
        )
    {
        return vsnprintf(aBuffer, aBufferLength, aFormat, aArg);
    }
};

// wchar_t用。
template<>
struct tImpl< wchar_t >
{
    // 終端文字。
    static const wchar_t TERM_VALUE = '\0';

    // Lengthの実装。
    static pword_t Length(const wchar_t* aStr)
    {
        return std::wcslen(aStr);
    }

    // Equalsの実装。
    static bool Equals(const wchar_t* aStrA, const wchar_t* aStrB)
    {
        return std::wcscmp(aStrA, aStrB) == 0;
    }

    // NCopyの実装。
    static int NCopy(
        wchar_t* aBuffer,
        const pword_t aBufferLength,
        const wchar_t* aStr
        )
    {
        return SNPrintf(aBuffer, aBufferLength, L"%s", aStr);
    }

    // SNPrintfの実装。
    static int SNPrintf(
        wchar_t* aBuffer,
        const pword_t aBufferLength,
        const wchar_t* aFormat,
        ...
        )
    {
        va_list arg;
        va_start(arg, aFormat);
        int result = VSNPrintf(aBuffer, aBufferLength, aFormat, arg);
        va_end(arg);
        return result;
    }

    // VSNPrintfの実装。
    static int VSNPrintf(
        wchar_t* aBuffer,
        const pword_t aBufferLength,
        const wchar_t* aFormat,
        va_list aArg
        )
    {
        return vswprintf(aBuffer, aBufferLength, aFormat, aArg);
    }
};

}
//------------------------------------------------------------------------------
namespace {
    // Lengthの実装。
template < typename CharType >
pword_t tLength(const CharType* aStr)
{
    // ポインタチェック。
    if (PointerCheck::InvalidCheck(aStr)) {
        return 0;
    }

    // 結果を返す。
    return tImpl< CharType >::Length(aStr);
}
}

// Lengthの実装(char版)。
template <>
pword_t StringTraits< char >::Length(const char* aStr)
{
    return tLength< char >(aStr);
}

// Lengthの実装(wchar_t版)。
template <>
pword_t StringTraits< wchar_t >::Length(const wchar_t* aStr)
{
    return tLength< wchar_t >(aStr);
}

//------------------------------------------------------------------------------
namespace {
    // Equalsの実装。
template < typename CharType >
bool tEquals(const CharType* aStrA, const CharType* aStrB)
{
    // ポインタチェック。
    if (PointerCheck::InvalidCheck(aStrA)
        || PointerCheck::InvalidCheck(aStrB)
        )
    {
        return 0;
    }

    // 結果を返す。
    return tImpl< CharType >::Equals(aStrA, aStrB);
}

}

// Equalsの実装(char版)。
template <>
bool StringTraits< char >::Equals(const char* aStrA, const char* aStrB)
{
    return tEquals< char >(aStrA, aStrB);
}

// Equalsの実装(wchar_t版)。
template <>
bool StringTraits< wchar_t >::Equals(const wchar_t* aStrA, const wchar_t* aStrB)
{
    return tEquals< wchar_t >(aStrA, aStrB);
}

//------------------------------------------------------------------------------
namespace {
// NCopyStrictの実装。
template< typename CharType >
const typename StringTraits< CharType >::WriteResult tNCopyStrict(
    CharType* aBuffer,
    const pword_t aBufferLength,
    const CharType* aStr
    )
{
    // 結果用変数
    typename StringTraits< CharType >::WriteResult result = {};

    // ポインタチェック
    if (PointerCheck::InvalidCheck(aBuffer)
        || PointerCheck::InvalidCheck(aStr)
        )
    {// 無効なポインタ
        return result;
    }

    // 実行
    int ret = tImpl< CharType >::NCopy(aBuffer, aBufferLength, aStr);
    if (ret < 0) {
        // 失敗
        return result;
    }

    // 成功
    result.isSuccess = true;
    result.length = pword_t(ret);
    return result;
}
}

// NCopyStrictの実装(char版)。
template <>
const StringTraits< char >::WriteResult StringTraits< char >::NCopyStrict(
    char* aBuffer,
    const pword_t aBufferLength,
    const char* aStr
    )
{
    return tNCopyStrict< char >(aBuffer, aBufferLength, aStr);
}

// NCopyStrictの実装(wchar_t版)。
template <>
const StringTraits< wchar_t >::WriteResult StringTraits< wchar_t >::NCopyStrict(
    wchar_t* aBuffer,
    const pword_t aBufferLength,
    const wchar_t* aStr
    )
{
    return tNCopyStrict< wchar_t >(aBuffer, aBufferLength, aStr);
}

//------------------------------------------------------------------------------
namespace {
// NCopyの実装。
template< typename CharType >
const typename StringTraits< CharType >::WriteResult tNCopy(
    CharType* aBuffer,
    const pword_t aBufferLength,
    const CharType* aStr
    )
{
    // 結果用変数
    typedef typename StringTraits< CharType >::WriteResult WriteResult;
    WriteResult result = {};

    // バッファ長チェック
    if (aBufferLength < 1) {
        // 不正な引数
        AE_BASE_ERROR_INVALID_VALUE(aBufferLength);
        return result;
    }

    // 実行
    result = StringTraits< CharType >::NCopyStrict(aBuffer, aBufferLength, aStr);

    // 終端文字設定
    if (!result.isSuccess
        || aBufferLength <= result.length
        )
    {// 想定していないことが起きたときの処理
        // 本来あってはならない
        AE_BASE_ASSERT_NOT_REACHED();

        // result初期化
        const WriteResult tmpResult = {};
        result = tmpResult;

        // 終端文字設定
        aBuffer[0] = tImpl< CharType >::TERM_VALUE;
    }

    // 結果を返す
    return result;
}

}

// NCopyの実装(char版)。
template <>
const StringTraits< char >::WriteResult StringTraits< char >::NCopy(
    char* aBuffer,
    const pword_t aBufferLength,
    const char* aStr
    )
{
    return tNCopy< char >(aBuffer, aBufferLength, aStr);
}

// NCopyの実装(wchar_t版)。
template <>
const StringTraits< wchar_t >::WriteResult StringTraits< wchar_t >::NCopy(
    wchar_t* aBuffer,
    const pword_t aBufferLength,
    const wchar_t* aStr
    )
{
    return tNCopy< wchar_t >(aBuffer, aBufferLength, aStr);
}

//------------------------------------------------------------------------------
namespace {
// VSNPrintfStrictの実装。
template< typename CharType >
const typename StringTraits< CharType >::WriteResult tVSNPrintfStrict(
    CharType* aBuffer,
    const pword_t aBufferLength,
    const CharType* aFormat,
    va_list aArg
    )
{
    // 結果用変数
    typename StringTraits< CharType >::WriteResult result = {};

    // ポインタチェック
    if (PointerCheck::InvalidCheck(aBuffer)
        || PointerCheck::InvalidCheck(aFormat)
        )
    {// 無効なポインタ
        return result;
    }

    // 実行
    int ret = tImpl< CharType >::VSNPrintf(aBuffer, aBufferLength, aFormat, aArg);
    if (ret < 0) {
        // 失敗
        return result;
    }

    // 成功
    result.isSuccess = true;
    result.length = pword_t(ret);
    return result;
}
}

// VSNPrintfStrictの実装(char版)。
template <>
const StringTraits< char >::WriteResult StringTraits< char >::VSNPrintfStrict(
    char* aBuffer,
    const pword_t aBufferLength,
    const char* aFormat,
    va_list aArg
    )
{
    return tVSNPrintfStrict< char >(aBuffer, aBufferLength, aFormat, aArg);
}

// VSNPrintfStrictの実装(wchar_t版)。
template <>
const StringTraits< wchar_t >::WriteResult StringTraits< wchar_t >::VSNPrintfStrict(
    wchar_t* aBuffer,
    const pword_t aBufferLength,
    const wchar_t* aFormat,
    va_list aArg
    )
{
    return tVSNPrintfStrict< wchar_t >(aBuffer, aBufferLength, aFormat, aArg);
}

//------------------------------------------------------------------------------
// 特殊化関数をSNPrintfより先に定義しないといけないので
// VSNPrintfを先に定義。
namespace {
// VSNPrintfの実装。
template< typename CharType >
const typename StringTraits< CharType >::WriteResult tVSNPrintf(
    CharType* aBuffer,
    const pword_t aBufferLength,
    const CharType* aFormat,
    va_list aArg
    )
{
    // 結果用変数
    typedef typename StringTraits< CharType >::WriteResult WriteResult;
    WriteResult result = {};

    // バッファ長チェック
    if (aBufferLength < 1) {
        // 不正な引数
        AE_BASE_ERROR_INVALID_VALUE(aBufferLength);
        return result;
    }

    // 実行
    result = StringTraits< CharType >::VSNPrintfStrict(aBuffer, aBufferLength, aFormat, aArg);

    // 終端文字設定
    if (!result.isSuccess
        || aBufferLength <= result.length
        )
    {// 想定していないことが起きたときの処理
        // 本来あってはならない
        AE_BASE_ASSERT_NOT_REACHED();

        // result初期化
        const WriteResult tmpResult = {};
        result = tmpResult;

        // 終端文字設定
        aBuffer[0] = tImpl< CharType >::TERM_VALUE;
    }

    // 結果を返す
    return result;
}
}

// VSNPrintfの実装(char版)。
template <>
const StringTraits< char >::WriteResult StringTraits< char >::VSNPrintf(
    char* aBuffer,
    const pword_t aBufferLength,
    const char* aFormat,
    va_list aArg
    )
{
    return tVSNPrintf< char >(aBuffer, aBufferLength, aFormat, aArg);
}

// VSNPrintfの実装(wchar_t版)。
template <>
const StringTraits< wchar_t >::WriteResult StringTraits< wchar_t >::VSNPrintf(
    wchar_t* aBuffer,
    const pword_t aBufferLength,
    const wchar_t* aFormat,
    va_list aArg
    )
{
    return tVSNPrintf< wchar_t >(aBuffer, aBufferLength, aFormat, aArg);
}

//------------------------------------------------------------------------------
// SNPrintfStrictの実装(char版)。
template <>
const StringTraits< char >::WriteResult StringTraits< char >::SNPrintfStrict(
    char* aBuffer,
    const pword_t aBufferLength,
    const char* aFormat,
    ...
    )
{
    va_list arg;
    va_start(arg, aFormat);
    const WriteResult result = VSNPrintfStrict(aBuffer, aBufferLength, aFormat, arg);
    va_end(arg);
    return result;
}

// SNPrintfStrictの実装(wchar_t版)。
template <>
const StringTraits< wchar_t >::WriteResult StringTraits< wchar_t >::SNPrintfStrict(
    wchar_t* aBuffer,
    const pword_t aBufferLength,
    const wchar_t* aFormat,
    ...
    )
{
    va_list arg;
    va_start(arg, aFormat);
    const WriteResult result = VSNPrintfStrict(aBuffer, aBufferLength, aFormat, arg);
    va_end(arg);
    return result;
}

//------------------------------------------------------------------------------
// SNPrintfの実装(char版)。
template <>
const StringTraits< char >::WriteResult StringTraits< char >::SNPrintf(
    char* aBuffer,
    const pword_t aBufferLength,
    const char* aFormat,
    ...
    )
{
    va_list arg;
    va_start(arg, aFormat);
    const WriteResult result = VSNPrintf(aBuffer, aBufferLength, aFormat, arg);
    va_end(arg);
    return result;
}

// SNPrintfの実装(wchar_t版)。
template <>
const StringTraits< wchar_t >::WriteResult StringTraits< wchar_t >::SNPrintf(
    wchar_t* aBuffer,
    const pword_t aBufferLength,
    const wchar_t* aFormat,
    ...
    )
{
    va_list arg;
    va_start(arg, aFormat);
    const WriteResult result = VSNPrintf(aBuffer, aBufferLength, aFormat, arg);
    va_end(arg);
    return result;
}

}} // namespace
// EOF
