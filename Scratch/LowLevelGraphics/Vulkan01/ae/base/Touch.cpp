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
void Touch::Update(const TouchUpdateData& aData)
{
    // バックアップ
    data_ = aData;

    // 更新
    for (int i = 0; i < tapCount_; ++i) {
        taps_[i].Update(aData.taps[i]);
    }
}

//------------------------------------------------------------------------------
const TouchUpdateData Touch::LastUpdateData()const
{
    return data_;
}

//------------------------------------------------------------------------------
int Touch::TapCount()const
{
    return tapCount_;
}

//------------------------------------------------------------------------------
const TouchTap Touch::TapAtIndex(const int aIndex)const
{
    if (TapCount() <= aIndex) {
        AE_BASE_ERROR_INVALID_VALUE(aIndex);
        return TouchTap();
    }
    return taps_[aIndex];
}

}} // namespace
// EOF
