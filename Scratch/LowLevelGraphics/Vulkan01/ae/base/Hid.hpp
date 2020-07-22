// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_HID_HPP)
#else
#define AE_BASE_INCLUDED_HID_HPP

#include <ae/base/Noncopyable.hpp>
#include <ae/base/Os.hpp>

#if defined(AE_BASE_OS_WINDOWS)
    #include <ae/base/Hid_Windows.hpp>
#elif defined(AE_BASE_OS_MACOSX)
    #include <ae/base/Hid_MacOSX.hpp>
#elif defined(AE_BASE_OS_IOS)
    #include <ae/base/Hid_iOS.hpp>
#endif

namespace ae {
namespace base {
class Display;
class Keyboard;
class Mouse;
class Touch;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Hid
//@{
/// @brief Hid(Human Interface Device)にアクセスするクラス。
class Hid : public Noncopyable<Hid>
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// コンストラクタ。
    Hid(Display&);
    /// デストラクタ。
    ~Hid();
    //@}

    /// @name キーボードデバイス
    //@{
    /// キーボードの総数。
    int           keyboardCount()const;

    /// 指定番目のキーボードを取得。
    const Keyboard keyboardAtIndex(int aIndex)const;

    /// @brief 存在する環境なら0番のキーボードを取得する。
    /// @details 
    /// 存在しなければ空のキーボードを返す。
    const Keyboard keyboard()const;
    //@}

    /// @name マウスデバイス
    //@{
    /// マウスの総数。
    int           mouseCount()const;

    /// 指定番目のマウスを取得。
    const Mouse mouseAtIndex(int aIndex)const;

    /// @brief 存在する環境なら0番のマウスを取得する。
    /// @details 
    /// 存在しなければ空のマウスを返す。
    const Mouse mouse()const;
    //@}

    /// @name タッチデバイス
    //@{
    /// @brief この機器でサポートされているタップ数を取得する。
    /// @details 
    /// シングルタッチしかサポートしない環境は1、マルチタッチをサポートする環境では2以上の値が返ります。@n
    int supportedTouchTapCount()const;

    /// タッチデバイスの総数。
    int touchCount()const;

    /// 指定番目のタッチデバイスの取得。
    const Touch touchAtIndex(int aIndex)const;

    /// @brief 存在する環境なら0番のタッチデバイスを取得する。
    /// @details 
    /// 存在しなければ空のタッチデバイスを返す。
    const Touch touch()const;
    //@}

    //============================================================
    // 内部実装用関数群。
    Hid_Ext& ext_(); // 拡張。

private:
    Display& mDisplay;
    Hid_Ext  mExt;
};
//@}

}} // namespace
#endif
// EOF
