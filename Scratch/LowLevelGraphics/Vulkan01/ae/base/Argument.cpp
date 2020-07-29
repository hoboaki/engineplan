// 文字コード：UTF-8
#include <ae/base/Argument.hpp>

#include <ae/base/PointerCheck.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Argument::Argument(
    const int aArgCount,
    const char* const* aArgValues,
    const char* aExeFileName,
    const char* aExeDirPath
    )
: argCount_(aArgCount)
, argValues_(aArgValues)
, exeFileName_(aExeFileName)
, exeDirPath_(aExeDirPath)
{
}

//------------------------------------------------------------------------------
int Argument::argCount()const
{
    return argCount_;
}

//------------------------------------------------------------------------------
const char* Argument::argValue(const int aIndex)const
{
    // 範囲外チェック
    if (argCount_ <= aIndex) {
        AE_BASE_ERROR_INVALID_VALUE(aIndex);
        return "";
    }

    // 配列ポインタチェック
    if (PointerCheck::InvalidCheck(argValues_)) {
        return "";
    }

    // 文字列ポインタチェック
    const char* value = argValues_[aIndex];
    if (PointerCheck::InvalidCheck(value)) {
        return "";
    }

    // 結果を返す
    return value;
}

//------------------------------------------------------------------------------
const char* Argument::exeFileName()const
{
    if (PointerCheck::InvalidCheck(exeFileName_)) {
        return "";
    }
    return exeFileName_;
}

//------------------------------------------------------------------------------
const char* Argument::exeDirPath()const
{
    if (PointerCheck::InvalidCheck(exeDirPath_)) {
        return "";
    }
    return exeDirPath_;
}

}} // namespace
// EOF
