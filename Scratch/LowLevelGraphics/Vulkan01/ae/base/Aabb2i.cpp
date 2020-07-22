// 文字コード：UTF-8
#include <ae/base/Aabb2i.hpp>

#include <ae/base/Aabb2.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::Largest()
{
    return Aabb2i(Vector2iPod::Min(), 0xFFFFFFFF, 0xFFFFFFFF);
}

//------------------------------------------------------------------------------
Aabb2i::Aabb2i()
: mMin(Vector2i::Zero())
, mTerm(mMin)
{
}

//------------------------------------------------------------------------------
Aabb2i::Aabb2i(const Vector2iPod& aBegin)
: mMin(aBegin)
, mTerm(mMin)
{
}

//------------------------------------------------------------------------------
Aabb2i::Aabb2i(
    const Vector2iPod& aBegin,
    const int aWidth,
    const int aHeight
    )
: mMin(aBegin)
, mTerm(
    aBegin.x + reinterpret_cast<const int&>(aWidth),
    aBegin.y + reinterpret_cast<const int&>(aHeight)
    )
{
    AE_BASE_ASSERT_LESS_EQUALS(mMin.x, mTerm.x);
    AE_BASE_ASSERT_LESS_EQUALS(mMin.y, mTerm.y);
}

//------------------------------------------------------------------------------
const Vector2iPod Aabb2i::begin()const
{
    return mMin;
}

//------------------------------------------------------------------------------
const Vector2iPod Aabb2i::end()const
{
    return mTerm;
}

//------------------------------------------------------------------------------
const Vector2iPod Aabb2i::min()const
{
    return mMin;
}

//------------------------------------------------------------------------------
const Vector2iPod Aabb2i::term()const
{
    return mTerm;
}

//------------------------------------------------------------------------------
int Aabb2i::width()const
{
    return int(mTerm.x - mMin.x);
}

//------------------------------------------------------------------------------
int Aabb2i::height()const
{
    return int(mTerm.y - mMin.y);
}

//------------------------------------------------------------------------------
bool Aabb2i::isPositive()const
{
    return 0 <= mMin.x
        && 0 <= mMin.y;
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::toPositive()const
{
    const Vector2i newMin = mMin.max(Vector2i::Zero());
    const Vector2i newTerm = mTerm.max(Vector2i::Zero());
    const Vector2i newSize = newTerm - newMin;
    return Aabb2i(
        newMin,
        uint(newSize.x),
        uint(newSize.y)
        );
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::merge(const Aabb2i& aAABB)const
{
    Aabb2i aabb(*this);
    aabb.mergeAssign(aAABB);
    return aabb;
}

//------------------------------------------------------------------------------
void Aabb2i::mergeAssign(const Aabb2i& aAABB)
{
    mMin = mMin.min(aAABB.mMin);
    mTerm = mTerm.max(aAABB.mTerm);
}

//------------------------------------------------------------------------------
bool Aabb2i::isIntersects(const Aabb2i& aAABB)const
{
    return mMin.x < aAABB.mTerm.x
        && mMin.y < aAABB.mTerm.y
        && aAABB.mMin.x < mTerm.x
        && aAABB.mMin.y < mTerm.y;
}

//------------------------------------------------------------------------------
bool Aabb2i::isContains(const Vector2iPod& aPos)const
{
    return mMin.x <= aPos.x
        && mMin.y <= aPos.y
        && aPos.x < mTerm.x
        && aPos.y < mTerm.y;
}

//------------------------------------------------------------------------------
bool Aabb2i::isContains(const Aabb2i& aAABB)const
{
    return mMin.x <= aAABB.mMin.x
        && mMin.y <= aAABB.mMin.y
        && aAABB.mTerm.x <= mTerm.x
        && aAABB.mTerm.y <= mTerm.y;
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::add(const Vector2iPod& aTrans)const
{
    Aabb2i aabb = *this;
    aabb.addAssign(aTrans);
    return aabb;
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::sub(const Vector2iPod& aTrans)const
{
    Aabb2i aabb = *this;
    aabb.subAssign(aTrans);
    return aabb;
}

//------------------------------------------------------------------------------
void Aabb2i::addAssign(const Vector2iPod& aTrans)
{
    mMin += aTrans;
    mTerm += aTrans;
}

//------------------------------------------------------------------------------
void Aabb2i::subAssign(const Vector2iPod& aTrans)
{
    mMin -= aTrans;
    mTerm -= aTrans;
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::operator+(const Vector2iPod& aTrans)const
{
    return add(aTrans);
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::operator-(const Vector2iPod& aTrans)const
{
    return sub(aTrans);
}

//------------------------------------------------------------------------------
Aabb2i& Aabb2i::operator+=(const Vector2iPod& aTrans)
{
    addAssign(aTrans);
    return *this;
}

//------------------------------------------------------------------------------
Aabb2i& Aabb2i::operator-=(const Vector2iPod& aTrans)
{
    subAssign(aTrans);
    return *this;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2i::toAABB2f()const
{
    return Aabb2(
        min().toXYf(),
        term().toXYf()
        );
}

}} // namespace
// EOF
