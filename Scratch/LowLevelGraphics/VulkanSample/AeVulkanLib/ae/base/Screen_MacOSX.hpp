// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_SCREEN_MACOSX_HPP)
#else
#define AE_BASE_INCLUDED_SCREEN_MACOSX_HPP

struct AeBaseNSMetalView;

//------------------------------------------------------------------------------
namespace ae::base {

// MacOSX環境でのScreenの拡張。
class Screen_Ext {
public:
    //============================================================
    AeBaseNSMetalView* metalView = nullptr;

    //============================================================
    Screen_Ext();
    void* MetalLayer();
};
//@}

} // namespace ae::base
#endif
// EOF
