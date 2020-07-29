// 文字コード：UTF-8
#include <ae/base/Angle.hpp>

#include <ae/base/Degree.hpp>
#include <ae/base/Radian.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Angle::Angle()
: rad_(0)
{
}

//------------------------------------------------------------------------------
Angle::Angle(const DegreePod& aDegree)
: rad_(aDegree.toRadian().value)
{
}

//------------------------------------------------------------------------------
Angle::Angle(const RadianPod& aRadian)
: rad_(aRadian.value)
{
}

//------------------------------------------------------------------------------
f32 Angle::rad()const
{
    return rad_;
}

//------------------------------------------------------------------------------
f32 Angle::deg()const
{
    return Radian(rad_).toDegree().value;
}

}} // namespace
// EOF
