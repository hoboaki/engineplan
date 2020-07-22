// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_SCREEN_IOS_HPP)
#else
#define AE_BASE_INCLUDED_SCREEN_IOS_HPP

struct AeG3dUIOpenGLView;

//------------------------------------------------------------------------------
namespace ae {
namespace base {

// iOS環境でのScreenの拡張。
class Screen_Ext
{
public:
    //============================================================
    AeG3dUIOpenGLView* glView;

    //============================================================
    Screen_Ext();
};
//@}

}} // namespace
#endif
// EOF
