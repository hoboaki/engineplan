// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_MOUSEBTNBITSET_HPP)
#else
#define AE_BASE_INCLUDED_MOUSEBTNBITSET_HPP

#include <ae/base/BitSet.hpp>
#include <ae/base/MouseBtnKind.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Hid
//@{
/// @brief マウスのボタンのビットセット。
/// @details
/// ビットのインデックスは MouseBtnKind を使用しています。
typedef BitSet< MouseBtnKind::TERM > MouseBtnBitSet;
//@}

}} // namespace
#endif
// EOF
