// 文字コード：UTF-8
#include <ae/base/EntryPoint.hpp>

// includes
#include <ae/base/Application.hpp>
#include <ae/base/Argument.hpp>
#include <ae/base/Config.hpp>
#include <ae/base/Console.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/SdkHeader.hpp>
#include <ae/base/StringTraits.hpp>
#include <ae/base/Unused.hpp>

//------------------------------------------------------------------------------
#pragma warning(disable : 4996)

//------------------------------------------------------------------------------
namespace {

enum
{
    tExeFilePathLength = 260, // Windowsのファイル名はパスを含めて最長260文字。
    tExeFileNameLength = 260,
    tExeDirPathLength = 260,
    tArgCharsLength = 8192, // WindowsXP以降のコマンドライン引数の最長。
    tArgPtrsLength = ::ae::base::Argument::ArgCountMax
};

bool tIsConsole = false;
char tExeFilePath[tExeFilePathLength];
char tExeFileName[tExeFileNameLength];
char tExeDirPath[tExeDirPathLength];
int tArgCount = 0;
char tArgChars[tArgCharsLength];
char* tArgPtrs[tArgPtrsLength];

// 指定の文字の最後のindex値取得。
int tLastIndexOf(const char ch, const char* str)
{
    AE_BASE_ASSERT_POINTER(str);
    int index = -1;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == ch) {
            index = i;
        }
    }
    return index;
}

// 文字置き換え。
void tReplaceChar(const char targetCh, const char newCh, char* str)
{
    AE_BASE_ASSERT_POINTER(str);
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == targetCh) {
            str[i] = newCh;
        }
    }
}

// tExeFilePathからtExeFileName,tExeDirPathを設定する
void tSetupExeInfo()
{
    // 最後の'\'の位置
    const int dirPathLength = tLastIndexOf('\\', tExeFilePath);
    AE_BASE_ASSERT_MIN_TERM(dirPathLength, 0, int(tExeDirPathLength));

    // ディレクトリパス
    ::ae::base::StringTraits<char>::NCopy(
        tExeDirPath,
        tExeDirPathLength,
        tExeFilePath);
    tExeDirPath[dirPathLength] = '\0';
    tReplaceChar('\\', '/', tExeDirPath);

    // ファイル名
    ::ae::base::StringTraits<char>::NCopy(
        tExeFileName,
        tExeFileNameLength,
        &tExeFilePath[dirPathLength + 1]);
}

// 空白文字か
bool tIsWhiteCh(const char ch)
{
    switch (ch) {
    case ' ':
    case '\t':
    case '\r':
    case '\n': return true;
    default: break;
    }
    return false;
}

// tArgCharsからtArgCountとaArgPtrsを設定する。
void tSetupArg()
{
    int index = 0;
    while (tArgChars[index] != '\0') {
        // 空白文字をスキップする
        while (tIsWhiteCh(tArgChars[index])) {
            ++index;
        }

        // 0なら何もせず終了
        if (tArgChars[index] == '\0') {
            break;
        }

        // 最初の文字で分岐
        if (tArgChars[index] == '\"') {
            // ダブルコーテーション
            // 次の文字からスタート
            ++index;

            // 先頭が0なら何もせず終了
            if (tArgChars[index] == '\0') {
                break;
            }

            // 先頭ポインタ設定
            tArgPtrs[tArgCount] = &tArgChars[index];

            // 次のダブルコーテーションまで探す
            while (tArgChars[index] != '\0' && tArgChars[index] != '\"') {
                ++index;
            }

            // 現在のindex値に\0を入れる
            tArgChars[index] = '\0';
            ++index;
            ++tArgCount;
        } else { // 通常
            // 先頭ポインタ設定
            tArgPtrs[tArgCount] = &tArgChars[index];

            // 空白文字が見つかるまで進める
            while (!tIsWhiteCh(tArgChars[index])) {
                ++index;
            }

            // 現在のindex値に\0を入れる
            tArgChars[index] = '\0';
            ++index;
            ++tArgCount;
        }
    }
}

// main関数の共通部分。
int tWinMainIN(HINSTANCE instance, int cmdShow)
{
    // 引数の作成
    const ::ae::base::Argument arg(
        tArgCount,
        tArgPtrs,
        tExeFileName,
        tExeDirPath);
    AE_BASE_UNUSED(instance);
    AE_BASE_UNUSED(cmdShow);

    // アプリケーション作成
    ::ae::base::Application app(arg);

    // 実行
    return ::aemain(&app);
}

} // namespace

//------------------------------------------------------------------------------
int WINAPI WinMain(
    HINSTANCE instance,
    HINSTANCE prevInstance,
    LPSTR cmdLine,
    int cmdShow)
{
    // 実行ファイルのパス
    GetModuleFileNameA(instance, tExeFilePath, tExeFilePathLength);
    tSetupExeInfo();

    // 引数の解析
    {
        // まずコピー
        ::ae::base::StringTraits<char>::NCopy(
            tArgChars,
            tArgCharsLength,
            cmdLine);

        // 解析開始
        tSetupArg();
    }

    // 引数の作成
    AE_BASE_UNUSED(instance);
    AE_BASE_UNUSED(prevInstance);
    AE_BASE_UNUSED(cmdLine);
    AE_BASE_UNUSED(cmdShow);
    /// @todo 引数の解析

    // 実行
    return tWinMainIN(instance, cmdShow);
}

//------------------------------------------------------------------------------
#if !defined(AE_BASE_FINAL)
int Main(const int argCount, const char* argValues[])
{
    // フラグオン
    tIsConsole = true;

    // [0]は実行ファイルのフルパス
    // C:\dirname\FileName.exe といった文字列が入っている。
    {
        // フルパス取得
        AE_BASE_ASSERT_LESS_EQUALS(1, argCount);
        const char* fullPath = argValues[0];

        // フルパスを設定
        ::ae::base::StringTraits<char>::NCopy(
            tExeFilePath,
            tExeFilePathLength,
            fullPath);

        // セットアップ
        tSetupExeInfo();
    }

    { // 引数
        int index = 0;
        for (int i = 1; i < argCount && i < tArgPtrsLength; ++i) {
            const ::ae::base::StringTraits<char>::WriteResult result =
                ::ae::base::StringTraits<char>::NCopy(
                    tArgChars,
                    tArgCharsLength - index,
                    argValues[i]);
            tArgPtrs[i] = &tArgChars[index];
            index += ::ae::base::uint(result.length + 1);
        }
        tArgCount = ::ae::base::uint(argCount - 1);
    }

    // 実行
    return tWinMainIN((HINSTANCE)GetModuleHandle(NULL), SW_SHOWNORMAL);
}
#endif
// EOF
