// 文字コード：UTF-8
#include <ae/base/Vector3.hpp>

#include <ae/base/DivideCheck.hpp>
#include <ae/base/Infinity.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/ScalerTypes.hpp>
#include <ae/base/Vector2.hpp>
#include <ae/base/Vector4.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Zero()
{
    Vector3Pod obj = {};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::One()
{
    Vector3Pod obj = {1, 1, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Min()
{
    Vector3Pod obj = {-AE_BASE_INFINITY, -AE_BASE_INFINITY, -AE_BASE_INFINITY};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Max()
{
    Vector3Pod obj = {AE_BASE_INFINITY, AE_BASE_INFINITY, AE_BASE_INFINITY};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::UnitX()
{
    Vector3Pod obj = {1, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::UnitY()
{
    Vector3Pod obj = {0, 1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::UnitZ()
{
    Vector3Pod obj = {0, 0, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::NegUnitX()
{
    Vector3Pod obj = {-1, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::NegUnitY()
{
    Vector3Pod obj = {0, -1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::NegUnitZ()
{
    Vector3Pod obj = {0, 0, -1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector3Pod::toXY()const
{
    return Vector2(x, y);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector3Pod::toXX()const
{
    return Vector2(x, x);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector3Pod::toYY()const
{
    return Vector2(y, y);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector3Pod::toZZ()const
{
    return Vector2(z, z);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::toX00()const
{
    return Vector3(x, 0, 0);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::toXY0()const
{
    return Vector3(x, y, 0);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::to0Y0()const
{
    return Vector3(0, y, 0);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::to0YZ()const
{
    return Vector3(0, y, z);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::to00Z()const
{
    return Vector3(0, 0, z);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::toXXX()const
{
    return Vector3(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::toYYY()const
{
    return Vector3(y, y, y);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::toZZZ()const
{
    return Vector3(z, z, z);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector3Pod::toXYZ0()const
{
    return Vector4(x, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector3Pod::toXXXX()const
{
    return Vector4(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector3Pod::toYYYY()const
{
    return Vector4(y, y, y, y);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector3Pod::toZZZZ()const
{
    return Vector4(z, z, z, z);
}

//------------------------------------------------------------------------------
bool Vector3Pod::equals(const Vector3Pod& aVec)const
{
    return Math::IsEqualsF32(x, aVec.x)
        && Math::IsEqualsF32(y, aVec.y)
        && Math::IsEqualsF32(z, aVec.z);
}

//------------------------------------------------------------------------------
bool Vector3Pod::equalsStrict(const Vector3Pod& aVec)const
{
    return x == aVec.x && y == aVec.y && z == aVec.z;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::add(const float aVal)const
{
    Vector3 vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::sub(const float aVal)const
{
    Vector3 vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::mul(const float aVal)const
{
    Vector3 vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::div(const float aVal)const
{
    Vector3 vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::add(const Vector3Pod& aVal)const
{
    Vector3 vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::sub(const Vector3Pod& aVal)const
{
    Vector3 vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::mul(const Vector3Pod& aVal)const
{
    Vector3 vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::div(const Vector3Pod& aVal)const
{
    Vector3 vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
void Vector3Pod::addAssign(const float aVal)
{
    x += aVal;
    y += aVal;
    z += aVal;
}

//------------------------------------------------------------------------------
void Vector3Pod::subAssign(const float aVal)
{
    x -= aVal;
    y -= aVal;
    z -= aVal;
}

//------------------------------------------------------------------------------
void Vector3Pod::mulAssign(const float aVal)
{
    x *= aVal;
    y *= aVal;
    z *= aVal;
}

//------------------------------------------------------------------------------
void Vector3Pod::divAssign(const float aVal)
{
    if (aVal == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    mulAssign(1.0f / aVal);
}

//------------------------------------------------------------------------------
void Vector3Pod::addAssign(const Vector3Pod& aVal)
{
    x += aVal.x;
    y += aVal.y;
    z += aVal.z;
}

//------------------------------------------------------------------------------
void Vector3Pod::subAssign(const Vector3Pod& aVal)
{
    x -= aVal.x;
    y -= aVal.y;
    z -= aVal.z;
}

//------------------------------------------------------------------------------
void Vector3Pod::mulAssign(const Vector3Pod& aVal)
{
    x *= aVal.x;
    y *= aVal.y;
    z *= aVal.z;
}

//------------------------------------------------------------------------------
void Vector3Pod::divAssign(const Vector3Pod& aVal)
{
    AE_BASE_DIV_ASSIGN(x, aVal.x);
    AE_BASE_DIV_ASSIGN(y, aVal.y);
    AE_BASE_DIV_ASSIGN(z, aVal.z);
}

//------------------------------------------------------------------------------
Vector3Pod& Vector3Pod::operator+=(const float aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3Pod& Vector3Pod::operator-=(const float aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3Pod& Vector3Pod::operator*=(const float aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3Pod& Vector3Pod::operator/=(const float aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3Pod& Vector3Pod::operator+=(const Vector3Pod& aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3Pod& Vector3Pod::operator-=(const Vector3Pod& aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3Pod& Vector3Pod::operator*=(const Vector3Pod& aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3Pod& Vector3Pod::operator/=(const Vector3Pod& aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator+(const float aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator-(const float aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator*(const float aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator/(const float aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator+(const Vector3Pod& aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator-(const Vector3Pod& aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator*(const Vector3Pod& aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator/(const Vector3Pod& aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator-()const
{
    return neg();
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::min(const Vector3Pod& aVal)const
{
    return Vector3(
        Math::Min(x, aVal.x),
        Math::Min(y, aVal.y),
        Math::Min(z, aVal.z)
        );
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::max(const Vector3Pod& aVal)const
{
    return Vector3(
        Math::Max(x, aVal.x),
        Math::Max(y, aVal.y),
        Math::Max(z, aVal.z)
        );
}


//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::clamp(
    const Vector3Pod& aMin,
    const Vector3Pod& aMax
)const
{
    return max(aMin).min(aMax);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::clampPositive()const
{
    return max(Zero());
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::clampNegative()const
{
    return min(Zero());
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::abs()const
{
    return Vector3(
        Math::AbsF32(x),
        Math::AbsF32(y),
        Math::AbsF32(z)
        );
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::neg()const
{
    Vector3 vec(*this);
    vec.mulAssign(-1.0f);
    return vec;
}

//------------------------------------------------------------------------------
f32 Vector3Pod::squareLength()const
{
    return x * x + y * y + z * z;
}

//------------------------------------------------------------------------------
f32 Vector3Pod::length()const
{
    return Math::SqrtF32(squareLength());
}

//------------------------------------------------------------------------------
f32 Vector3Pod::distance(const Vector3Pod& aVal)const
{
    return sub(aVal).length();
}

//------------------------------------------------------------------------------
bool Vector3Pod::isZero()const
{
    return Math::IsZeroF32(length());
}

//------------------------------------------------------------------------------
bool Vector3Pod::isZeroStrict()const
{
    return x == 0 && y == 0 && z == 0;
}

//------------------------------------------------------------------------------
bool Vector3Pod::isUnit()const
{
    return Math::IsEqualsF32(length(), 1.0f);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::unit()const
{
    Vector3 vec(*this);
    vec.unitAssign();
    return vec;
}

//------------------------------------------------------------------------------
void Vector3Pod::unitAssign()
{
    if (isZeroStrict()) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    mulAssign(1.0f / length());
}

//------------------------------------------------------------------------------
f32 Vector3Pod::dot(const Vector3Pod& aVec)const
{
    return x * aVec.x + y * aVec.y + z * aVec.z;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::cross(const Vector3Pod& aVec)const
{
    return Vector3(
        y * aVec.z - z * aVec.y,
        z * aVec.x - x * aVec.z,
        x * aVec.y - y * aVec.x
        );
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Vector3Pod::toShortString()const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s,%s",
        F32(x).toShortString().readPtr(),
        F32(y).toShortString().readPtr(),
        F32(z).toShortString().readPtr()
        );
}

//------------------------------------------------------------------------------
Vector3::Vector3()
: Vector3Pod(Zero())
{
}

//------------------------------------------------------------------------------
Vector3::Vector3(const Vector3Pod& aVec)
: Vector3Pod(aVec)
{
}

//------------------------------------------------------------------------------
Vector3::Vector3(const float aV)
{
    x = aV;
    y = aV;
    z = aV;
}

//------------------------------------------------------------------------------
Vector3::Vector3(const Vector2Pod& aXY, const float aZ)
{
    x = aXY.x;
    y = aXY.y;
    z = aZ;
}

//------------------------------------------------------------------------------
Vector3::Vector3(const float aX, const float aY, const float aZ)
{
    x = aX;
    y = aY;
    z = aZ;
}

}} // namespace
// EOF
