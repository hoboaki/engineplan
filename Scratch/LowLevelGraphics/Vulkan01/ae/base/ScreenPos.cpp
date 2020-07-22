// 文字コード：UTF-8
#include <ae/base/ScreenPos.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
ScreenPos::ScreenPos()
{
    x = 0;
    y = 0;
}

//------------------------------------------------------------------------------
ScreenPos::ScreenPos(const sint16 aX, const sint16 aY)
{
    x = aX;
    y = aY;
}

//------------------------------------------------------------------------------
ScreenPos::ScreenPos(const ScreenPosPod& aObj)
{
    static_cast<ScreenPosPod&>(*this) = aObj;
}

}} // namespace
// EOF
