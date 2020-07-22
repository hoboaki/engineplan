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
const Vector2Pod Vector2Pod::toX0()const
{
    return Vector2(x, 0);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::toXX()const
{
    return Vector2(x, x);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::toYX()const
{
    return Vector2(y, x);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::toYY()const
{
    return Vector2(y, y);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector2Pod::toXY0()const
{
    return Vector3(x, y, 0);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector2Pod::toXXX()const
{
    return Vector3(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector2Pod::toYYY()const
{
    return Vector3(y, y, y);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector2Pod::toXY00()const
{
    return Vector4(x, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector2Pod::toXXXX()const
{
    return Vector4(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector2Pod::toYYYY()const
{
    return Vector4(y, y, y, y);
}

//------------------------------------------------------------------------------
bool Vector2Pod::equals(const Vector2Pod& aVec)const
{
    return Math::IsEqualsF32(x, aVec.x)
        && Math::IsEqualsF32(y, aVec.y);
}

//------------------------------------------------------------------------------
bool Vector2Pod::equalsStrict(const Vector2Pod& aVec)const
{
    return x == aVec.x && y == aVec.y;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::add(const float aVal)const
{
    Vector2 vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::sub(const float aVal)const
{
    Vector2 vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::mul(const float aVal)const
{
    Vector2 vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::div(const float aVal)const
{
    Vector2 vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::add(const Vector2Pod& aVal)const
{
    Vector2 vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::sub(const Vector2Pod& aVal)const
{
    Vector2 vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::mul(const Vector2Pod& aVal)const
{
    Vector2 vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::div(const Vector2Pod& aVal)const
{
    Vector2 vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
void Vector2Pod::addAssign(const float aVal)
{
    x += aVal;
    y += aVal;
}

//------------------------------------------------------------------------------
void Vector2Pod::subAssign(const float aVal)
{
    x -= aVal;
    y -= aVal;
}

//------------------------------------------------------------------------------
void Vector2Pod::mulAssign(const float aVal)
{
    x *= aVal;
    y *= aVal;
}

//------------------------------------------------------------------------------
void Vector2Pod::divAssign(const float aVal)
{
    if (aVal == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    mulAssign(1.0f / aVal);
}

//------------------------------------------------------------------------------
void Vector2Pod::addAssign(const Vector2Pod& aVal)
{
    x += aVal.x;
    y += aVal.y;
}

//------------------------------------------------------------------------------
void Vector2Pod::subAssign(const Vector2Pod& aVal)
{
    x -= aVal.x;
    y -= aVal.y;
}

//------------------------------------------------------------------------------
void Vector2Pod::mulAssign(const Vector2Pod& aVal)
{
    x *= aVal.x;
    y *= aVal.y;
}

//------------------------------------------------------------------------------
void Vector2Pod::divAssign(const Vector2Pod& aVal)
{
    AE_BASE_DIV_ASSIGN(x, aVal.x);
    AE_BASE_DIV_ASSIGN(y, aVal.y);
}

//------------------------------------------------------------------------------
Vector2Pod& Vector2Pod::operator+=(const float aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2Pod& Vector2Pod::operator-=(const float aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2Pod& Vector2Pod::operator*=(const float aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2Pod& Vector2Pod::operator/=(const float aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2Pod& Vector2Pod::operator+=(const Vector2Pod& aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2Pod& Vector2Pod::operator-=(const Vector2Pod& aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2Pod& Vector2Pod::operator*=(const Vector2Pod& aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2Pod& Vector2Pod::operator/=(const Vector2Pod& aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator+(const float aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator-(const float aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator*(const float aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator/(const float aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator+(const Vector2Pod& aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator-(const Vector2Pod& aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator*(const Vector2Pod& aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator/(const Vector2Pod& aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::operator-()const
{
    return neg();
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::min(const Vector2Pod& aVal)const
{
    return Vector2(
        Math::Min(x, aVal.x),
        Math::Min(y, aVal.y)
        );
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::max(const Vector2Pod& aVal)const
{
    return Vector2(
        Math::Max(x, aVal.x),
        Math::Max(y, aVal.y)
        );
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::clamp(
    const Vector2Pod& aMin,
    const Vector2Pod& aMax
)const
{
    return max(aMin).min(aMax);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::clampPositive()const
{
    return max(Zero());
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::clampNegative()const
{
    return min(Zero());
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::abs()const
{
    return Vector2(
        Math::AbsF32(x),
        Math::AbsF32(y)
        );
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::neg()const
{
    Vector2 vec(*this);
    vec.mulAssign(-1.0f);
    return vec;
}

//------------------------------------------------------------------------------
f32 Vector2Pod::squareLength()const
{
    return x * x + y * y;
}

//------------------------------------------------------------------------------
f32 Vector2Pod::length()const
{
    return Math::SqrtF32(squareLength());
}

//------------------------------------------------------------------------------
f32 Vector2Pod::distance(const Vector2Pod& aVal)const
{
    return sub(aVal).length();
}

//------------------------------------------------------------------------------
bool Vector2Pod::isZero()const
{
    return Math::IsZeroF32(length());
}

//------------------------------------------------------------------------------
bool Vector2Pod::isZeroStrict()const
{
    return x == 0 && y == 0;
}

//------------------------------------------------------------------------------
bool Vector2Pod::isUnit()const
{
    return Math::IsEqualsF32(length(), 1.0f);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2Pod::unit()const
{
    Vector2 vec(*this);
    vec.unitAssign();
    return vec;
}

//------------------------------------------------------------------------------
void Vector2Pod::unitAssign()
{
    if (isZeroStrict()) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    mulAssign(1.0f / length());
}

//------------------------------------------------------------------------------
f32 Vector2Pod::dot(const Vector2Pod& aVec)const
{
    return x * aVec.x + y * aVec.y;
}

//------------------------------------------------------------------------------
f32 Vector2Pod::cross(const Vector2Pod& aVec)const
{
    return x * aVec.y - aVec.y * x;
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Vector2Pod::toShortString()const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s",
        F32(x).toShortString().readPtr(),
        F32(y).toShortString().readPtr()
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
