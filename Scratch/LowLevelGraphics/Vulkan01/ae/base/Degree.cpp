// 文字コード：UTF-8
#include <ae/base/Degree.hpp>

#include <ae/base/Angle.hpp>
#include <ae/base/Pi.hpp>
#include <ae/base/Radian.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
namespace {

const float tToRadianRate = AE_BASE_PI / 180.0f;

} // namespace

//------------------------------------------------------------------------------
const Angle DegreePod::toAngle()const
{
    return Angle(*this);
}

//------------------------------------------------------------------------------
const RadianPod DegreePod::toRadian()const
{
    return Radian(value * tToRadianRate);
}

//------------------------------------------------------------------------------
Degree::Degree()
: DegreePod()
{
    value = 0;
}

//------------------------------------------------------------------------------
Degree::Degree(const float aDegree)
: DegreePod()
{
    value = aDegree;
}

//------------------------------------------------------------------------------
Degree::Degree(const DegreePod& aVal)
: DegreePod(aVal)
{
}

}} // namespace
// EOF
