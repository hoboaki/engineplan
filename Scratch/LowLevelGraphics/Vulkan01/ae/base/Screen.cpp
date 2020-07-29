// 文字コード：UTF-8
#include <ae/base/Screen.hpp>

#include <ae/base/ScreenPos.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Screen::Screen(
    Display_Ext& aOwner,
    const int aWidth,
    const int aHeight
    )
: owner_(aOwner)
, ext_()
, width_(aWidth)
, height_(aHeight)
{
}

//------------------------------------------------------------------------------
int Screen::Width()const
{
    return width_;
}

//------------------------------------------------------------------------------
int Screen::Height()const
{
    return height_;
}

//------------------------------------------------------------------------------
bool Screen::IsContains(const ScreenPosPod& aPos)const
{
    return 0 <= aPos.x && aPos.x < int(width_)
        && 0 <= aPos.y && aPos.y < int(height_);
}

//------------------------------------------------------------------------------
Display_Ext& Screen::display_()
{
    return owner_;
}

//------------------------------------------------------------------------------
Screen_Ext& Screen::Ext_()
{
    return ext_;
}

}} // namespace
// EOF
