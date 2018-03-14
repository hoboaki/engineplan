// 文字コード：UTF-8
#include <ae/base/EntryPoint.hpp>

#include <ae/base/Application.hpp>
#include <ae/base/Argument.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
extern "C" int mainC(int aArgCount, const char* aArgValues[], const char* aExeFileName, const char* aExeDirPath);
int mainC(
    const int aArgCount,
    const char* aArgValues[],
    const char* aExeFileName,
    const char* aExeDirPath
    )
{
    // 引数作成
    const int offset = 1; // Exeのパスは別で処理しているためパス。
    AE_BASE_ASSERT_LESS_EQUALS(offset, aArgCount);
    const ::ae::base::Argument arg(
        ::ae::base::uint(aArgCount - offset),
        &aArgValues[offset],
        aExeFileName,
        aExeDirPath
        );

// アプリケーション作成
    ::ae::base::Application app(arg);

    // 実行
    return xmain(app);
}

//------------------------------------------------------------------------------
// EOF
