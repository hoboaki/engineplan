// 文字コード：UTF-8
#include <ae/base/Degree.hpp>

// includes
#include <ae/base/Angle.hpp>
#include <ae/base/Pi.hpp>
#include <ae/base/Radian.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
namespace {

const float tToRadianRate = AE_BASE_PI / 180.0f;

} // namespace

//------------------------------------------------------------------------------
const Angle DegreePod::ToAngle() const
{
    return Angle(*this);
}

//------------------------------------------------------------------------------
const RadianPod DegreePod::ToRadian() const
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
Degree::Degree(const float degree)
: DegreePod()
{
    value = degree;
}

//------------------------------------------------------------------------------
Degree::Degree(const DegreePod& val)
: DegreePod(val)
{
}

} // namespace ae::base
// EOF
