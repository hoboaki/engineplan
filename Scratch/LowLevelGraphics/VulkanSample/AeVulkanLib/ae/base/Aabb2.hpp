// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_AABBOX2_HPP)
#else
#define AE_BASE_INCLUDED_AABBOX2_HPP

#include <ae/base/Vector2.hpp>

namespace ae::base {
class Aabb2i;
struct Extent2Pod;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @Addtogroup AeBase-Math
//@{
/// @brief 浮動小数型2次元AABB(Axis Aligned Bounding Box)。
/// @details
/// 四則演算のAdd( AABB ),Mul( scale
/// )は２つのAABBの補間を実現するために実装しています。@n
class Aabb2 {
public:
    //------------------------------------------------------------------------------
    /// @name コンストラクタ
    //@{
    Aabb2(); ///< Aabb2( Vector2::Zero() ) で作成。
    Aabb2(const Vector2Pod& pos); ///< 1点を含むAABBを作成。
    Aabb2(
        const Vector2Pod& pos1,
        const Vector2Pod& pos2); ///< 2点を含むAABBを作成。
    Aabb2(
        const Vector2Pod& pos,
        const Extent2Pod& extent); ///< 基準となる点と範囲を指定してAABBを作成。
    //@}

    //------------------------------------------------------------------------------
    /// @name 点の取得
    //@{
    const Vector2Pod Min() const; ///< AABBの小さい方の点を取得。
    const Vector2Pod Max() const; ///< AABBの大きい方の点を取得。
    const Vector2Pod Center() const; ///< AABBの中心点を取得。
    const Vector2Pod PosLb() const; ///< Vector2( Left()  , Bottom() )を取得。
    const Vector2Pod PosRb() const; ///< Vector2( Right() , Bottom() )を取得。
    const Vector2Pod PosLt() const; ///< Vector2( Left()  , Top() )を取得。
    const Vector2Pod PosRt() const; ///< Vector2( Right() , Top() )を取得。
    float Left() const; ///< Min().xを取得。
    float Right() const; ///< Max().xを取得。
    float Bottom() const; ///< Min().yを取得。
    float Top() const; ///< Max().yを取得。
    //@}

    //------------------------------------------------------------------------------
    /// @name 大きさの取得
    //@{
    float Width() const; ///< xの幅を取得。
    float Height() const; ///< yの幅を取得。
    Extent2Pod Extent() const; ///< 範囲を取得。
    const Vector2Pod Size() const; ///< Vector2( Width() , Height() ) を取得。
    const Vector2Pod HalfSize() const; ///< Size() * 0.5f を取得。
    //@}

    //------------------------------------------------------------------------------
    /// @name 結合。
    //@{
    const Aabb2 Merge(
        const Vector2Pod& pos) const; ///< 自分自身と指定の点を含むAABBを取得。
    const Aabb2 Merge(
        const Aabb2& aABB) const; ///< 自分自身と指定のAABBを含むAABBを取得。
    void MergeAssign(
        const Vector2Pod& pos); ///< 自分自身と指定の点を含むAABBに設定する。
    void MergeAssign(
        const Aabb2& aABB); ///< 自分自身と指定のAABBを含むAABBに設定する。
    //@}

    //------------------------------------------------------------------------------
    /// @name 判定
    //@{
    /// @brief 指定のAABBが重なっているか。
    /// @details
    /// 同線上は重なっているとして判定します。
    bool IsIntersects(const Aabb2& aABB) const;

    /// @brief 指定の点を含んでいるか。
    /// @details
    /// 線上は含んでいるとして判定します。
    bool IsContains(const Vector2Pod& pos) const;

    /// @brief 指定のAABBを含んでいるか。
    /// @details
    /// 同線上は含んでいると判定しています。
    bool IsContains(const Aabb2& aABB) const;
    //@}

    //------------------------------------------------------------------------------
    /// @name 四則演算
    //@{
    const Aabb2 Add(const Vector2Pod& trans)
        const; ///< Min() Max() に値を加算した結果を取得する。
    const Aabb2 Sub(const Vector2Pod& trans)
        const; ///< Min() Max() から値を減算した結果を取得する。
    const Aabb2 Add(const Aabb2& aABB)
        const; ///< Min() Max() をそれぞれ加算した結果を取得する。
    const Aabb2 Sub(const Aabb2& aABB)
        const; ///< Min() Max() をそれぞれ減算した結果を取得する。
    const Aabb2 Mul(
        f32 scale) const; ///< Min() Max() に値を乗算した結果を取得する。
    void AddAssign(const Vector2Pod& trans); ///< Min() Max() に値を加算する。
    void SubAssign(const Vector2Pod& trans); ///< Min() Max() から値を減算する。
    void AddAssign(const Aabb2& aABB); ///< Min() Max() をそれぞれ加算する。
    void SubAssign(const Aabb2& aABB); ///< Min() Max() をそれぞれ減算する。
    void MulAssign(f32 scale); ///< Min() Max() に値を乗算する。
    //@}

    //------------------------------------------------------------------------------
    /// @name 演算子オーバーロード
    //@{
    const Aabb2 operator+(const Vector2Pod&) const; ///< Add() 。
    const Aabb2 operator-(const Vector2Pod&) const; ///< Sub() 。
    const Aabb2 operator+(const Aabb2&) const; ///< Add() 。
    const Aabb2 operator-(const Aabb2&) const; ///< Sub() 。
    const Aabb2 operator*(f32) const; ///< Mul() 。
    Aabb2& operator+=(const Vector2Pod&); ///< AddAssign() 。
    Aabb2& operator-=(const Vector2Pod&); ///< SubAssign() 。
    Aabb2& operator+=(const Aabb2&); ///< AddAssign() 。
    Aabb2& operator-=(const Aabb2&); ///< SubAssign() 。
    Aabb2& operator*=(f32); ///< MulAssign() 。
    //@}

    //------------------------------------------------------------------------------
    /// @name 変換
    //@{
    const Aabb2i ToAabb2i()
        const; ///< 切り捨てたMin()、切り上げたMax()の値を使って整数版AABBに変換。
    //@}
private:
    Vector2 min_;
    Vector2 max_;
};
//@}

} // namespace ae::base
#endif
// EOF
