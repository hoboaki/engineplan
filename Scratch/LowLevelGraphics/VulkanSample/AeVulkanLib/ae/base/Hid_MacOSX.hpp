// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_HID_MACOSX_HPP)
#else
#define AE_BASE_INCLUDED_HID_MACOSX_HPP

#include <ae/base/Keyboard.hpp>
#include <ae/base/Mouse.hpp>
#include <ae/base/Noncopyable.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

// MacOSXのHid拡張。
class Hid_Ext : private Noncopyable<Hid_Ext> {
public:
    Keyboard keyboard;
    Mouse mouse;
};

} // namespace ae::base
#endif
// EOF
