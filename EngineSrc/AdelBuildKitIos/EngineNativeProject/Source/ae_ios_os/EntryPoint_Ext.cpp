// 文字コード：UTF-8
#include <ae/base/EntryPoint.hpp>

#include <pthread.h>
#include <ae/base/Application.hpp>
#include <ae/base/Argument.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/Unused.hpp>
#include "EntryPoint_Ext.h"
#include "EntryPoint_Sync.h"

//------------------------------------------------------------------------------
namespace {

// スレッドの引数
struct tThreadArg
{
    int result;
    const ::ae::base::Argument* argPtr;
};

} // namespace

//------------------------------------------------------------------------------
int xmainThreadEntryPointC(void* aArg)
{
    // 変換
    tThreadArg* arg = static_cast<tThreadArg*>(aArg);

    // UIMainが立ち上がるまで待つ。
    AeBaseEntryPointSync_XMainWait();

    {// 起動処理開始  
        // Application作成
        ::ae::base::Application app(*arg->argPtr);

        // xmain実行
        arg->result = xmain(app);
    }

    // UIMainに終了したことを通知
    AeBaseEntryPointSync_UIMainSignal();

    // スレッド終了
    return 0;
}

//------------------------------------------------------------------------------
int mainC(
    const int aArgCount,
    char* aArgValues[],
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

// 同期オブジェクト作成
    AeBaseEntryPointSync_Initialize();

    // xmainスレッド作成
    tThreadArg threadArg = {};
    threadArg.argPtr = &arg;
    pthread_t threadXMain;
    {
        int result = pthread_create(
            &threadXMain,
            0, // attr
            xmainThreadEntryPoint,
            &threadArg
            );
        AE_BASE_UNUSED(result);
        AE_BASE_ASSERT_EQUALS(result, 0);
    }

    // UIMain実行
    mainUI(aArgCount, aArgValues);

    // xmainスレッド終了待ち
    {
        int result = pthread_join(threadXMain, 0);
        AE_BASE_UNUSED(result);
        AE_BASE_ASSERT_EQUALS(result, 0);
    }

    // 同期オブジェクト後始末
    AeBaseEntryPointSync_Finalize();

    // 終了
    return threadArg.result;
}

//------------------------------------------------------------------------------
// EOF
