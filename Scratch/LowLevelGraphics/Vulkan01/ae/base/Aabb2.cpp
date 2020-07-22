// 文字コード：UTF-8
#include <ae/base/Aabb2.hpp>

#include <ae/base/Aabb2i.hpp>
#include <ae/base/Math.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Aabb2::Aabb2()
: mMin()
, mMax()
{
}

//------------------------------------------------------------------------------
Aabb2::Aabb2(const Vector2Pod& aPos)
: mMin(aPos)
, mMax(aPos)
{
}

//------------------------------------------------------------------------------
Aabb2::Aabb2(
    const Vector2Pod& aPos1,
    const Vector2Pod& aPos2
    )
: mMin(aPos1.min(aPos2))
, mMax(aPos1.max(aPos2))
{
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::min()const
{
    return mMin;
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::max()const
{
    return mMax;
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::center()const
{
    return (mMin + mMax) * 0.5f;
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::posLB()const
{
    return Vector2(mMin.x, mMin.y);
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::posRB()const
{
    return Vector2(mMax.x, mMin.y);
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::posLT()const
{
    return Vector2(mMin.x, mMax.y);
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::posRT()const
{
    return Vector2(mMax.x, mMax.y);
}

//------------------------------------------------------------------------------
float Aabb2::left()const
{
    return mMin.x;
}

//------------------------------------------------------------------------------
float Aabb2::right()const
{
    return mMax.x;
}

//------------------------------------------------------------------------------
float Aabb2::bottom()const
{
    return mMin.y;
}

//------------------------------------------------------------------------------
float Aabb2::top()const
{
    return mMax.y;
}

//------------------------------------------------------------------------------
float Aabb2::width()const
{
    return mMax.x - mMin.x;
}

//------------------------------------------------------------------------------
float Aabb2::height()const
{
    return mMax.y - mMin.y;
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::size()const
{
    return Vector2(width(), height());
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::halfSize()const
{
    return size() * 0.5f;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::merge(const Vector2Pod& aPos)const
{
    Aabb2 aabb = *this;
    aabb.mergeAssign(aPos);
    return aabb;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::merge(const Aabb2& aAABB)const
{
    Aabb2 aabb = *this;
    aabb.mergeAssign(aAABB);
    return aabb;
}

//------------------------------------------------------------------------------
void Aabb2::mergeAssign(const Vector2Pod& aPos)
{
    mMin = mMin.min(aPos);
    mMax = mMax.max(aPos);
}

//------------------------------------------------------------------------------
void Aabb2::mergeAssign(const Aabb2& aAABB)
{
    mMin = mMin.min(aAABB.mMin);
    mMax = mMax.max(aAABB.mMax);
}

//------------------------------------------------------------------------------
bool Aabb2::isIntersects(const Aabb2& aAABB)const
{
    return mMin.x <= aAABB.mMax.x
        && mMin.y <= aAABB.mMax.y
        && aAABB.mMin.x <= mMax.x
        && aAABB.mMin.y <= mMax.y;
}

//------------------------------------------------------------------------------
bool Aabb2::isContains(const Vector2Pod& aPos)const
{
    return mMin.x <= aPos.x
        && mMin.y <= aPos.y
        && aPos.x <= mMax.x
        && aPos.y <= mMax.y;
}

//------------------------------------------------------------------------------
bool Aabb2::isContains(const Aabb2& aAABB)const
{
    return isContains(aAABB.mMin)
        && isContains(aAABB.mMax);
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::add(const Vector2Pod& aTrans)const
{
    Aabb2 aabb = *this;
    aabb += aTrans;
    return aabb;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::sub(const Vector2Pod& aTrans)const
{
    Aabb2 aabb = *this;
    aabb -= aTrans;
    return aabb;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::add(const Aabb2& aAABB)const
{
    Aabb2 aabb = *this;
    aabb += aAABB;
    return aabb;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::sub(const Aabb2& aAABB)const
{
    Aabb2 aabb = *this;
    aabb -= aAABB;
    return aabb;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::mul(const float aScale)const
{
    Aabb2 aabb = *this;
    aabb *= aScale;
    return aabb;
}

//------------------------------------------------------------------------------
void Aabb2::addAssign(const Vector2Pod& aTrans)
{
    mMin += aTrans;
    mMax += aTrans;
}

//------------------------------------------------------------------------------
void Aabb2::subAssign(const Vector2Pod& aTrans)
{
    mMin -= aTrans;
    mMax -= aTrans;
}

//------------------------------------------------------------------------------
void Aabb2::addAssign(const Aabb2& aAABB)
{
    mMin += aAABB.mMin;
    mMax += aAABB.mMax;
}

//------------------------------------------------------------------------------
void Aabb2::subAssign(const Aabb2& aAABB)
{
    mMin -= aAABB.mMin;
    mMax -= aAABB.mMax;
}

//------------------------------------------------------------------------------
void Aabb2::mulAssign(const float aScale)
{
    mMin *= aScale;
    mMax *= aScale;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::operator+(const Vector2Pod& aTrans)const
{
    return add(aTrans);
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::operator-(const Vector2Pod& aTrans)const
{
    return sub(aTrans);
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::operator+(const Aabb2& aAABB)const
{
    return add(aAABB);
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::operator-(const Aabb2& aAABB)const
{
    return sub(aAABB);
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::operator*(const float aScale)const
{
    return mul(aScale);
}

//------------------------------------------------------------------------------
Aabb2& Aabb2::operator+=(const Vector2Pod& aTrans)
{
    addAssign(aTrans);
    return *this;
}

//------------------------------------------------------------------------------
Aabb2& Aabb2::operator-=(const Vector2Pod& aTrans)
{
    subAssign(aTrans);
    return *this;
}

//------------------------------------------------------------------------------
Aabb2& Aabb2::operator+=(const Aabb2& aAABB)
{
    addAssign(aAABB);
    return *this;
}

//------------------------------------------------------------------------------
Aabb2& Aabb2::operator-=(const Aabb2& aAABB)
{
    subAssign(aAABB);
    return *this;
}

//------------------------------------------------------------------------------
Aabb2& Aabb2::operator*=(const float aScale)
{
    mulAssign(aScale);
    return *this;
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2::toAABB2i()const
{
    const Vector2i newMin(
        int(Math::FloorF32(mMin.x)),
        int(Math::FloorF32(mMin.y))
        );
    const Vector2i newTerm(
        int(Math::CeilF32(mMax.x)),
        int(Math::CeilF32(mMax.y))
        );
    return Aabb2i(
        newMin,
        uint(newTerm.x - newMin.x),
        uint(newTerm.y - newMin.y)
        );
}

}} // namespace
// EOF
