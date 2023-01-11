// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_DISPLAY_IOS_HPP)
#else
#define AE_BASE_INCLUDED_DISPLAY_IOS_HPP

#include <ae/base/DisplayContext.hpp>
#include <ae/base/Placement.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/base/Screen.hpp>

struct AeBaseUIWindow;
namespace ae::base {
class Hid;
}

//------------------------------------------------------------------------------
namespace ae::base {

// MacOSX環境でのDisplayの拡張。
class Display_Ext {
public:
    //============================================================
    AeBaseUIWindow* windowPtr;
    Placement<Screen> mainScreen;
    Pointer<Hid> hidPtr;

    //============================================================
    Display_Ext(const DisplayContext&);
    ~Display_Ext();
};

} // namespace ae::base
#endif
// EOF
