// 文字コード：UTF-8
#include <ae/base/TouchTap.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
TouchTap::TouchTap()
: data_()
, prevData_()
{
}

//------------------------------------------------------------------------------
TouchTap::~TouchTap()
{
}

//------------------------------------------------------------------------------
void TouchTap::Update(const TouchTapUpdateData& data)
{
    prevData_ = data_;
    data_ = data;
}

//------------------------------------------------------------------------------
const TouchTapUpdateData TouchTap::LastUpdateData() const
{
    return data_;
}

//------------------------------------------------------------------------------
int TouchTap::TapCount() const
{
    return data_.tapCount;
}

//------------------------------------------------------------------------------
const ScreenPosPod TouchTap::Pos() const
{
    return data_.pos;
}

//------------------------------------------------------------------------------
bool TouchTap::IsHold() const
{
    return 0 < data_.tapCount;
}

//------------------------------------------------------------------------------
bool TouchTap::IsTrigger() const
{
    return data_.tapCount != 0 && prevData_.tapCount == 0;
}

//------------------------------------------------------------------------------
bool TouchTap::IsRelease() const
{
    return data_.tapCount == 0 && prevData_.tapCount != 0;
}

} // namespace ae::base
// EOF
