// 文字コード：UTF-8
#include <ae/base/Vector2i.hpp>

#include <ae/base/DivideCheck.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/ScalerTypes.hpp>
#include <ae/base/Vector2.hpp>
#include <ae/base/Vector3i.hpp>
#include <ae/base/Vector4i.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Zero()
{
    Vector2iPod obj = {};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::One()
{
    Vector2iPod obj = {1, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Min()
{
    Vector2iPod obj = {std::numeric_limits< int >::min(), std::numeric_limits< int >::min()};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Max()
{
    Vector2iPod obj = {std::numeric_limits< int >::max(), std::numeric_limits< int >::max()};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::UnitX()
{
    Vector2iPod obj = {1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::UnitY()
{
    Vector2iPod obj = {0, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::NegUnitX()
{
    Vector2iPod obj = {-1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::NegUnitY()
{
    Vector2iPod obj = {0, -1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::toX0()const
{
    return Vector2i(x, 0);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::toXX()const
{
    return Vector2i(x, x);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::toYX()const
{
    return Vector2i(y, x);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::toYY()const
{
    return Vector2i(y, y);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector2iPod::toXY0()const
{
    return Vector3i(x, y, 0);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector2iPod::toXXX()const
{
    return Vector3i(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector2iPod::toYYY()const
{
    return Vector3i(y, y, y);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector2iPod::toXY00()const
{
    return Vector4i(x, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector2iPod::toXXXX()const
{
    return Vector4i(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector2iPod::toYYYY()const
{
    return Vector4i(y, y, y, y);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2iPod::toXYf()const
{
    return Vector2(f32(x), f32(y));
}

//------------------------------------------------------------------------------
bool Vector2iPod::equals(const Vector2iPod& aVec)const
{
    return x == aVec.x
        && y == aVec.y;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::add(const s32 aVal)const
{
    Vector2i vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::sub(const s32 aVal)const
{
    Vector2i vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::mul(const s32 aVal)const
{
    Vector2i vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::div(const s32 aVal)const
{
    Vector2i vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::add(const Vector2iPod& aVal)const
{
    Vector2i vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::sub(const Vector2iPod& aVal)const
{
    Vector2i vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::mul(const Vector2iPod& aVal)const
{
    Vector2i vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::div(const Vector2iPod& aVal)const
{
    Vector2i vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
void Vector2iPod::addAssign(const s32 aVal)
{
    x += aVal;
    y += aVal;
}

//------------------------------------------------------------------------------
void Vector2iPod::subAssign(const s32 aVal)
{
    x -= aVal;
    y -= aVal;
}

//------------------------------------------------------------------------------
void Vector2iPod::mulAssign(const s32 aVal)
{
    x *= aVal;
    y *= aVal;
}

//------------------------------------------------------------------------------
void Vector2iPod::divAssign(const s32 aVal)
{
    if (aVal == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    x /= aVal;
    y /= aVal;
}

//------------------------------------------------------------------------------
void Vector2iPod::addAssign(const Vector2iPod& aVal)
{
    x += aVal.x;
    y += aVal.y;
}

//------------------------------------------------------------------------------
void Vector2iPod::subAssign(const Vector2iPod& aVal)
{
    x -= aVal.x;
    y -= aVal.y;
}

//------------------------------------------------------------------------------
void Vector2iPod::mulAssign(const Vector2iPod& aVal)
{
    x *= aVal.x;
    y *= aVal.y;
}

//------------------------------------------------------------------------------
void Vector2iPod::divAssign(const Vector2iPod& aVal)
{
    AE_BASE_DIV_ASSIGN(x, aVal.x);
    AE_BASE_DIV_ASSIGN(y, aVal.y);
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator+=(const s32 aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator-=(const s32 aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator*=(const s32 aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator/=(const s32 aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator+=(const Vector2iPod& aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator-=(const Vector2iPod& aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator*=(const Vector2iPod& aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator/=(const Vector2iPod& aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator+(const s32 aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator-(const s32 aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator*(const s32 aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator/(const s32 aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator+(const Vector2iPod& aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator-(const Vector2iPod& aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator*(const Vector2iPod& aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator/(const Vector2iPod& aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator-()const
{
    return neg();
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::min(const Vector2iPod& aVal)const
{
    return Vector2i(
        Math::Min(x, aVal.x),
        Math::Min(y, aVal.y)
        );
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::max(const Vector2iPod& aVal)const
{
    return Vector2i(
        Math::Max(x, aVal.x),
        Math::Max(y, aVal.y)
        );
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::clamp(
    const Vector2iPod& aMin,
    const Vector2iPod& aMax
)const
{
    return max(aMin).min(aMax);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::clampPositive()const
{
    return max(Zero());
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::clampNegative()const
{
    return min(Zero());
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::abs()const
{
    return Vector2i(
        Math::AbsS32(x),
        Math::AbsS32(y)
        );
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::neg()const
{
    Vector2i vec(*this);
    vec.mulAssign(-1);
    return vec;
}

//------------------------------------------------------------------------------
bool Vector2iPod::isPositive()const
{
    return 0 <= x
        && 0 <= y;
}

//------------------------------------------------------------------------------
bool Vector2iPod::isZero()const
{
    return x == 0 && y == 0;
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Vector2iPod::toShortString()const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s",
        S32(x).toShortString().readPtr(),
        S32(y).toShortString().readPtr()
        );
}

//------------------------------------------------------------------------------
Vector2i::Vector2i()
: Vector2iPod(Zero())
{
}

//------------------------------------------------------------------------------
Vector2i::Vector2i(const Vector2iPod& aVec)
: Vector2iPod(aVec)
{
}

//------------------------------------------------------------------------------
Vector2i::Vector2i(const s32 aV)
{
    x = aV;
    y = aV;
}

//------------------------------------------------------------------------------
Vector2i::Vector2i(const s32 aX, const s32 aY)
{
    x = aX;
    y = aY;
}

}} // namespace
// EOF
