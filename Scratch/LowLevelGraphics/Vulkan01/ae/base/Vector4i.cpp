// 文字コード：UTF-8
#include <ae/base/Vector4i.hpp>

#include <ae/base/DivideCheck.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/ScalerTypes.hpp>
#include <ae/base/Vector2i.hpp>
#include <ae/base/Vector3i.hpp>
#include <ae/base/Vector4.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Zero()
{
    Vector4iPod obj = {};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::One()
{
    Vector4iPod obj = {1, 1, 1, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Min()
{
    Vector4iPod obj = {std::numeric_limits< int >::min(), std::numeric_limits< int >::min(), std::numeric_limits< int >::min(), std::numeric_limits< int >::min()};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Max()
{
    Vector4iPod obj = {std::numeric_limits< int >::max(), std::numeric_limits< int >::max(), std::numeric_limits< int >::max(), std::numeric_limits< int >::max()};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::UnitX()
{
    Vector4iPod obj = {1, 0, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::UnitY()
{
    Vector4iPod obj = {0, 1, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::UnitZ()
{
    Vector4iPod obj = {0, 0, 1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::UnitW()
{
    Vector4iPod obj = {0, 0, 0, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::NegUnitX()
{
    Vector4iPod obj = {-1, 0, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::NegUnitY()
{
    Vector4iPod obj = {0, -1, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::NegUnitZ()
{
    Vector4iPod obj = {0, 0, -1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::NegUnitW()
{
    Vector4iPod obj = {0, 0, 0, -1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector4iPod::toXY()const
{
    return Vector2i(x, y);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector4iPod::toXX()const
{
    return Vector2i(x, x);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector4iPod::toYY()const
{
    return Vector2i(y, y);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector4iPod::toZZ()const
{
    return Vector2i(z, z);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector4iPod::toWW()const
{
    return Vector2i(w, w);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector4iPod::toXYZ()const
{
    return Vector3i(x, y, z);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector4iPod::toXXX()const
{
    return Vector3i(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector4iPod::toYYY()const
{
    return Vector3i(y, y, y);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector4iPod::toZZZ()const
{
    return Vector3i(z, z, z);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector4iPod::toWWW()const
{
    return Vector3i(w, w, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::toXYZ0()const
{
    return Vector4i(x, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::toXY0W()const
{
    return Vector4i(x, y, 0, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::toXY00()const
{
    return Vector4i(x, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::toX0ZW()const
{
    return Vector4i(x, 0, z, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::toX0Z0()const
{
    return Vector4i(x, 0, z, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::toX00W()const
{
    return Vector4i(x, 0, 0, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::toX000()const
{
    return Vector4i(x, 0, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::to0YZ0()const
{
    return Vector4i(0, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::to0Y0W()const
{
    return Vector4i(0, y, 0, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::to0Y00()const
{
    return Vector4i(0, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::to00ZW()const
{
    return Vector4i(0, 0, z, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::to00Z0()const
{
    return Vector4i(0, 0, z, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::to000W()const
{
    return Vector4i(0, 0, 0, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::toXXXX()const
{
    return Vector4i(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::toYYYY()const
{
    return Vector4i(y, y, y, y);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::toZZZZ()const
{
    return Vector4i(z, z, z, z);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::toWWWW()const
{
    return Vector4i(w, w, w, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4iPod::toXYZWf()const
{
    return Vector4(f32(x), f32(y), f32(z), f32(w));
}

//------------------------------------------------------------------------------
bool Vector4iPod::equals(const Vector4iPod& aVec)const
{
    return x == aVec.x
        && y == aVec.y
        && z == aVec.z
        && w == aVec.w
        ;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::add(const s32 aVal)const
{
    Vector4i vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::sub(const s32 aVal)const
{
    Vector4i vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::mul(const s32 aVal)const
{
    Vector4i vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::div(const s32 aVal)const
{
    Vector4i vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::add(const Vector4iPod& aVal)const
{
    Vector4i vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::sub(const Vector4iPod& aVal)const
{
    Vector4i vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::mul(const Vector4iPod& aVal)const
{
    Vector4i vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::div(const Vector4iPod& aVal)const
{
    Vector4i vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
void Vector4iPod::addAssign(const s32 aVal)
{
    x += aVal;
    y += aVal;
    z += aVal;
    w += aVal;
}

//------------------------------------------------------------------------------
void Vector4iPod::subAssign(const s32 aVal)
{
    x -= aVal;
    y -= aVal;
    z -= aVal;
    w -= aVal;
}

//------------------------------------------------------------------------------
void Vector4iPod::mulAssign(const s32 aVal)
{
    x *= aVal;
    y *= aVal;
    z *= aVal;
    w *= aVal;
}

//------------------------------------------------------------------------------
void Vector4iPod::divAssign(const s32 aVal)
{
    if (aVal == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    x /= aVal;
    y /= aVal;
    z /= aVal;
    w /= aVal;
}

//------------------------------------------------------------------------------
void Vector4iPod::addAssign(const Vector4iPod& aVal)
{
    x += aVal.x;
    y += aVal.y;
    z += aVal.z;
    w += aVal.w;
}

//------------------------------------------------------------------------------
void Vector4iPod::subAssign(const Vector4iPod& aVal)
{
    x -= aVal.x;
    y -= aVal.y;
    z -= aVal.z;
    w -= aVal.w;
}

//------------------------------------------------------------------------------
void Vector4iPod::mulAssign(const Vector4iPod& aVal)
{
    x *= aVal.x;
    y *= aVal.y;
    z *= aVal.z;
    w *= aVal.w;
}

//------------------------------------------------------------------------------
void Vector4iPod::divAssign(const Vector4iPod& aVal)
{
    AE_BASE_DIV_ASSIGN(x, aVal.x);
    AE_BASE_DIV_ASSIGN(y, aVal.y);
    AE_BASE_DIV_ASSIGN(z, aVal.z);
    AE_BASE_DIV_ASSIGN(w, aVal.w);
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator+=(const s32 aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator-=(const s32 aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator*=(const s32 aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator/=(const s32 aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator+=(const Vector4iPod& aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator-=(const Vector4iPod& aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator*=(const Vector4iPod& aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator/=(const Vector4iPod& aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator+(const s32 aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator-(const s32 aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator*(const s32 aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator/(const s32 aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator+(const Vector4iPod& aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator-(const Vector4iPod& aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator*(const Vector4iPod& aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator/(const Vector4iPod& aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator-()const
{
    return neg();
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::min(const Vector4iPod& aVal)const
{
    return Vector4i(
        Math::Min(x, aVal.x),
        Math::Min(y, aVal.y),
        Math::Min(z, aVal.z),
        Math::Min(w, aVal.w)
        );
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::max(const Vector4iPod& aVal)const
{
    return Vector4i(
        Math::Max(x, aVal.x),
        Math::Max(y, aVal.y),
        Math::Max(z, aVal.z),
        Math::Max(w, aVal.w)
        );
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::clamp(
    const Vector4iPod& aMin,
    const Vector4iPod& aMax
)const
{
    return max(aMin).min(aMax);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::clampPositive()const
{
    return max(Zero());
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::clampNegative()const
{
    return min(Zero());
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::abs()const
{
    return Vector4i(
        Math::AbsS32(x),
        Math::AbsS32(y),
        Math::AbsS32(z),
        Math::AbsS32(2)
        );
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::neg()const
{
    Vector4i vec(*this);
    vec.mulAssign(-1);
    return vec;
}

//------------------------------------------------------------------------------
bool Vector4iPod::isPositive()const
{
    return 0 <= x
        && 0 <= y
        && 0 <= z
        && 0 <= w;
}

//------------------------------------------------------------------------------
bool Vector4iPod::isZero()const
{
    return x == 0 && y == 0 && z == 0 && w == 0;
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Vector4iPod::toShortString()const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s,%s,%s",
        S32(x).toShortString().readPtr(),
        S32(y).toShortString().readPtr(),
        S32(z).toShortString().readPtr(),
        S32(w).toShortString().readPtr()
        );
}

//------------------------------------------------------------------------------
Vector4i::Vector4i()
: Vector4iPod(Zero())
{
}

//------------------------------------------------------------------------------
Vector4i::Vector4i(const Vector4iPod& aVec)
: Vector4iPod(aVec)
{
}

//------------------------------------------------------------------------------
Vector4i::Vector4i(const s32 aV)
{
    x = aV;
    y = aV;
    z = aV;
    w = aV;
}

//------------------------------------------------------------------------------
Vector4i::Vector4i(const Vector2iPod& aXY, const s32 aZ, const s32 aW)
{
    x = aXY.x;
    y = aXY.y;
    z = aZ;
    w = aW;
}

//------------------------------------------------------------------------------
Vector4i::Vector4i(const Vector3iPod& aXYZ, const s32 aW)
{
    x = aXYZ.x;
    y = aXYZ.y;
    z = aXYZ.z;
    w = aW;
}

//------------------------------------------------------------------------------
Vector4i::Vector4i(const s32 aX, const s32 aY, const s32 aZ, const s32 aW)
{
    x = aX;
    y = aY;
    z = aZ;
    w = aW;
}

}} // namespace
// EOF
