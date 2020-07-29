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
const Vector2iPod Vector2iPod::ToX0()const
{
    return Vector2i(x, 0);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::ToXX()const
{
    return Vector2i(x, x);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::ToYX()const
{
    return Vector2i(y, x);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::ToYY()const
{
    return Vector2i(y, y);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector2iPod::ToXY0()const
{
    return Vector3i(x, y, 0);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector2iPod::ToXXX()const
{
    return Vector3i(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector2iPod::ToYYY()const
{
    return Vector3i(y, y, y);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector2iPod::ToXY00()const
{
    return Vector4i(x, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector2iPod::ToXXXX()const
{
    return Vector4i(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector2iPod::ToYYYY()const
{
    return Vector4i(y, y, y, y);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2iPod::ToXYf()const
{
    return Vector2(f32(x), f32(y));
}

//------------------------------------------------------------------------------
bool Vector2iPod::Equals(const Vector2iPod& aVec)const
{
    return x == aVec.x
        && y == aVec.y;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Add(const s32 aVal)const
{
    Vector2i vec(*this);
    vec.AddAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Sub(const s32 aVal)const
{
    Vector2i vec(*this);
    vec.SubAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Mul(const s32 aVal)const
{
    Vector2i vec(*this);
    vec.MulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Div(const s32 aVal)const
{
    Vector2i vec(*this);
    vec.DivAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Add(const Vector2iPod& aVal)const
{
    Vector2i vec(*this);
    vec.AddAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Sub(const Vector2iPod& aVal)const
{
    Vector2i vec(*this);
    vec.SubAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Mul(const Vector2iPod& aVal)const
{
    Vector2i vec(*this);
    vec.MulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Div(const Vector2iPod& aVal)const
{
    Vector2i vec(*this);
    vec.DivAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
void Vector2iPod::AddAssign(const s32 aVal)
{
    x += aVal;
    y += aVal;
}

//------------------------------------------------------------------------------
void Vector2iPod::SubAssign(const s32 aVal)
{
    x -= aVal;
    y -= aVal;
}

//------------------------------------------------------------------------------
void Vector2iPod::MulAssign(const s32 aVal)
{
    x *= aVal;
    y *= aVal;
}

//------------------------------------------------------------------------------
void Vector2iPod::DivAssign(const s32 aVal)
{
    if (aVal == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    x /= aVal;
    y /= aVal;
}

//------------------------------------------------------------------------------
void Vector2iPod::AddAssign(const Vector2iPod& aVal)
{
    x += aVal.x;
    y += aVal.y;
}

//------------------------------------------------------------------------------
void Vector2iPod::SubAssign(const Vector2iPod& aVal)
{
    x -= aVal.x;
    y -= aVal.y;
}

//------------------------------------------------------------------------------
void Vector2iPod::MulAssign(const Vector2iPod& aVal)
{
    x *= aVal.x;
    y *= aVal.y;
}

//------------------------------------------------------------------------------
void Vector2iPod::DivAssign(const Vector2iPod& aVal)
{
    AE_BASE_DIV_ASSIGN(x, aVal.x);
    AE_BASE_DIV_ASSIGN(y, aVal.y);
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator+=(const s32 aVal)
{
    AddAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator-=(const s32 aVal)
{
    SubAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator*=(const s32 aVal)
{
    MulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator/=(const s32 aVal)
{
    DivAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator+=(const Vector2iPod& aVal)
{
    AddAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator-=(const Vector2iPod& aVal)
{
    SubAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator*=(const Vector2iPod& aVal)
{
    MulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator/=(const Vector2iPod& aVal)
{
    DivAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator+(const s32 aVal)const
{
    return Add(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator-(const s32 aVal)const
{
    return Sub(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator*(const s32 aVal)const
{
    return Mul(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator/(const s32 aVal)const
{
    return Div(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator+(const Vector2iPod& aVal)const
{
    return Add(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator-(const Vector2iPod& aVal)const
{
    return Sub(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator*(const Vector2iPod& aVal)const
{
    return Mul(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator/(const Vector2iPod& aVal)const
{
    return Div(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator-()const
{
    return Neg();
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Min(const Vector2iPod& aVal)const
{
    return Vector2i(
        Math::Min(x, aVal.x),
        Math::Min(y, aVal.y)
        );
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Max(const Vector2iPod& aVal)const
{
    return Vector2i(
        Math::Max(x, aVal.x),
        Math::Max(y, aVal.y)
        );
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Clamp(
    const Vector2iPod& aMin,
    const Vector2iPod& aMax
)const
{
    return Max(aMin).Min(aMax);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::ClampPositive()const
{
    return Max(Zero());
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::ClampNegative()const
{
    return Min(Zero());
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Abs()const
{
    return Vector2i(
        Math::AbsS32(x),
        Math::AbsS32(y)
        );
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Neg()const
{
    Vector2i vec(*this);
    vec.MulAssign(-1);
    return vec;
}

//------------------------------------------------------------------------------
bool Vector2iPod::IsPositive()const
{
    return 0 <= x
        && 0 <= y;
}

//------------------------------------------------------------------------------
bool Vector2iPod::IsZero()const
{
    return x == 0 && y == 0;
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Vector2iPod::ToShortString()const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s",
        S32(x).ToShortString().ReadPtr(),
        S32(y).ToShortString().ReadPtr()
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
