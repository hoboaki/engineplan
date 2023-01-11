// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_MOUSE_HPP)
#else
#define AE_BASE_INCLUDED_MOUSE_HPP

#include <ae/base/MouseUpdateData.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Hid
//@{
/// @brief マウス。
/// @details
/// マスターとなるマウスは Hid が所持しています。 @n
/// @n
/// マウスのコピーをアプリケーションが持つことによって
/// 「ポーズ中はキー情報を更新しないマウス」といった
/// 特殊なマウスを作成することができます。
class Mouse {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// 何も押されていない画面外状態のマウスを作成。
    Mouse();
    //@}

    /// @name 更新
    //@{
    /// 状態を更新する。
    void Update(const MouseUpdateData& data);

    /// 前回の更新データを取得する。
    const MouseUpdateData LastUpdateData() const;
    //@}

    /// @name カーソル位置取得
    //@{
    /// @brief 最新のカーソル位置情報がとれるか。
    /// @details
    /// カーソルがウィンドウ外などに移動して位置情報がとれなかったときにfalseを返します。@n
    /// false なら Pos() は最後に更新された位置を返します。@n
    bool IsPosUpdated() const;

    /// @brief カーソル位置を取得する。
    /// @see IsPosUpdated()
    /// @details
    /// 初期値は(0,0)を返します。
    const ScreenPosPod Pos() const;
    //@}

    /// @name ボタンの状態取得
    //@{
    bool IsHold(MouseBtnKind::EnumType kind) const; ///< 押されているか。
    bool IsTrigger(MouseBtnKind::EnumType kind) const; ///< 押された瞬間か。
    bool IsRelease(MouseBtnKind::EnumType kind) const; ///< 離された瞬間か。
    //@}

    /// @name ボタンのビットセット取得
    //@{
    const MouseBtnBitSet Hold() const; ///< IsHold() のビットセット。
    const MouseBtnBitSet Trigger() const; ///< IsTrigger() のビットセット。
    const MouseBtnBitSet Release() const; ///< IsRelease() のビットセット。
    //@}

private:
    MouseUpdateData data_;
    ScreenPos pos_;
    MouseBtnBitSet trigger_;
    MouseBtnBitSet release_;
};
//@}

} // namespace ae::base
#endif
// EOF
