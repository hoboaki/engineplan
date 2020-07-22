// 文字コード：UTF-8
#include <ae/base/Radian.hpp>

#include <ae/base/Angle.hpp>
#include <ae/base/Degree.hpp>
#include <ae/base/Pi.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {
//------------------------------------------------------------------------------
namespace {

const float tToDegreeRate = 180.0f / AE_BASE_PI;
}
//------------------------------------------------------------------------------
const Angle RadianPod::toAngle()const
{
    return Angle(*this);
}

//------------------------------------------------------------------------------
const DegreePod RadianPod::toDegree()const
{
    return Degree(value * tToDegreeRate);
}

//------------------------------------------------------------------------------
Radian::Radian()
: RadianPod()
{
    value = 0;
}

//------------------------------------------------------------------------------
Radian::Radian(const float aRadian)
: RadianPod()
{
    value = aRadian;
}

//------------------------------------------------------------------------------
Radian::Radian(const RadianPod& aVal)
: RadianPod(aVal)
{
}

}} // namespace
// EOF
