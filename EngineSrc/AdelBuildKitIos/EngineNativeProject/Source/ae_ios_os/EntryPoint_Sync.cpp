// 文字コード：UTF-8
#include "EntryPoint_Sync.h"

#include <pthread.h>
#include <ae/base/Placement.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace {

// condのラッパークラス。
class tSynbObj
{
public:
    tSynbObj()
        : mMutex(),
        mCond(),
        mValue(1)
    {
        int result = int();
        result = pthread_mutex_init(&mMutex, 0);
        AE_BASE_ASSERT_EQUALS(result, 0);
        result = pthread_cond_init(&mCond, 0);
        AE_BASE_ASSERT_EQUALS(result, 0);
    }

    ~tSynbObj()
    {
        int result = int();
        result = pthread_cond_destroy(&mCond);
        AE_BASE_ASSERT_EQUALS(result, 0);
        result = pthread_mutex_destroy(&mMutex);
        AE_BASE_ASSERT_EQUALS(result, 0);
    }

    void signal()
    {
        int result = int();
        result = pthread_mutex_lock(&mMutex);
        AE_BASE_ASSERT_EQUALS(result, 0);

        AE_BASE_ASSERT_EQUALS(mValue, 1);
        mValue = 0;

        result = pthread_cond_broadcast(&mCond);
        AE_BASE_ASSERT_EQUALS(result, 0);

        result = pthread_mutex_unlock(&mMutex);
        AE_BASE_ASSERT_EQUALS(result, 0);
    }

    void wait()
    {
        int result = int();
        result = pthread_mutex_lock(&mMutex);
        AE_BASE_ASSERT_EQUALS(result, 0);

        while (0 < mValue) {
            result = pthread_cond_wait(&mCond, &mMutex);
            AE_BASE_ASSERT_EQUALS(result, 0);
        }
        mValue = 1;

        result = pthread_cond_broadcast(&mCond);
        AE_BASE_ASSERT_EQUALS(result, 0);

        result = pthread_mutex_unlock(&mMutex);
        AE_BASE_ASSERT_EQUALS(result, 0);
    }
private:
    pthread_mutex_t mMutex;
    pthread_cond_t  mCond;
    volatile int mValue;
};

// 複数のCondをまとめたもの。
class tSyncObjSet
{
public:
    tSynbObj syncXMain;
    tSynbObj syncUIMain;
};

// 同期オブジェクトの変数。
::ae::base::Placement< tSyncObjSet > tSyncObjSetInstance;
AeBaseAppEvent tAppEvent = AeBaseAppEvent_INVALID;

} // namespace

//------------------------------------------------------------------------------
void AeBaseEntryPointSync_Initialize()
{
    tSyncObjSetInstance.init();
}

//------------------------------------------------------------------------------
void AeBaseEntryPointSync_Finalize()
{
    tSyncObjSetInstance.reset();
}

//------------------------------------------------------------------------------
void AeBaseEntryPointSync_XMainWait()
{
    AeBaseEntryPointSync_CATransactionFlush();
    tSyncObjSetInstance->syncXMain.wait();
}

//------------------------------------------------------------------------------
void AeBaseEntryPointSync_XMainSignal()
{
    tSyncObjSetInstance->syncXMain.signal();
}

//------------------------------------------------------------------------------
void AeBaseEntryPointSync_UIMainWait()
{
    AeBaseEntryPointSync_CATransactionFlush();
    tSyncObjSetInstance->syncUIMain.wait();
}

//------------------------------------------------------------------------------
void AeBaseEntryPointSync_UIMainSignal()
{
    tSyncObjSetInstance->syncUIMain.signal();
}

//------------------------------------------------------------------------------
void AeBaseEntryPointSync_SetAppEvent(const AeBaseAppEvent aEvent)
{
    tAppEvent = aEvent;
}

//------------------------------------------------------------------------------
AeBaseAppEvent AeBaseEntryPointSync_GetAppEvent()
{
    return tAppEvent;
}

//------------------------------------------------------------------------------
// EOF
