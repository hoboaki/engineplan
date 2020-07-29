// 文字コード：UTF-8
#include <ae/base/Touch.hpp>

#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Touch::Touch(const int aTapCount)
: tapCount_(aTapCount)
, data_()
, taps_()
{
    if (TouchUpdateData::TAP_COUNT_MAX < tapCount_) {
        AE_BASE_ERROR_INVALID_VALUE(aTapCount);
        tapCount_ = TouchUpdateData::TAP_COUNT_MAX;
    }
}

//------------------------------------------------------------------------------
Touch::~Touch()
{
}

//------------------------------------------------------------------------------
void Touch::update(const TouchUpdateData& aData)
{
    // バックアップ
    data_ = aData;

    // 更新
    for (int i = 0; i < tapCount_; ++i) {
        taps_[i].update(aData.taps[i]);
    }
}

//------------------------------------------------------------------------------
const TouchUpdateData Touch::lastUpdateData()const
{
    return data_;
}

//------------------------------------------------------------------------------
int Touch::tapCount()const
{
    return tapCount_;
}

//------------------------------------------------------------------------------
const TouchTap Touch::tapAtIndex(const int aIndex)const
{
    if (tapCount() <= aIndex) {
        AE_BASE_ERROR_INVALID_VALUE(aIndex);
        return TouchTap();
    }
    return taps_[aIndex];
}

}} // namespace
// EOF
