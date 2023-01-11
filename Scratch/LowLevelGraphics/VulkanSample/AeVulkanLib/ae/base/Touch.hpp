// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_TOUCH_HPP)
#else
#define AE_BASE_INCLUDED_TOUCH_HPP

#include <ae/base/TouchTap.hpp>
#include <ae/base/TouchUpdateData.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Hid
//@{
/// @brief タッチ入力。
/// @details
/// マルチタッチをサポートします。@n
class Touch {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// @briefコンストラクタ。
    /// @param tapCount 要求する最大タップ数。
    /// @details
    /// tapCountはシングルタップなら1、マルチタップなら2以上を指定してください。@n
    /// 最大でも TouchUpdateData::TAP_COUNT_MAX までしか指定できません。@n
    Touch(int tapCount);

    /// デストラクタ。
    ~Touch();
    //@}

    /// @name 更新
    //@{
    /// 状態を更新する。
    void Update(const TouchUpdateData& data);

    /// 前回の更新データを取得する。
    const TouchUpdateData LastUpdateData() const;
    //@}

    /// @name 入力取得
    //@{
    /// @brief タップ入力の総数を取得。
    int TapCount() const;

    /// @brief 指定番目の入力を取得します。
    /// @details
    /// 0番がタッチ -> 1番がタッチ -> 0番がリリースされたとき
    /// 配列的には穴が空いてしまう状態になりますが
    /// 次のフレームでも1番のタッチ位置は取得できます。
    const TouchTap TapAtIndex(int index) const;
    //@}

private:
    int tapCount_;
    TouchUpdateData data_;
    TouchTap taps_[TouchUpdateData::TAP_COUNT_MAX];
};
//@}

} // namespace ae::base
#endif
// EOF
