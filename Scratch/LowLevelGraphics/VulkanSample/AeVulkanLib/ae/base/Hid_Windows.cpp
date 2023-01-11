// 文字コード：UTF-8
#include <ae/base/Hid.hpp>

// includes
#include <ae/base/Display.hpp>
#include <ae/base/Touch.hpp>
#include <ae/base/Unused.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
int Hid::KeyboardCount() const
{
    return 1;
}

//------------------------------------------------------------------------------
const Keyboard Hid::KeyboardAtIndex(const int index) const
{
    AE_BASE_ASSERT_LESS(index, KeyboardCount());
    AE_BASE_UNUSED(index);
    return ext_.keyboard;
}

//------------------------------------------------------------------------------
int Hid::MouseCount() const
{
    return 1;
}

//------------------------------------------------------------------------------
const Mouse Hid::MouseAtIndex(const int index) const
{
    AE_BASE_ASSERT_LESS(index, MouseCount());
    AE_BASE_UNUSED(index);
    return ext_.mouse;
}

//------------------------------------------------------------------------------
int Hid::SupportedTouchTapCount() const
{
    return 0;
}

//------------------------------------------------------------------------------
int Hid::TouchCount() const
{
    return 0;
}

//------------------------------------------------------------------------------
const Touch Hid::TouchAtIndex(const int) const
{
    AE_BASE_ASSERT_NOT_REACHED();
    return base::Touch(1);
}

} // namespace ae::base
// EOF
