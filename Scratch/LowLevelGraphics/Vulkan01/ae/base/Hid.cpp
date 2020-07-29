// 文字コード：UTF-8
#include <ae/base/Hid.hpp>

#include <ae/base/Display.hpp>
#include <ae/base/Keyboard.hpp>
#include <ae/base/Mouse.hpp>
#include <ae/base/Touch.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Hid::Hid(Display& aDisplay)
: display_(aDisplay)
, ext_()
{
    display_.Ext_().hidPtr.Set(*this);
}

//------------------------------------------------------------------------------
Hid::~Hid()
{
    display_.Ext_().hidPtr.Unset(*this);
}

//------------------------------------------------------------------------------
const Keyboard Hid::Keyboard()const
{
    if (0 < KeyboardCount()) {
        return KeyboardAtIndex(0);
    }
    return Keyboard();
}

//------------------------------------------------------------------------------
const Mouse Hid::Mouse()const
{
    if (0 < MouseCount()) {
        return MouseAtIndex(0);
    }
    return Mouse();
}

//------------------------------------------------------------------------------
const Touch Hid::Touch()const
{
    if (0 < TouchCount()) {
        return TouchAtIndex(0);
    }
    return base::Touch(0);
}

//------------------------------------------------------------------------------
Hid_Ext& Hid::Ext_()
{
    return ext_;
}

}} // namespace
// EOF
