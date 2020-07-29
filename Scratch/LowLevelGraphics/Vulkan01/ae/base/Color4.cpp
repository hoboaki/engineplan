// 文字コード：UTF-8
#include <ae/base/Color4.hpp>

#include <ae/base/Color4b.hpp>
#include <ae/base/DivideCheck.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/ScalerTypes.hpp>
#include <ae/base/Vector4.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

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
const Color4Pod Color4Pod::ToRRRR()const
{
    return Color4(r, r, r, r);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::ToGGGG()const
{
    return Color4(g, g, g, g);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::ToBBBB()const
{
    return Color4(b, b, b, b);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::ToAAAA()const
{
    return Color4(a, a, a, a);
}

//------------------------------------------------------------------------------
const Color4bPod Color4Pod::ToRGBAb()const
{
    const Color4 tmp = ToVector4().Clamp(Vector4::Zero(), Vector4::One()) * 255.0f;
    return Color4b(
        static_cast<u8>(tmp.r),
        static_cast<u8>(tmp.g),
        static_cast<u8>(tmp.b),
        static_cast<u8>(tmp.a)
        );
}

//------------------------------------------------------------------------------
const Vector4Pod Color4Pod::ToVector4()const
{
    return Vector4(r, g, b, a);
}

//------------------------------------------------------------------------------
bool Color4Pod::Equals(const Color4Pod& aRHS)const
{
    return Math::IsEqualsF32(r, aRHS.r)
        && Math::IsEqualsF32(g, aRHS.g)
        && Math::IsEqualsF32(b, aRHS.b)
        && Math::IsEqualsF32(a, aRHS.a);
}

//------------------------------------------------------------------------------
bool Color4Pod::EqualsStrict(const Color4Pod& aRHS)const
{
    return r == aRHS.r
        && g == aRHS.g
        && b == aRHS.b
        && a == aRHS.a;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Add(const float aVal)const
{
    Color4 col(*this);
    col.AddAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Sub(const float aVal)const
{
    Color4 col(*this);
    col.SubAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Mul(const float aVal)const
{
    Color4 col(*this);
    col.MulAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Div(const float aVal)const
{
    Color4 col(*this);
    col.DivAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Add(const Color4Pod& aVal)const
{
    Color4 col(*this);
    col.AddAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Sub(const Color4Pod& aVal)const
{
    Color4 col(*this);
    col.SubAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Mul(const Color4Pod& aVal)const
{
    Color4 col(*this);
    col.MulAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Div(const Color4Pod& aVal)const
{
    Color4 col(*this);
    col.DivAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::Neg()const
{
    Color4 col(*this);
    col.MulAssign(-1.0f);
    return col;
}

//------------------------------------------------------------------------------
void Color4Pod::AddAssign(const float aVal)
{
    r += aVal;
    g += aVal;
    b += aVal;
    a += aVal;
}

//------------------------------------------------------------------------------
void Color4Pod::SubAssign(const float aVal)
{
    r -= aVal;
    g -= aVal;
    b -= aVal;
    a -= aVal;
}

//------------------------------------------------------------------------------
void Color4Pod::MulAssign(const float aVal)
{
    r *= aVal;
    g *= aVal;
    b *= aVal;
    a *= aVal;
}

//------------------------------------------------------------------------------
void Color4Pod::DivAssign(const float aVal)
{
    if (aVal == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    MulAssign(1.0f / aVal);
}

//------------------------------------------------------------------------------
void Color4Pod::AddAssign(const Color4Pod& aVal)
{
    r += aVal.r;
    g += aVal.g;
    b += aVal.b;
    a += aVal.a;
}

//------------------------------------------------------------------------------
void Color4Pod::SubAssign(const Color4Pod& aVal)
{
    r -= aVal.r;
    g -= aVal.g;
    b -= aVal.b;
    a -= aVal.a;
}

//------------------------------------------------------------------------------
void Color4Pod::MulAssign(const Color4Pod& aVal)
{
    r *= aVal.r;
    g *= aVal.g;
    b *= aVal.b;
    a *= aVal.a;
}

//------------------------------------------------------------------------------
void Color4Pod::DivAssign(const Color4Pod& aVal)
{
    AE_BASE_DIV_ASSIGN(r, aVal.r);
    AE_BASE_DIV_ASSIGN(g, aVal.g);
    AE_BASE_DIV_ASSIGN(b, aVal.b);
    AE_BASE_DIV_ASSIGN(a, aVal.a);
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator+=(const float aVal)
{
    AddAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator-=(const float aVal)
{
    SubAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator*=(const float aVal)
{
    MulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator/=(const float aVal)
{
    DivAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator+=(const Color4Pod& aVal)
{
    AddAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator-=(const Color4Pod& aVal)
{
    SubAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator*=(const Color4Pod& aVal)
{
    MulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator/=(const Color4Pod& aVal)
{
    DivAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator+(const float aVal)const
{
    return Add(aVal);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator-(const float aVal)const
{
    return Sub(aVal);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator*(const float aVal)const
{
    return Mul(aVal);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator/(const float aVal)const
{
    return Div(aVal);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator+(const Color4Pod& aVal)const
{
    return Add(aVal);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator-(const Color4Pod& aVal)const
{
    return Sub(aVal);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator*(const Color4Pod& aVal)const
{
    return Mul(aVal);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator/(const Color4Pod& aVal)const
{
    return Div(aVal);
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Color4Pod::ToShortString()const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s,%s,%s",
        F32(r).ToShortString().ReadPtr(),
        F32(g).ToShortString().ReadPtr(),
        F32(b).ToShortString().ReadPtr(),
        F32(a).ToShortString().ReadPtr()
        );
}

//------------------------------------------------------------------------------
Color4::Color4()
: Color4Pod(Zero())
{
}

//------------------------------------------------------------------------------
Color4::Color4(const Color4Pod& aCol)
: Color4Pod(aCol)
{
}

//------------------------------------------------------------------------------
Color4::Color4(const float aR, const float aG, const float aB, const float aA)
{
    r = aR;
    g = aG;
    b = aB;
    a = aA;
}

//------------------------------------------------------------------------------
Color4::Color4(const Vector4Pod& aVec)
{
    r = aVec.x;
    g = aVec.y;
    b = aVec.z;
    a = aVec.w;
}

}} // namespace
// EOF
