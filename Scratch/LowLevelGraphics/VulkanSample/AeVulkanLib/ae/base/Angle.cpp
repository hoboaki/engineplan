// 文字コード：UTF-8
#include <ae/base/Angle.hpp>

// includes
#include <ae/base/Degree.hpp>
#include <ae/base/Radian.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
Angle::Angle()
: rad_(0)
{
}

//------------------------------------------------------------------------------
Angle::Angle(const DegreePod& degree)
: rad_(degree.ToRadian().value)
{
}

//------------------------------------------------------------------------------
Angle::Angle(const RadianPod& radian)
: rad_(radian.value)
{
}

//------------------------------------------------------------------------------
f32 Angle::Rad() const
{
    return rad_;
}

//------------------------------------------------------------------------------
f32 Angle::Deg() const
{
    return Radian(rad_).ToDegree().value;
}

} // namespace ae::base
// EOF
