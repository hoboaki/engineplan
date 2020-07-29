// 文字コード：UTF-8
#include <ae/base/TouchTap.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

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
void TouchTap::update(const TouchTapUpdateData& aData)
{
    prevData_ = data_;
    data_ = aData;
}

//------------------------------------------------------------------------------
const TouchTapUpdateData TouchTap::lastUpdateData()const
{
    return data_;
}

//------------------------------------------------------------------------------
int TouchTap::tapCount()const
{
    return data_.tapCount;
}

//------------------------------------------------------------------------------
const ScreenPosPod TouchTap::pos()const
{
    return data_.pos;
}

//------------------------------------------------------------------------------
bool TouchTap::isHold()const
{
    return 0 < data_.tapCount;
}

//------------------------------------------------------------------------------
bool TouchTap::isTrigger()const
{
    return data_.tapCount != 0 && prevData_.tapCount == 0;
}

//------------------------------------------------------------------------------
bool TouchTap::isRelease()const
{
    return data_.tapCount == 0 && prevData_.tapCount != 0;
}

}} // namespace
// EOF
