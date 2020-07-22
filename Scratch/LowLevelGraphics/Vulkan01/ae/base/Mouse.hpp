// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_MOUSE_HPP)
#else
#define AE_BASE_INCLUDED_MOUSE_HPP

#include <ae/base/MouseUpdateData.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Hid
//@{
/// @brief マウス。
/// @details
/// マスターとなるマウスは Hid が所持しています。 @n
/// @n
/// マウスのコピーをアプリケーションが持つことによって
/// 「ポーズ中はキー情報を更新しないマウス」といった
/// 特殊なマウスを作成することができます。
class Mouse
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// 何も押されていない画面外状態のマウスを作成。
    Mouse();
    //@}

    /// @name 更新
    //@{
    /// 状態を更新する。
    void update(const MouseUpdateData& aData);

    /// 前回の更新データを取得する。
    const MouseUpdateData lastUpdateData()const;
    //@}

    /// @name カーソル位置取得
    //@{
    /// @brief 最新のカーソル位置情報がとれるか。
    /// @details
    /// カーソルがウィンドウ外などに移動して位置情報がとれなかったときにfalseを返します。@n
    /// false なら pos() は最後に更新された位置を返します。@n
    bool isPosUpdated()const;

    /// @brief カーソル位置を取得する。
    /// @see isPosUpdated()
    /// @details
    /// 初期値は(0,0)を返します。
    const ScreenPosPod pos()const;
    //@}

    /// @name ボタンの状態取得
    //@{
    bool isHold(MouseBtnKind::EnumType aKind)const;    ///< 押されているか。
    bool isTrigger(MouseBtnKind::EnumType aKind)const; ///< 押された瞬間か。
    bool isRelease(MouseBtnKind::EnumType aKind)const; ///< 離された瞬間か。
    //@}

    /// @name ボタンのビットセット取得
    //@{
    const MouseBtnBitSet hold()const;    ///< isHold() のビットセット。
    const MouseBtnBitSet trigger()const; ///< isTrigger() のビットセット。
    const MouseBtnBitSet release()const; ///< isRelease() のビットセット。
    //@}

private:
    MouseUpdateData mData;
    ScreenPos       mPos;
    MouseBtnBitSet  mTrigger;
    MouseBtnBitSet  mRelease;
};
//@}

}} // namespace
#endif
// EOF
