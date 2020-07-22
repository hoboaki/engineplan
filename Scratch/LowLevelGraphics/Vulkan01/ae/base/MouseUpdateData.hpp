// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_MOUSEUPDATEDATA_HPP)
#else
#define AE_BASE_INCLUDED_MOUSEUPDATEDATA_HPP

#include <ae/base/Bool.hpp>
#include <ae/base/MouseBtnBitSet.hpp>
#include <ae/base/ScreenPos.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Hid
//@{
/// マウスの更新データ。
struct MouseUpdateData
{
    ScreenPos pos;
    MouseBtnBitSet hold;
    BoolPod32 posUpdated; // trueならposは最新の値が入っている。falseならウィンドウ外でキャプチャに失敗している可能性がある。
};
//@}

}} // namespace
#endif
// EOF
