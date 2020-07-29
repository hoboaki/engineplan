// 文字コード：UTF-8
#include <ae/base/Random.hpp>

#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Random::Random()
: x_(123456789)
, y_(362436069)
, z_(521288629)
, w_(88675123)
{
}

//------------------------------------------------------------------------------
Random::Random(
    const u32 aX,
    const u32 aY,
    const u32 aZ,
    const u32 aW
    )
: x_(aX)
, y_(aY)
, z_(aZ)
, w_(aW)
{
}

//------------------------------------------------------------------------------
u32 Random::Rand()
{
    u32 t = u32();
    t = (x_ ^ (x_ << 11));
    x_ = y_;
    y_ = z_;
    z_ = w_;
    w_ = (w_ ^ (w_ >> 19)) ^ (t ^ (t >> 8));
    return w_;
}

//------------------------------------------------------------------------------
u32 Random::RandU32(const u32 aTerm)
{
    if (aTerm == 0) {
        AE_BASE_ERROR_INVALID_VALUE(aTerm);
        return 0;
    }
    return Rand() % aTerm;
}

//------------------------------------------------------------------------------
s32 Random::RandS32(const s32 aTerm)
{
    if (aTerm == 0) {
        AE_BASE_ERROR_INVALID_VALUE(aTerm);
        return 0;
    }
    return Rand() % aTerm;
}

//------------------------------------------------------------------------------
s32 Random::RandS32(const s32 aMin, const s32 aMax)
{
    if (aMin == aMax) {
        return aMin;
    }
    return aMin + RandS32(aMax - aMin);
}

//------------------------------------------------------------------------------
f32 Random::RandF32N()
{
    return f32(rand() % 0x10000) / f32(0x10000);
}

//------------------------------------------------------------------------------
f32 Random::RandF32SN()
{
    return -1.0f + 2.0f * RandF32N();
}

//------------------------------------------------------------------------------
unsigned int Random::operator()(const unsigned int aTerm)
{
    return Rand() % (aTerm + 1);
}

}} // namespace
// EOF
