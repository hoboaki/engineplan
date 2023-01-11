// 文字コード：UTF-8
#include <ae/base/Random.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
Random::Random()
: x_(123456789)
, y_(362436069)
, z_(521288629)
, w_(88675123)
{
}

//------------------------------------------------------------------------------
Random::Random(const u32 x, const u32 y, const u32 z, const u32 w)
: x_(x)
, y_(y)
, z_(z)
, w_(w)
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
u32 Random::RandU32(const u32 term)
{
    if (term == 0) {
        AE_BASE_ERROR_INVALID_VALUE(term);
        return 0;
    }
    return Rand() % term;
}

//------------------------------------------------------------------------------
s32 Random::RandS32(const s32 term)
{
    if (term == 0) {
        AE_BASE_ERROR_INVALID_VALUE(term);
        return 0;
    }
    return Rand() % term;
}

//------------------------------------------------------------------------------
s32 Random::RandS32(const s32 min, const s32 max)
{
    if (min == max) {
        return min;
    }
    return min + RandS32(max - min);
}

//------------------------------------------------------------------------------
f32 Random::RandF32N()
{
    return f32(Rand() % 0x10000) / f32(0x10000);
}

//------------------------------------------------------------------------------
f32 Random::RandF32SN()
{
    return -1.0f + 2.0f * RandF32N();
}

//------------------------------------------------------------------------------
unsigned int Random::operator()(const unsigned int term)
{
    return Rand() % (term + 1);
}

} // namespace ae::base
// EOF
