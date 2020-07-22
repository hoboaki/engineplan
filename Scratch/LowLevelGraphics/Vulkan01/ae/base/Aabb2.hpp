// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_AABBOX2_HPP)
#else
#define AE_BASE_INCLUDED_AABBOX2_HPP

#include <ae/base/Vector2.hpp>

namespace ae {
namespace base {
class Aabb2i;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Math
//@{
/// @brief 浮動小数型2次元AABB(Axis Aligned Bounding Box)。
/// @details
/// 四則演算のadd( AABB ),mul( scale )は２つのAABBの補間を実現するために実装しています。@n
class Aabb2
{
public:
    //------------------------------------------------------------------------------
    /// @name コンストラクタ
    //@{
    Aabb2(); ///< Aabb2( Vector2::Zero() ) で作成。
    Aabb2(const Vector2Pod& aPos); ///< 1点を含むAABBを作成。
    Aabb2(const Vector2Pod& aPos1, const Vector2Pod& aPos2); ///< 2点を含むAABBを作成。
    //@}

    //------------------------------------------------------------------------------
    /// @name 点の取得
    //@{
    const Vector2Pod min()const;    ///< AABBの小さい方の点を取得。
    const Vector2Pod max()const;    ///< AABBの大きい方の点を取得。
    const Vector2Pod center()const; ///< AABBの中心点を取得。
    const Vector2Pod posLB()const; ///< Vector2( left()  , bottom() )を取得。
    const Vector2Pod posRB()const; ///< Vector2( right() , bottom() )を取得。
    const Vector2Pod posLT()const; ///< Vector2( left()  , top() )を取得。
    const Vector2Pod posRT()const; ///< Vector2( right() , top() )を取得。
    float left()const;   ///< min().xを取得。
    float right()const;  ///< max().xを取得。
    float bottom()const; ///< min().yを取得。
    float top()const;    ///< max().yを取得。
    //@}

    //------------------------------------------------------------------------------
    /// @name 大きさの取得
    //@{
    float width()const;  ///< xの幅を取得。
    float height()const; ///< yの幅を取得。
    const Vector2Pod size()const;     ///< Vector2( width() , height() ) を取得。
    const Vector2Pod halfSize()const; ///< size() * 0.5f を取得。
    //@}

    //------------------------------------------------------------------------------
    /// @name 結合。
    //@{
    const Aabb2 merge(const Vector2Pod& aPos)const; ///< 自分自身と指定の点を含むAABBを取得。
    const Aabb2 merge(const Aabb2& aAABB)const; ///< 自分自身と指定のAABBを含むAABBを取得。
    void mergeAssign(const Vector2Pod& aPos); ///< 自分自身と指定の点を含むAABBに設定する。
    void mergeAssign(const Aabb2& aAABB); ///< 自分自身と指定のAABBを含むAABBに設定する。
    //@}

    //------------------------------------------------------------------------------
    /// @name 判定
    //@{
    /// @brief 指定のAABBが重なっているか。
    /// @details 
    /// 同線上は重なっているとして判定します。
    bool isIntersects(const Aabb2& aAABB)const;

    /// @brief 指定の点を含んでいるか。
    /// @details 
    /// 線上は含んでいるとして判定します。
    bool isContains(const Vector2Pod& aPos)const;

    /// @brief 指定のAABBを含んでいるか。
    /// @details
    /// 同線上は含んでいると判定しています。
    bool isContains(const Aabb2& aAABB)const;
    //@}

    //------------------------------------------------------------------------------
    /// @name 四則演算
    //@{
    const Aabb2 add(const Vector2Pod& aTrans)const; ///< min() max() に値を加算した結果を取得する。
    const Aabb2 sub(const Vector2Pod& aTrans)const; ///< min() max() から値を減算した結果を取得する。
    const Aabb2 add(const Aabb2& aAABB)const; ///< min() max() をそれぞれ加算した結果を取得する。
    const Aabb2 sub(const Aabb2& aAABB)const; ///< min() max() をそれぞれ減算した結果を取得する。
    const Aabb2 mul(f32 aScale)const; ///< min() max() に値を乗算した結果を取得する。
    void addAssign(const Vector2Pod& aTrans); ///< min() max() に値を加算する。
    void subAssign(const Vector2Pod& aTrans); ///< min() max() から値を減算する。
    void addAssign(const Aabb2& aAABB); ///< min() max() をそれぞれ加算する。
    void subAssign(const Aabb2& aAABB); ///< min() max() をそれぞれ減算する。
    void mulAssign(f32 aScale); ///< min() max() に値を乗算する。
    //@}

    //------------------------------------------------------------------------------
    /// @name 演算子オーバーロード
    //@{
    const Aabb2 operator+(const Vector2Pod&)const; ///< add() 。
    const Aabb2 operator-(const Vector2Pod&)const; ///< sub() 。
    const Aabb2 operator+(const Aabb2&)const; ///< add() 。
    const Aabb2 operator-(const Aabb2&)const; ///< sub() 。
    const Aabb2 operator*(f32)const; ///< mul() 。
    Aabb2& operator+=(const Vector2Pod&); ///< addAssign() 。
    Aabb2& operator-=(const Vector2Pod&); ///< subAssign() 。
    Aabb2& operator+=(const Aabb2&); ///< addAssign() 。
    Aabb2& operator-=(const Aabb2&); ///< subAssign() 。
    Aabb2& operator*=(f32); ///< mulAssign() 。
    //@}

    //------------------------------------------------------------------------------
    /// @name 変換
    //@{
    const Aabb2i toAABB2i()const; ///< 切り捨てたmin()、切り上げたmax()の値を使って整数版AABBに変換。
    //@}
private:
    Vector2 mMin;
    Vector2 mMax;
};
//@}

}} // namespace
#endif
// EOF
