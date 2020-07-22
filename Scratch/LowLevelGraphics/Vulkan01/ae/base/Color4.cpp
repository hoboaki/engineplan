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
const Color4Pod Color4Pod::toRRRR()const
{
    return Color4(r, r, r, r);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::toGGGG()const
{
    return Color4(g, g, g, g);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::toBBBB()const
{
    return Color4(b, b, b, b);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::toAAAA()const
{
    return Color4(a, a, a, a);
}

//------------------------------------------------------------------------------
const Color4bPod Color4Pod::toRGBAb()const
{
    const Color4 tmp = toVector4().clamp(Vector4::Zero(), Vector4::One()) * 255.0f;
    return Color4b(
        static_cast<u8>(tmp.r),
        static_cast<u8>(tmp.g),
        static_cast<u8>(tmp.b),
        static_cast<u8>(tmp.a)
        );
}

//------------------------------------------------------------------------------
const Vector4Pod Color4Pod::toVector4()const
{
    return Vector4(r, g, b, a);
}

//------------------------------------------------------------------------------
bool Color4Pod::equals(const Color4Pod& aRHS)const
{
    return Math::IsEqualsF32(r, aRHS.r)
        && Math::IsEqualsF32(g, aRHS.g)
        && Math::IsEqualsF32(b, aRHS.b)
        && Math::IsEqualsF32(a, aRHS.a);
}

//------------------------------------------------------------------------------
bool Color4Pod::equalsStrict(const Color4Pod& aRHS)const
{
    return r == aRHS.r
        && g == aRHS.g
        && b == aRHS.b
        && a == aRHS.a;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::add(const float aVal)const
{
    Color4 col(*this);
    col.addAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::sub(const float aVal)const
{
    Color4 col(*this);
    col.subAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::mul(const float aVal)const
{
    Color4 col(*this);
    col.mulAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::div(const float aVal)const
{
    Color4 col(*this);
    col.divAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::add(const Color4Pod& aVal)const
{
    Color4 col(*this);
    col.addAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::sub(const Color4Pod& aVal)const
{
    Color4 col(*this);
    col.subAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::mul(const Color4Pod& aVal)const
{
    Color4 col(*this);
    col.mulAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::div(const Color4Pod& aVal)const
{
    Color4 col(*this);
    col.divAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::neg()const
{
    Color4 col(*this);
    col.mulAssign(-1.0f);
    return col;
}

//------------------------------------------------------------------------------
void Color4Pod::addAssign(const float aVal)
{
    r += aVal;
    g += aVal;
    b += aVal;
    a += aVal;
}

//------------------------------------------------------------------------------
void Color4Pod::subAssign(const float aVal)
{
    r -= aVal;
    g -= aVal;
    b -= aVal;
    a -= aVal;
}

//------------------------------------------------------------------------------
void Color4Pod::mulAssign(const float aVal)
{
    r *= aVal;
    g *= aVal;
    b *= aVal;
    a *= aVal;
}

//------------------------------------------------------------------------------
void Color4Pod::divAssign(const float aVal)
{
    if (aVal == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    mulAssign(1.0f / aVal);
}

//------------------------------------------------------------------------------
void Color4Pod::addAssign(const Color4Pod& aVal)
{
    r += aVal.r;
    g += aVal.g;
    b += aVal.b;
    a += aVal.a;
}

//------------------------------------------------------------------------------
void Color4Pod::subAssign(const Color4Pod& aVal)
{
    r -= aVal.r;
    g -= aVal.g;
    b -= aVal.b;
    a -= aVal.a;
}

//------------------------------------------------------------------------------
void Color4Pod::mulAssign(const Color4Pod& aVal)
{
    r *= aVal.r;
    g *= aVal.g;
    b *= aVal.b;
    a *= aVal.a;
}

//------------------------------------------------------------------------------
void Color4Pod::divAssign(const Color4Pod& aVal)
{
    AE_BASE_DIV_ASSIGN(r, aVal.r);
    AE_BASE_DIV_ASSIGN(g, aVal.g);
    AE_BASE_DIV_ASSIGN(b, aVal.b);
    AE_BASE_DIV_ASSIGN(a, aVal.a);
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator+=(const float aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator-=(const float aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator*=(const float aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator/=(const float aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator+=(const Color4Pod& aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator-=(const Color4Pod& aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator*=(const Color4Pod& aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4Pod& Color4Pod::operator/=(const Color4Pod& aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator+(const float aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator-(const float aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator*(const float aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator/(const float aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator+(const Color4Pod& aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator-(const Color4Pod& aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator*(const Color4Pod& aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Color4Pod Color4Pod::operator/(const Color4Pod& aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Color4Pod::toShortString()const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s,%s,%s",
        F32(r).toShortString().readPtr(),
        F32(g).toShortString().readPtr(),
        F32(b).toShortString().readPtr(),
        F32(a).toShortString().readPtr()
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
