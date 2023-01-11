// 文字コード：UTF-8
#include <ae/base/Radian.hpp>

// includes
#include <ae/base/Angle.hpp>
#include <ae/base/Degree.hpp>
#include <ae/base/Pi.hpp>

//------------------------------------------------------------------------------
namespace ae::base {
//------------------------------------------------------------------------------
namespace {

const float tToDegreeRate = 180.0f / AE_BASE_PI;
}
//------------------------------------------------------------------------------
const Angle RadianPod::ToAngle() const
{
    return Angle(*this);
}

//------------------------------------------------------------------------------
const DegreePod RadianPod::ToDegree() const
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
Radian::Radian(const float radian)
: RadianPod()
{
    value = radian;
}

//------------------------------------------------------------------------------
Radian::Radian(const RadianPod& val)
: RadianPod(val)
{
}

} // namespace ae::base
// EOF
