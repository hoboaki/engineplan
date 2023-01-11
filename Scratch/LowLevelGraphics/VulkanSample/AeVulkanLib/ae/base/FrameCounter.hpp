// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_FRAMECOUNTER_HPP)
#else
#define AE_BASE_INCLUDED_FRAMECOUNTER_HPP

#include <ae/base/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Util
//@{
/// フレームカウンター。
class FrameCounter {
public:
    /// @name コンストラクタ
    //@{
    FrameCounter(); ///< 総フレーム数0で作成。
    FrameCounter(int totalFrame); ///< 総フレーム数を指定して作成。
    //@{

    /// @name リセット
    //@{
    void Reset(); ///< 設定済みの総フレーム数でリセット。
    void Reset(int totalFrame); ///< 新しい総フレーム数を指定してリセット。
    //@}

    /// @name 更新
    //@{
    /// @brief フレームを1進める。
    /// @details IsEnd() 状態なら何もしません。
    void Advance();

    /// @brief フレームを1進める。
    /// @details IsEnd() 状態で呼ぶとエラーになります。
    void AdvanceStrict();

    /// @brief 最終フレームまで進める。
    void ToEnd();
    //@}

    /// @name 取得
    //@{
    int Frame() const; ///< 現在のフレーム数。
    int TotalFrame() const; ///< 総フレーム数。
    bool IsEnd() const; ///< 現在のフレームが総フレームに達しているか。
    bool IsCounting() const; ///< 現在のフレームが総フレームに達していないか。
    float RateFrame() const; ///< 0.0f <= 1.0f の範囲に正規化されたフレーム。
    float InvRateFrame() const; ///< 1.0f - RateFrame()。
    //@}

private:
    int frame_;
    int totalFrame_;
};
//@}

} // namespace ae::base
#endif
// EOF
