// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_VECTOR2I_HPP)
#else
#define AE_BASE_INCLUDED_VECTOR2I_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ShortString.hpp>

namespace ae::base {
struct Vector2Pod;
struct Vector3iPod;
struct Vector4iPod;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// @brief 整数型2次元ベクトル構造体。
/// @details
/// 使用頻度のことを考えて Vec2i という名前でもアクセスできます。
/// メモリ配置は32bit符号有り整数が先頭からx,yの順番に並んでいます。
struct Vector2iPod
{
    //============================================================
    /// @name 定数取得
    //@{
    static const Vector2iPod Zero(); ///< 0ベクトル。
    static const Vector2iPod One(); ///< X,Yが全て1のベクトル。
    static const Vector2iPod Min(); ///< 最小値のベクトル。
    static const Vector2iPod Max(); ///< 最大値のベクトル。
    static const Vector2iPod UnitX(); ///< X単位ベクトル。
    static const Vector2iPod UnitY(); ///< Y単位ベクトル。
    static const Vector2iPod NegUnitX(); ///< -X単位ベクトル。
    static const Vector2iPod NegUnitY(); ///< -Y単位ベクトル。
    //@}

    //============================================================
    /// @name 変数
    //@{
    s32 x; ///< x。
    s32 y; ///< y。
    //@}

    //============================================================
    /// @name 変換
    //@{
    const Vector2iPod ToX0() const;
    const Vector2iPod To0Y() const;
    const Vector2iPod ToXX() const;
    const Vector2iPod ToYX() const;
    const Vector2iPod ToYY() const;
    const Vector3iPod ToXY0() const;
    const Vector3iPod ToXXX() const;
    const Vector3iPod ToYYY() const;
    const Vector4iPod ToXY00() const;
    const Vector4iPod ToXXXX() const;
    const Vector4iPod ToYYYY() const;
    const Vector2Pod ToXYf() const;
    //@}

    //============================================================
    /// @name 等価比較
    //@{
    bool Equals(const Vector2iPod&) const; ///< 等価比較。
    //@}

    //============================================================
    /// @name 四則演算
    //@{
    const Vector2iPod Add(s32) const; ///< 各要素に値を加算した結果を取得する。
    const Vector2iPod Sub(
        s32) const; ///< 各要素から値を減算した結果を取得する。
    const Vector2iPod Mul(s32) const; ///< 各要素に値をかけた結果を取得する。
    const Vector2iPod Div(s32) const; ///< 各要素から値をわった結果を取得する。
    const Vector2iPod Add(
        const Vector2iPod&) const; ///< 対応する値同士を加算した結果を取得する。
    const Vector2iPod Sub(const Vector2iPod&)
        const; ///< 対応する値に対して減算した結果を取得する。
    const Vector2iPod Mul(
        const Vector2iPod&) const; ///< 対応する値同士をかけた結果を取得する。
    const Vector2iPod Div(const Vector2iPod&)
        const; ///< 対応する値に対して割り算をした結果を取得する。
    void AddAssign(s32); ///< 各要素に値を加算する。
    void SubAssign(s32); ///< 各要素から値を減算する。
    void MulAssign(s32); ///< 各要素に値をかける。
    void DivAssign(s32); ///< 各要素から値をわる。
    void AddAssign(const Vector2iPod&); ///< 対応する値同士を加算する。
    void SubAssign(const Vector2iPod&); ///< 対応する値に対して減算する。
    void MulAssign(const Vector2iPod&); ///< 対応する値同士をかける。
    void DivAssign(const Vector2iPod&); ///< 対応する値に対して割り算をする。
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Vector2iPod operator+(s32) const; ///< Add()。
    const Vector2iPod operator-(s32) const; ///< Sub()。
    const Vector2iPod operator*(s32) const; ///< Mul()。
    const Vector2iPod operator/(s32) const; ///< Div()。
    const Vector2iPod operator+(const Vector2iPod&) const; ///< Add()。
    const Vector2iPod operator-(const Vector2iPod&) const; ///< Sub()。
    const Vector2iPod operator*(const Vector2iPod&) const; ///< Mul()。
    const Vector2iPod operator/(const Vector2iPod&) const; ///< Div()。
    const Vector2iPod operator-() const; ///< Neg()。
    Vector2iPod& operator+=(s32); ///< AddAssign()。
    Vector2iPod& operator-=(s32); ///< SubAssign()。
    Vector2iPod& operator*=(s32); ///< MulAssign()。
    Vector2iPod& operator/=(s32); ///< DivAssign()。
    Vector2iPod& operator+=(const Vector2iPod&); ///< AddAssign()。
    Vector2iPod& operator-=(const Vector2iPod&); ///< SubAssign()。
    Vector2iPod& operator*=(const Vector2iPod&); ///< MulAssign()。
    Vector2iPod& operator/=(const Vector2iPod&); ///< DivAssign()。
    //@}

    //============================================================
    /// @name 選択
    //@{
    const Vector2iPod Min(const Vector2iPod&)
        const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
    const Vector2iPod Max(const Vector2iPod&)
        const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
    //@}

    //============================================================
    /// @name クランプ
    //@{
    const Vector2iPod Clamp(const Vector2iPod& min, const Vector2iPod& max)
        const; ///< min以上aMax以下になるようにクランプする。
    const Vector2iPod ClampPositive()
        const; ///< Clamp( Zero() , Max() ) を取得する。
    const Vector2iPod ClampNegative()
        const; ///< Clamp( Min() , Zero() ) を取得する。
    //@}

    //============================================================
    /// @name 符号
    //@{
    const Vector2iPod Abs() const; ///< 各要素を正に置き換えたベクトルを取得。
    const Vector2iPod Neg() const; ///< 符号を反転させた結果を取得する。
    bool IsPositive() const; ///< 各要素が0以上か。
    //@}

    //============================================================
    /// @name 長さ
    //@{
    bool IsZero() const; ///< 全てが0か。
    //@}

    //============================================================
    /// @name ユーティリティ
    //@{
    /// x,y形式の文字列に変換。
    const ShortString ToShortString() const;
    //@}
};

/// Vector2iPod のクラス版。
class Vector2i : public Vector2iPod {
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Vector2i(); ///< Zero() で作成。
    Vector2i(const Vector2iPod& xY); ///< コピーして作成。
    Vector2i(s32 v); ///< 全要素同じ値で作成。
    Vector2i(s32 x, s32 y); ///< XYを指定して作成。
    //@}
};

/// Vector2iPod のエイリアス。
typedef Vector2iPod Vec2i;
//@}

} // namespace ae::base
#endif
// EOF
