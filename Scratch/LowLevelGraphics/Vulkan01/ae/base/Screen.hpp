// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_SCREEN_HPP)
#else
#define AE_BASE_INCLUDED_SCREEN_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/base/Os.hpp>

#if defined(AE_BASE_OS_MACOSX)
    #include <ae/base/Screen_MacOSX.hpp>
#elif defined(AE_BASE_OS_IOS)
    #include <ae/base/Screen_iOS.hpp>
#else
    #include <ae/base/Screen_Default.hpp>
#endif

namespace ae {
namespace base {
class Display_Ext;
struct ScreenPosPod;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @name addtogroup AeBase-System
//@{
/// @brief Displayが所持する描画領域。
/// @details
/// WindowsやMacOSXなどのWindowSystem環境では１つの Display に１つの Screen が存在します。 @n
/// NintendoDSなど2枚の描画領域を持つ環境では１つの Display に２つの Screen が存在します。 @n
class Screen : ::ae::base::Noncopyable<Screen>
{
public:
    // コンストラクタ。システムが呼ぶ。
    Screen(Display_Ext& aOwner, int aWidth, int aHeight);

    /// @name 解像度
    //@{
    /// 横ピクセル数。
    int width()const;

    /// 縦ピクセル数。
    int height()const;

    /// @brief 指定の位置がスクリーン内かどうか判定する。
    /// @return 0 <= aPos.x < width() && 0 <= aPos.y < height()
    bool isContains(const ScreenPosPod& aPos)const;
    //@}

    //============================================================
    // 内部実装用関数群。
    Display_Ext& display_();
    Screen_Ext& ext_();

private:
    Display_Ext& mOwner;
    Screen_Ext mExt;
    int mWidth;
    int mHeight;
};
//@}

}} // namespace
#endif
// EOF
