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
s64 TimeSpanPod::ticks()const
{
    return ticks_;
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::microseconds()const
{
    return ticks_ / 10;
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::milliseconds()const
{
    return ticks_ / (1000 * 10);
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::seconds()const
{
    return ticks_ / (1000 * 1000 * 10);
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::minutes()const
{
    return ticks_ / (60 * 1000 * 1000 * 10);
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::hours()const
{
    return ticks_ / (s64(60) * 60 * 1000 * 1000 * 10);
}

//------------------------------------------------------------------------------
s64 TimeSpanPod::days()const
{
    return ticks_ / (s64(24) * 60 * 60 * 1000 * 1000 * 10);
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::add(const TimeSpanPod& aTimeSpan)const
{
    TimeSpanPod obj = *this;
    obj += aTimeSpan;
    return obj;
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::operator+(const TimeSpanPod& aTimeSpan)const
{
    return add(aTimeSpan);
}

//------------------------------------------------------------------------------
TimeSpanPod& TimeSpanPod::addAssign(const TimeSpanPod& aTimeSpan)
{
    ticks_ += aTimeSpan.ticks_;
    return *this;
}

//------------------------------------------------------------------------------
TimeSpanPod& TimeSpanPod::operator+=(const TimeSpanPod& aTimeSpan)
{
    return addAssign(aTimeSpan);
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::sub(const TimeSpanPod& aTimeSpan)const
{
    TimeSpanPod obj = *this;
    obj -= aTimeSpan;
    return obj;
}

//------------------------------------------------------------------------------
const TimeSpanPod TimeSpanPod::operator-(const TimeSpanPod& aTimeSpan)const
{
    return sub(aTimeSpan);
}

//------------------------------------------------------------------------------
TimeSpanPod& TimeSpanPod::subAssign(const TimeSpanPod& aTimeSpan)
{
    ticks_ -= aTimeSpan.ticks_;
    return *this;
}

//------------------------------------------------------------------------------
TimeSpanPod& TimeSpanPod::operator-=(const TimeSpanPod& aTimeSpan)
{
    return subAssign(aTimeSpan);
}

}} // namespace
// EOF
