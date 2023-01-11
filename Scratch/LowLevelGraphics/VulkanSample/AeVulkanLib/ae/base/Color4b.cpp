// 文字コード：UTF-8
#include <ae/base/Color4b.hpp>

// includes
#include <ae/base/Color4.hpp>
#include <ae/base/DivideCheck.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/ScalerTypes.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

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
const Color4bPod Color4bPod::ToRRRR() const
{
    return Color4b(r, r, r, r);
}

//------------------------------------------------------------------------------
const Color4bPod Color4bPod::ToGGGG() const
{
    return Color4b(g, g, g, g);
}

//------------------------------------------------------------------------------
const Color4bPod Color4bPod::ToBBBB() const
{
    return Color4b(b, b, b, b);
}

//------------------------------------------------------------------------------
const Color4bPod Color4bPod::ToAAAA() const
{
    return Color4b(a, a, a, a);
}

//------------------------------------------------------------------------------
const Color4Pod Color4bPod::ToRGBAf() const
{
    const float rate = 1.0f / 255.0f;
    return Color4(r * rate, g * rate, b * rate, a * rate);
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Color4bPod::ToShortString() const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s,%s,%s",
        U8(r).ToShortString().ReadPtr(),
        U8(g).ToShortString().ReadPtr(),
        U8(b).ToShortString().ReadPtr(),
        U8(a).ToShortString().ReadPtr());
}

//------------------------------------------------------------------------------
Color4b::Color4b()
: Color4bPod(Zero())
{
}

//------------------------------------------------------------------------------
Color4b::Color4b(const Color4bPod& col)
: Color4bPod(col)
{
}

//------------------------------------------------------------------------------
Color4b::Color4b(const u8 r, const u8 g, const u8 b, const u8 a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

} // namespace ae::base
// EOF
