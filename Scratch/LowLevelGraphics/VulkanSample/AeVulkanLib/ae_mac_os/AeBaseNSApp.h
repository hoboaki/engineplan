// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_XBASENSAPP_H)
#else
#define AE_BASE_INCLUDED_XBASENSAPP_H

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
extern void AeBaseNSApp_Initialize(void);
extern void AeBaseNSApp_Finalize(void);
extern void AeBaseNSApp_PollEvent(void);
extern void AeBaseNSApp_Terminate(void);
#ifdef __cplusplus
}
#endif

#endif
// EOF
