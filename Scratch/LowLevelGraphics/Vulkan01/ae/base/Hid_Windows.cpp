// 文字コード：UTF-8
#include <ae/base/Hid.hpp>

#include <ae/base/Display.hpp>
#include <ae/base/Touch.hpp>
#include <ae/base/Unused.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
int Hid::KeyboardCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
const Keyboard Hid::KeyboardAtIndex(const int aIndex)const
{
    AE_BASE_ASSERT_LESS(aIndex, KeyboardCount());
    AE_BASE_UNUSED(aIndex);
    return ext_.keyboard;
}

//------------------------------------------------------------------------------
int Hid::MouseCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
const Mouse Hid::MouseAtIndex(const int aIndex)const
{
    AE_BASE_ASSERT_LESS(aIndex, MouseCount());
    AE_BASE_UNUSED(aIndex);
    return ext_.mouse;
}

//------------------------------------------------------------------------------
int Hid::SupportedTouchTapCount()const
{
    return 0;
}

//------------------------------------------------------------------------------
int Hid::TouchCount()const
{
    return 0;
}

//------------------------------------------------------------------------------
const Touch Hid::TouchAtIndex(const int)const
{
    AE_BASE_ASSERT_NOT_REACHED();
    return base::Touch(1);
}

}} // namespace
// EOF
