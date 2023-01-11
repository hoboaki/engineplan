// 文字コード：UTF-8
#include <ae/base/Vector4.hpp>

// includes
#include <ae/base/DivideCheck.hpp>
#include <ae/base/Infinity.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/ScalerTypes.hpp>
#include <ae/base/Vector2.hpp>
#include <ae/base/Vector3.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Zero()
{
    Vector4Pod obj = {};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::One()
{
    Vector4Pod obj = { 1, 1, 1, 1 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Min()
{
    Vector4Pod obj = {
        -AE_BASE_INFINITY,
        -AE_BASE_INFINITY,
        -AE_BASE_INFINITY,
        -AE_BASE_INFINITY
    };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Max()
{
    Vector4Pod obj = {
        AE_BASE_INFINITY,
        AE_BASE_INFINITY,
        AE_BASE_INFINITY,
        AE_BASE_INFINITY
    };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::UnitX()
{
    Vector4Pod obj = { 1, 0, 0, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::UnitY()
{
    Vector4Pod obj = { 0, 1, 0, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::UnitZ()
{
    Vector4Pod obj = { 0, 0, 1, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::UnitW()
{
    Vector4Pod obj = { 0, 0, 0, 1 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::NegUnitX()
{
    Vector4Pod obj = { -1, 0, 0, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::NegUnitY()
{
    Vector4Pod obj = { 0, -1, 0, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::NegUnitZ()
{
    Vector4Pod obj = { 0, 0, -1, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::NegUnitW()
{
    Vector4Pod obj = { 0, 0, 0, -1 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::ToXY() const
{
    return Vector2(x, y);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::ToXX() const
{
    return Vector2(x, x);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::ToYY() const
{
    return Vector2(y, y);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::ToZZ() const
{
    return Vector2(z, z);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::ToWW() const
{
    return Vector2(w, w);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::ToXYZ() const
{
    return Vector3(x, y, z);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::ToXXX() const
{
    return Vector3(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::ToYYY() const
{
    return Vector3(y, y, y);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::ToZZZ() const
{
    return Vector3(z, z, z);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::ToWWW() const
{
    return Vector3(w, w, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToXYZ0() const
{
    return Vector4(x, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToXY0W() const
{
    return Vector4(x, y, 0, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToXY00() const
{
    return Vector4(x, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToX0ZW() const
{
    return Vector4(x, 0, z, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToX0Z0() const
{
    return Vector4(x, 0, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToX00W() const
{
    return Vector4(x, 0, 0, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToX000() const
{
    return Vector4(x, 0, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::To0YZ0() const
{
    return Vector4(0, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::To0Y0W() const
{
    return Vector4(0, y, 0, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::To0Y00() const
{
    return Vector4(0, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::To00ZW() const
{
    return Vector4(0, 0, z, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::To00Z0() const
{
    return Vector4(0, 0, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::To000W() const
{
    return Vector4(0, 0, 0, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToXXXX() const
{
    return Vector4(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToYYYY() const
{
    return Vector4(y, y, y, y);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToZZZZ() const
{
    return Vector4(z, z, z, z);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ToWWWW() const
{
    return Vector4(w, w, w, w);
}

//------------------------------------------------------------------------------
bool Vector4Pod::Equals(const Vector4Pod& vec) const
{
    return Math::IsEqualsF32(x, vec.x) && Math::IsEqualsF32(y, vec.y) &&
           Math::IsEqualsF32(z, vec.z) && Math::IsEqualsF32(w, vec.w);
}

//------------------------------------------------------------------------------
bool Vector4Pod::EqualsStrict(const Vector4Pod& vec) const
{
    return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Add(const float val) const
{
    Vector4 vec(*this);
    vec.AddAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Sub(const float val) const
{
    Vector4 vec(*this);
    vec.SubAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Mul(const float val) const
{
    Vector4 vec(*this);
    vec.MulAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Div(const float val) const
{
    Vector4 vec(*this);
    vec.DivAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Add(const Vector4Pod& val) const
{
    Vector4 vec(*this);
    vec.AddAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Sub(const Vector4Pod& val) const
{
    Vector4 vec(*this);
    vec.SubAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Mul(const Vector4Pod& val) const
{
    Vector4 vec(*this);
    vec.MulAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Div(const Vector4Pod& val) const
{
    Vector4 vec(*this);
    vec.DivAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
void Vector4Pod::AddAssign(const float val)
{
    x += val;
    y += val;
    z += val;
    w += val;
}

//------------------------------------------------------------------------------
void Vector4Pod::SubAssign(const float val)
{
    x -= val;
    y -= val;
    z -= val;
    w -= val;
}

//------------------------------------------------------------------------------
void Vector4Pod::MulAssign(const float val)
{
    x *= val;
    y *= val;
    z *= val;
    w *= val;
}

//------------------------------------------------------------------------------
void Vector4Pod::DivAssign(const float val)
{
    if (val == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    MulAssign(1.0f / val);
}

//------------------------------------------------------------------------------
void Vector4Pod::AddAssign(const Vector4Pod& val)
{
    x += val.x;
    y += val.y;
    z += val.z;
    w += val.w;
}

//------------------------------------------------------------------------------
void Vector4Pod::SubAssign(const Vector4Pod& val)
{
    x -= val.x;
    y -= val.y;
    z -= val.z;
    w -= val.w;
}

//------------------------------------------------------------------------------
void Vector4Pod::MulAssign(const Vector4Pod& val)
{
    x *= val.x;
    y *= val.y;
    z *= val.z;
    w *= val.w;
}

//------------------------------------------------------------------------------
void Vector4Pod::DivAssign(const Vector4Pod& val)
{
    AE_BASE_DIV_ASSIGN(x, val.x);
    AE_BASE_DIV_ASSIGN(y, val.y);
    AE_BASE_DIV_ASSIGN(z, val.z);
    AE_BASE_DIV_ASSIGN(w, val.w);
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator+=(const float val)
{
    AddAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator-=(const float val)
{
    SubAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator*=(const float val)
{
    MulAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator/=(const float val)
{
    DivAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator+=(const Vector4Pod& val)
{
    AddAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator-=(const Vector4Pod& val)
{
    SubAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator*=(const Vector4Pod& val)
{
    MulAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector4Pod& Vector4Pod::operator/=(const Vector4Pod& val)
{
    DivAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator+(const float val) const
{
    return Add(val);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator-(const float val) const
{
    return Sub(val);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator*(const float val) const
{
    return Mul(val);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator/(const float val) const
{
    return Div(val);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator+(const Vector4Pod& val) const
{
    return Add(val);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator-(const Vector4Pod& val) const
{
    return Sub(val);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator*(const Vector4Pod& val) const
{
    return Mul(val);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator/(const Vector4Pod& val) const
{
    return Div(val);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::operator-() const
{
    return Neg();
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Min(const Vector4Pod& val) const
{
    return Vector4(
        Math::Min(x, val.x),
        Math::Min(y, val.y),
        Math::Min(z, val.z),
        Math::Min(w, val.w));
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Max(const Vector4Pod& val) const
{
    return Vector4(
        Math::Max(x, val.x),
        Math::Max(y, val.y),
        Math::Max(z, val.z),
        Math::Max(w, val.w));
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Clamp(const Vector4Pod& min, const Vector4Pod& max)
    const
{
    return Max(min).Min(max);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ClampPositive() const
{
    return Max(Zero());
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::ClampNegative() const
{
    return Min(Zero());
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Abs() const
{
    return Vector4(
        Math::AbsF32(x),
        Math::AbsF32(y),
        Math::AbsF32(z),
        Math::AbsF32(w));
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Neg() const
{
    Vector4 vec(*this);
    vec.MulAssign(-1.0f);
    return vec;
}

//------------------------------------------------------------------------------
f32 Vector4Pod::SquareLength() const
{
    return x * x + y * y + z * z + w * w;
}

//------------------------------------------------------------------------------
f32 Vector4Pod::Length() const
{
    return Math::SqrtF32(SquareLength());
}

//------------------------------------------------------------------------------
f32 Vector4Pod::Distance(const Vector4Pod& val) const
{
    return Sub(val).Length();
}

//------------------------------------------------------------------------------
bool Vector4Pod::IsZero() const
{
    return Math::IsZeroF32(Length());
}

//------------------------------------------------------------------------------
bool Vector4Pod::IsZeroStrict() const
{
    return x == 0 && y == 0 && z == 0 && w == 0;
}

//------------------------------------------------------------------------------
bool Vector4Pod::IsUnit() const
{
    return Math::IsEqualsF32(Length(), 1.0f);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Unit() const
{
    Vector4 vec(*this);
    vec.UnitAssign();
    return vec;
}

//------------------------------------------------------------------------------
void Vector4Pod::UnitAssign()
{
    if (IsZeroStrict()) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    MulAssign(1.0f / Length());
}

//------------------------------------------------------------------------------
f32 Vector4Pod::Dot(const Vector4Pod& vec) const
{
    return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Vector4Pod::ToShortString() const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s,%s,%s",
        F32(x).ToShortString().ReadPtr(),
        F32(y).ToShortString().ReadPtr(),
        F32(z).ToShortString().ReadPtr(),
        F32(w).ToShortString().ReadPtr());
}

//------------------------------------------------------------------------------
Vector4::Vector4()
: Vector4Pod(Zero())
{
}

//------------------------------------------------------------------------------
Vector4::Vector4(const Vector4Pod& vec)
: Vector4Pod(vec)
{
}

//------------------------------------------------------------------------------
Vector4::Vector4(const float v)
{
    this->x = v;
    this->y = v;
    this->z = v;
    this->w = v;
}

//------------------------------------------------------------------------------
Vector4::Vector4(const Vector2Pod& xY, const float z, const float w)
{
    this->x = xY.x;
    this->y = xY.y;
    this->z = z;
    this->w = w;
}

//------------------------------------------------------------------------------
Vector4::Vector4(const Vector3Pod& xYZ, const float w)
{
    this->x = xYZ.x;
    this->y = xYZ.y;
    this->z = xYZ.z;
    this->w = w;
}

//------------------------------------------------------------------------------
Vector4::Vector4(const float x, const float y, const float z, const float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

} // namespace ae::base
// EOF
