// 文字コード：UTF-8
#include <ae/base/Color4b.hpp>

#include <ae/base/Color4.hpp>
#include <ae/base/DivideCheck.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/ScalerTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
const Color4bPod Color4bPod::Zero()
{
    return Color4b(0, 0, 0, 0);
}

//------------------------------------------------------------------------------
const Color4bPod Color4bPod::One()
{
    return Color4b(0xFF, 0xFF, 0xFF, 0xFF);
}

//------------------------------------------------------------------------------
const Color4bPod Color4bPod::UnitR()
{
    return Color4b(0xFF, 0, 0, 0);
}

//------------------------------------------------------------------------------
const Color4bPod Color4bPod::UnitG()
{
    return Color4b(0, 0xFF, 0, 0);
}

//------------------------------------------------------------------------------
const Color4bPod Color4bPod::UnitB()
{
    return Color4b(0, 0, 0xFF, 0);
}

//------------------------------------------------------------------------------
const Color4bPod Color4bPod::UnitA()
{
    return Color4b(0, 0, 0, 0xFF);
}

//------------------------------------------------------------------------------
const Color4bPod Color4bPod::toRRRR()const
{
    return Color4b(r, r, r, r);
}

//------------------------------------------------------------------------------
const Color4bPod Color4bPod::toGGGG()const
{
    return Color4b(g, g, g, g);
}

//------------------------------------------------------------------------------
const Color4bPod Color4bPod::toBBBB()const
{
    return Color4b(b, b, b, b);
}

//------------------------------------------------------------------------------
const Color4bPod Color4bPod::toAAAA()const
{
    return Color4b(a, a, a, a);
}

//------------------------------------------------------------------------------
const Color4Pod Color4bPod::toRGBAf()const
{
    const float rate = 1.0f / 255.0f;
    return Color4(r * rate, g * rate, b * rate, a * rate);
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Color4bPod::toShortString()const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s,%s,%s",
        U8(r).toShortString().readPtr(),
        U8(g).toShortString().readPtr(),
        U8(b).toShortString().readPtr(),
        U8(a).toShortString().readPtr()
        );
}

//------------------------------------------------------------------------------
Color4b::Color4b()
: Color4bPod(Zero())
{
}

//------------------------------------------------------------------------------
Color4b::Color4b(const Color4bPod& aCol)
: Color4bPod(aCol)
{
}

//------------------------------------------------------------------------------
Color4b::Color4b(const u8 aR, const u8 aG, const u8 aB, const u8 aA)
{
    r = aR;
    g = aG;
    b = aB;
    a = aA;
}

}} // namespace
// EOF
