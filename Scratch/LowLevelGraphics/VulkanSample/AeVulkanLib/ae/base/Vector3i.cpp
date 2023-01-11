// 文字コード：UTF-8
#include <ae/base/Vector3i.hpp>

// includes
#include <ae/base/DivideCheck.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/ScalerTypes.hpp>
#include <ae/base/Vector2i.hpp>
#include <ae/base/Vector3.hpp>
#include <ae/base/Vector4i.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Zero()
{
    Vector3iPod obj = {};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::One()
{
    Vector3iPod obj = { 1, 1, 1 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Min()
{
    Vector3iPod obj = {
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::min()
    };
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Max()
{
    Vector3iPod obj = {
        std::numeric_limits<int>::max(),
        std::numeric_limits<int>::max(),
        std::numeric_limits<int>::max()
    };
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::UnitX()
{
    Vector3iPod obj = { 1, 0, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::UnitY()
{
    Vector3iPod obj = { 0, 1, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::UnitZ()
{
    Vector3iPod obj = { 0, 0, 1 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::NegUnitX()
{
    Vector3iPod obj = { -1, 0, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::NegUnitY()
{
    Vector3iPod obj = { 0, -1, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::NegUnitZ()
{
    Vector3iPod obj = { 0, 0, -1 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector3iPod::ToXY() const
{
    return Vector2i(x, y);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector3iPod::ToXX() const
{
    return Vector2i(x, x);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector3iPod::ToYY() const
{
    return Vector2i(y, y);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector3iPod::ToZZ() const
{
    return Vector2i(z, z);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::ToX00() const
{
    return Vector3i(x, 0, 0);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::ToXY0() const
{
    return Vector3i(x, y, 0);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::To0Y0() const
{
    return Vector3i(0, y, 0);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::To0YZ() const
{
    return Vector3i(0, y, z);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::To00Z() const
{
    return Vector3i(0, 0, z);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::ToXXX() const
{
    return Vector3i(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::ToYYY() const
{
    return Vector3i(y, y, y);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::ToZZZ() const
{
    return Vector3i(z, z, z);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector3iPod::ToXYZ0() const
{
    return Vector4i(x, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector3iPod::ToXXXX() const
{
    return Vector4i(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector3iPod::ToYYYY() const
{
    return Vector4i(y, y, y, y);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector3iPod::ToZZZZ() const
{
    return Vector4i(z, z, z, z);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3iPod::ToXYZf() const
{
    return Vector3(f32(x), f32(y), f32(z));
}

//------------------------------------------------------------------------------
bool Vector3iPod::Equals(const Vector3iPod& vec) const
{
    return x == vec.x && y == vec.y && z == vec.z;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Add(const s32 val) const
{
    Vector3i vec(*this);
    vec.AddAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Sub(const s32 val) const
{
    Vector3i vec(*this);
    vec.SubAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Mul(const s32 val) const
{
    Vector3i vec(*this);
    vec.MulAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Div(const s32 val) const
{
    Vector3i vec(*this);
    vec.DivAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Add(const Vector3iPod& val) const
{
    Vector3i vec(*this);
    vec.AddAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Sub(const Vector3iPod& val) const
{
    Vector3i vec(*this);
    vec.SubAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Mul(const Vector3iPod& val) const
{
    Vector3i vec(*this);
    vec.MulAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Div(const Vector3iPod& val) const
{
    Vector3i vec(*this);
    vec.DivAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
void Vector3iPod::AddAssign(const s32 val)
{
    x += val;
    y += val;
    z += val;
}

//------------------------------------------------------------------------------
void Vector3iPod::SubAssign(const s32 val)
{
    x -= val;
    y -= val;
    z -= val;
}

//------------------------------------------------------------------------------
void Vector3iPod::MulAssign(const s32 val)
{
    x *= val;
    y *= val;
    z *= val;
}

//------------------------------------------------------------------------------
void Vector3iPod::DivAssign(const s32 val)
{
    if (val == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    x /= val;
    y /= val;
    z /= val;
}

//------------------------------------------------------------------------------
void Vector3iPod::AddAssign(const Vector3iPod& val)
{
    x += val.x;
    y += val.y;
    z += val.z;
}

//------------------------------------------------------------------------------
void Vector3iPod::SubAssign(const Vector3iPod& val)
{
    x -= val.x;
    y -= val.y;
    z -= val.z;
}

//------------------------------------------------------------------------------
void Vector3iPod::MulAssign(const Vector3iPod& val)
{
    x *= val.x;
    y *= val.y;
    z *= val.z;
}

//------------------------------------------------------------------------------
void Vector3iPod::DivAssign(const Vector3iPod& val)
{
    AE_BASE_DIV_ASSIGN(x, val.x);
    AE_BASE_DIV_ASSIGN(y, val.y);
    AE_BASE_DIV_ASSIGN(z, val.z);
}

//------------------------------------------------------------------------------
Vector3iPod& Vector3iPod::operator+=(const s32 val)
{
    AddAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector3iPod& Vector3iPod::operator-=(const s32 val)
{
    SubAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector3iPod& Vector3iPod::operator*=(const s32 val)
{
    MulAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector3iPod& Vector3iPod::operator/=(const s32 val)
{
    DivAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector3iPod& Vector3iPod::operator+=(const Vector3iPod& val)
{
    AddAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector3iPod& Vector3iPod::operator-=(const Vector3iPod& val)
{
    SubAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector3iPod& Vector3iPod::operator*=(const Vector3iPod& val)
{
    MulAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector3iPod& Vector3iPod::operator/=(const Vector3iPod& val)
{
    DivAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator+(const s32 val) const
{
    return Add(val);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator-(const s32 val) const
{
    return Sub(val);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator*(const s32 val) const
{
    return Mul(val);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator/(const s32 val) const
{
    return Div(val);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator+(const Vector3iPod& val) const
{
    return Add(val);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator-(const Vector3iPod& val) const
{
    return Sub(val);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator*(const Vector3iPod& val) const
{
    return Mul(val);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator/(const Vector3iPod& val) const
{
    return Div(val);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::operator-() const
{
    return Neg();
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Min(const Vector3iPod& val) const
{
    return Vector3i(
        Math::Min(x, val.x),
        Math::Min(y, val.y),
        Math::Min(z, val.z));
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Max(const Vector3iPod& val) const
{
    return Vector3i(
        Math::Max(x, val.x),
        Math::Max(y, val.y),
        Math::Max(z, val.z));
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Clamp(
    const Vector3iPod& min,
    const Vector3iPod& max) const
{
    return Max(min).Min(max);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::ClampPositive() const
{
    return Max(Zero());
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::ClampNegative() const
{
    return Min(Zero());
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Abs() const
{
    return Vector3i(Math::AbsS32(x), Math::AbsS32(y), Math::AbsS32(z));
}

//------------------------------------------------------------------------------
const Vector3iPod Vector3iPod::Neg() const
{
    Vector3i vec(*this);
    vec.MulAssign(-1);
    return vec;
}

//------------------------------------------------------------------------------
bool Vector3iPod::IsPositive() const
{
    return 0 <= x && 0 <= y && 0 <= z;
}

//------------------------------------------------------------------------------
bool Vector3iPod::IsZero() const
{
    return x == 0 && y == 0 && z == 0;
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Vector3iPod::ToShortString() const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s,%s",
        S32(x).ToShortString().ReadPtr(),
        S32(y).ToShortString().ReadPtr(),
        S32(z).ToShortString().ReadPtr());
}

//------------------------------------------------------------------------------
Vector3i::Vector3i()
: Vector3iPod(Zero())
{
}

//------------------------------------------------------------------------------
Vector3i::Vector3i(const Vector3iPod& vec)
: Vector3iPod(vec)
{
}

//------------------------------------------------------------------------------
Vector3i::Vector3i(const s32 v)
{
    this->x = v;
    this->y = v;
    this->z = v;
}

//------------------------------------------------------------------------------
Vector3i::Vector3i(const Vector2iPod& xY, const s32 z)
{
    this->x = xY.x;
    this->y = xY.y;
    this->z = z;
}

//------------------------------------------------------------------------------
Vector3i::Vector3i(const s32 x, const s32 y, const s32 z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

} // namespace ae::base
// EOF
