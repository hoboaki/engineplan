// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_TOUCHTAP_HPP)
#else
#define AE_BASE_INCLUDED_TOUCHTAP_HPP

#include <ae/base/TouchTapUpdateData.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Hid
//@{
/// @brief タッチのタップ入力。
class TouchTap {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    TouchTap();
    ~TouchTap();
    //@}

    /// @name 更新
    //@{
    /// 状態を更新する。
    void Update(const TouchTapUpdateData& data);

    /// 前回の更新データを取得する。
    const TouchTapUpdateData LastUpdateData() const;
    //@}

    /// @name 状態取得
    //@{
    /// @brief タップ数を返す。
    /// @details
    /// 押されていなければ0、シングルタップなら1、ダブルタップなら2を返します。@n
    /// 3以上のタップ数をサポートしている環境なら3以上の値を返します。@n
    int TapCount() const;

    /// @brief 押している位置。
    /// @details 離している状態なら最後に押していた位置を返します。
    const ScreenPosPod Pos() const;

    bool IsHold() const; ///< 押されているか。
    bool IsTrigger() const; ///< 押された瞬間か。
    bool IsRelease() const; ///< 離された瞬間か。
    //@}

private:
    TouchTapUpdateData data_;
    TouchTapUpdateData prevData_;
};
//@}

} // namespace ae::base
#endif
// EOF
