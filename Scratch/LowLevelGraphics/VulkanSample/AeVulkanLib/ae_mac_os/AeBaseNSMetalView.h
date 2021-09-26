// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_AEBASENSMETALVIEW_H)
#else
#define AE_BASE_INCLUDED_AEBASENSMETALVIEW_H

struct AeBaseNSWindow;
struct AeBaseNSMetalView;

#define AE_BASE_METALVIEW_TAG (255)

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
extern struct AeBaseNSMetalView* AeBaseNSMetalView_Setup(
    struct AeBaseNSWindow* window);
void AeBaseNSMetalView_DestroyView(struct AeBaseNSMetalView* view);
void* AeBaseNSMetalView_GetLayer(struct AeBaseNSMetalView* view);
void AeBaseNSMetalView_GetDrawableSize(
    struct AeBaseNSWindow* window,
    int* w,
    int* h);
#ifdef __cplusplus
}
#endif

#endif
// EOF
