// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_XBASENSSCREEN_H)
#else
#define AE_BASE_INCLUDED_XBASENSSCREEN_H

//------------------------------------------------------------------------------
struct AeBaseNSRect {
    float originX;
    float originY;
    float sizeW;
    float sizeH;
};

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
extern void AeBaseNSScreen_GetMainScreenFrame(struct AeBaseNSRect*);
extern void AeBaseNSScreen_GetMainScreenVisibleFrame(struct AeBaseNSRect*);
#ifdef __cplusplus
}
#endif

#endif
// EOF
