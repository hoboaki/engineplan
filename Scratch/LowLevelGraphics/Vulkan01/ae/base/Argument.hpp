// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_ARGUMENT_HPP)
#else
#define AE_BASE_INCLUDED_ARGUMENT_HPP

#include <ae/base/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-System
//@{
/// エントリーポイントの引数。
class Argument
{
public:
    // 引数の最大数。
    enum { ArgCountMax = 256 };

    // コンストラクタをユーザーが直接呼ぶことは想定していない。
    // 引数のポインタはポインタをコピーするだけでポインタ先はコピーしない。
    // つまりポインタ先のデータを破棄しないように注意すること。
    Argument(
        int aArgCount
        , const char* const* aArgValues
        , const char* aAppFileName
        , const char* aAppDirPath
    );

/// @name 引数（実行ファイルの情報は含まれない）
//@{
    int        argCount()const;
    const char* argValue(int aIndex)const;
    //@}

    /// @name 実行ファイル情報
    //@{
    /// @brief 実行ファイルのファイル名。
    /// @details 
    /// そういう概念がないOSでは長さ0の文字列を返します。 @n
    const char* exeFileName()const;

    /// @brief 実行ファイルのディレクトリへのパス。
    /// @details 
    /// そういう概念がないOSでは長さ0の文字列を返します。@n 
    /// ディレクトリの区切り文字はWindows上でも'/'を使用します。@n
    /// c:\\dirname\\FileName.exe ならc:/dirname を返します。 @n
    const char* exeDirPath()const;
    //@}

private:
    int              mArgCount;
    const char*const* mArgValues;
    const char*       mExeFileName;
    const char*       mExeDirPath;
};
//@}

}} // namespace
#endif
// EOF
