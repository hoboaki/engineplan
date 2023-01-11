// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_AABBOX2I_HPP)
#else
#define AE_BASE_INCLUDED_AABBOX2I_HPP

#include <ae/base/Vector2i.hpp>

namespace ae::base {
class Aabb2;
struct Extent2iPod;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// @brief 整数型2次元AABB(Axis Aligned Bounding Box)。
/// @details
/// float版のAABBとは領域の示し方が異なるので注意してください。@n
/// float版は Min() と Max() で表現していますが、
/// int版は Begin() と End() で表現しています。@n
/// また、float版とは異なり End() 上の点は範囲内とは判定しません。@n
/// @n
/// このようなルールを設けるため、AABB内の各セルの処理について次のようなfor分を書くことを想定しています。@n
/// 経験上、整数版のAABBはこのほうが使い勝手がよいと作者は考えています。@n
/// @code
/// void func(const Aabb2i& aABB)
/// {
///     for (int y = aABB.Begin().y; t < aABB.End().y; ++y) {
///         for (int x = aABB.Begin().x; t < aABB.End().x; ++x) {
///         }
///     }
/// }
/// @endcode
class Aabb2i {
public:
    //------------------------------------------------------------------------------
    /// @name 定数
    //@{
    static const Aabb2i Largest(); ///< 全てを包むAABB。
    //@}

    //------------------------------------------------------------------------------
    /// @name コンストラクタ
    //@{
    Aabb2i(); ///< Aabb2i( Vector2i::Zero() ) で作成。
    Aabb2i(const Vector2iPod& begin); ///< Aabb2i( pos , 0 , 0 ) で作成。
    Aabb2i(
        const Vector2iPod& begin,
        int width,
        int height); ///< 基準となる点とサイズを指定してAABBを作成。
    Aabb2i(
        const Vector2iPod& begin,
        const Extent2iPod&
            extent); ///< 基準となる点と範囲を指定してAABBを作成。
    //@}

    //------------------------------------------------------------------------------
    /// @name 点の取得
    //@{
    const Vector2iPod Begin() const; ///< AABBの基準点を取得。
    const Vector2iPod End() const; ///< AABBの端点を取得。
    const Vector2iPod Min() const; ///< Begin() のエイリアス。
    const Vector2iPod Term() const; ///< End() のエイリアス。
    //@}

    //------------------------------------------------------------------------------
    /// @name 大きさの取得
    //@{
    int Width() const; ///< xの幅を取得。
    int Height() const; ///< yの幅を取得。
    Extent2iPod Extent() const; ///< 範囲を取得。
    //@}

    //------------------------------------------------------------------------------
    /// @name 正領域
    //@{
    bool IsPositive() const; ///< Begin() が (0,0) 以上か。
    const Aabb2i ToPositive()
        const; ///< Begin() が (0,0) 未満なら (0,0) 以上になるようにしたAABBを取得する。
    //@}

    //------------------------------------------------------------------------------
    /// @name 結合
    //@{
    const Aabb2i Merge(
        const Aabb2i& aABB) const; ///< 自分自身と指定のAABBを含むAABBを取得。
    void MergeAssign(
        const Aabb2i& aABB); ///< 自分自身と指定のAABBを含むAABBに設定する。
    //@}

    //------------------------------------------------------------------------------
    /// @name 判定
    //@{
    /// @brief 指定のAABBが重なっているか。
    /// @details
    /// Term() 線上は重なっていないとして判定します。
    bool IsIntersects(const Aabb2i& aABB) const;

    /// @brief 指定の点を含んでいるか。
    /// @return Begin() <= pos && pos() < End()
    bool IsContains(const Vector2iPod& pos) const;

    /// @brief 指定のAABBを含んでいるか。
    /// @details
    /// Term() 線上は重なっていないとして判定します。
    bool IsContains(const Aabb2i& aABB) const;
    //@}

    //------------------------------------------------------------------------------
    /// @name 四則演算
    //@{
    const Aabb2i Add(const Vector2iPod& trans)
        const; ///< Min() Term() に値を加算した結果を取得する。
    const Aabb2i Sub(const Vector2iPod& trans)
        const; ///< Min() Term() から値を減算した結果を取得する。
    void AddAssign(const Vector2iPod& trans); ///< Min() Term() に値を加算する。
    void SubAssign(
        const Vector2iPod& trans); ///< Min() Term() から値を減算する。
    //@}

    //------------------------------------------------------------------------------
    /// @name 演算子オーバーロード
    //@{
    const Aabb2i operator+(const Vector2iPod&) const; ///< Add() 。
    const Aabb2i operator-(const Vector2iPod&) const; ///< Sub() 。
    Aabb2i& operator+=(const Vector2iPod&); ///< AddAssign() 。
    Aabb2i& operator-=(const Vector2iPod&); ///< SubAssign() 。
    //@}

    //------------------------------------------------------------------------------
    /// @name 変換
    //@{
    const Aabb2 ToAABB2f() const; ///< Aabb2( Min() , Term() ) に変換。
    //@}

private:
    Vector2i min_;
    Vector2i term_;
};
//@}

} // namespace ae::base
#endif
// EOF
