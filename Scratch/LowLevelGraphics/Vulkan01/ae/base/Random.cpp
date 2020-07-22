// 文字コード：UTF-8
#include <ae/base/Random.hpp>

#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Random::Random()
: mX(123456789)
, mY(362436069)
, mZ(521288629)
, mW(88675123)
{
}

//------------------------------------------------------------------------------
Random::Random(
    const u32 aX,
    const u32 aY,
    const u32 aZ,
    const u32 aW
    )
: mX(aX)
, mY(aY)
, mZ(aZ)
, mW(aW)
{
}

//------------------------------------------------------------------------------
u32 Random::rand()
{
    u32 t = u32();
    t = (mX ^ (mX << 11));
    mX = mY;
    mY = mZ;
    mZ = mW;
    mW = (mW ^ (mW >> 19)) ^ (t ^ (t >> 8));
    return mW;
}

//------------------------------------------------------------------------------
u32 Random::randU32(const u32 aTerm)
{
    if (aTerm == 0) {
        AE_BASE_ERROR_INVALID_VALUE(aTerm);
        return 0;
    }
    return rand() % aTerm;
}

//------------------------------------------------------------------------------
s32 Random::randS32(const s32 aTerm)
{
    if (aTerm == 0) {
        AE_BASE_ERROR_INVALID_VALUE(aTerm);
        return 0;
    }
    return rand() % aTerm;
}

//------------------------------------------------------------------------------
s32 Random::randS32(const s32 aMin, const s32 aMax)
{
    if (aMin == aMax) {
        return aMin;
    }
    return aMin + randS32(aMax - aMin);
}

//------------------------------------------------------------------------------
f32 Random::randF32N()
{
    return f32(rand() % 0x10000) / f32(0x10000);
}

//------------------------------------------------------------------------------
f32 Random::randF32SN()
{
    return -1.0f + 2.0f * randF32N();
}

//------------------------------------------------------------------------------
unsigned int Random::operator()(const unsigned int aTerm)
{
    return rand() % (aTerm + 1);
}

}} // namespace
// EOF
