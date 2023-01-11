// 文字コード：UTF-8
#include <ae/base/StringTraits.hpp>

// includes
#include <ae/base/Compiler.hpp>
#include <ae/base/PointerCheck.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <cstdio>
#include <cstring>
#include <cwchar>

//------------------------------------------------------------------------------
#if defined(AE_BASE_COMPILER_MSVC)
#pragma warning(disable : 4996) // for vsnprintf
#endif

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
namespace {

// 関数実装用テンプレート構造体宣言。
template <typename CharType>
struct tImpl;

// char用。
template <>
struct tImpl<char>
{
    // 終端文字。
    static const char TERM_VALUE = '\0';

    // Lengthの実装。
    static pword_t Length(const char* str) { return std::strlen(str); }

    // Equalsの実装。
    static bool Equals(const char* strA, const char* strB)
    {
        return std::strcmp(strA, strB) == 0;
    }

    // NCopyの実装。
    static int NCopy(
        char* buffer,
        const pword_t bufferLength,
        const char* str)
    {
        return SNPrintf(buffer, bufferLength, "%s", str);
    }

    // SNPrintfの実装。
    static int SNPrintf(
        char* buffer,
        const pword_t bufferLength,
        const char* format,
        ...)
    {
        va_list arg;
        va_start(arg, format);
        int result = VSNPrintf(buffer, bufferLength, format, arg);
        va_end(arg);
        return result;
    }

    // VSNPrintfの実装。
    static int VSNPrintf(
        char* buffer,
        const pword_t bufferLength,
        const char* format,
        va_list arg)
    {
        return vsnprintf(buffer, bufferLength, format, arg);
    }
};

// wchar_t用。
template <>
struct tImpl<wchar_t>
{
    // 終端文字。
    static const wchar_t TERM_VALUE = '\0';

    // Lengthの実装。
    static pword_t Length(const wchar_t* str) { return std::wcslen(str); }

    // Equalsの実装。
    static bool Equals(const wchar_t* strA, const wchar_t* strB)
    {
        return std::wcscmp(strA, strB) == 0;
    }

    // NCopyの実装。
    static int NCopy(
        wchar_t* buffer,
        const pword_t bufferLength,
        const wchar_t* str)
    {
        return SNPrintf(buffer, bufferLength, L"%s", str);
    }

    // SNPrintfの実装。
    static int SNPrintf(
        wchar_t* buffer,
        const pword_t bufferLength,
        const wchar_t* format,
        ...)
    {
        va_list arg;
        va_start(arg, format);
        int result = VSNPrintf(buffer, bufferLength, format, arg);
        va_end(arg);
        return result;
    }

    // VSNPrintfの実装。
    static int VSNPrintf(
        wchar_t* buffer,
        const pword_t bufferLength,
        const wchar_t* format,
        va_list arg)
    {
        return vswprintf(buffer, bufferLength, format, arg);
    }
};

} // namespace
//------------------------------------------------------------------------------
namespace {
// Lengthの実装。
template <typename CharType>
pword_t tLength(const CharType* str)
{
    // ポインタチェック。
    if (PointerCheck::InvalidCheck(str)) {
        return 0;
    }

    // 結果を返す。
    return tImpl<CharType>::Length(str);
}
} // namespace

// Lengthの実装(char版)。
template <>
pword_t StringTraits<char>::Length(const char* str)
{
    return tLength<char>(str);
}

// Lengthの実装(wchar_t版)。
template <>
pword_t StringTraits<wchar_t>::Length(const wchar_t* str)
{
    return tLength<wchar_t>(str);
}

//------------------------------------------------------------------------------
namespace {
// Equalsの実装。
template <typename CharType>
bool tEquals(const CharType* strA, const CharType* strB)
{
    // ポインタチェック。
    if (PointerCheck::InvalidCheck(strA) || PointerCheck::InvalidCheck(strB)) {
        return 0;
    }

    // 結果を返す。
    return tImpl<CharType>::Equals(strA, strB);
}

} // namespace

// Equalsの実装(char版)。
template <>
bool StringTraits<char>::Equals(const char* strA, const char* strB)
{
    return tEquals<char>(strA, strB);
}

// Equalsの実装(wchar_t版)。
template <>
bool StringTraits<wchar_t>::Equals(const wchar_t* strA, const wchar_t* strB)
{
    return tEquals<wchar_t>(strA, strB);
}

//------------------------------------------------------------------------------
namespace {
// NCopyStrictの実装。
template <typename CharType>
const typename StringTraits<CharType>::WriteResult tNCopyStrict(
    CharType* buffer,
    const pword_t bufferLength,
    const CharType* str)
{
    // 結果用変数
    typename StringTraits<CharType>::WriteResult result = {};

    // ポインタチェック
    if (PointerCheck::InvalidCheck(buffer) ||
        PointerCheck::InvalidCheck(str)) { // 無効なポインタ
        return result;
    }

    // 実行
    int ret = tImpl<CharType>::NCopy(buffer, bufferLength, str);
    if (ret < 0) {
        // 失敗
        return result;
    }

    // 成功
    result.isSuccess = true;
    result.length = pword_t(ret);
    return result;
}
} // namespace

// NCopyStrictの実装(char版)。
template <>
const StringTraits<char>::WriteResult StringTraits<char>::NCopyStrict(
    char* buffer,
    const pword_t bufferLength,
    const char* str)
{
    return tNCopyStrict<char>(buffer, bufferLength, str);
}

// NCopyStrictの実装(wchar_t版)。
template <>
const StringTraits<wchar_t>::WriteResult StringTraits<wchar_t>::NCopyStrict(
    wchar_t* buffer,
    const pword_t bufferLength,
    const wchar_t* str)
{
    return tNCopyStrict<wchar_t>(buffer, bufferLength, str);
}

//------------------------------------------------------------------------------
namespace {
// NCopyの実装。
template <typename CharType>
const typename StringTraits<CharType>::WriteResult tNCopy(
    CharType* buffer,
    const pword_t bufferLength,
    const CharType* str)
{
    // 結果用変数
    typedef typename StringTraits<CharType>::WriteResult WriteResult;
    WriteResult result = {};

    // バッファ長チェック
    if (bufferLength < 1) {
        // 不正な引数
        AE_BASE_ERROR_INVALID_VALUE(bufferLength);
        return result;
    }

    // 実行
    result = StringTraits<CharType>::NCopyStrict(buffer, bufferLength, str);

    // 終端文字設定
    if (!result.isSuccess ||
        bufferLength <= result.length) { // 想定していないことが起きたときの処理
        // 本来あってはならない
        AE_BASE_ASSERT_NOT_REACHED();

        // result初期化
        const WriteResult tmpResult = {};
        result = tmpResult;

        // 終端文字設定
        buffer[0] = tImpl<CharType>::TERM_VALUE;
    }

    // 結果を返す
    return result;
}

} // namespace

// NCopyの実装(char版)。
template <>
const StringTraits<char>::WriteResult StringTraits<char>::NCopy(
    char* buffer,
    const pword_t bufferLength,
    const char* str)
{
    return tNCopy<char>(buffer, bufferLength, str);
}

// NCopyの実装(wchar_t版)。
template <>
const StringTraits<wchar_t>::WriteResult StringTraits<wchar_t>::NCopy(
    wchar_t* buffer,
    const pword_t bufferLength,
    const wchar_t* str)
{
    return tNCopy<wchar_t>(buffer, bufferLength, str);
}

//------------------------------------------------------------------------------
namespace {
// VSNPrintfStrictの実装。
template <typename CharType>
const typename StringTraits<CharType>::WriteResult tVSNPrintfStrict(
    CharType* buffer,
    const pword_t bufferLength,
    const CharType* format,
    va_list arg)
{
    // 結果用変数
    typename StringTraits<CharType>::WriteResult result = {};

    // ポインタチェック
    if (PointerCheck::InvalidCheck(buffer) ||
        PointerCheck::InvalidCheck(format)) { // 無効なポインタ
        return result;
    }

    // 実行
    int ret = tImpl<CharType>::VSNPrintf(buffer, bufferLength, format, arg);
    if (ret < 0) {
        // 失敗
        return result;
    }

    // 成功
    result.isSuccess = true;
    result.length = pword_t(ret);
    return result;
}
} // namespace

// VSNPrintfStrictの実装(char版)。
template <>
const StringTraits<char>::WriteResult StringTraits<char>::VSNPrintfStrict(
    char* buffer,
    const pword_t bufferLength,
    const char* format,
    va_list arg)
{
    return tVSNPrintfStrict<char>(buffer, bufferLength, format, arg);
}

// VSNPrintfStrictの実装(wchar_t版)。
template <>
const StringTraits<wchar_t>::WriteResult StringTraits<wchar_t>::VSNPrintfStrict(
    wchar_t* buffer,
    const pword_t bufferLength,
    const wchar_t* format,
    va_list arg)
{
    return tVSNPrintfStrict<wchar_t>(buffer, bufferLength, format, arg);
}

//------------------------------------------------------------------------------
// 特殊化関数をSNPrintfより先に定義しないといけないので
// VSNPrintfを先に定義。
namespace {
// VSNPrintfの実装。
template <typename CharType>
const typename StringTraits<CharType>::WriteResult tVSNPrintf(
    CharType* buffer,
    const pword_t bufferLength,
    const CharType* format,
    va_list arg)
{
    // 結果用変数
    typedef typename StringTraits<CharType>::WriteResult WriteResult;
    WriteResult result = {};

    // バッファ長チェック
    if (bufferLength < 1) {
        // 不正な引数
        AE_BASE_ERROR_INVALID_VALUE(bufferLength);
        return result;
    }

    // 実行
    result = StringTraits<CharType>::VSNPrintfStrict(
        buffer,
        bufferLength,
        format,
        arg);

    // 終端文字設定
    if (!result.isSuccess ||
        bufferLength <= result.length) { // 想定していないことが起きたときの処理
        // 本来あってはならない
        AE_BASE_ASSERT_NOT_REACHED();

        // result初期化
        const WriteResult tmpResult = {};
        result = tmpResult;

        // 終端文字設定
        buffer[0] = tImpl<CharType>::TERM_VALUE;
    }

    // 結果を返す
    return result;
}
} // namespace

// VSNPrintfの実装(char版)。
template <>
const StringTraits<char>::WriteResult StringTraits<char>::VSNPrintf(
    char* buffer,
    const pword_t bufferLength,
    const char* format,
    va_list arg)
{
    return tVSNPrintf<char>(buffer, bufferLength, format, arg);
}

// VSNPrintfの実装(wchar_t版)。
template <>
const StringTraits<wchar_t>::WriteResult StringTraits<wchar_t>::VSNPrintf(
    wchar_t* buffer,
    const pword_t bufferLength,
    const wchar_t* format,
    va_list arg)
{
    return tVSNPrintf<wchar_t>(buffer, bufferLength, format, arg);
}

//------------------------------------------------------------------------------
// SNPrintfStrictの実装(char版)。
template <>
const StringTraits<char>::WriteResult StringTraits<char>::SNPrintfStrict(
    char* buffer,
    const pword_t bufferLength,
    const char* format,
    ...)
{
    va_list arg;
    va_start(arg, format);
    const WriteResult result =
        VSNPrintfStrict(buffer, bufferLength, format, arg);
    va_end(arg);
    return result;
}

// SNPrintfStrictの実装(wchar_t版)。
template <>
const StringTraits<wchar_t>::WriteResult StringTraits<wchar_t>::SNPrintfStrict(
    wchar_t* buffer,
    const pword_t bufferLength,
    const wchar_t* format,
    ...)
{
    va_list arg;
    va_start(arg, format);
    const WriteResult result =
        VSNPrintfStrict(buffer, bufferLength, format, arg);
    va_end(arg);
    return result;
}

//------------------------------------------------------------------------------
// SNPrintfの実装(char版)。
template <>
const StringTraits<char>::WriteResult StringTraits<char>::SNPrintf(
    char* buffer,
    const pword_t bufferLength,
    const char* format,
    ...)
{
    va_list arg;
    va_start(arg, format);
    const WriteResult result = VSNPrintf(buffer, bufferLength, format, arg);
    va_end(arg);
    return result;
}

// SNPrintfの実装(wchar_t版)。
template <>
const StringTraits<wchar_t>::WriteResult StringTraits<wchar_t>::SNPrintf(
    wchar_t* buffer,
    const pword_t bufferLength,
    const wchar_t* format,
    ...)
{
    va_list arg;
    va_start(arg, format);
    const WriteResult result = VSNPrintf(buffer, bufferLength, format, arg);
    va_end(arg);
    return result;
}

} // namespace ae::base
// EOF
