// 文字コード：UTF-8
#include <ae/base/Vector3.hpp>

// includes
#include <ae/base/DivideCheck.hpp>
#include <ae/base/Infinity.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/ScalerTypes.hpp>
#include <ae/base/Vector2.hpp>
#include <ae/base/Vector4.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Zero()
{
    Vector3Pod obj = {};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::One()
{
    Vector3Pod obj = { 1, 1, 1 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Min()
{
    Vector3Pod obj = {
        -AE_BASE_INFINITY,
        -AE_BASE_INFINITY,
        -AE_BASE_INFINITY
    };
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Max()
{
    Vector3Pod obj = { AE_BASE_INFINITY, AE_BASE_INFINITY, AE_BASE_INFINITY };
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::UnitX()
{
    Vector3Pod obj = { 1, 0, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::UnitY()
{
    Vector3Pod obj = { 0, 1, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::UnitZ()
{
    Vector3Pod obj = { 0, 0, 1 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::NegUnitX()
{
    Vector3Pod obj = { -1, 0, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::NegUnitY()
{
    Vector3Pod obj = { 0, -1, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::NegUnitZ()
{
    Vector3Pod obj = { 0, 0, -1 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector3Pod::ToXY() const
{
    return Vector2(x, y);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector3Pod::ToXX() const
{
    return Vector2(x, x);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector3Pod::ToYY() const
{
    return Vector2(y, y);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector3Pod::ToZZ() const
{
    return Vector2(z, z);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::ToX00() const
{
    return Vector3(x, 0, 0);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::ToXY0() const
{
    return Vector3(x, y, 0);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::To0Y0() const
{
    return Vector3(0, y, 0);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::To0YZ() const
{
    return Vector3(0, y, z);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::To00Z() const
{
    return Vector3(0, 0, z);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::ToXXX() const
{
    return Vector3(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::ToYYY() const
{
    return Vector3(y, y, y);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::ToZZZ() const
{
    return Vector3(z, z, z);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector3Pod::ToXYZ0() const
{
    return Vector4(x, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector3Pod::ToXXXX() const
{
    return Vector4(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector3Pod::ToYYYY() const
{
    return Vector4(y, y, y, y);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector3Pod::ToZZZZ() const
{
    return Vector4(z, z, z, z);
}

//------------------------------------------------------------------------------
bool Vector3Pod::Equals(const Vector3Pod& vec) const
{
    return Math::IsEqualsF32(x, vec.x) && Math::IsEqualsF32(y, vec.y) &&
           Math::IsEqualsF32(z, vec.z);
}

//------------------------------------------------------------------------------
bool Vector3Pod::EqualsStrict(const Vector3Pod& vec) const
{
    return x == vec.x && y == vec.y && z == vec.z;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Add(const float val) const
{
    Vector3 vec(*this);
    vec.AddAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Sub(const float val) const
{
    Vector3 vec(*this);
    vec.SubAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Mul(const float val) const
{
    Vector3 vec(*this);
    vec.MulAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Div(const float val) const
{
    Vector3 vec(*this);
    vec.DivAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Add(const Vector3Pod& val) const
{
    Vector3 vec(*this);
    vec.AddAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Sub(const Vector3Pod& val) const
{
    Vector3 vec(*this);
    vec.SubAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Mul(const Vector3Pod& val) const
{
    Vector3 vec(*this);
    vec.MulAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Div(const Vector3Pod& val) const
{
    Vector3 vec(*this);
    vec.DivAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
void Vector3Pod::AddAssign(const float val)
{
    x += val;
    y += val;
    z += val;
}

//------------------------------------------------------------------------------
void Vector3Pod::SubAssign(const float val)
{
    x -= val;
    y -= val;
    z -= val;
}

//------------------------------------------------------------------------------
void Vector3Pod::MulAssign(const float val)
{
    x *= val;
    y *= val;
    z *= val;
}

//------------------------------------------------------------------------------
void Vector3Pod::DivAssign(const float val)
{
    if (val == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    MulAssign(1.0f / val);
}

//------------------------------------------------------------------------------
void Vector3Pod::AddAssign(const Vector3Pod& val)
{
    x += val.x;
    y += val.y;
    z += val.z;
}

//------------------------------------------------------------------------------
void Vector3Pod::SubAssign(const Vector3Pod& val)
{
    x -= val.x;
    y -= val.y;
    z -= val.z;
}

//------------------------------------------------------------------------------
void Vector3Pod::MulAssign(const Vector3Pod& val)
{
    x *= val.x;
    y *= val.y;
    z *= val.z;
}

//------------------------------------------------------------------------------
void Vector3Pod::DivAssign(const Vector3Pod& val)
{
    AE_BASE_DIV_ASSIGN(x, val.x);
    AE_BASE_DIV_ASSIGN(y, val.y);
    AE_BASE_DIV_ASSIGN(z, val.z);
}

//------------------------------------------------------------------------------
Vector3Pod& Vector3Pod::operator+=(const float val)
{
    AddAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector3Pod& Vector3Pod::operator-=(const float val)
{
    SubAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector3Pod& Vector3Pod::operator*=(const float val)
{
    MulAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector3Pod& Vector3Pod::operator/=(const float val)
{
    DivAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector3Pod& Vector3Pod::operator+=(const Vector3Pod& val)
{
    AddAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector3Pod& Vector3Pod::operator-=(const Vector3Pod& val)
{
    SubAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector3Pod& Vector3Pod::operator*=(const Vector3Pod& val)
{
    MulAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector3Pod& Vector3Pod::operator/=(const Vector3Pod& val)
{
    DivAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator+(const float val) const
{
    return Add(val);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator-(const float val) const
{
    return Sub(val);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator*(const float val) const
{
    return Mul(val);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator/(const float val) const
{
    return Div(val);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator+(const Vector3Pod& val) const
{
    return Add(val);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator-(const Vector3Pod& val) const
{
    return Sub(val);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator*(const Vector3Pod& val) const
{
    return Mul(val);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator/(const Vector3Pod& val) const
{
    return Div(val);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::operator-() const
{
    return Neg();
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Min(const Vector3Pod& val) const
{
    return Vector3(
        Math::Min(x, val.x),
        Math::Min(y, val.y),
        Math::Min(z, val.z));
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Max(const Vector3Pod& val) const
{
    return Vector3(
        Math::Max(x, val.x),
        Math::Max(y, val.y),
        Math::Max(z, val.z));
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Clamp(const Vector3Pod& min, const Vector3Pod& max)
    const
{
    return Max(min).Min(max);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::ClampPositive() const
{
    return Max(Zero());
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::ClampNegative() const
{
    return Min(Zero());
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Abs() const
{
    return Vector3(Math::AbsF32(x), Math::AbsF32(y), Math::AbsF32(z));
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Neg() const
{
    Vector3 vec(*this);
    vec.MulAssign(-1.0f);
    return vec;
}

//------------------------------------------------------------------------------
f32 Vector3Pod::SquareLength() const
{
    return x * x + y * y + z * z;
}

//------------------------------------------------------------------------------
f32 Vector3Pod::Length() const
{
    return Math::SqrtF32(SquareLength());
}

//------------------------------------------------------------------------------
f32 Vector3Pod::Distance(const Vector3Pod& val) const
{
    return Sub(val).Length();
}

//------------------------------------------------------------------------------
bool Vector3Pod::IsZero() const
{
    return Math::IsZeroF32(Length());
}

//------------------------------------------------------------------------------
bool Vector3Pod::IsZeroStrict() const
{
    return x == 0 && y == 0 && z == 0;
}

//------------------------------------------------------------------------------
bool Vector3Pod::IsUnit() const
{
    return Math::IsEqualsF32(Length(), 1.0f);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Unit() const
{
    Vector3 vec(*this);
    vec.UnitAssign();
    return vec;
}

//------------------------------------------------------------------------------
void Vector3Pod::UnitAssign()
{
    if (IsZeroStrict()) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    MulAssign(1.0f / Length());
}

//------------------------------------------------------------------------------
f32 Vector3Pod::Dot(const Vector3Pod& vec) const
{
    return x * vec.x + y * vec.y + z * vec.z;
}

//------------------------------------------------------------------------------
const Vector3Pod Vector3Pod::Cross(const Vector3Pod& vec) const
{
    return Vector3(
        y * vec.z - z * vec.y,
        z * vec.x - x * vec.z,
        x * vec.y - y * vec.x);
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Vector3Pod::ToShortString() const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s,%s",
        F32(x).ToShortString().ReadPtr(),
        F32(y).ToShortString().ReadPtr(),
        F32(z).ToShortString().ReadPtr());
}

//------------------------------------------------------------------------------
Vector3::Vector3()
: Vector3Pod(Zero())
{
}

//------------------------------------------------------------------------------
Vector3::Vector3(const Vector3Pod& vec)
: Vector3Pod(vec)
{
}

//------------------------------------------------------------------------------
Vector3::Vector3(const float v)
{
    this->x = v;
    this->y = v;
    this->z = v;
}

//------------------------------------------------------------------------------
Vector3::Vector3(const Vector2Pod& xY, const float z)
{
    this->x = xY.x;
    this->y = xY.y;
    this->z = z;
}

//------------------------------------------------------------------------------
Vector3::Vector3(const float x, const float y, const float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

} // namespace ae::base
// EOF
