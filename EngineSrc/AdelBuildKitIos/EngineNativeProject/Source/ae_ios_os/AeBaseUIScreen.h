// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_XBASEUICREEN_H)
#else
#define AE_BASE_INCLUDED_XBASEUISCREEN_H

//------------------------------------------------------------------------------
struct AeBaseUIRect
{
    float originX;
    float originY;
    float sizeW;
    float sizeH;
};

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
extern void AeBaseUIScreen_GetMainScreenBounds(struct AeBaseUIRect*);
#ifdef __cplusplus
}
#endif

#endif
// EOF
