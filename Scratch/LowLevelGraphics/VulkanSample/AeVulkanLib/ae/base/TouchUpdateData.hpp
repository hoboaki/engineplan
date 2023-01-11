// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_TOUCHUPDATEDATA_HPP)
#else
#define AE_BASE_INCLUDED_TOUCHUPDATEDATA_HPP

#include <ae/base/TouchTapUpdateData.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Hid
//@{
/// タッチ入力の更新データ。
struct TouchUpdateData
{
    enum
    {
        /// サポートしている最大タップ数。
        TAP_COUNT_MAX = 8
    };
    TouchTapUpdateData taps[TAP_COUNT_MAX];
};
//@}

} // namespace ae::base
#endif
// EOF
