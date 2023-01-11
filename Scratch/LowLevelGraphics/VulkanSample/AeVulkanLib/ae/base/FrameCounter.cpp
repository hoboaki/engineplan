// 文字コード：UTF-8
#include <ae/base/FrameCounter.hpp>

// includes
#include <ae/base/DivideCheck.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
FrameCounter::FrameCounter()
: frame_(0)
, totalFrame_(0)
{
}

//------------------------------------------------------------------------------
FrameCounter::FrameCounter(const int totalFrame)
: frame_(0)
, totalFrame_(totalFrame)
{
}

//------------------------------------------------------------------------------
void FrameCounter::Reset()
{
    frame_ = 0;
}

//------------------------------------------------------------------------------
void FrameCounter::Reset(const int totalFrame)
{
    frame_ = 0;
    totalFrame_ = totalFrame;
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
int FrameCounter::Frame() const
{
    return frame_;
}

//------------------------------------------------------------------------------
int FrameCounter::TotalFrame() const
{
    return totalFrame_;
}

//------------------------------------------------------------------------------
bool FrameCounter::IsEnd() const
{
    return !IsCounting();
}

//------------------------------------------------------------------------------
bool FrameCounter::IsCounting() const
{
    return frame_ < totalFrame_;
}

//------------------------------------------------------------------------------
float FrameCounter::RateFrame() const
{
    if (IsEnd()) {
        return 1.0f;
    } else {
        return AE_BASE_DIV(float(frame_), totalFrame_);
    }
}

//------------------------------------------------------------------------------
float FrameCounter::InvRateFrame() const
{
    return 1.0f - RateFrame();
}

} // namespace ae::base
// EOF
