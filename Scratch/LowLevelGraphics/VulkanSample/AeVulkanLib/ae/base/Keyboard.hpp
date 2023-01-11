// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_KEYBOARD_HPP)
#else
#define AE_BASE_INCLUDED_KEYBOARD_HPP

#include <ae/base/KeyboardUpdateData.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Hid
//@{
/// @brief キーボード。
/// @details
/// マスターとなるキーボードは Hid が所持しています。 @n
/// @n
/// キーボードのコピーをアプリケーションが持つことによって
/// 「ポーズ中はキー情報を更新しないキーボード」といった
/// 特殊なキーボードを作成することができます。
class Keyboard {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// 何も押されていない状態のキーボードを作成。
    Keyboard();
    //@}

    /// @name 更新
    //@{
    /// 状態を更新する。
    void Update(const KeyboardUpdateData& data);

    /// 前回の更新データを取得する。
    const KeyboardUpdateData LastUpdateData() const;
    //@}

    /// @name 状態取得
    //@{
    bool IsHold(KeyKind::EnumType kind) const; ///< 押されているか。
    bool IsTrigger(KeyKind::EnumType kind) const; ///< 押された瞬間か。
    bool IsRepeat(
        KeyKind::EnumType kind) const; ///< 押しっぱなしの状態で入力が入ったか。
    bool IsPulse(KeyKind::EnumType kind) const; ///< IsTrigger() || IsRepeat()。
    bool IsRelease(KeyKind::EnumType kind) const; ///< 離された瞬間か。
    //@}

    /// @name ビットセット取得
    //@{
    const KeyBitSet Hold() const; ///< IsHold() のビットセット。
    const KeyBitSet Trigger() const; ///< IsTrigger() のビットセット。
    const KeyBitSet Repeat() const; ///< IsRepeat() のビットセット。
    const KeyBitSet Pulse() const; ///< IsPulse() のビットセット。
    const KeyBitSet Release() const; ///< IsRelease() のビットセット。
    //@}

private:
    KeyboardUpdateData data_;
    KeyBitSet trigger_;
    KeyBitSet repeat_;
    KeyBitSet pulse_;
    KeyBitSet release_;
};
//@}

} // namespace ae::base
#endif
// EOF
