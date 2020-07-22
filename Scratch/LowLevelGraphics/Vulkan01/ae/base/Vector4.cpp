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
const Vector2Pod Vector4Pod::toXY()const
{
    return Vector2(x, y);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::toXX()const
{
    return Vector2(x, x);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::toYY()const
{
    return Vector2(y, y);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::toZZ()const
{
    return Vector2(z, z);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::toWW()const
{
    return Vector2(w, w);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::toXYZ()const
{
    return Vector3(x, y, z);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::toXXX()const
{
    return Vector3(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::toYYY()const
{
    return Vector3(y, y, y);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::toZZZ()const
{
    return Vector3(z, z, z);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::toWWW()const
{
    return Vector3(w, w, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toXYZ0()const
{
    return Vector4(x, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toXY0W()const
{
    return Vector4(x, y, 0, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toXY00()const
{
    return Vector4(x, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toX0ZW()const
{
    return Vector4(x, 0, z, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toX0Z0()const
{
    return Vector4(x, 0, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toX00W()const
{
    return Vector4(x, 0, 0, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toX000()const
{
    return Vector4(x, 0, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::to0YZ0()const
{
    return Vector4(0, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::to0Y0W()const
{
    return Vector4(0, y, 0, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::to0Y00()const
{
    return Vector4(0, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::to00ZW()const
{
    return Vector4(0, 0, z, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::to00Z0()const
{
    return Vector4(0, 0, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::to000W()const
{
    return Vector4(0, 0, 0, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toXXXX()const
{
    return Vector4(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toYYYY()const
{
    return Vector4(y, y, y, y);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toZZZZ()const
{
    return Vector4(z, z, z, z);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toWWWW()const
{
    return Vector4(w, w, w, w);
}

//------------------------------------------------------------------------------
bool Vector4Pod::equals(const Vector4Pod& aVec)const
{
    return Math::IsEqualsF32(x, aVec.x)
        && Math::IsEqualsF32(y, aVec.y)
        && Math::IsEqualsF32(z, aVec.z)
        && Math::IsEqualsF32(w, aVec.w);
}

//------------------------------------------------------------------------------
bool Vector4Pod::equalsStrict(const Vector4Pod& aVec)const
{
    return x == aVec.x && y == aVec.y && z == aVec.z && w == aVec.w;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::add(const float aVal)const
{
    Vector4 vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::sub(const float aVal)const
{
    Vector4 vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::mul(const float aVal)const
{
    Vector4 vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::div(const float aVal)const
{
    Vector4 vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::add(const Vector4Pod& aVal)const
{
    Vector4 vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::sub(const Vector4Pod& aVal)const
{
    Vector4 vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::mul(const Vector4Pod& aVal)const
{
    Vector4 vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::div(const Vector4Pod& aVal)const
{
    Vector4 vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
void Vector4Pod::addAssign(const float aVal)
{
    x += aVal;
    y += aVal;
    z += aVal;
    w += aVal;
}

//------------------------------------------------------------------------------
void Vector4Pod::subAssign(const float aVal)
{
    x -= aVal;
    y -= aVal;
    z -= aVal;
    w -= aVal;
}

//------------------------------------------------------------------------------
void Vector4Pod::mulAssign(const float aVal)
{
    x *= aVal;
    y *= aVal;
    z *= aVal;
    w *= aVal;
}

//------------------------------------------------------------------------------
void Vector4Pod::divAssign(const float aVal)
{
    if (aVal == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    mulAssign(1.0f / aVal);
}

//------------------------------------------------------------------------------
void Vector4Pod::addAssign(const Vector4Pod& aVal)
{
    x += aVal.x;
    y += aVal.y;
    z += aVal.z;
    w += aVal.w;
}

//------------------------------------------------------------------------------
void Vector4Pod::subAssign(const Vector4Pod& aVal)
{
    x -= aVal.x;
    y -= aVal.y;
    z -= aVal.z;
    w -= aVal.w;
}

//------------------------------------------------------------------------------
void Vector4Pod::mulAssign(const Vector4Pod& aVal)
{
    x *= aVal.x;
    y *= aVal.y;
    z *= aVal.z;
    w *= aVal.w;
}

//------------------------------------------------------------------------------
void Vector4Pod::divAssign(const Vector4Pod& aVal)
{
    AE_BASE_DIV_ASSIGN(x, aVal.x);
    AE_BASE_DIV_ASSIGN(y, aVal.y);
    AE_BASE_DIV_ASSIGN(z, aVal.z);
    AE_BASE_DIV_ASSIGN(w, aVal.w);
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator+=(const float aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator-=(const float aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator*=(const float aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator/=(const float aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator+=(const Vector4Pod& aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator-=(const Vector4Pod& aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator*=(const Vector4Pod& aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator/=(const Vector4Pod& aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator+(const float aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator-(const float aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator*(const float aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator/(const float aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator+(const Vector4Pod& aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator-(const Vector4Pod& aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator*(const Vector4Pod& aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator/(const Vector4Pod& aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator-()const
{
    return neg();
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::min(const Vector4Pod& aVal)const
{
    return Vector4(
        Math::Min(x, aVal.x),
        Math::Min(y, aVal.y),
        Math::Min(z, aVal.z),
        Math::Min(w, aVal.w)
        );
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::max(const Vector4Pod& aVal)const
{
    return Vector4(
        Math::Max(x, aVal.x),
        Math::Max(y, aVal.y),
        Math::Max(z, aVal.z),
        Math::Max(w, aVal.w)
        );
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::clamp(
    const Vector4Pod& aMin,
    const Vector4Pod& aMax
)const
{
    return max(aMin).min(aMax);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::clampPositive()const
{
    return max(Zero());
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::clampNegative()const
{
    return min(Zero());
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::abs()const
{
    return Vector4(
        Math::AbsF32(x),
        Math::AbsF32(y),
        Math::AbsF32(z),
        Math::AbsF32(w)
        );
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::neg()const
{
    Vector4 vec(*this);
    vec.mulAssign(-1.0f);
    return vec;
}

//------------------------------------------------------------------------------
f32 Vector4Pod::squareLength()const
{
    return x * x + y * y + z * z + w * w;
}

//------------------------------------------------------------------------------
f32 Vector4Pod::length()const
{
    return Math::SqrtF32(squareLength());
}

//------------------------------------------------------------------------------
f32 Vector4Pod::distance(const Vector4Pod& aVal)const
{
    return sub(aVal).length();
}

//------------------------------------------------------------------------------
bool Vector4Pod::isZero()const
{
    return Math::IsZeroF32(length());
}

//------------------------------------------------------------------------------
bool Vector4Pod::isZeroStrict()const
{
    return x == 0 && y == 0 && z == 0 && w == 0;
}

//------------------------------------------------------------------------------
bool Vector4Pod::isUnit()const
{
    return Math::IsEqualsF32(length(), 1.0f);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::unit()const
{
    Vector4 vec(*this);
    vec.unitAssign();
    return vec;
}

//------------------------------------------------------------------------------
void Vector4Pod::unitAssign()
{
    if (isZeroStrict()) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    mulAssign(1.0f / length());
}

//------------------------------------------------------------------------------
f32 Vector4Pod::dot(const Vector4Pod& aVec)const
{
    return x * aVec.x + y * aVec.y + z * aVec.z + w * aVec.w;
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Vector4Pod::toShortString()const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s,%s,%s",
        F32(x).toShortString().readPtr(),
        F32(y).toShortString().readPtr(),
        F32(z).toShortString().readPtr(),
        F32(w).toShortString().readPtr()
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
