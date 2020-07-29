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
void FrameCounter::reset()
{
    frame_ = 0;
}

//------------------------------------------------------------------------------
void FrameCounter::reset(const int aTotalFrame)
{
    frame_ = 0;
    totalFrame_ = aTotalFrame;
}

//------------------------------------------------------------------------------
void FrameCounter::advance()
{
    if (isCounting()) {
        advanceStrict();
    }
}

//------------------------------------------------------------------------------
void FrameCounter::advanceStrict()
{
    if (isEnd()) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    ++frame_;
}

//------------------------------------------------------------------------------
void FrameCounter::toEnd()
{
    frame_ = totalFrame_;
}

//------------------------------------------------------------------------------
int FrameCounter::frame()const
{
    return frame_;

}

//------------------------------------------------------------------------------
int FrameCounter::totalFrame()const
{
    return totalFrame_;
}

//------------------------------------------------------------------------------
bool FrameCounter::isEnd()const
{
    return !isCounting();
}

//------------------------------------------------------------------------------
bool FrameCounter::isCounting()const
{
    return frame_ < totalFrame_;
}

//------------------------------------------------------------------------------
float FrameCounter::rateFrame()const
{
    if (isEnd()) {
        return 1.0f;
    }
    else
    {
        return AE_BASE_DIV(float(frame_), totalFrame_);
    }
}

//------------------------------------------------------------------------------
float FrameCounter::invRateFrame()const
{
    return 1.0f - rateFrame();
}

}} // namespace
// EOF
