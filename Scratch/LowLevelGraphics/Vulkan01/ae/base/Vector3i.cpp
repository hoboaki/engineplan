// 文字コード：UTF-8
#include <ae/base/Vector3i.hpp>

#include <ae/base/DivideCheck.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/ScalerTypes.hpp>
#include <ae/base/Vector2i.hpp>
#include <ae/base/Vector3.hpp>
#include <ae/base/Vector4i.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Zero()
{
    Vector3iPod obj = {};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::One()
{
    Vector3iPod obj = {1, 1, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Min()
{
    Vector3iPod obj = {std::numeric_limits< int >::min(), std::numeric_limits< int >::min(), std::numeric_limits< int >::min()};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Max()
{
    Vector3iPod obj = {std::numeric_limits< int >::max(), std::numeric_limits< int >::max(), std::numeric_limits< int >::max()};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::UnitX()
{
    Vector3iPod obj = {1, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::UnitY()
{
    Vector3iPod obj = {0, 1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::UnitZ()
{
    Vector3iPod obj = {0, 0, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::NegUnitX()
{
    Vector3iPod obj = {-1, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::NegUnitY()
{
    Vector3iPod obj = {0, -1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::NegUnitZ()
{
    Vector3iPod obj = {0, 0, -1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector3iPod::toXY()const
{
    return Vector2i(x, y);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector3iPod::toXX()const
{
    return Vector2i(x, x);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector3iPod::toYY()const
{
    return Vector2i(y, y);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector3iPod::toZZ()const
{
    return Vector2i(z, z);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::toX00()const
{
    return Vector3i(x, 0, 0);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::toXY0()const
{
    return Vector3i(x, y, 0);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::to0Y0()const
{
    return Vector3i(0, y, 0);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::to0YZ()const
{
    return Vector3i(0, y, z);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::to00Z()const
{
    return Vector3i(0, 0, z);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::toXXX()const
{
    return Vector3i(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::toYYY()const
{
    return Vector3i(y, y, y);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::toZZZ()const
{
    return Vector3i(z, z, z);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector3iPod::toXYZ0()const
{
    return Vector4i(x, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector3iPod::toXXXX()const
{
    return Vector4i(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector3iPod::toYYYY()const
{
    return Vector4i(y, y, y, y);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector3iPod::toZZZZ()const
{
    return Vector4i(z, z, z, z);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3iPod::toXYZf()const
{
    return Vector3(f32(x), f32(y), f32(z));
}

//------------------------------------------------------------------------------
bool Vector3iPod::equals(const Vector3iPod& aVec)const
{
    return x == aVec.x
        && y == aVec.y
        && z == aVec.z
        ;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::add(const s32 aVal)const
{
    Vector3i vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::sub(const s32 aVal)const
{
    Vector3i vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::mul(const s32 aVal)const
{
    Vector3i vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::div(const s32 aVal)const
{
    Vector3i vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::add(const Vector3iPod& aVal)const
{
    Vector3i vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::sub(const Vector3iPod& aVal)const
{
    Vector3i vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::mul(const Vector3iPod& aVal)const
{
    Vector3i vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::div(const Vector3iPod& aVal)const
{
    Vector3i vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
void Vector3iPod::addAssign(const s32 aVal)
{
    x += aVal;
    y += aVal;
    z += aVal;
}

//------------------------------------------------------------------------------
void Vector3iPod::subAssign(const s32 aVal)
{
    x -= aVal;
    y -= aVal;
    z -= aVal;
}

//------------------------------------------------------------------------------
void Vector3iPod::mulAssign(const s32 aVal)
{
    x *= aVal;
    y *= aVal;
    z *= aVal;
}

//------------------------------------------------------------------------------
void Vector3iPod::divAssign(const s32 aVal)
{
    if (aVal == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    x /= aVal;
    y /= aVal;
    z /= aVal;
}

//------------------------------------------------------------------------------
void Vector3iPod::addAssign(const Vector3iPod& aVal)
{
    x += aVal.x;
    y += aVal.y;
    z += aVal.z;
}

//------------------------------------------------------------------------------
void Vector3iPod::subAssign(const Vector3iPod& aVal)
{
    x -= aVal.x;
    y -= aVal.y;
    z -= aVal.z;
}

//------------------------------------------------------------------------------
void Vector3iPod::mulAssign(const Vector3iPod& aVal)
{
    x *= aVal.x;
    y *= aVal.y;
    z *= aVal.z;
}

//------------------------------------------------------------------------------
void Vector3iPod::divAssign(const Vector3iPod& aVal)
{
    AE_BASE_DIV_ASSIGN(x, aVal.x);
    AE_BASE_DIV_ASSIGN(y, aVal.y);
    AE_BASE_DIV_ASSIGN(z, aVal.z);
}

//------------------------------------------------------------------------------
Vector3iPod& Vector3iPod::operator+=(const s32 aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3iPod& Vector3iPod::operator-=(const s32 aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3iPod& Vector3iPod::operator*=(const s32 aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3iPod& Vector3iPod::operator/=(const s32 aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3iPod& Vector3iPod::operator+=(const Vector3iPod& aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3iPod& Vector3iPod::operator-=(const Vector3iPod& aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3iPod& Vector3iPod::operator*=(const Vector3iPod& aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3iPod& Vector3iPod::operator/=(const Vector3iPod& aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator+(const s32 aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator-(const s32 aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator*(const s32 aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator/(const s32 aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator+(const Vector3iPod& aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator-(const Vector3iPod& aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator*(const Vector3iPod& aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator/(const Vector3iPod& aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator-()const
{
    return neg();
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::min(const Vector3iPod& aVal)const
{
    return Vector3i(
        Math::Min(x, aVal.x),
        Math::Min(y, aVal.y),
        Math::Min(z, aVal.z)
        );
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::max(const Vector3iPod& aVal)const
{
    return Vector3i(
        Math::Max(x, aVal.x),
        Math::Max(y, aVal.y),
        Math::Max(z, aVal.z)
        );
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::clamp(
    const Vector3iPod& aMin,
    const Vector3iPod& aMax
)const
{
    return max(aMin).min(aMax);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::clampPositive()const
{
    return max(Zero());
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::clampNegative()const
{
    return min(Zero());
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::abs()const
{
    return Vector3i(
        Math::AbsS32(x),
        Math::AbsS32(y),
        Math::AbsS32(z)
        );
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::neg()const
{
    Vector3i vec(*this);
    vec.mulAssign(-1);
    return vec;
}

//------------------------------------------------------------------------------
bool Vector3iPod::isPositive()const
{
    return 0 <= x
        && 0 <= y
        && 0 <= z;
}

//------------------------------------------------------------------------------
bool Vector3iPod::isZero()const
{
    return x == 0 && y == 0 && z == 0;
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Vector3iPod::toShortString()const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s,%s",
        S32(x).toShortString().readPtr(),
        S32(y).toShortString().readPtr(),
        S32(z).toShortString().readPtr()
        );
}

//------------------------------------------------------------------------------
Vector3i::Vector3i()
: Vector3iPod(Zero())
{
}

//------------------------------------------------------------------------------
Vector3i::Vector3i(const Vector3iPod& aVec)
: Vector3iPod(aVec)
{
}

//------------------------------------------------------------------------------
Vector3i::Vector3i(const s32 aV)
{
    x = aV;
    y = aV;
    z = aV;
}

//------------------------------------------------------------------------------
Vector3i::Vector3i(const Vector2iPod& aXY, const s32 aZ)
{
    x = aXY.x;
    y = aXY.y;
    z = aZ;
}

//------------------------------------------------------------------------------
Vector3i::Vector3i(const s32 aX, const s32 aY, const s32 aZ)
{
    x = aX;
    y = aY;
    z = aZ;
}

}} // namespace
// EOF
