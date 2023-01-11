// 文字コード：UTF-8
#include <ae/base/Aabb2i.hpp>

// includes
#include <ae/base/Aabb2.hpp>
#include <ae/base/Extent2i.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

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
Aabb2i::Aabb2i(const Vector2iPod& begin)
: min_(begin)
, term_(min_)
{
}

//------------------------------------------------------------------------------
Aabb2i::Aabb2i(const Vector2iPod& begin, const int width, const int height)
: min_(begin)
, term_(
      begin.x + reinterpret_cast<const int&>(width),
      begin.y + reinterpret_cast<const int&>(height))
{
    AE_BASE_ASSERT_LESS_EQUALS(min_.x, term_.x);
    AE_BASE_ASSERT_LESS_EQUALS(min_.y, term_.y);
}

//------------------------------------------------------------------------------
Aabb2i::Aabb2i(const Vector2iPod& begin, const Extent2iPod& extent)
: Aabb2i(begin, extent.width, extent.height)
{
}

//------------------------------------------------------------------------------
const Vector2iPod Aabb2i::Begin() const
{
    return min_;
}

//------------------------------------------------------------------------------
const Vector2iPod Aabb2i::End() const
{
    return term_;
}

//------------------------------------------------------------------------------
const Vector2iPod Aabb2i::Min() const
{
    return min_;
}

//------------------------------------------------------------------------------
const Vector2iPod Aabb2i::Term() const
{
    return term_;
}

//------------------------------------------------------------------------------
int Aabb2i::Width() const
{
    return int(term_.x - min_.x);
}

//------------------------------------------------------------------------------
int Aabb2i::Height() const
{
    return int(term_.y - min_.y);
}

//------------------------------------------------------------------------------
Extent2iPod Aabb2i::Extent() const
{
    return Extent2i(Width(), Height());
}

//------------------------------------------------------------------------------
bool Aabb2i::IsPositive() const
{
    return 0 <= min_.x && 0 <= min_.y;
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::ToPositive() const
{
    const Vector2i newMin = min_.Max(Vector2i::Zero());
    const Vector2i newTerm = term_.Max(Vector2i::Zero());
    const Vector2i newSize = newTerm - newMin;
    return Aabb2i(newMin, uint(newSize.x), uint(newSize.y));
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::Merge(const Aabb2i& aABB) const
{
    Aabb2i aabb(*this);
    aabb.MergeAssign(aABB);
    return aabb;
}

//------------------------------------------------------------------------------
void Aabb2i::MergeAssign(const Aabb2i& aABB)
{
    min_ = min_.Min(aABB.min_);
    term_ = term_.Max(aABB.term_);
}

//------------------------------------------------------------------------------
bool Aabb2i::IsIntersects(const Aabb2i& aABB) const
{
    return min_.x < aABB.term_.x && min_.y < aABB.term_.y &&
           aABB.min_.x < term_.x && aABB.min_.y < term_.y;
}

//------------------------------------------------------------------------------
bool Aabb2i::IsContains(const Vector2iPod& pos) const
{
    return min_.x <= pos.x && min_.y <= pos.y && pos.x < term_.x &&
           pos.y < term_.y;
}

//------------------------------------------------------------------------------
bool Aabb2i::IsContains(const Aabb2i& aABB) const
{
    return min_.x <= aABB.min_.x && min_.y <= aABB.min_.y &&
           aABB.term_.x <= term_.x && aABB.term_.y <= term_.y;
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::Add(const Vector2iPod& trans) const
{
    Aabb2i aabb = *this;
    aabb.AddAssign(trans);
    return aabb;
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::Sub(const Vector2iPod& trans) const
{
    Aabb2i aabb = *this;
    aabb.SubAssign(trans);
    return aabb;
}

//------------------------------------------------------------------------------
void Aabb2i::AddAssign(const Vector2iPod& trans)
{
    min_ += trans;
    term_ += trans;
}

//------------------------------------------------------------------------------
void Aabb2i::SubAssign(const Vector2iPod& trans)
{
    min_ -= trans;
    term_ -= trans;
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::operator+(const Vector2iPod& trans) const
{
    return Add(trans);
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2i::operator-(const Vector2iPod& trans) const
{
    return Sub(trans);
}

//------------------------------------------------------------------------------
Aabb2i& Aabb2i::operator+=(const Vector2iPod& trans)
{
    AddAssign(trans);
    return *this;
}

//------------------------------------------------------------------------------
Aabb2i& Aabb2i::operator-=(const Vector2iPod& trans)
{
    SubAssign(trans);
    return *this;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2i::ToAABB2f() const
{
    return Aabb2(Min().ToXYf(), Term().ToXYf());
}

} // namespace ae::base
// EOF
