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

namespace ae::base {
class Application;
class Hid;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-System
//@{
// Windows環境でのDisplayの拡張。
// @todo 複数インスタンス対応。（今は１つしかインスタンスが作れない）
class Display_Ext {
public:
    //============================================================
    enum
    {
        KEY_NUM = 256
    };

    //============================================================
    static LRESULT CALLBACK WindowProcess(HWND, UINT, WPARAM, LPARAM);

    //============================================================
    HINSTANCE hinstance;
    HWND hwindow;
    WNDCLASSEX windowClass;
    MSG message;
    POINT minSize;
    Placement<Screen> mainScreen;
    Pointer<Hid> hidPtr;
    Bool32 isClosed;
    KeyboardUpdateData keyboardUpdateData;
    MouseUpdateData mouseUpdateData;

    //============================================================
    Display_Ext(const DisplayContext&);
    ~Display_Ext();

    //============================================================
    void PollEvent(Application&);
    LRESULT WindowProcessLocal(HWND, UINT, WPARAM, LPARAM);
};
//@}

} // namespace ae::base
#endif
// EOF
