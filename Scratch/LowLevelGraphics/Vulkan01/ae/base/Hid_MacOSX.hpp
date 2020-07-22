// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_HID_MACOSX_HPP)
#else
#define AE_BASE_INCLUDED_HID_MACOSX_HPP

#include <ae/base/Keyboard.hpp>
#include <ae/base/Mouse.hpp>
#include <ae/base/NonCopyable.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

// MacOSXのHid拡張。
class Hid_Ext : public NonCopyable
{
public:
    Keyboard keyboard;
    Mouse mouse;
};

}} // namespace
#endif
// EOF
