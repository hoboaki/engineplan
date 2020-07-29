// 文字コード：UTF-8
#include <ae/base/Vector2.hpp>

#include <ae/base/DivideCheck.hpp>
#include <ae/base/Infinity.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/ScalerTypes.hpp>
#include <ae/base/Vector3.hpp>
#include <ae/base/Vector4.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Zero()
{
    Vector2Pod obj = {};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::One()
{
    Vector2Pod obj = {1, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Min()
{
    Vector2Pod obj = {-AE_BASE_INFINITY, -AE_BASE_INFINITY};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Max()
{
    Vector2Pod obj = {AE_BASE_INFINITY, AE_BASE_INFINITY};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::UnitX()
{
    Vector2Pod obj = {1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::UnitY()
{
    Vector2Pod obj = {0, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::NegUnitX()
{
    Vector2Pod obj = {-1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::NegUnitY()
{
    Vector2Pod obj = {0, -1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::ToX0()const
{
    return Vector2(x, 0);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::ToXX()const
{
    return Vector2(x, x);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::ToYX()const
{
    return Vector2(y, x);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::ToYY()const
{
    return Vector2(y, y);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector2Pod::ToXY0()const
{
    return Vector3(x, y, 0);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector2Pod::ToXXX()const
{
    return Vector3(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector2Pod::ToYYY()const
{
    return Vector3(y, y, y);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector2Pod::ToXY00()const
{
    return Vector4(x, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector2Pod::ToXXXX()const
{
    return Vector4(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector2Pod::ToYYYY()const
{
    return Vector4(y, y, y, y);
}

//------------------------------------------------------------------------------
bool Vector2Pod::Equals(const Vector2Pod& aVec)const
{
    return Math::IsEqualsF32(x, aVec.x)
        && Math::IsEqualsF32(y, aVec.y);
}

//------------------------------------------------------------------------------
bool Vector2Pod::EqualsStrict(const Vector2Pod& aVec)const
{
    return x == aVec.x && y == aVec.y;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Add(const float aVal)const
{
    Vector2 vec(*this);
    vec.AddAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Sub(const float aVal)const
{
    Vector2 vec(*this);
    vec.SubAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Mul(const float aVal)const
{
    Vector2 vec(*this);
    vec.MulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Div(const float aVal)const
{
    Vector2 vec(*this);
    vec.DivAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Add(const Vector2Pod& aVal)const
{
    Vector2 vec(*this);
    vec.AddAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Sub(const Vector2Pod& aVal)const
{
    Vector2 vec(*this);
    vec.SubAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Mul(const Vector2Pod& aVal)const
{
    Vector2 vec(*this);
    vec.MulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Div(const Vector2Pod& aVal)const
{
    Vector2 vec(*this);
    vec.DivAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
void Vector2Pod::AddAssign(const float aVal)
{
    x += aVal;
    y += aVal;
}

//------------------------------------------------------------------------------
void Vector2Pod::SubAssign(const float aVal)
{
    x -= aVal;
    y -= aVal;
}

//------------------------------------------------------------------------------
void Vector2Pod::MulAssign(const float aVal)
{
    x *= aVal;
    y *= aVal;
}

//------------------------------------------------------------------------------
void Vector2Pod::DivAssign(const float aVal)
{
    if (aVal == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    MulAssign(1.0f / aVal);
}

//------------------------------------------------------------------------------
void Vector2Pod::AddAssign(const Vector2Pod& aVal)
{
    x += aVal.x;
    y += aVal.y;
}

//------------------------------------------------------------------------------
void Vector2Pod::SubAssign(const Vector2Pod& aVal)
{
    x -= aVal.x;
    y -= aVal.y;
}

//------------------------------------------------------------------------------
void Vector2Pod::MulAssign(const Vector2Pod& aVal)
{
    x *= aVal.x;
    y *= aVal.y;
}

//------------------------------------------------------------------------------
void Vector2Pod::DivAssign(const Vector2Pod& aVal)
{
    AE_BASE_DIV_ASSIGN(x, aVal.x);
    AE_BASE_DIV_ASSIGN(y, aVal.y);
}

//------------------------------------------------------------------------------
Vector2Pod& Vector2Pod::operator+=(const float aVal)
{
    AddAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2Pod& Vector2Pod::operator-=(const float aVal)
{
    SubAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2Pod& Vector2Pod::operator*=(const float aVal)
{
    MulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2Pod& Vector2Pod::operator/=(const float aVal)
{
    DivAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2Pod& Vector2Pod::operator+=(const Vector2Pod& aVal)
{
    AddAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2Pod& Vector2Pod::operator-=(const Vector2Pod& aVal)
{
    SubAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2Pod& Vector2Pod::operator*=(const Vector2Pod& aVal)
{
    MulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2Pod& Vector2Pod::operator/=(const Vector2Pod& aVal)
{
    DivAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator+(const float aVal)const
{
    return Add(aVal);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator-(const float aVal)const
{
    return Sub(aVal);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator*(const float aVal)const
{
    return Mul(aVal);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator/(const float aVal)const
{
    return Div(aVal);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator+(const Vector2Pod& aVal)const
{
    return Add(aVal);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator-(const Vector2Pod& aVal)const
{
    return Sub(aVal);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator*(const Vector2Pod& aVal)const
{
    return Mul(aVal);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator/(const Vector2Pod& aVal)const
{
    return Div(aVal);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator-()const
{
    return Neg();
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Min(const Vector2Pod& aVal)const
{
    return Vector2(
        Math::Min(x, aVal.x),
        Math::Min(y, aVal.y)
        );
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Max(const Vector2Pod& aVal)const
{
    return Vector2(
        Math::Max(x, aVal.x),
        Math::Max(y, aVal.y)
        );
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Clamp(
    const Vector2Pod& aMin,
    const Vector2Pod& aMax
)const
{
    return Max(aMin).Min(aMax);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::ClampPositive()const
{
    return Max(Zero());
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::ClampNegative()const
{
    return Min(Zero());
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Abs()const
{
    return Vector2(
        Math::AbsF32(x),
        Math::AbsF32(y)
        );
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Neg()const
{
    Vector2 vec(*this);
    vec.MulAssign(-1.0f);
    return vec;
}

//------------------------------------------------------------------------------
f32 Vector2Pod::SquareLength()const
{
    return x * x + y * y;
}

//------------------------------------------------------------------------------
f32 Vector2Pod::Length()const
{
    return Math::SqrtF32(SquareLength());
}

//------------------------------------------------------------------------------
f32 Vector2Pod::Distance(const Vector2Pod& aVal)const
{
    return Sub(aVal).Length();
}

//------------------------------------------------------------------------------
bool Vector2Pod::IsZero()const
{
    return Math::IsZeroF32(Length());
}

//------------------------------------------------------------------------------
bool Vector2Pod::IsZeroStrict()const
{
    return x == 0 && y == 0;
}

//------------------------------------------------------------------------------
bool Vector2Pod::IsUnit()const
{
    return Math::IsEqualsF32(Length(), 1.0f);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::Unit()const
{
    Vector2 vec(*this);
    vec.UnitAssign();
    return vec;
}

//------------------------------------------------------------------------------
void Vector2Pod::UnitAssign()
{
    if (IsZeroStrict()) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    MulAssign(1.0f / Length());
}

//------------------------------------------------------------------------------
f32 Vector2Pod::Dot(const Vector2Pod& aVec)const
{
    return x * aVec.x + y * aVec.y;
}

//------------------------------------------------------------------------------
f32 Vector2Pod::Cross(const Vector2Pod& aVec)const
{
    return x * aVec.y - aVec.y * x;
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Vector2Pod::ToShortString()const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s",
        F32(x).ToShortString().ReadPtr(),
        F32(y).ToShortString().ReadPtr()
        );
}

//------------------------------------------------------------------------------
Vector2::Vector2()
: Vector2Pod(Zero())
{
}

//------------------------------------------------------------------------------
Vector2::Vector2(const Vector2Pod& aVec)
: Vector2Pod(aVec)
{
}

//------------------------------------------------------------------------------
Vector2::Vector2(const float aV)
{
    x = aV;
    y = aV;
}

//------------------------------------------------------------------------------
Vector2::Vector2(const float aX, const float aY)
{
    x = aX;
    y = aY;
}

}} // namespace
// EOF
