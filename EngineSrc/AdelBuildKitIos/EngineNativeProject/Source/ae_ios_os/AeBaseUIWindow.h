// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_XBASEUIWindow_H)
#else
#define AE_BASE_INCLUDED_XBASEUIWindow_H

struct AeBaseUIWindow;
#define AE_BASE_UITOUCHSET_TOUCH_COUNT_MAX (4)

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
typedef struct 
{
    int   tapCount;
    float tapPosX;
    float tapPosY;
} AeBaseUITouch;
typedef struct
{
    AeBaseUITouch touches[AE_BASE_UITOUCHSET_TOUCH_COUNT_MAX];
} AeBaseUITouchSet;
extern struct AeBaseUIWindow* AeBaseUIWindow_Create();
extern void AeBaseUIWindow_Destroy( struct AeBaseUIWindow* );
extern void AeBaseUIWindow_Show( struct AeBaseUIWindow* );
extern const AeBaseUITouchSet* AeBaseUIWindow_PollTouch( struct AeBaseUIWindow* );
#ifdef __cplusplus
}
#endif

#endif
// EOF
