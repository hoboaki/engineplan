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
const Vector2iPod Aabb2i::Begin()const
{
    return min_;
}

//------------------------------------------------------------------------------
const Vector2iPod Aabb2i::End()const
{
    return term_;
}

//------------------------------------------------------------------------------
const Vector2iPod Aabb2i::Min()const
{
    return min_;
}

//------------------------------------------------------------------------------
const Vector2iPod Aabb2i::Term()const
{
    return term_;
}

//------------------------------------------------------------------------------
int Aabb2i::Width()const
{
    return int(term_.x - min_.x);
}

//------------------------------------------------------------------------------
int Aabb2i::Height()const
{
    return int(term_.y - min_.y);
}

//------------------------------------------------------------------------------
bool Aabb2i::IsPositive()const
{
    return 0 <= min_.x
        && 0 <= min_.y;
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::ToPositive()const
{
    const Vector2i newMin = min_.Max(Vector2i::Zero());
    const Vector2i newTerm = term_.Max(Vector2i::Zero());
    const Vector2i newSize = newTerm - newMin;
    return Aabb2i(
        newMin,
        uint(newSize.x),
        uint(newSize.y)
        );
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::Merge(const Aabb2i& aAABB)const
{
    Aabb2i aabb(*this);
    aabb.MergeAssign(aAABB);
    return aabb;
}

//------------------------------------------------------------------------------
void Aabb2i::MergeAssign(const Aabb2i& aAABB)
{
    min_ = min_.Min(aAABB.min_);
    term_ = term_.Max(aAABB.term_);
}

//------------------------------------------------------------------------------
bool Aabb2i::IsIntersects(const Aabb2i& aAABB)const
{
    return min_.x < aAABB.term_.x
        && min_.y < aAABB.term_.y
        && aAABB.min_.x < term_.x
        && aAABB.min_.y < term_.y;
}

//------------------------------------------------------------------------------
bool Aabb2i::IsContains(const Vector2iPod& aPos)const
{
    return min_.x <= aPos.x
        && min_.y <= aPos.y
        && aPos.x < term_.x
        && aPos.y < term_.y;
}

//------------------------------------------------------------------------------
bool Aabb2i::IsContains(const Aabb2i& aAABB)const
{
    return min_.x <= aAABB.min_.x
        && min_.y <= aAABB.min_.y
        && aAABB.term_.x <= term_.x
        && aAABB.term_.y <= term_.y;
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::Add(const Vector2iPod& aTrans)const
{
    Aabb2i aabb = *this;
    aabb.AddAssign(aTrans);
    return aabb;
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::Sub(const Vector2iPod& aTrans)const
{
    Aabb2i aabb = *this;
    aabb.SubAssign(aTrans);
    return aabb;
}

//------------------------------------------------------------------------------
void Aabb2i::AddAssign(const Vector2iPod& aTrans)
{
    min_ += aTrans;
    term_ += aTrans;
}

//------------------------------------------------------------------------------
void Aabb2i::SubAssign(const Vector2iPod& aTrans)
{
    min_ -= aTrans;
    term_ -= aTrans;
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::operator+(const Vector2iPod& aTrans)const
{
    return Add(aTrans);
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::operator-(const Vector2iPod& aTrans)const
{
    return Sub(aTrans);
}

//------------------------------------------------------------------------------
Aabb2i& Aabb2i::operator+=(const Vector2iPod& aTrans)
{
    AddAssign(aTrans);
    return *this;
}

//------------------------------------------------------------------------------
Aabb2i& Aabb2i::operator-=(const Vector2iPod& aTrans)
{
    SubAssign(aTrans);
    return *this;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2i::ToAABB2f()const
{
    return Aabb2(
        Min().ToXYf(),
        Term().ToXYf()
        );
}

}} // namespace
// EOF
