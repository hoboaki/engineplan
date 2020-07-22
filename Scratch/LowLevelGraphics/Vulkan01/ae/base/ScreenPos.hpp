// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_SCREENPOS_HPP)
#else
#define AE_BASE_INCLUDED_SCREENPOS_HPP

#include <ae/base/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @name AeBase-Util
//@{
/// @brief スクリーン上の位置。
/// @details
/// スクリーンの左下が原点になります。@n
/// 符号有りにしているのはマウスのドラッグ操作でウィンドウ外の座標を扱うことがあるためです。@n
struct ScreenPosPod
{
    s16 x; ///< x位置。
    s16 y; ///< y位置。
};

/// ScreenPosPodのクラス版。
class ScreenPos : public ScreenPosPod
{
public:
    /// @name コンストラクタ。
    //@{
    ScreenPos(); ///< (0,0)で作成。
    ScreenPos(s16 aX, s16 aY); ///< x,yを指定して作成。
    ScreenPos(const ScreenPosPod&); ///< コピーして作成。
    //@}
};
//@}

}} // namespace
#endif
// EOF
