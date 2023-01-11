// 文字コード：UTF-8
#include <ae/base/TimeSpan.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::FromTicks(const s64 ticks)
{
    TimeSpanPod obj = { ticks };
    return obj;
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::FromMicroseconds(const s64 usecs)
{
    return FromTicks(usecs * 10);
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::FromMilliseconds(const s64 mSecs)
{
    return FromMicroseconds(mSecs * 1000);
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::FromSeconds(const s64 secs)
{
    return FromMilliseconds(secs * 1000);
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::FromMinnutes(const s64 mins)
{
    return FromSeconds(mins * 60);
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::FromHours(const s64 hours)
{
    return FromMinnutes(hours * 60);
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::FromDays(const s64 days)
{
    return FromHours(days * 24);
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::Ticks() const
{
    return ticks_;
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::Microseconds() const
{
    return ticks_ / 10;
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::Milliseconds() const
{
    return ticks_ / (1000 * 10);
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::Seconds() const
{
    return ticks_ / (1000 * 1000 * 10);
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::Minutes() const
{
    return ticks_ / (60 * 1000 * 1000 * 10);
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::Hours() const
{
    return ticks_ / (s64(60) * 60 * 1000 * 1000 * 10);
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::Days() const
{
    return ticks_ / (s64(24) * 60 * 60 * 1000 * 1000 * 10);
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::Add(const TimeSpanPod& timeSpan) const
{
    TimeSpanPod obj = *this;
    obj += timeSpan;
    return obj;
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::operator+(const TimeSpanPod& timeSpan) const
{
    return Add(timeSpan);
}

//------------------------------------------------------------------------------
TimeSpanPod& TimeSpanPod::AddAssign(const TimeSpanPod& timeSpan)
{
    ticks_ += timeSpan.ticks_;
    return *this;
}

//------------------------------------------------------------------------------
TimeSpanPod& TimeSpanPod::operator+=(const TimeSpanPod& timeSpan)
{
    return AddAssign(timeSpan);
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::Sub(const TimeSpanPod& timeSpan) const
{
    TimeSpanPod obj = *this;
    obj -= timeSpan;
    return obj;
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::operator-(const TimeSpanPod& timeSpan) const
{
    return Sub(timeSpan);
}

//------------------------------------------------------------------------------
TimeSpanPod& TimeSpanPod::SubAssign(const TimeSpanPod& timeSpan)
{
    ticks_ -= timeSpan.ticks_;
    return *this;
}

//------------------------------------------------------------------------------
TimeSpanPod& TimeSpanPod::operator-=(const TimeSpanPod& timeSpan)
{
    return SubAssign(timeSpan);
}

} // namespace ae::base
// EOF
