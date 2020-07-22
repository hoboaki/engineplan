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
: mOwner(aOwner)
, mExt()
, mWidth(aWidth)
, mHeight(aHeight)
{
}

//------------------------------------------------------------------------------
int Screen::width()const
{
    return mWidth;
}

//------------------------------------------------------------------------------
int Screen::height()const
{
    return mHeight;
}

//------------------------------------------------------------------------------
bool Screen::isContains(const ScreenPosPod& aPos)const
{
    return 0 <= aPos.x && aPos.x < int(mWidth)
        && 0 <= aPos.y && aPos.y < int(mHeight);
}

//------------------------------------------------------------------------------
Display_Ext& Screen::display_()
{
    return mOwner;
}

//------------------------------------------------------------------------------
Screen_Ext& Screen::ext_()
{
    return mExt;
}

}} // namespace
// EOF
