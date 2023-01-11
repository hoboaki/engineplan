// 文字コード：UTF-8
#include <ae/base/Color4.hpp>

// includes
#include <ae/base/Color4b.hpp>
#include <ae/base/DivideCheck.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/ScalerTypes.hpp>
#include <ae/base/Vector4.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Zero()
{
    return Color4(0, 0, 0, 0);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::One()
{
    return Color4(1, 1, 1, 1);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::UnitR()
{
    return Color4(1, 0, 0, 0);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::UnitG()
{
    return Color4(0, 1, 0, 0);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::UnitB()
{
    return Color4(0, 0, 1, 0);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::UnitA()
{
    return Color4(0, 0, 0, 1);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::ToRRRR() const
{
    return Color4(r, r, r, r);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::ToGGGG() const
{
    return Color4(g, g, g, g);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::ToBBBB() const
{
    return Color4(b, b, b, b);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::ToAAAA() const
{
    return Color4(a, a, a, a);
}

//------------------------------------------------------------------------------
const Color4bPod Color4Pod::ToRGBAb() const
{
    const Color4 tmp =
        ToVector4().Clamp(Vector4::Zero(), Vector4::One()) * 255.0f;
    return Color4b(
        static_cast<u8>(tmp.r),
        static_cast<u8>(tmp.g),
        static_cast<u8>(tmp.b),
        static_cast<u8>(tmp.a));
}

//------------------------------------------------------------------------------
const Vector4Pod Color4Pod::ToVector4() const
{
    return Vector4(r, g, b, a);
}

//------------------------------------------------------------------------------
bool Color4Pod::Equals(const Color4Pod& rHS) const
{
    return Math::IsEqualsF32(r, rHS.r) && Math::IsEqualsF32(g, rHS.g) &&
           Math::IsEqualsF32(b, rHS.b) && Math::IsEqualsF32(a, rHS.a);
}

//------------------------------------------------------------------------------
bool Color4Pod::EqualsStrict(const Color4Pod& rHS) const
{
    return r == rHS.r && g == rHS.g && b == rHS.b && a == rHS.a;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Add(const float val) const
{
    Color4 col(*this);
    col.AddAssign(val);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Sub(const float val) const
{
    Color4 col(*this);
    col.SubAssign(val);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Mul(const float val) const
{
    Color4 col(*this);
    col.MulAssign(val);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Div(const float val) const
{
    Color4 col(*this);
    col.DivAssign(val);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Add(const Color4Pod& val) const
{
    Color4 col(*this);
    col.AddAssign(val);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Sub(const Color4Pod& val) const
{
    Color4 col(*this);
    col.SubAssign(val);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Mul(const Color4Pod& val) const
{
    Color4 col(*this);
    col.MulAssign(val);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Div(const Color4Pod& val) const
{
    Color4 col(*this);
    col.DivAssign(val);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Neg() const
{
    Color4 col(*this);
    col.MulAssign(-1.0f);
    return col;
}

//------------------------------------------------------------------------------
void Color4Pod::AddAssign(const float val)
{
    r += val;
    g += val;
    b += val;
    a += val;
}

//------------------------------------------------------------------------------
void Color4Pod::SubAssign(const float val)
{
    r -= val;
    g -= val;
    b -= val;
    a -= val;
}

//------------------------------------------------------------------------------
void Color4Pod::MulAssign(const float val)
{
    r *= val;
    g *= val;
    b *= val;
    a *= val;
}

//------------------------------------------------------------------------------
void Color4Pod::DivAssign(const float val)
{
    if (val == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    MulAssign(1.0f / val);
}

//------------------------------------------------------------------------------
void Color4Pod::AddAssign(const Color4Pod& val)
{
    r += val.r;
    g += val.g;
    b += val.b;
    a += val.a;
}

//------------------------------------------------------------------------------
void Color4Pod::SubAssign(const Color4Pod& val)
{
    r -= val.r;
    g -= val.g;
    b -= val.b;
    a -= val.a;
}

//------------------------------------------------------------------------------
void Color4Pod::MulAssign(const Color4Pod& val)
{
    r *= val.r;
    g *= val.g;
    b *= val.b;
    a *= val.a;
}

//------------------------------------------------------------------------------
void Color4Pod::DivAssign(const Color4Pod& val)
{
    AE_BASE_DIV_ASSIGN(r, val.r);
    AE_BASE_DIV_ASSIGN(g, val.g);
    AE_BASE_DIV_ASSIGN(b, val.b);
    AE_BASE_DIV_ASSIGN(a, val.a);
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator+=(const float val)
{
    AddAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator-=(const float val)
{
    SubAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator*=(const float val)
{
    MulAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator/=(const float val)
{
    DivAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator+=(const Color4Pod& val)
{
    AddAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator-=(const Color4Pod& val)
{
    SubAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator*=(const Color4Pod& val)
{
    MulAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator/=(const Color4Pod& val)
{
    DivAssign(val);
    return *this;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator+(const float val) const
{
    return Add(val);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator-(const float val) const
{
    return Sub(val);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator*(const float val) const
{
    return Mul(val);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator/(const float val) const
{
    return Div(val);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator+(const Color4Pod& val) const
{
    return Add(val);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator-(const Color4Pod& val) const
{
    return Sub(val);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator*(const Color4Pod& val) const
{
    return Mul(val);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator/(const Color4Pod& val) const
{
    return Div(val);
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Color4Pod::ToShortString() const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s,%s,%s",
        F32(r).ToShortString().ReadPtr(),
        F32(g).ToShortString().ReadPtr(),
        F32(b).ToShortString().ReadPtr(),
        F32(a).ToShortString().ReadPtr());
}

//------------------------------------------------------------------------------
Color4::Color4()
: Color4Pod(Zero())
{
}

//------------------------------------------------------------------------------
Color4::Color4(const Color4Pod& col)
: Color4Pod(col)
{
}

//------------------------------------------------------------------------------
Color4::Color4(const float r, const float g, const float b, const float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

//------------------------------------------------------------------------------
Color4::Color4(const Vector4Pod& vec)
{
    this->r = vec.x;
    this->g = vec.y;
    this->b = vec.z;
    this->a = vec.w;
}

} // namespace ae::base
// EOF
