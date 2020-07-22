// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_TOUCH_HPP)
#else
#define AE_BASE_INCLUDED_TOUCH_HPP

#include <ae/base/TouchTap.hpp>
#include <ae/base/TouchUpdateData.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Hid
//@{
/// @brief タッチ入力。
/// @details
/// マルチタッチをサポートします。@n
class Touch
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// @briefコンストラクタ。
    /// @param aTapCount 要求する最大タップ数。
    /// @details
    /// aTapCountはシングルタップなら1、マルチタップなら2以上を指定してください。@n
    /// 最大でも TouchUpdateData::TAP_COUNT_MAX までしか指定できません。@n
    Touch(int aTapCount);

    /// デストラクタ。
    ~Touch();
    //@}

    /// @name 更新
    //@{
    /// 状態を更新する。
    void update(const TouchUpdateData& aData);

    /// 前回の更新データを取得する。
    const TouchUpdateData lastUpdateData()const;
    //@}

    /// @name 入力取得
    //@{
    /// @brief タップ入力の総数を取得。
    int tapCount()const;

    /// @brief 指定番目の入力を取得します。
    /// @details
    /// 0番がタッチ -> 1番がタッチ -> 0番がリリースされたとき
    /// 配列的には穴が空いてしまう状態になりますが
    /// 次のフレームでも1番のタッチ位置は取得できます。
    const TouchTap tapAtIndex(int aIndex)const;
    //@}

private:
    int mTapCount;
    TouchUpdateData mData;
    TouchTap mTaps[TouchUpdateData::TAP_COUNT_MAX];
};
//@}

}} // namespace
#endif
// EOF
