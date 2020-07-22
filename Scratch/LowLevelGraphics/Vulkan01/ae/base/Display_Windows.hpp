// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_DISPLAY_WINDOWS_HPP)
#else
#define AE_BASE_INCLUDED_DISPLAY_WINDOWS_HPP

#include <ae/base/Bool.hpp>
#include <ae/base/DisplayContext.hpp>
#include <ae/base/KeyboardUpdateData.hpp>
#include <ae/base/MouseUpdateData.hpp>
#include <ae/base/Placement.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/base/Screen.hpp>
#include <ae/base/SdkHeader.hpp>

namespace ae {
namespace base {
class Application;
class Hid;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-System
//@{
// Windows環境でのDisplayの拡張。
class Display_Ext
{
public:
    //============================================================
    enum { KEY_NUM = 256 };

    //============================================================
    static LRESULT CALLBACK WindowProcess(HWND, UINT, WPARAM, LPARAM);

    //============================================================
    HINSTANCE hinstance;
    HWND hwindow;
    WNDCLASSEX windowClass;
    MSG  message;
    POINT minSize;
    Placement< Screen > mainScreen;
    Pointer< Hid > hidPtr;
    Bool32 isClosed;
    KeyboardUpdateData keyboardUpdateData;
    MouseUpdateData mouseUpdateData;

    //============================================================
    Display_Ext(const DisplayContext&);

    //============================================================
    void    pollEvent(Application&);
    LRESULT windowProcess(HWND, UINT, WPARAM, LPARAM);
};
//@}

}} // namespace
#endif
// EOF
