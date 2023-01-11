// 文字コード：UTF-8
#include <ae/base/Argument.hpp>

// includes
#include <ae/base/PointerCheck.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
Argument::Argument(
    const int argCount,
    const char* const* argValues,
    const char* exeFileName,
    const char* exeDirPath)
: argCount_(argCount)
, argValues_(argValues)
, exeFileName_(exeFileName)
, exeDirPath_(exeDirPath)
{
}

//------------------------------------------------------------------------------
int Argument::ArgCount() const
{
    return argCount_;
}

//------------------------------------------------------------------------------
const char* Argument::ArgValue(const int index) const
{
    // 範囲外チェック
    if (argCount_ <= index) {
        AE_BASE_ERROR_INVALID_VALUE(index);
        return "";
    }

    // 配列ポインタチェック
    if (PointerCheck::InvalidCheck(argValues_)) {
        return "";
    }

    // 文字列ポインタチェック
    const char* value = argValues_[index];
    if (PointerCheck::InvalidCheck(value)) {
        return "";
    }

    // 結果を返す
    return value;
}

//------------------------------------------------------------------------------
const char* Argument::ExeFileName() const
{
    if (PointerCheck::InvalidCheck(exeFileName_)) {
        return "";
    }
    return exeFileName_;
}

//------------------------------------------------------------------------------
const char* Argument::ExeDirPath() const
{
    if (PointerCheck::InvalidCheck(exeDirPath_)) {
        return "";
    }
    return exeDirPath_;
}

} // namespace ae::base
// EOF
