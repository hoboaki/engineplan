// 文字コード：UTF-8
#include <ae/base/Angle.hpp>

#include <ae/base/Degree.hpp>
#include <ae/base/Radian.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Angle::Angle()
: mRad(0)
{
}

//------------------------------------------------------------------------------
Angle::Angle(const DegreePod& aDegree)
: mRad(aDegree.toRadian().value)
{
}

//------------------------------------------------------------------------------
Angle::Angle(const RadianPod& aRadian)
: mRad(aRadian.value)
{
}

//------------------------------------------------------------------------------
f32 Angle::rad()const
{
    return mRad;
}

//------------------------------------------------------------------------------
f32 Angle::deg()const
{
    return Radian(mRad).toDegree().value;
}

}} // namespace
// EOF
