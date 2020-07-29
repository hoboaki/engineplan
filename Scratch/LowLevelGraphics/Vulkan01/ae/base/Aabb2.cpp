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
: min_(aPos1.Min(aPos2))
, max_(aPos1.Max(aPos2))
{
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::Min()const
{
    return min_;
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::Max()const
{
    return max_;
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::Center()const
{
    return (min_ + max_) * 0.5f;
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::PosLb()const
{
    return Vector2(min_.x, min_.y);
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::PosRb()const
{
    return Vector2(max_.x, min_.y);
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::PosLt()const
{
    return Vector2(min_.x, max_.y);
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::PosRt()const
{
    return Vector2(max_.x, max_.y);
}

//------------------------------------------------------------------------------
float Aabb2::Left()const
{
    return min_.x;
}

//------------------------------------------------------------------------------
float Aabb2::Right()const
{
    return max_.x;
}

//------------------------------------------------------------------------------
float Aabb2::Bottom()const
{
    return min_.y;
}

//------------------------------------------------------------------------------
float Aabb2::Top()const
{
    return max_.y;
}

//------------------------------------------------------------------------------
float Aabb2::Width()const
{
    return max_.x - min_.x;
}

//------------------------------------------------------------------------------
float Aabb2::Height()const
{
    return max_.y - min_.y;
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::Size()const
{
    return Vector2(Width(), Height());
}

//------------------------------------------------------------------------------
const Vector2Pod Aabb2::HalfSize()const
{
    return Size() * 0.5f;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::Merge(const Vector2Pod& aPos)const
{
    Aabb2 aabb = *this;
    aabb.MergeAssign(aPos);
    return aabb;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::Merge(const Aabb2& aAABB)const
{
    Aabb2 aabb = *this;
    aabb.MergeAssign(aAABB);
    return aabb;
}

//------------------------------------------------------------------------------
void Aabb2::MergeAssign(const Vector2Pod& aPos)
{
    min_ = min_.Min(aPos);
    max_ = max_.Max(aPos);
}

//------------------------------------------------------------------------------
void Aabb2::MergeAssign(const Aabb2& aAABB)
{
    min_ = min_.Min(aAABB.min_);
    max_ = max_.Max(aAABB.max_);
}

//------------------------------------------------------------------------------
bool Aabb2::IsIntersects(const Aabb2& aAABB)const
{
    return min_.x <= aAABB.max_.x
        && min_.y <= aAABB.max_.y
        && aAABB.min_.x <= max_.x
        && aAABB.min_.y <= max_.y;
}

//------------------------------------------------------------------------------
bool Aabb2::IsContains(const Vector2Pod& aPos)const
{
    return min_.x <= aPos.x
        && min_.y <= aPos.y
        && aPos.x <= max_.x
        && aPos.y <= max_.y;
}

//------------------------------------------------------------------------------
bool Aabb2::IsContains(const Aabb2& aAABB)const
{
    return IsContains(aAABB.min_)
        && IsContains(aAABB.max_);
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::Add(const Vector2Pod& aTrans)const
{
    Aabb2 aabb = *this;
    aabb += aTrans;
    return aabb;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::Sub(const Vector2Pod& aTrans)const
{
    Aabb2 aabb = *this;
    aabb -= aTrans;
    return aabb;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::Add(const Aabb2& aAABB)const
{
    Aabb2 aabb = *this;
    aabb += aAABB;
    return aabb;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::Sub(const Aabb2& aAABB)const
{
    Aabb2 aabb = *this;
    aabb -= aAABB;
    return aabb;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::Mul(const float aScale)const
{
    Aabb2 aabb = *this;
    aabb *= aScale;
    return aabb;
}

//------------------------------------------------------------------------------
void Aabb2::AddAssign(const Vector2Pod& aTrans)
{
    min_ += aTrans;
    max_ += aTrans;
}

//------------------------------------------------------------------------------
void Aabb2::SubAssign(const Vector2Pod& aTrans)
{
    min_ -= aTrans;
    max_ -= aTrans;
}

//------------------------------------------------------------------------------
void Aabb2::AddAssign(const Aabb2& aAABB)
{
    min_ += aAABB.min_;
    max_ += aAABB.max_;
}

//------------------------------------------------------------------------------
void Aabb2::SubAssign(const Aabb2& aAABB)
{
    min_ -= aAABB.min_;
    max_ -= aAABB.max_;
}

//------------------------------------------------------------------------------
void Aabb2::MulAssign(const float aScale)
{
    min_ *= aScale;
    max_ *= aScale;
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::operator+(const Vector2Pod& aTrans)const
{
    return Add(aTrans);
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::operator-(const Vector2Pod& aTrans)const
{
    return Sub(aTrans);
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::operator+(const Aabb2& aAABB)const
{
    return Add(aAABB);
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::operator-(const Aabb2& aAABB)const
{
    return Sub(aAABB);
}

//------------------------------------------------------------------------------
const Aabb2 Aabb2::operator*(const float aScale)const
{
    return Mul(aScale);
}

//------------------------------------------------------------------------------
Aabb2& Aabb2::operator+=(const Vector2Pod& aTrans)
{
    AddAssign(aTrans);
    return *this;
}

//------------------------------------------------------------------------------
Aabb2& Aabb2::operator-=(const Vector2Pod& aTrans)
{
    SubAssign(aTrans);
    return *this;
}

//------------------------------------------------------------------------------
Aabb2& Aabb2::operator+=(const Aabb2& aAABB)
{
    AddAssign(aAABB);
    return *this;
}

//------------------------------------------------------------------------------
Aabb2& Aabb2::operator-=(const Aabb2& aAABB)
{
    SubAssign(aAABB);
    return *this;
}

//------------------------------------------------------------------------------
Aabb2& Aabb2::operator*=(const float aScale)
{
    MulAssign(aScale);
    return *this;
}

//------------------------------------------------------------------------------
const Aabb2i Aabb2::ToAabb2i()const
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
