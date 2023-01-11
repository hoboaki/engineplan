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

namespace ae::base {
class Display;
class Keyboard;
class Mouse;
class Touch;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Hid
//@{
/// @brief Hid(Human Interface Device)にアクセスするクラス。
class Hid : public Noncopyable<Hid> {
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
    int KeyboardCount() const;

    /// 指定番目のキーボードを取得。
    const base::Keyboard KeyboardAtIndex(int index) const;

    /// @brief 存在する環境なら0番のキーボードを取得する。
    /// @details
    /// 存在しなければ空のキーボードを返す。
    const base::Keyboard Keyboard() const;
    //@}

    /// @name マウスデバイス
    //@{
    /// マウスの総数。
    int MouseCount() const;

    /// 指定番目のマウスを取得。
    const base::Mouse MouseAtIndex(int index) const;

    /// @brief 存在する環境なら0番のマウスを取得する。
    /// @details
    /// 存在しなければ空のマウスを返す。
    const base::Mouse Mouse() const;
    //@}

    /// @name タッチデバイス
    //@{
    /// @brief この機器でサポートされているタップ数を取得する。
    /// @details
    /// シングルタッチしかサポートしない環境は1、マルチタッチをサポートする環境では2以上の値が返ります。@n
    int SupportedTouchTapCount() const;

    /// タッチデバイスの総数。
    int TouchCount() const;

    /// 指定番目のタッチデバイスの取得。
    const base::Touch TouchAtIndex(int index) const;

    /// @brief 存在する環境なら0番のタッチデバイスを取得する。
    /// @details
    /// 存在しなければ空のタッチデバイスを返す。
    const base::Touch Touch() const;
    //@}

    //============================================================
    // 内部実装用関数群。
    Hid_Ext& Ext_(); // 拡張。

private:
    Display& display_;
    Hid_Ext ext_;
};
//@}

} // namespace ae::base
#endif
// EOF
