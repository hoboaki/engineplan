// 文字コード：UTF-8
#include <ae/base/FrameCounter.hpp>

#include <ae/base/DivideCheck.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
FrameCounter::FrameCounter()
: frame_(0)
, totalFrame_(0)
{
}

//------------------------------------------------------------------------------
FrameCounter::FrameCounter(const int aTotalFrame)
: frame_(0)
, totalFrame_(aTotalFrame)
{
}

//------------------------------------------------------------------------------
void FrameCounter::Reset()
{
    frame_ = 0;
}

//------------------------------------------------------------------------------
void FrameCounter::Reset(const int aTotalFrame)
{
    frame_ = 0;
    totalFrame_ = aTotalFrame;
}

//------------------------------------------------------------------------------
void FrameCounter::Advance()
{
    if (IsCounting()) {
        AdvanceStrict();
    }
}

//------------------------------------------------------------------------------
void FrameCounter::AdvanceStrict()
{
    if (IsEnd()) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    ++frame_;
}

//------------------------------------------------------------------------------
void FrameCounter::ToEnd()
{
    frame_ = totalFrame_;
}

//------------------------------------------------------------------------------
int FrameCounter::Frame()const
{
    return frame_;

}

//------------------------------------------------------------------------------
int FrameCounter::TotalFrame()const
{
    return totalFrame_;
}

//------------------------------------------------------------------------------
bool FrameCounter::IsEnd()const
{
    return !IsCounting();
}

//------------------------------------------------------------------------------
bool FrameCounter::IsCounting()const
{
    return frame_ < totalFrame_;
}

//------------------------------------------------------------------------------
float FrameCounter::RateFrame()const
{
    if (IsEnd()) {
        return 1.0f;
    }
    else
    {
        return AE_BASE_DIV(float(frame_), totalFrame_);
    }
}

//------------------------------------------------------------------------------
float FrameCounter::InvRateFrame()const
{
    return 1.0f - RateFrame();
}

}} // namespace
// EOF
