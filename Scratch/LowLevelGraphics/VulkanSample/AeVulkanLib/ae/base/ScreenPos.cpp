// 文字コード：UTF-8
#include <ae/base/ScreenPos.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
ScreenPos::ScreenPos()
{
    this->x = 0;
    this->y = 0;
}

//------------------------------------------------------------------------------
ScreenPos::ScreenPos(const sint16 x, const sint16 y)
{
    this->x = x;
    this->y = y;
}

//------------------------------------------------------------------------------
ScreenPos::ScreenPos(const ScreenPosPod& obj)
{
    static_cast<ScreenPosPod&>(*this) = obj;
}

} // namespace ae::base
// EOF
