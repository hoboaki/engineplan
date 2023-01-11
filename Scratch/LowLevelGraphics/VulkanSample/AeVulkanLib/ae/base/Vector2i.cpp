// 文字コード：UTF-8
#include <ae/base/Vector2i.hpp>

// includes
#include <ae/base/DivideCheck.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/ScalerTypes.hpp>
#include <ae/base/Vector2.hpp>
#include <ae/base/Vector3i.hpp>
#include <ae/base/Vector4i.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Zero()
{
    Vector2iPod obj = {};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::One()
{
    Vector2iPod obj = { 1, 1 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Min()
{
    Vector2iPod obj = {
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::min()
    };
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Max()
{
    Vector2iPod obj = {
        std::numeric_limits<int>::max(),
        std::numeric_limits<int>::max()
    };
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::UnitX()
{
    Vector2iPod obj = { 1, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::UnitY()
{
    Vector2iPod obj = { 0, 1 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::NegUnitX()
{
    Vector2iPod obj = { -1, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::NegUnitY()
{
    Vector2iPod obj = { 0, -1 };
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::ToX0() const
{
    return Vector2i(x, 0);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::ToXX() const
{
    return Vector2i(x, x);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::ToYX() const
{
    return Vector2i(y, x);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::ToYY() const
{
    return Vector2i(y, y);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector2iPod::ToXY0() const
{
    return Vector3i(x, y, 0);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector2iPod::ToXXX() const
{
    return Vector3i(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3iPod Vector2iPod::ToYYY() const
{
    return Vector3i(y, y, y);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector2iPod::ToXY00() const
{
    return Vector4i(x, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector2iPod::ToXXXX() const
{
    return Vector4i(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4iPod Vector2iPod::ToYYYY() const
{
    return Vector4i(y, y, y, y);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector2iPod::ToXYf() const
{
    return Vector2(f32(x), f32(y));
}

//------------------------------------------------------------------------------
bool Vector2iPod::Equals(const Vector2iPod& vec) const
{
    return x == vec.x && y == vec.y;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Add(const s32 val) const
{
    Vector2i vec(*this);
    vec.AddAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Sub(const s32 val) const
{
    Vector2i vec(*this);
    vec.SubAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Mul(const s32 val) const
{
    Vector2i vec(*this);
    vec.MulAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Div(const s32 val) const
{
    Vector2i vec(*this);
    vec.DivAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Add(const Vector2iPod& val) const
{
    Vector2i vec(*this);
    vec.AddAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Sub(const Vector2iPod& val) const
{
    Vector2i vec(*this);
    vec.SubAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Mul(const Vector2iPod& val) const
{
    Vector2i vec(*this);
    vec.MulAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Div(const Vector2iPod& val) const
{
    Vector2i vec(*this);
    vec.DivAssign(val);
    return vec;
}

//------------------------------------------------------------------------------
void Vector2iPod::AddAssign(const s32 val)
{
    x += val;
    y += val;
}

//------------------------------------------------------------------------------
void Vector2iPod::SubAssign(const s32 val)
{
    x -= val;
    y -= val;
}

//------------------------------------------------------------------------------
void Vector2iPod::MulAssign(const s32 val)
{
    x *= val;
    y *= val;
}

//------------------------------------------------------------------------------
void Vector2iPod::DivAssign(const s32 val)
{
    if (val == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    x /= val;
    y /= val;
}

//------------------------------------------------------------------------------
void Vector2iPod::AddAssign(const Vector2iPod& val)
{
    x += val.x;
    y += val.y;
}

//------------------------------------------------------------------------------
void Vector2iPod::SubAssign(const Vector2iPod& val)
{
    x -= val.x;
    y -= val.y;
}

//------------------------------------------------------------------------------
void Vector2iPod::MulAssign(const Vector2iPod& val)
{
    x *= val.x;
    y *= val.y;
}

//------------------------------------------------------------------------------
void Vector2iPod::DivAssign(const Vector2iPod& val)
{
    AE_BASE_DIV_ASSIGN(x, val.x);
    AE_BASE_DIV_ASSIGN(y, val.y);
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator+=(const s32 val)
{
    AddAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator-=(const s32 val)
{
    SubAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator*=(const s32 val)
{
    MulAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator/=(const s32 val)
{
    DivAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator+=(const Vector2iPod& val)
{
    AddAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator-=(const Vector2iPod& val)
{
    SubAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator*=(const Vector2iPod& val)
{
    MulAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPod& Vector2iPod::operator/=(const Vector2iPod& val)
{
    DivAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator+(const s32 val) const
{
    return Add(val);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator-(const s32 val) const
{
    return Sub(val);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator*(const s32 val) const
{
    return Mul(val);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator/(const s32 val) const
{
    return Div(val);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator+(const Vector2iPod& val) const
{
    return Add(val);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator-(const Vector2iPod& val) const
{
    return Sub(val);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator*(const Vector2iPod& val) const
{
    return Mul(val);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator/(const Vector2iPod& val) const
{
    return Div(val);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::operator-() const
{
    return Neg();
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Min(const Vector2iPod& val) const
{
    return Vector2i(Math::Min(x, val.x), Math::Min(y, val.y));
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Max(const Vector2iPod& val) const
{
    return Vector2i(Math::Max(x, val.x), Math::Max(y, val.y));
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Clamp(
    const Vector2iPod& min,
    const Vector2iPod& max) const
{
    return Max(min).Min(max);
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::ClampPositive() const
{
    return Max(Zero());
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::ClampNegative() const
{
    return Min(Zero());
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Abs() const
{
    return Vector2i(Math::AbsS32(x), Math::AbsS32(y));
}

//------------------------------------------------------------------------------
const Vector2iPod Vector2iPod::Neg() const
{
    Vector2i vec(*this);
    vec.MulAssign(-1);
    return vec;
}

//------------------------------------------------------------------------------
bool Vector2iPod::IsPositive() const
{
    return 0 <= x && 0 <= y;
}

//------------------------------------------------------------------------------
bool Vector2iPod::IsZero() const
{
    return x == 0 && y == 0;
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Vector2iPod::ToShortString() const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s",
        S32(x).ToShortString().ReadPtr(),
        S32(y).ToShortString().ReadPtr());
}

//------------------------------------------------------------------------------
Vector2i::Vector2i()
: Vector2iPod(Zero())
{
}

//------------------------------------------------------------------------------
Vector2i::Vector2i(const Vector2iPod& vec)
: Vector2iPod(vec)
{
}

//------------------------------------------------------------------------------
Vector2i::Vector2i(const s32 v)
{
    this->x = v;
    this->y = v;
}

//------------------------------------------------------------------------------
Vector2i::Vector2i(const s32 x, const s32 y)
{
    this->x = x;
    this->y = y;
}

} // namespace ae::base
// EOF
