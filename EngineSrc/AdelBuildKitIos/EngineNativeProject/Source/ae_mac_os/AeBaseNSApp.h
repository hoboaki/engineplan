// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_XBASENSAPP_H)
#else
#define AE_BASE_INCLUDED_XBASENSAPP_H

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
extern void AeBaseNSApp_Initialize();
extern void AeBaseNSApp_Finalize();
extern void AeBaseNSApp_PollEvent();
extern void AeBaseNSApp_Terminate();
#ifdef __cplusplus
}
#endif

#endif
// EOF
