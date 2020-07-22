// 文字コード：UTF-8
#include <ae/base/Touch.hpp>

#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Touch::Touch(const int aTapCount)
: mTapCount(aTapCount)
, mData()
, mTaps()
{
    if (TouchUpdateData::TAP_COUNT_MAX < mTapCount) {
        AE_BASE_ERROR_INVALID_VALUE(aTapCount);
        mTapCount = TouchUpdateData::TAP_COUNT_MAX;
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
    mData = aData;

    // 更新
    for (int i = 0; i < mTapCount; ++i) {
        mTaps[i].update(aData.taps[i]);
    }
}

//------------------------------------------------------------------------------
const TouchUpdateData Touch::lastUpdateData()const
{
    return mData;
}

//------------------------------------------------------------------------------
int Touch::tapCount()const
{
    return mTapCount;
}

//------------------------------------------------------------------------------
const TouchTap Touch::tapAtIndex(const int aIndex)const
{
    if (tapCount() <= aIndex) {
        AE_BASE_ERROR_INVALID_VALUE(aIndex);
        return TouchTap();
    }
    return mTaps[aIndex];
}

}} // namespace
// EOF
