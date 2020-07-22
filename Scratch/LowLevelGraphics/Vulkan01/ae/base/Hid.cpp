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
: mDisplay(aDisplay)
, mExt()
{
    mDisplay.ext_().hidPtr.set(*this);
}

//------------------------------------------------------------------------------
Hid::~Hid()
{
    mDisplay.ext_().hidPtr.unset(*this);
}

//------------------------------------------------------------------------------
const Keyboard Hid::keyboard()const
{
    if (0 < keyboardCount()) {
        return keyboardAtIndex(0);
    }
    return Keyboard();
}

//------------------------------------------------------------------------------
const Mouse Hid::mouse()const
{
    if (0 < mouseCount()) {
        return mouseAtIndex(0);
    }
    return Mouse();
}

//------------------------------------------------------------------------------
const Touch Hid::touch()const
{
    if (0 < touchCount()) {
        return touchAtIndex(0);
    }
    return Touch(0);
}

//------------------------------------------------------------------------------
Hid_Ext& Hid::ext_()
{
    return mExt;
}

}} // namespace
// EOF
