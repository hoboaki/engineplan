// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_SCREEN_MACOSX_HPP)
#else
#define AE_BASE_INCLUDED_SCREEN_MACOSX_HPP

struct AeG3dNSOpenGLView;

//------------------------------------------------------------------------------
namespace ae {
namespace base {

// MacOSX環境でのScreenの拡張。
class Screen_Ext
{
public:
    //============================================================
    AeG3dNSOpenGLView* glView;

    //============================================================
    Screen_Ext();
};
//@}

}} // namespace
#endif
// EOF
