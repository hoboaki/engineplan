// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_ENTRYPOINT_SYNC_H)
#else
#define AE_BASE_INCLUDED_ENTRYPOINT_SYNC_H

#include "AeBaseAppEvent.h"

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
extern void AeBaseEntryPointSync_Initialize();
extern void AeBaseEntryPointSync_Finalize();
extern void AeBaseEntryPointSync_XMainWait();
extern void AeBaseEntryPointSync_XMainSignal();
extern void AeBaseEntryPointSync_UIMainWait();
extern void AeBaseEntryPointSync_UIMainSignal();
extern void AeBaseEntryPointSync_SetAppEvent( AeBaseAppEvent );
extern AeBaseAppEvent AeBaseEntryPointSync_GetAppEvent();
extern void AeBaseEntryPointSync_CATransactionFlush();
#ifdef __cplusplus
}
#endif
#endif
// EOF
