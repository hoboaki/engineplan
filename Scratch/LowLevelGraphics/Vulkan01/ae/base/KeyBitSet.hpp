// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_KEYBITSET_HPP)
#else
#define AE_BASE_INCLUDED_KEYBITSET_HPP

#include <ae/base/BitSet.hpp>
#include <ae/base/KeyKind.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Hid
//@{
/// @brief キーボードのキーのビットセット。
/// @details
/// ビットのインデックスは KeyKind を使用しています。
typedef BitSet< KeyKind::TERM > KeyBitSet;
//@}

}} // namespace
#endif
// EOF
