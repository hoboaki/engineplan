// 文字コード：UTF-8
#include <ae/base/Touch.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
Touch::Touch(const int tapCount)
: tapCount_(tapCount)
, data_()
, taps_()
{
    if (TouchUpdateData::TAP_COUNT_MAX < tapCount_) {
        AE_BASE_ERROR_INVALID_VALUE(tapCount);
        tapCount_ = TouchUpdateData::TAP_COUNT_MAX;
    }
}

//------------------------------------------------------------------------------
Touch::~Touch()
{
}

//------------------------------------------------------------------------------
void Touch::Update(const TouchUpdateData& data)
{
    // バックアップ
    data_ = data;

    // 更新
    for (int i = 0; i < tapCount_; ++i) {
        taps_[i].Update(data.taps[i]);
    }
}

//------------------------------------------------------------------------------
const TouchUpdateData Touch::LastUpdateData() const
{
    return data_;
}

//------------------------------------------------------------------------------
int Touch::TapCount() const
{
    return tapCount_;
}

//------------------------------------------------------------------------------
const TouchTap Touch::TapAtIndex(const int index) const
{
    if (TapCount() <= index) {
        AE_BASE_ERROR_INVALID_VALUE(index);
        return TouchTap();
    }
    return taps_[index];
}

} // namespace ae::base
// EOF
