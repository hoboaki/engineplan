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
const Vector2iPod Vector4iPod::ToXY()const
{
    return Vector2i(x, y);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector4iPod::ToXX()const
{
    return Vector2i(x, x);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector4iPod::ToYY()const
{
    return Vector2i(y, y);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector4iPod::ToZZ()const
{
    return Vector2i(z, z);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector4iPod::ToWW()const
{
    return Vector2i(w, w);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector4iPod::ToXYZ()const
{
    return Vector3i(x, y, z);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector4iPod::ToXXX()const
{
    return Vector3i(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector4iPod::ToYYY()const
{
    return Vector3i(y, y, y);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector4iPod::ToZZZ()const
{
    return Vector3i(z, z, z);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector4iPod::ToWWW()const
{
    return Vector3i(w, w, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToXYZ0()const
{
    return Vector4i(x, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToXY0W()const
{
    return Vector4i(x, y, 0, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToXY00()const
{
    return Vector4i(x, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToX0ZW()const
{
    return Vector4i(x, 0, z, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToX0Z0()const
{
    return Vector4i(x, 0, z, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToX00W()const
{
    return Vector4i(x, 0, 0, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToX000()const
{
    return Vector4i(x, 0, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::To0YZ0()const
{
    return Vector4i(0, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::To0Y0W()const
{
    return Vector4i(0, y, 0, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::To0Y00()const
{
    return Vector4i(0, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::To00ZW()const
{
    return Vector4i(0, 0, z, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::To00Z0()const
{
    return Vector4i(0, 0, z, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::To000W()const
{
    return Vector4i(0, 0, 0, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToXXXX()const
{
    return Vector4i(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToYYYY()const
{
    return Vector4i(y, y, y, y);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToZZZZ()const
{
    return Vector4i(z, z, z, z);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToWWWW()const
{
    return Vector4i(w, w, w, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4iPod::ToXYZWf()const
{
    return Vector4(f32(x), f32(y), f32(z), f32(w));
}

//------------------------------------------------------------------------------
bool Vector4iPod::Equals(const Vector4iPod& aVec)const
{
    return x == aVec.x
        && y == aVec.y
        && z == aVec.z
        && w == aVec.w
        ;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Add(const s32 aVal)const
{
    Vector4i vec(*this);
    vec.AddAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Sub(const s32 aVal)const
{
    Vector4i vec(*this);
    vec.SubAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Mul(const s32 aVal)const
{
    Vector4i vec(*this);
    vec.MulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Div(const s32 aVal)const
{
    Vector4i vec(*this);
    vec.DivAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Add(const Vector4iPod& aVal)const
{
    Vector4i vec(*this);
    vec.AddAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Sub(const Vector4iPod& aVal)const
{
    Vector4i vec(*this);
    vec.SubAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Mul(const Vector4iPod& aVal)const
{
    Vector4i vec(*this);
    vec.MulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Div(const Vector4iPod& aVal)const
{
    Vector4i vec(*this);
    vec.DivAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
void Vector4iPod::AddAssign(const s32 aVal)
{
    x += aVal;
    y += aVal;
    z += aVal;
    w += aVal;
}

//------------------------------------------------------------------------------
void Vector4iPod::SubAssign(const s32 aVal)
{
    x -= aVal;
    y -= aVal;
    z -= aVal;
    w -= aVal;
}

//------------------------------------------------------------------------------
void Vector4iPod::MulAssign(const s32 aVal)
{
    x *= aVal;
    y *= aVal;
    z *= aVal;
    w *= aVal;
}

//------------------------------------------------------------------------------
void Vector4iPod::DivAssign(const s32 aVal)
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
void Vector4iPod::AddAssign(const Vector4iPod& aVal)
{
    x += aVal.x;
    y += aVal.y;
    z += aVal.z;
    w += aVal.w;
}

//------------------------------------------------------------------------------
void Vector4iPod::SubAssign(const Vector4iPod& aVal)
{
    x -= aVal.x;
    y -= aVal.y;
    z -= aVal.z;
    w -= aVal.w;
}

//------------------------------------------------------------------------------
void Vector4iPod::MulAssign(const Vector4iPod& aVal)
{
    x *= aVal.x;
    y *= aVal.y;
    z *= aVal.z;
    w *= aVal.w;
}

//------------------------------------------------------------------------------
void Vector4iPod::DivAssign(const Vector4iPod& aVal)
{
    AE_BASE_DIV_ASSIGN(x, aVal.x);
    AE_BASE_DIV_ASSIGN(y, aVal.y);
    AE_BASE_DIV_ASSIGN(z, aVal.z);
    AE_BASE_DIV_ASSIGN(w, aVal.w);
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator+=(const s32 aVal)
{
    AddAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator-=(const s32 aVal)
{
    SubAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator*=(const s32 aVal)
{
    MulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator/=(const s32 aVal)
{
    DivAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator+=(const Vector4iPod& aVal)
{
    AddAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator-=(const Vector4iPod& aVal)
{
    SubAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator*=(const Vector4iPod& aVal)
{
    MulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator/=(const Vector4iPod& aVal)
{
    DivAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator+(const s32 aVal)const
{
    return Add(aVal);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator-(const s32 aVal)const
{
    return Sub(aVal);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator*(const s32 aVal)const
{
    return Mul(aVal);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator/(const s32 aVal)const
{
    return Div(aVal);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator+(const Vector4iPod& aVal)const
{
    return Add(aVal);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator-(const Vector4iPod& aVal)const
{
    return Sub(aVal);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator*(const Vector4iPod& aVal)const
{
    return Mul(aVal);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator/(const Vector4iPod& aVal)const
{
    return Div(aVal);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator-()const
{
    return Neg();
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Min(const Vector4iPod& aVal)const
{
    return Vector4i(
        Math::Min(x, aVal.x),
        Math::Min(y, aVal.y),
        Math::Min(z, aVal.z),
        Math::Min(w, aVal.w)
        );
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Max(const Vector4iPod& aVal)const
{
    return Vector4i(
        Math::Max(x, aVal.x),
        Math::Max(y, aVal.y),
        Math::Max(z, aVal.z),
        Math::Max(w, aVal.w)
        );
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Clamp(
    const Vector4iPod& aMin,
    const Vector4iPod& aMax
)const
{
    return Max(aMin).Min(aMax);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ClampPositive()const
{
    return Max(Zero());
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ClampNegative()const
{
    return Min(Zero());
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Abs()const
{
    return Vector4i(
        Math::AbsS32(x),
        Math::AbsS32(y),
        Math::AbsS32(z),
        Math::AbsS32(2)
        );
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Neg()const
{
    Vector4i vec(*this);
    vec.MulAssign(-1);
    return vec;
}

//------------------------------------------------------------------------------
bool Vector4iPod::IsPositive()const
{
    return 0 <= x
        && 0 <= y
        && 0 <= z
        && 0 <= w;
}

//------------------------------------------------------------------------------
bool Vector4iPod::IsZero()const
{
    return x == 0 && y == 0 && z == 0 && w == 0;
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Vector4iPod::ToShortString()const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s,%s,%s",
        S32(x).ToShortString().ReadPtr(),
        S32(y).ToShortString().ReadPtr(),
        S32(z).ToShortString().ReadPtr(),
        S32(w).ToShortString().ReadPtr()
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
