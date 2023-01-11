// 文字コード：UTF-8
#include <ae/base/Screen.hpp>

// includes
#include <ae/base/ScreenPos.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
Screen::Screen(Display_Ext& owner, const int width, const int height)
: owner_(owner)
, ext_()
, width_(width)
, height_(height)
{
}

//------------------------------------------------------------------------------
int Screen::Width() const
{
    return width_;
}

//------------------------------------------------------------------------------
int Screen::Height() const
{
    return height_;
}

//------------------------------------------------------------------------------
bool Screen::IsContains(const ScreenPosPod& pos) const
{
    return 0 <= pos.x && pos.x < int(width_) && 0 <= pos.y &&
           pos.y < int(height_);
}

//------------------------------------------------------------------------------
Display_Ext& Screen::Display_()
{
    return owner_;
}

//------------------------------------------------------------------------------
Screen_Ext& Screen::Ext_()
{
    return ext_;
}

//------------------------------------------------------------------------------
void Screen::SetExtent_(const Extent2iPod& extent)
{
    width_ = extent.width;
    height_ = extent.height;
}

} // namespace ae::base
// EOF
