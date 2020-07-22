// 文字コード：UTF-8
#include <ae/base/Hid.hpp>

#include <ae/base/Display.hpp>
#include <ae/base/Touch.hpp>
#include <ae/base/Unused.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
int Hid::keyboardCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
const Keyboard Hid::keyboardAtIndex(const int aIndex)const
{
    AE_BASE_ASSERT_LESS(aIndex, keyboardCount());
    AE_BASE_UNUSED(aIndex);
    return mExt.keyboard;
}

//------------------------------------------------------------------------------
int Hid::mouseCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
const Mouse Hid::mouseAtIndex(const int aIndex)const
{
    AE_BASE_ASSERT_LESS(aIndex, mouseCount());
    AE_BASE_UNUSED(aIndex);
    return mExt.mouse;
}

//------------------------------------------------------------------------------
int Hid::supportedTouchTapCount()const
{
    return 0;
}

//------------------------------------------------------------------------------
int Hid::touchCount()const
{
    return 0;
}

//------------------------------------------------------------------------------
const Touch Hid::touchAtIndex(const int)const
{
    AE_BASE_ASSERT_NOT_REACHED();
    return Touch(1);
}

}} // namespace
// EOF
