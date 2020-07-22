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
namespace ae {
namespace base {
class Hid;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

// MacOSX環境でのDisplayの拡張。
class Display_Ext
{
public:
    //============================================================
    static void CBKeyEvent(void* aEXT, int aUnicode, int aIsDown);
    static void CBModKeyEvent(void* aEXT, int aIsShift, int aIsCtrl, int aIsAlt);
    static void CBMouseEvent(void* aEXT, int aPressedButtons, float aX, float aY);

    //============================================================
    AeBaseNSWindow* windowPtr;
    Placement< Screen > mainScreen;
    Pointer< Hid > hidPtr;
    int isClosed;
    KeyboardUpdateData keyboardUpdateData;
    MouseUpdateData mouseUpdateData;

    //============================================================
    Display_Ext(const DisplayContext&);
    ~Display_Ext();
};

}} // namespace
#endif
// EOF
