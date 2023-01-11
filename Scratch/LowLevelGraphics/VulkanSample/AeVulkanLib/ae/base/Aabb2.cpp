// 文字コード：UTF-8
#include <ae/base/Aabb2.hpp>

// includes
#include <ae/base/Aabb2i.hpp>
#include <ae/base/Extent2.hpp>
#include <ae/base/Math.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
Aabb2::Aabb2()
: min_()
, max_()
{
}

//------------------------------------------------------------------------------
Aabb2::Aabb2(const Vector2Pod& pos)
: min_(pos)
, max_(pos)
{
}

//------------------------------------------------------------------------------
Aabb2::Aabb2(const Vector2Pod& pos1, const Vector2Pod& pos2)
: min_(pos1.Min(pos2))
, max_(pos1.Max(pos2))
{
}

//------------------------------------------------------------------------------
Aabb2::Aabb2(const Vector2Pod& pos, const Extent2Pod& extent)
: min_(pos)
, max_(pos.x + extent.width, pos.y + extent.height)
{
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::Min() const
{
    return min_;
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::Max() const
{
    return max_;
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::Center() const
{
    return (min_ + max_) * 0.5f;
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::PosLb() const
{
    return Vector2(min_.x, min_.y);
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::PosRb() const
{
    return Vector2(max_.x, min_.y);
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::PosLt() const
{
    return Vector2(min_.x, max_.y);
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::PosRt() const
{
    return Vector2(max_.x, max_.y);
}

//------------------------------------------------------------------------------
float Aabb2::Left() const
{
    return min_.x;
}

//------------------------------------------------------------------------------
float Aabb2::Right() const
{
    return max_.x;
}

//------------------------------------------------------------------------------
float Aabb2::Bottom() const
{
    return min_.y;
}

//------------------------------------------------------------------------------
float Aabb2::Top() const
{
    return max_.y;
}

//------------------------------------------------------------------------------
float Aabb2::Width() const
{
    return max_.x - min_.x;
}

//------------------------------------------------------------------------------
float Aabb2::Height() const
{
    return max_.y - min_.y;
}

//------------------------------------------------------------------------------
Extent2Pod Aabb2::Extent() const
{
    return Extent2(max_.x - min_.x, max_.y - min_.y);
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::Size() const
{
    return Vector2(Width(), Height());
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::HalfSize() const
{
    return Size() * 0.5f;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::Merge(const Vector2Pod& pos) const
{
    Aabb2 tmp = *this;
    tmp.MergeAssign(pos);
    return tmp;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::Merge(const Aabb2& aabb) const
{
    Aabb2 tmp = *this;
    tmp.MergeAssign(aabb);
    return tmp;
}

//------------------------------------------------------------------------------
void Aabb2::MergeAssign(const Vector2Pod& pos)
{
    min_ = min_.Min(pos);
    max_ = max_.Max(pos);
}

//------------------------------------------------------------------------------
void Aabb2::MergeAssign(const Aabb2& aabb)
{
    min_ = min_.Min(aabb.min_);
    max_ = max_.Max(aabb.max_);
}

//------------------------------------------------------------------------------
bool Aabb2::IsIntersects(const Aabb2& aabb) const
{
    return min_.x <= aabb.max_.x && min_.y <= aabb.max_.y &&
           aabb.min_.x <= max_.x && aabb.min_.y <= max_.y;
}

//------------------------------------------------------------------------------
bool Aabb2::IsContains(const Vector2Pod& pos) const
{
    return min_.x <= pos.x && min_.y <= pos.y && pos.x <= max_.x &&
           pos.y <= max_.y;
}

//------------------------------------------------------------------------------
bool Aabb2::IsContains(const Aabb2& aabb) const
{
    return IsContains(aabb.min_) && IsContains(aabb.max_);
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::Add(const Vector2Pod& trans) const
{
    Aabb2 tmp = *this;
    tmp += trans;
    return tmp;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::Sub(const Vector2Pod& trans) const
{
    Aabb2 tmp = *this;
    tmp -= trans;
    return tmp;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::Add(const Aabb2& aabb) const
{
    Aabb2 tmp = *this;
    tmp += aabb;
    return tmp;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::Sub(const Aabb2& aabb) const
{
    Aabb2 tmp = *this;
    tmp -= aabb;
    return tmp;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::Mul(const float scale) const
{
    Aabb2 tmp = *this;
    tmp *= scale;
    return tmp;
}

//------------------------------------------------------------------------------
void Aabb2::AddAssign(const Vector2Pod& trans)
{
    min_ += trans;
    max_ += trans;
}

//------------------------------------------------------------------------------
void Aabb2::SubAssign(const Vector2Pod& trans)
{
    min_ -= trans;
    max_ -= trans;
}

//------------------------------------------------------------------------------
void Aabb2::AddAssign(const Aabb2& aabb)
{
    min_ += aabb.min_;
    max_ += aabb.max_;
}

//------------------------------------------------------------------------------
void Aabb2::SubAssign(const Aabb2& aabb)
{
    min_ -= aabb.min_;
    max_ -= aabb.max_;
}

//------------------------------------------------------------------------------
void Aabb2::MulAssign(const float scale)
{
    min_ *= scale;
    max_ *= scale;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::operator+(const Vector2Pod& trans) const
{
    return Add(trans);
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::operator-(const Vector2Pod& trans) const
{
    return Sub(trans);
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::operator+(const Aabb2& aabb) const
{
    return Add(aabb);
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::operator-(const Aabb2& aabb) const
{
    return Sub(aabb);
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::operator*(const float scale) const
{
    return Mul(scale);
}

//------------------------------------------------------------------------------
Aabb2& Aabb2::operator+=(const Vector2Pod& trans)
{
    AddAssign(trans);
    return *this;
}

//------------------------------------------------------------------------------
Aabb2& Aabb2::operator-=(const Vector2Pod& trans)
{
    SubAssign(trans);
    return *this;
}

//------------------------------------------------------------------------------
Aabb2& Aabb2::operator+=(const Aabb2& aabb)
{
    AddAssign(aabb);
    return *this;
}

//------------------------------------------------------------------------------
Aabb2& Aabb2::operator-=(const Aabb2& aabb)
{
    SubAssign(aabb);
    return *this;
}

//------------------------------------------------------------------------------
Aabb2& Aabb2::operator*=(const float scale)
{
    MulAssign(scale);
    return *this;
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2::ToAabb2i() const
{
    const Vector2i newMin(
        int(Math::FloorF32(min_.x)),
        int(Math::FloorF32(min_.y)));
    const Vector2i newTerm(
        int(Math::CeilF32(max_.x)),
        int(Math::CeilF32(max_.y)));
    return Aabb2i(
        newMin,
        uint(newTerm.x - newMin.x),
        uint(newTerm.y - newMin.y));
}

} // namespace ae::base
// EOF
