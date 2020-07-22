// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_TOUCHTAPUPDATEDATA_HPP)
#else
#define AE_BASE_INCLUDED_TOUCHTAPUPDATEDATA_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ScreenPos.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Hid
//@{
/// タッチの1タップの更新データ。
struct TouchTapUpdateData
{
    uint32       tapCount;
    ScreenPosPod pos;
};
//@}

}} // namespace
#endif
// EOF
