// 文字コード：UTF-8
#include <ae/base/Hid.hpp>

#include <ae/base/Display.hpp>
#include <ae/base/Keyboard.hpp>
#include <ae/base/Mouse.hpp>
#include "AeBaseUIWindow.h"

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
int Hid::keyboardCount()const
{
    return 0;
}

//------------------------------------------------------------------------------
const Keyboard Hid::keyboardAtIndex(const int)const
{
    AE_BASE_ASSERT_NOT_REACHED();
    return Keyboard();
}

//------------------------------------------------------------------------------
int Hid::mouseCount()const
{
    return 0;
}

//------------------------------------------------------------------------------
const Mouse Hid::mouseAtIndex(const int)const
{
    AE_BASE_ASSERT_NOT_REACHED();
    return Mouse();
}

//------------------------------------------------------------------------------
int Hid::supportedTouchTapCount()const
{
    return AE_BASE_UITOUCHSET_TOUCH_COUNT_MAX;
}

//------------------------------------------------------------------------------
int Hid::touchCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
const Touch Hid::touchAtIndex(const int aIndex)const
{
    if (touchCount() <= aIndex) {
        AE_BASE_ERROR_INVALID_VALUE(aIndex);
        return Touch(AE_BASE_UITOUCHSET_TOUCH_COUNT_MAX);
    }
    return mExt.touch;
}

//------------------------------------------------------------------------------
Hid_Ext::Hid_Ext()
: touch(AE_BASE_UITOUCHSET_TOUCH_COUNT_MAX)
{
}

}} // namespace
// EOF
