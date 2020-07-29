// 文字コード：UTF-8
#include <ae/base/Aabb2.hpp>

#include <ae/base/Aabb2i.hpp>
#include <ae/base/Math.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Aabb2::Aabb2()
: min_()
, max_()
{
}

//------------------------------------------------------------------------------
Aabb2::Aabb2(const Vector2Pod& aPos)
: min_(aPos)
, max_(aPos)
{
}

//------------------------------------------------------------------------------
Aabb2::Aabb2(
    const Vector2Pod& aPos1,
    const Vector2Pod& aPos2
    )
: min_(aPos1.min(aPos2))
, max_(aPos1.max(aPos2))
{
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::min()const
{
    return min_;
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::max()const
{
    return max_;
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::center()const
{
    return (min_ + max_) * 0.5f;
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::posLB()const
{
    return Vector2(min_.x, min_.y);
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::posRB()const
{
    return Vector2(max_.x, min_.y);
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::posLT()const
{
    return Vector2(min_.x, max_.y);
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::posRT()const
{
    return Vector2(max_.x, max_.y);
}

//------------------------------------------------------------------------------
float Aabb2::left()const
{
    return min_.x;
}

//------------------------------------------------------------------------------
float Aabb2::right()const
{
    return max_.x;
}

//------------------------------------------------------------------------------
float Aabb2::bottom()const
{
    return min_.y;
}

//------------------------------------------------------------------------------
float Aabb2::top()const
{
    return max_.y;
}

//------------------------------------------------------------------------------
float Aabb2::width()const
{
    return max_.x - min_.x;
}

//------------------------------------------------------------------------------
float Aabb2::height()const
{
    return max_.y - min_.y;
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
    min_ = min_.min(aPos);
    max_ = max_.max(aPos);
}

//------------------------------------------------------------------------------
void Aabb2::mergeAssign(const Aabb2& aAABB)
{
    min_ = min_.min(aAABB.min_);
    max_ = max_.max(aAABB.max_);
}

//------------------------------------------------------------------------------
bool Aabb2::isIntersects(const Aabb2& aAABB)const
{
    return min_.x <= aAABB.max_.x
        && min_.y <= aAABB.max_.y
        && aAABB.min_.x <= max_.x
        && aAABB.min_.y <= max_.y;
}

//------------------------------------------------------------------------------
bool Aabb2::isContains(const Vector2Pod& aPos)const
{
    return min_.x <= aPos.x
        && min_.y <= aPos.y
        && aPos.x <= max_.x
        && aPos.y <= max_.y;
}

//------------------------------------------------------------------------------
bool Aabb2::isContains(const Aabb2& aAABB)const
{
    return isContains(aAABB.min_)
        && isContains(aAABB.max_);
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
    min_ += aTrans;
    max_ += aTrans;
}

//------------------------------------------------------------------------------
void Aabb2::subAssign(const Vector2Pod& aTrans)
{
    min_ -= aTrans;
    max_ -= aTrans;
}

//------------------------------------------------------------------------------
void Aabb2::addAssign(const Aabb2& aAABB)
{
    min_ += aAABB.min_;
    max_ += aAABB.max_;
}

//------------------------------------------------------------------------------
void Aabb2::subAssign(const Aabb2& aAABB)
{
    min_ -= aAABB.min_;
    max_ -= aAABB.max_;
}

//------------------------------------------------------------------------------
void Aabb2::mulAssign(const float aScale)
{
    min_ *= aScale;
    max_ *= aScale;
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
        int(Math::FloorF32(min_.x)),
        int(Math::FloorF32(min_.y))
        );
    const Vector2i newTerm(
        int(Math::CeilF32(max_.x)),
        int(Math::CeilF32(max_.y))
        );
    return Aabb2i(
        newMin,
        uint(newTerm.x - newMin.x),
        uint(newTerm.y - newMin.y)
        );
}

}} // namespace
// EOF
