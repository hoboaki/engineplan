// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_XBASENSWINDOW_H)
#else
#define AE_BASE_INCLUDED_XBASENSWINDOW_H

struct AeBaseNSWindow;

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    typedef void (*AeBaseNSWindow_CBKeyEvent)( void* aOwner , int aUnicode , int aIsDown );
    typedef void (*AeBaseNSWindow_CBModKeyEvent)( void* aOwner , int aIsShift , int aIsCtrl , int aIsAlt );
    typedef void (*AeBaseNSWindow_CBMouseEvent)( void* aOwner , int aPressedButtons , float aX , float aY );
    extern struct AeBaseNSWindow* AeBaseNSWindow_Create( float aPosX , float aPosY , float aWidth , float aHeight , void* aOwnerPtr , int* aIsClosedPtr , AeBaseNSWindow_CBKeyEvent , AeBaseNSWindow_CBModKeyEvent , AeBaseNSWindow_CBMouseEvent );
    extern void AeBaseNSWindow_Destroy( struct AeBaseNSWindow* );
    extern void AeBaseNSWindow_Show( struct AeBaseNSWindow* );
#ifdef __cplusplus
}
#endif

#endif
// EOF
