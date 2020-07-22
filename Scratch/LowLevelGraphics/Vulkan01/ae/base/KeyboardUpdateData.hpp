// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_KEYBOARDUPDATEDATA_HPP)
#else
#define AE_BASE_INCLUDED_KEYBOARDUPDATEDATA_HPP

#include <ae/base/KeyBitSet.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Hid
//@{
/// キーボードの更新データ。
struct KeyboardUpdateData
{
    KeyBitSet hold;
    KeyBitSet pulse;
};
//@}

}} // namespace
#endif
// EOF
