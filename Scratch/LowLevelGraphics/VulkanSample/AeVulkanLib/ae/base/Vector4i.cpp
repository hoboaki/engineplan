// 文字コード：UTF-8
#include <ae/base/Vector4i.hpp>

// includes
#include <ae/base/DivideCheck.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/ScalerTypes.hpp>
#include <ae/base/Vector2i.hpp>
#include <ae/base/Vector3i.hpp>
#include <ae/base/Vector4.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Zero()
{
    Vector4iPod obj = {};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::One()
{
    Vector4iPod obj = { 1, 1, 1, 1 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Min()
{
    Vector4iPod obj = {
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::min()
    };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Max()
{
    Vector4iPod obj = {
        std::numeric_limits<int>::max(),
        std::numeric_limits<int>::max(),
        std::numeric_limits<int>::max(),
        std::numeric_limits<int>::max()
    };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::UnitX()
{
    Vector4iPod obj = { 1, 0, 0, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::UnitY()
{
    Vector4iPod obj = { 0, 1, 0, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::UnitZ()
{
    Vector4iPod obj = { 0, 0, 1, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::UnitW()
{
    Vector4iPod obj = { 0, 0, 0, 1 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::NegUnitX()
{
    Vector4iPod obj = { -1, 0, 0, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::NegUnitY()
{
    Vector4iPod obj = { 0, -1, 0, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::NegUnitZ()
{
    Vector4iPod obj = { 0, 0, -1, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::NegUnitW()
{
    Vector4iPod obj = { 0, 0, 0, -1 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector4iPod::ToXY() const
{
    return Vector2i(x, y);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector4iPod::ToXX() const
{
    return Vector2i(x, x);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector4iPod::ToYY() const
{
    return Vector2i(y, y);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector4iPod::ToZZ() const
{
    return Vector2i(z, z);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector4iPod::ToWW() const
{
    return Vector2i(w, w);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector4iPod::ToXYZ() const
{
    return Vector3i(x, y, z);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector4iPod::ToXXX() const
{
    return Vector3i(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector4iPod::ToYYY() const
{
    return Vector3i(y, y, y);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector4iPod::ToZZZ() const
{
    return Vector3i(z, z, z);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector4iPod::ToWWW() const
{
    return Vector3i(w, w, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToXYZ0() const
{
    return Vector4i(x, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToXY0W() const
{
    return Vector4i(x, y, 0, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToXY00() const
{
    return Vector4i(x, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToX0ZW() const
{
    return Vector4i(x, 0, z, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToX0Z0() const
{
    return Vector4i(x, 0, z, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToX00W() const
{
    return Vector4i(x, 0, 0, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToX000() const
{
    return Vector4i(x, 0, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::To0YZ0() const
{
    return Vector4i(0, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::To0Y0W() const
{
    return Vector4i(0, y, 0, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::To0Y00() const
{
    return Vector4i(0, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::To00ZW() const
{
    return Vector4i(0, 0, z, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::To00Z0() const
{
    return Vector4i(0, 0, z, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::To000W() const
{
    return Vector4i(0, 0, 0, w);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToXXXX() const
{
    return Vector4i(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToYYYY() const
{
    return Vector4i(y, y, y, y);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToZZZZ() const
{
    return Vector4i(z, z, z, z);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ToWWWW() const
{
    return Vector4i(w, w, w, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4iPod::ToXYZWf() const
{
    return Vector4(f32(x), f32(y), f32(z), f32(w));
}

//------------------------------------------------------------------------------
bool Vector4iPod::Equals(const Vector4iPod& vec) const
{
    return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Add(const s32 val) const
{
    Vector4i vec(*this);
    vec.AddAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Sub(const s32 val) const
{
    Vector4i vec(*this);
    vec.SubAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Mul(const s32 val) const
{
    Vector4i vec(*this);
    vec.MulAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Div(const s32 val) const
{
    Vector4i vec(*this);
    vec.DivAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Add(const Vector4iPod& val) const
{
    Vector4i vec(*this);
    vec.AddAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Sub(const Vector4iPod& val) const
{
    Vector4i vec(*this);
    vec.SubAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Mul(const Vector4iPod& val) const
{
    Vector4i vec(*this);
    vec.MulAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Div(const Vector4iPod& val) const
{
    Vector4i vec(*this);
    vec.DivAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
void Vector4iPod::AddAssign(const s32 val)
{
    x += val;
    y += val;
    z += val;
    w += val;
}

//------------------------------------------------------------------------------
void Vector4iPod::SubAssign(const s32 val)
{
    x -= val;
    y -= val;
    z -= val;
    w -= val;
}

//------------------------------------------------------------------------------
void Vector4iPod::MulAssign(const s32 val)
{
    x *= val;
    y *= val;
    z *= val;
    w *= val;
}

//------------------------------------------------------------------------------
void Vector4iPod::DivAssign(const s32 val)
{
    if (val == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    x /= val;
    y /= val;
    z /= val;
    w /= val;
}

//------------------------------------------------------------------------------
void Vector4iPod::AddAssign(const Vector4iPod& val)
{
    x += val.x;
    y += val.y;
    z += val.z;
    w += val.w;
}

//------------------------------------------------------------------------------
void Vector4iPod::SubAssign(const Vector4iPod& val)
{
    x -= val.x;
    y -= val.y;
    z -= val.z;
    w -= val.w;
}

//------------------------------------------------------------------------------
void Vector4iPod::MulAssign(const Vector4iPod& val)
{
    x *= val.x;
    y *= val.y;
    z *= val.z;
    w *= val.w;
}

//------------------------------------------------------------------------------
void Vector4iPod::DivAssign(const Vector4iPod& val)
{
    AE_BASE_DIV_ASSIGN(x, val.x);
    AE_BASE_DIV_ASSIGN(y, val.y);
    AE_BASE_DIV_ASSIGN(z, val.z);
    AE_BASE_DIV_ASSIGN(w, val.w);
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator+=(const s32 val)
{
    AddAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator-=(const s32 val)
{
    SubAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator*=(const s32 val)
{
    MulAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator/=(const s32 val)
{
    DivAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator+=(const Vector4iPod& val)
{
    AddAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator-=(const Vector4iPod& val)
{
    SubAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator*=(const Vector4iPod& val)
{
    MulAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector4iPod& Vector4iPod::operator/=(const Vector4iPod& val)
{
    DivAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator+(const s32 val) const
{
    return Add(val);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator-(const s32 val) const
{
    return Sub(val);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator*(const s32 val) const
{
    return Mul(val);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator/(const s32 val) const
{
    return Div(val);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator+(const Vector4iPod& val) const
{
    return Add(val);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator-(const Vector4iPod& val) const
{
    return Sub(val);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator*(const Vector4iPod& val) const
{
    return Mul(val);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator/(const Vector4iPod& val) const
{
    return Div(val);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::operator-() const
{
    return Neg();
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Min(const Vector4iPod& val) const
{
    return Vector4i(
        Math::Min(x, val.x),
        Math::Min(y, val.y),
        Math::Min(z, val.z),
        Math::Min(w, val.w));
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Max(const Vector4iPod& val) const
{
    return Vector4i(
        Math::Max(x, val.x),
        Math::Max(y, val.y),
        Math::Max(z, val.z),
        Math::Max(w, val.w));
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Clamp(
    const Vector4iPod& min,
    const Vector4iPod& max) const
{
    return Max(min).Min(max);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ClampPositive() const
{
    return Max(Zero());
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::ClampNegative() const
{
    return Min(Zero());
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Abs() const
{
    return Vector4i(
        Math::AbsS32(x),
        Math::AbsS32(y),
        Math::AbsS32(z),
        Math::AbsS32(2));
}

//------------------------------------------------------------------------------
const Vector4iPod Vector4iPod::Neg() const
{
    Vector4i vec(*this);
    vec.MulAssign(-1);
    return vec;
}

//------------------------------------------------------------------------------
bool Vector4iPod::IsPositive() const
{
    return 0 <= x && 0 <= y && 0 <= z && 0 <= w;
}

//------------------------------------------------------------------------------
bool Vector4iPod::IsZero() const
{
    return x == 0 && y == 0 && z == 0 && w == 0;
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Vector4iPod::ToShortString() const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s,%s,%s",
        S32(x).ToShortString().ReadPtr(),
        S32(y).ToShortString().ReadPtr(),
        S32(z).ToShortString().ReadPtr(),
        S32(w).ToShortString().ReadPtr());
}

//------------------------------------------------------------------------------
Vector4i::Vector4i()
: Vector4iPod(Zero())
{
}

//------------------------------------------------------------------------------
Vector4i::Vector4i(const Vector4iPod& vec)
: Vector4iPod(vec)
{
}

//------------------------------------------------------------------------------
Vector4i::Vector4i(const s32 v)
{
    this->x = v;
    this->y = v;
    this->z = v;
    this->w = v;
}

//------------------------------------------------------------------------------
Vector4i::Vector4i(const Vector2iPod& xY, const s32 z, const s32 w)
{
    this->x = xY.x;
    this->y = xY.y;
    this->z = z;
    this->w = w;
}

//------------------------------------------------------------------------------
Vector4i::Vector4i(const Vector3iPod& xYZ, const s32 w)
{
    this->x = xYZ.x;
    this->y = xYZ.y;
    this->z = xYZ.z;
    this->w = w;
}

//------------------------------------------------------------------------------
Vector4i::Vector4i(const s32 x, const s32 y, const s32 z, const s32 w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

} // namespace ae::base
// EOF
