// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_KEYBOARD_HPP)
#else
#define AE_BASE_INCLUDED_KEYBOARD_HPP

#include <ae/base/KeyboardUpdateData.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Hid
//@{
/// @brief キーボード。
/// @details
/// マスターとなるキーボードは Hid が所持しています。 @n
/// @n
/// キーボードのコピーをアプリケーションが持つことによって
/// 「ポーズ中はキー情報を更新しないキーボード」といった
/// 特殊なキーボードを作成することができます。
class Keyboard
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// 何も押されていない状態のキーボードを作成。
    Keyboard();
    //@}

    /// @name 更新
    //@{
    /// 状態を更新する。
    void update(const KeyboardUpdateData& aData);

    /// 前回の更新データを取得する。
    const KeyboardUpdateData lastUpdateData()const;
    //@}

    /// @name 状態取得
    //@{
    bool isHold(KeyKind::EnumType aKind)const;    ///< 押されているか。
    bool isTrigger(KeyKind::EnumType aKind)const; ///< 押された瞬間か。
    bool isRepeat(KeyKind::EnumType aKind)const;  ///< 押しっぱなしの状態で入力が入ったか。
    bool isPulse(KeyKind::EnumType aKind)const;   ///< isTrigger() || isRepeat()。
    bool isRelease(KeyKind::EnumType aKind)const; ///< 離された瞬間か。
    //@}

    /// @name ビットセット取得
    //@{
    const KeyBitSet hold()const;    ///< isHold() のビットセット。
    const KeyBitSet trigger()const; ///< isTrigger() のビットセット。
    const KeyBitSet repeat()const;  ///< isRepeat() のビットセット。
    const KeyBitSet pulse()const;   ///< isPulse() のビットセット。
    const KeyBitSet release()const; ///< isRelease() のビットセット。
    //@}

private:
    KeyboardUpdateData mData;
    KeyBitSet mTrigger;
    KeyBitSet mRepeat;
    KeyBitSet mPulse;
    KeyBitSet mRelease;
};
//@}

}} // namespace
#endif
// EOF
