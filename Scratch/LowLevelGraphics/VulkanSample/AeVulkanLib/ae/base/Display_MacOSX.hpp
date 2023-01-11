// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_DISPLAY_MACOSX_HPP)
#else
#define AE_BASE_INCLUDED_DISPLAY_MACOSX_HPP

#include <ae/base/DisplayContext.hpp>
#include <ae/base/KeyboardUpdateData.hpp>
#include <ae/base/MouseUpdateData.hpp>
#include <ae/base/Placement.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/base/Screen.hpp>

struct AeBaseNSWindow;
namespace ae::base {
class Hid;
}

//------------------------------------------------------------------------------
namespace ae::base {

// MacOSX環境でのDisplayの拡張。
class Display_Ext {
public:
    //============================================================
    static void CBKeyEvent(void* eXT, int unicode, int isDown);
    static void CBModKeyEvent(void* eXT, int isShift, int isCtrl, int isAlt);
    static void CBMouseEvent(void* eXT, int pressedButtons, float x, float y);

    //============================================================
    AeBaseNSWindow* windowPtr;
    Placement<Screen> mainScreen;
    Pointer<Hid> hidPtr;
    int isClosed;
    KeyboardUpdateData keyboardUpdateData;
    MouseUpdateData mouseUpdateData;

    //============================================================
    Display_Ext(const DisplayContext&);
    ~Display_Ext();
};

} // namespace ae::base
#endif
// EOF
