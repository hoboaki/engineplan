// 文字コード：UTF-8
#include <ae/base/FrameCounter.hpp>

#include <ae/base/DivideCheck.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
FrameCounter::FrameCounter()
: mFrame(0)
, mTotalFrame(0)
{
}

//------------------------------------------------------------------------------
FrameCounter::FrameCounter(const int aTotalFrame)
: mFrame(0)
, mTotalFrame(aTotalFrame)
{
}

//------------------------------------------------------------------------------
void FrameCounter::reset()
{
    mFrame = 0;
}

//------------------------------------------------------------------------------
void FrameCounter::reset(const int aTotalFrame)
{
    mFrame = 0;
    mTotalFrame = aTotalFrame;
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
    ++mFrame;
}

//------------------------------------------------------------------------------
void FrameCounter::toEnd()
{
    mFrame = mTotalFrame;
}

//------------------------------------------------------------------------------
int FrameCounter::frame()const
{
    return mFrame;

}

//------------------------------------------------------------------------------
int FrameCounter::totalFrame()const
{
    return mTotalFrame;
}

//------------------------------------------------------------------------------
bool FrameCounter::isEnd()const
{
    return !isCounting();
}

//------------------------------------------------------------------------------
bool FrameCounter::isCounting()const
{
    return mFrame < mTotalFrame;
}

//------------------------------------------------------------------------------
float FrameCounter::rateFrame()const
{
    if (isEnd()) {
        return 1.0f;
    }
    else
    {
        return AE_BASE_DIV(float(mFrame), mTotalFrame);
    }
}

//------------------------------------------------------------------------------
float FrameCounter::invRateFrame()const
{
    return 1.0f - rateFrame();
}

}} // namespace
// EOF
