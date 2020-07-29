// 文字コード：UTF-8
#include <ae/base/Vector4.hpp>

#include <ae/base/DivideCheck.hpp>
#include <ae/base/Infinity.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/ScalerTypes.hpp>
#include <ae/base/Vector2.hpp>
#include <ae/base/Vector3.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Zero()
{
    Vector4Pod obj = {};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::One()
{
    Vector4Pod obj = {1, 1, 1, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Min()
{
    Vector4Pod obj = {-AE_BASE_INFINITY, -AE_BASE_INFINITY, -AE_BASE_INFINITY, -AE_BASE_INFINITY};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Max()
{
    Vector4Pod obj = {AE_BASE_INFINITY, AE_BASE_INFINITY, AE_BASE_INFINITY, AE_BASE_INFINITY};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::UnitX()
{
    Vector4Pod obj = {1, 0, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::UnitY()
{
    Vector4Pod obj = {0, 1, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::UnitZ()
{
    Vector4Pod obj = {0, 0, 1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::UnitW()
{
    Vector4Pod obj = {0, 0, 0, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::NegUnitX()
{
    Vector4Pod obj = {-1, 0, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::NegUnitY()
{
    Vector4Pod obj = {0, -1, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::NegUnitZ()
{
    Vector4Pod obj = {0, 0, -1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::NegUnitW()
{
    Vector4Pod obj = {0, 0, 0, -1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::ToXY()const
{
    return Vector2(x, y);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::ToXX()const
{
    return Vector2(x, x);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::ToYY()const
{
    return Vector2(y, y);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::ToZZ()const
{
    return Vector2(z, z);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::ToWW()const
{
    return Vector2(w, w);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::ToXYZ()const
{
    return Vector3(x, y, z);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::ToXXX()const
{
    return Vector3(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::ToYYY()const
{
    return Vector3(y, y, y);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::ToZZZ()const
{
    return Vector3(z, z, z);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::ToWWW()const
{
    return Vector3(w, w, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToXYZ0()const
{
    return Vector4(x, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToXY0W()const
{
    return Vector4(x, y, 0, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToXY00()const
{
    return Vector4(x, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToX0ZW()const
{
    return Vector4(x, 0, z, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToX0Z0()const
{
    return Vector4(x, 0, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToX00W()const
{
    return Vector4(x, 0, 0, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToX000()const
{
    return Vector4(x, 0, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::To0YZ0()const
{
    return Vector4(0, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::To0Y0W()const
{
    return Vector4(0, y, 0, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::To0Y00()const
{
    return Vector4(0, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::To00ZW()const
{
    return Vector4(0, 0, z, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::To00Z0()const
{
    return Vector4(0, 0, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::To000W()const
{
    return Vector4(0, 0, 0, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToXXXX()const
{
    return Vector4(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToYYYY()const
{
    return Vector4(y, y, y, y);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToZZZZ()const
{
    return Vector4(z, z, z, z);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToWWWW()const
{
    return Vector4(w, w, w, w);
}

//------------------------------------------------------------------------------
bool Vector4Pod::Equals(const Vector4Pod& aVec)const
{
    return Math::IsEqualsF32(x, aVec.x)
        && Math::IsEqualsF32(y, aVec.y)
        && Math::IsEqualsF32(z, aVec.z)
        && Math::IsEqualsF32(w, aVec.w);
}

//------------------------------------------------------------------------------
bool Vector4Pod::EqualsStrict(const Vector4Pod& aVec)const
{
    return x == aVec.x && y == aVec.y && z == aVec.z && w == aVec.w;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Add(const float aVal)const
{
    Vector4 vec(*this);
    vec.AddAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Sub(const float aVal)const
{
    Vector4 vec(*this);
    vec.SubAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Mul(const float aVal)const
{
    Vector4 vec(*this);
    vec.MulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Div(const float aVal)const
{
    Vector4 vec(*this);
    vec.DivAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Add(const Vector4Pod& aVal)const
{
    Vector4 vec(*this);
    vec.AddAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Sub(const Vector4Pod& aVal)const
{
    Vector4 vec(*this);
    vec.SubAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Mul(const Vector4Pod& aVal)const
{
    Vector4 vec(*this);
    vec.MulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Div(const Vector4Pod& aVal)const
{
    Vector4 vec(*this);
    vec.DivAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
void Vector4Pod::AddAssign(const float aVal)
{
    x += aVal;
    y += aVal;
    z += aVal;
    w += aVal;
}

//------------------------------------------------------------------------------
void Vector4Pod::SubAssign(const float aVal)
{
    x -= aVal;
    y -= aVal;
    z -= aVal;
    w -= aVal;
}

//------------------------------------------------------------------------------
void Vector4Pod::MulAssign(const float aVal)
{
    x *= aVal;
    y *= aVal;
    z *= aVal;
    w *= aVal;
}

//------------------------------------------------------------------------------
void Vector4Pod::DivAssign(const float aVal)
{
    if (aVal == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    MulAssign(1.0f / aVal);
}

//------------------------------------------------------------------------------
void Vector4Pod::AddAssign(const Vector4Pod& aVal)
{
    x += aVal.x;
    y += aVal.y;
    z += aVal.z;
    w += aVal.w;
}

//------------------------------------------------------------------------------
void Vector4Pod::SubAssign(const Vector4Pod& aVal)
{
    x -= aVal.x;
    y -= aVal.y;
    z -= aVal.z;
    w -= aVal.w;
}

//------------------------------------------------------------------------------
void Vector4Pod::MulAssign(const Vector4Pod& aVal)
{
    x *= aVal.x;
    y *= aVal.y;
    z *= aVal.z;
    w *= aVal.w;
}

//------------------------------------------------------------------------------
void Vector4Pod::DivAssign(const Vector4Pod& aVal)
{
    AE_BASE_DIV_ASSIGN(x, aVal.x);
    AE_BASE_DIV_ASSIGN(y, aVal.y);
    AE_BASE_DIV_ASSIGN(z, aVal.z);
    AE_BASE_DIV_ASSIGN(w, aVal.w);
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator+=(const float aVal)
{
    AddAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator-=(const float aVal)
{
    SubAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator*=(const float aVal)
{
    MulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator/=(const float aVal)
{
    DivAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator+=(const Vector4Pod& aVal)
{
    AddAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator-=(const Vector4Pod& aVal)
{
    SubAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator*=(const Vector4Pod& aVal)
{
    MulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator/=(const Vector4Pod& aVal)
{
    DivAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator+(const float aVal)const
{
    return Add(aVal);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator-(const float aVal)const
{
    return Sub(aVal);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator*(const float aVal)const
{
    return Mul(aVal);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator/(const float aVal)const
{
    return Div(aVal);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator+(const Vector4Pod& aVal)const
{
    return Add(aVal);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator-(const Vector4Pod& aVal)const
{
    return Sub(aVal);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator*(const Vector4Pod& aVal)const
{
    return Mul(aVal);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator/(const Vector4Pod& aVal)const
{
    return Div(aVal);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator-()const
{
    return Neg();
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Min(const Vector4Pod& aVal)const
{
    return Vector4(
        Math::Min(x, aVal.x),
        Math::Min(y, aVal.y),
        Math::Min(z, aVal.z),
        Math::Min(w, aVal.w)
        );
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Max(const Vector4Pod& aVal)const
{
    return Vector4(
        Math::Max(x, aVal.x),
        Math::Max(y, aVal.y),
        Math::Max(z, aVal.z),
        Math::Max(w, aVal.w)
        );
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Clamp(
    const Vector4Pod& aMin,
    const Vector4Pod& aMax
)const
{
    return Max(aMin).Min(aMax);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ClampPositive()const
{
    return Max(Zero());
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ClampNegative()const
{
    return Min(Zero());
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Abs()const
{
    return Vector4(
        Math::AbsF32(x),
        Math::AbsF32(y),
        Math::AbsF32(z),
        Math::AbsF32(w)
        );
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Neg()const
{
    Vector4 vec(*this);
    vec.MulAssign(-1.0f);
    return vec;
}

//------------------------------------------------------------------------------
f32 Vector4Pod::SquareLength()const
{
    return x * x + y * y + z * z + w * w;
}

//------------------------------------------------------------------------------
f32 Vector4Pod::Length()const
{
    return Math::SqrtF32(SquareLength());
}

//------------------------------------------------------------------------------
f32 Vector4Pod::Distance(const Vector4Pod& aVal)const
{
    return Sub(aVal).Length();
}

//------------------------------------------------------------------------------
bool Vector4Pod::IsZero()const
{
    return Math::IsZeroF32(Length());
}

//------------------------------------------------------------------------------
bool Vector4Pod::IsZeroStrict()const
{
    return x == 0 && y == 0 && z == 0 && w == 0;
}

//------------------------------------------------------------------------------
bool Vector4Pod::IsUnit()const
{
    return Math::IsEqualsF32(Length(), 1.0f);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Unit()const
{
    Vector4 vec(*this);
    vec.UnitAssign();
    return vec;
}

//------------------------------------------------------------------------------
void Vector4Pod::UnitAssign()
{
    if (IsZeroStrict()) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    MulAssign(1.0f / Length());
}

//------------------------------------------------------------------------------
f32 Vector4Pod::Dot(const Vector4Pod& aVec)const
{
    return x * aVec.x + y * aVec.y + z * aVec.z + w * aVec.w;
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Vector4Pod::ToShortString()const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s,%s,%s",
        F32(x).ToShortString().ReadPtr(),
        F32(y).ToShortString().ReadPtr(),
        F32(z).ToShortString().ReadPtr(),
        F32(w).ToShortString().ReadPtr()
        );
}

//------------------------------------------------------------------------------
Vector4::Vector4()
: Vector4Pod(Zero())
{
}

//------------------------------------------------------------------------------
Vector4::Vector4(const Vector4Pod& aVec)
: Vector4Pod(aVec)
{
}

//------------------------------------------------------------------------------
Vector4::Vector4(const float aV)
{
    x = aV;
    y = aV;
    z = aV;
    w = aV;
}

//------------------------------------------------------------------------------
Vector4::Vector4(const Vector2Pod& aXY, const float aZ, const float aW)
{
    x = aXY.x;
    y = aXY.y;
    z = aZ;
    w = aW;
}

//------------------------------------------------------------------------------
Vector4::Vector4(const Vector3Pod& aXYZ, const float aW)
{
    x = aXYZ.x;
    y = aXYZ.y;
    z = aXYZ.z;
    w = aW;
}

//------------------------------------------------------------------------------
Vector4::Vector4(const float aX, const float aY, const float aZ, const float aW)
{
    x = aX;
    y = aY;
    z = aZ;
    w = aW;
}

}} // namespace
// EOF
