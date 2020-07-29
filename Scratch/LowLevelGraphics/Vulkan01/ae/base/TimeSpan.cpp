// 文字コード：UTF-8
#include <ae/base/TimeSpan.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::FromTicks(const s64 aTicks)
{
    TimeSpanPod obj = {aTicks};
    return obj;
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::FromMicroseconds(const s64 aUsecs)
{
    return FromTicks(aUsecs * 10);
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::FromMilliseconds(const s64 aMSecs)
{
    return FromMicroseconds(aMSecs * 1000);
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::FromSeconds(const s64 aSecs)
{
    return FromMilliseconds(aSecs * 1000);
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::FromMinnutes(const s64 aMins)
{
    return FromSeconds(aMins * 60);
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::FromHours(const s64 aHours)
{
    return FromMinnutes(aHours * 60);
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::FromDays(const s64 aDays)
{
    return FromHours(aDays * 24);
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::Ticks()const
{
    return ticks_;
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::Microseconds()const
{
    return ticks_ / 10;
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::Milliseconds()const
{
    return ticks_ / (1000 * 10);
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::Seconds()const
{
    return ticks_ / (1000 * 1000 * 10);
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::Minutes()const
{
    return ticks_ / (60 * 1000 * 1000 * 10);
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::Hours()const
{
    return ticks_ / (s64(60) * 60 * 1000 * 1000 * 10);
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::Days()const
{
    return ticks_ / (s64(24) * 60 * 60 * 1000 * 1000 * 10);
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::Add(const TimeSpanPod& aTimeSpan)const
{
    TimeSpanPod obj = *this;
    obj += aTimeSpan;
    return obj;
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::operator+(const TimeSpanPod& aTimeSpan)const
{
    return Add(aTimeSpan);
}

//------------------------------------------------------------------------------
TimeSpanPod& TimeSpanPod::AddAssign(const TimeSpanPod& aTimeSpan)
{
    ticks_ += aTimeSpan.ticks_;
    return *this;
}

//------------------------------------------------------------------------------
TimeSpanPod& TimeSpanPod::operator+=(const TimeSpanPod& aTimeSpan)
{
    return AddAssign(aTimeSpan);
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::Sub(const TimeSpanPod& aTimeSpan)const
{
    TimeSpanPod obj = *this;
    obj -= aTimeSpan;
    return obj;
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::operator-(const TimeSpanPod& aTimeSpan)const
{
    return Sub(aTimeSpan);
}

//------------------------------------------------------------------------------
TimeSpanPod& TimeSpanPod::SubAssign(const TimeSpanPod& aTimeSpan)
{
    ticks_ -= aTimeSpan.ticks_;
    return *this;
}

//------------------------------------------------------------------------------
TimeSpanPod& TimeSpanPod::operator-=(const TimeSpanPod& aTimeSpan)
{
    return SubAssign(aTimeSpan);
}

}} // namespace
// EOF
