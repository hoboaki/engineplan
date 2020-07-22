// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_AABBOX2I_HPP)
#else
#define AE_BASE_INCLUDED_AABBOX2I_HPP

#include <ae/base/Vector2i.hpp>

namespace ae {
namespace base {
class Aabb2;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Math
//@{
/// @brief 整数型2次元AABB(Axis Aligned Bounding Box)。
/// @details
/// float版のAABBとは領域の示し方が異なるので注意してください。@n
/// float版は min() と max() で表現していますが、
/// int版は begin() と end() で表現しています。@n
/// また、float版とは異なり end() 上の点は範囲内とは判定しません。@n
/// @n
/// このようなルールを設けるため、AABB内の各セルの処理について次のようなfor分を書くことを想定しています。@n
/// 経験上、整数版のAABBはこのほうが使い勝手がよいと作者は考えています。@n
/// @code
/// void func(const Aabb2i& aAABB)
/// {
///     for (int y = aAABB.begin().y; t < aAABB.end().y; ++y) {
///         for (int x = aAABB.begin().x; t < aAABB.end().x; ++x) {
///         }
///     }
/// }
/// @endcode
class Aabb2i
{
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
    Aabb2i(const Vector2iPod& aBegin); ///< Aabb2i( aPos , 0 , 0 ) で作成。
    Aabb2i(const Vector2iPod& aBegin, int aWidth, int aHeight); ///< 基準となる点とサイズを指定してAABBを作成。
    //@}

    //------------------------------------------------------------------------------
    /// @name 点の取得
    //@{
    const Vector2iPod begin()const; ///< AABBの基準点を取得。
    const Vector2iPod end()const;   ///< AABBの端点を取得。
    const Vector2iPod min()const;  ///< begin() のエイリアス。
    const Vector2iPod term()const; ///< end() のエイリアス。
    //@}

    //------------------------------------------------------------------------------
    /// @name 大きさの取得
    //@{
    int width()const;  ///< xの幅を取得。
    int height()const; ///< yの幅を取得。
    //@}

    //------------------------------------------------------------------------------
    /// @name 正領域
    //@{
    bool isPositive()const; ///< begin() が (0,0) 以上か。
    const Aabb2i toPositive()const; ///< begin() が (0,0) 未満なら (0,0) 以上になるようにしたAABBを取得する。
    //@}

    //------------------------------------------------------------------------------
    /// @name 結合
    //@{
    const Aabb2i merge(const Aabb2i& aAABB)const; ///< 自分自身と指定のAABBを含むAABBを取得。
    void mergeAssign(const Aabb2i& aAABB); ///< 自分自身と指定のAABBを含むAABBに設定する。
    //@}

    //------------------------------------------------------------------------------
    /// @name 判定
    //@{
    /// @brief 指定のAABBが重なっているか。
    /// @details 
    /// term() 線上は重なっていないとして判定します。
    bool isIntersects(const Aabb2i& aAABB)const;

    /// @brief 指定の点を含んでいるか。
    /// @return begin() <= aPos && aPos() < end()
    bool isContains(const Vector2iPod& aPos)const;

    /// @brief 指定のAABBを含んでいるか。
    /// @details
    /// term() 線上は重なっていないとして判定します。
    bool isContains(const Aabb2i& aAABB)const;
    //@}

    //------------------------------------------------------------------------------
    /// @name 四則演算
    //@{
    const Aabb2i add(const Vector2iPod& aTrans)const; ///< min() term() に値を加算した結果を取得する。
    const Aabb2i sub(const Vector2iPod& aTrans)const; ///< min() term() から値を減算した結果を取得する。
    void addAssign(const Vector2iPod& aTrans); ///< min() term() に値を加算する。
    void subAssign(const Vector2iPod& aTrans); ///< min() term() から値を減算する。
    //@}

    //------------------------------------------------------------------------------
    /// @name 演算子オーバーロード
    //@{
    const Aabb2i operator+(const Vector2iPod&)const; ///< add() 。
    const Aabb2i operator-(const Vector2iPod&)const; ///< sub() 。
    Aabb2i& operator+=(const Vector2iPod&); ///< addAssign() 。
    Aabb2i& operator-=(const Vector2iPod&); ///< subAssign() 。
    //@}

    //------------------------------------------------------------------------------
    /// @name 変換
    //@{
    const Aabb2 toAABB2f()const; ///< Aabb2( min() , term() ) に変換。
    //@}

private:
    Vector2i mMin;
    Vector2i mTerm;
};
//@}

}} // namespace
#endif
// EOF
