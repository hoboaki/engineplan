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
: min_(Vector2i::Zero())
, term_(min_)
{
}

//------------------------------------------------------------------------------
Aabb2i::Aabb2i(const Vector2iPod& aBegin)
: min_(aBegin)
, term_(min_)
{
}

//------------------------------------------------------------------------------
Aabb2i::Aabb2i(
    const Vector2iPod& aBegin,
    const int aWidth,
    const int aHeight
    )
: min_(aBegin)
, term_(
    aBegin.x + reinterpret_cast<const int&>(aWidth),
    aBegin.y + reinterpret_cast<const int&>(aHeight)
    )
{
    AE_BASE_ASSERT_LESS_EQUALS(min_.x, term_.x);
    AE_BASE_ASSERT_LESS_EQUALS(min_.y, term_.y);
}

//------------------------------------------------------------------------------
const Vector2iPod Aabb2i::begin()const
{
    return min_;
}

//------------------------------------------------------------------------------
const Vector2iPod Aabb2i::end()const
{
    return term_;
}

//------------------------------------------------------------------------------
const Vector2iPod Aabb2i::min()const
{
    return min_;
}

//------------------------------------------------------------------------------
const Vector2iPod Aabb2i::term()const
{
    return term_;
}

//------------------------------------------------------------------------------
int Aabb2i::width()const
{
    return int(term_.x - min_.x);
}

//------------------------------------------------------------------------------
int Aabb2i::height()const
{
    return int(term_.y - min_.y);
}

//------------------------------------------------------------------------------
bool Aabb2i::isPositive()const
{
    return 0 <= min_.x
        && 0 <= min_.y;
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::toPositive()const
{
    const Vector2i newMin = min_.max(Vector2i::Zero());
    const Vector2i newTerm = term_.max(Vector2i::Zero());
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
    min_ = min_.min(aAABB.min_);
    term_ = term_.max(aAABB.term_);
}

//------------------------------------------------------------------------------
bool Aabb2i::isIntersects(const Aabb2i& aAABB)const
{
    return min_.x < aAABB.term_.x
        && min_.y < aAABB.term_.y
        && aAABB.min_.x < term_.x
        && aAABB.min_.y < term_.y;
}

//------------------------------------------------------------------------------
bool Aabb2i::isContains(const Vector2iPod& aPos)const
{
    return min_.x <= aPos.x
        && min_.y <= aPos.y
        && aPos.x < term_.x
        && aPos.y < term_.y;
}

//------------------------------------------------------------------------------
bool Aabb2i::isContains(const Aabb2i& aAABB)const
{
    return min_.x <= aAABB.min_.x
        && min_.y <= aAABB.min_.y
        && aAABB.term_.x <= term_.x
        && aAABB.term_.y <= term_.y;
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
    min_ += aTrans;
    term_ += aTrans;
}

//------------------------------------------------------------------------------
void Aabb2i::subAssign(const Vector2iPod& aTrans)
{
    min_ -= aTrans;
    term_ -= aTrans;
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
