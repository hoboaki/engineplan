// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_VECTOR2_HPP)
#else
#define AE_BASE_INCLUDED_VECTOR2_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ShortString.hpp>

namespace ae::base {
struct Vector2Pod;
struct Vector3Pod;
struct Vector4Pod;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// Vector2Podのエイリアス。
typedef Vector2Pod Vec2;

/// @brief 浮動小数型2次元ベクトル構造体。
/// @details
/// 使用頻度のことを考えて Vec2 という名前でもアクセスできます。
/// メモリ配置は32bit浮動小数が先頭からx,yの順番に並んでいます。
struct Vector2Pod
{
    //============================================================
    /// @name 定数取得
    //@{
    static const Vector2Pod Zero(); ///< 0ベクトル。
    static const Vector2Pod One(); ///< X,Yが全て1のベクトル。
    static const Vector2Pod Min(); ///< 最小値のベクトル。
    static const Vector2Pod Max(); ///< 最大値のベクトル。
    static const Vector2Pod UnitX(); ///< X単位ベクトル。
    static const Vector2Pod UnitY(); ///< Y単位ベクトル。
    static const Vector2Pod NegUnitX(); ///< -X単位ベクトル。
    static const Vector2Pod NegUnitY(); ///< -Y単位ベクトル。
    //@}

    //============================================================
    /// @name 変数
    //@{
    f32 x; ///< x。
    f32 y; ///< y。
    //@}

    //============================================================
    /// @name 変換
    //@{
    const Vector2Pod ToX0() const;
    const Vector2Pod To0Y() const;
    const Vector2Pod ToXX() const;
    const Vector2Pod ToYX() const;
    const Vector2Pod ToYY() const;
    const Vector3Pod ToXY0() const;
    const Vector3Pod ToXXX() const;
    const Vector3Pod ToYYY() const;
    const Vector4Pod ToXY00() const;
    const Vector4Pod ToXXXX() const;
    const Vector4Pod ToYYYY() const;
    //@}

    //============================================================
    /// @name 等価比較
    //@{
    bool Equals(const Vector2Pod&) const; ///< 許容誤差を考慮した等価比較。
    bool EqualsStrict(
        const Vector2Pod&) const; ///< 許容誤差を許容しない等価比較。
    //@}

    //============================================================
    /// @name 四則演算
    //@{
    const Vector2Pod Add(f32) const; ///< 各要素に値を加算した結果を取得する。
    const Vector2Pod Sub(f32) const; ///< 各要素から値を減算した結果を取得する。
    const Vector2Pod Mul(f32) const; ///< 各要素に値をかけた結果を取得する。
    const Vector2Pod Div(f32) const; ///< 各要素から値をわった結果を取得する。
    const Vector2Pod Add(
        const Vector2Pod&) const; ///< 対応する値同士を加算した結果を取得する。
    const Vector2Pod Sub(const Vector2Pod&)
        const; ///< 対応する値に対して減算した結果を取得する。
    const Vector2Pod Mul(
        const Vector2Pod&) const; ///< 対応する値同士をかけた結果を取得する。
    const Vector2Pod Div(const Vector2Pod&)
        const; ///< 対応する値に対して割り算をした結果を取得する。
    void AddAssign(f32); ///< 各要素に値を加算する。
    void SubAssign(f32); ///< 各要素から値を減算する。
    void MulAssign(f32); ///< 各要素に値をかける。
    void DivAssign(f32); ///< 各要素から値をわる。
    void AddAssign(const Vector2Pod&); ///< 対応する値同士を加算する。
    void SubAssign(const Vector2Pod&); ///< 対応する値に対して減算する。
    void MulAssign(const Vector2Pod&); ///< 対応する値同士をかける。
    void DivAssign(const Vector2Pod&); ///< 対応する値に対して割り算をする。
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Vector2Pod operator+(f32) const; ///< Add()。
    const Vector2Pod operator-(f32) const; ///< Sub()。
    const Vector2Pod operator*(f32) const; ///< Mul()。
    const Vector2Pod operator/(f32) const; ///< Div()。
    const Vector2Pod operator+(const Vector2Pod&) const; ///< Add()。
    const Vector2Pod operator-(const Vector2Pod&) const; ///< Sub()。
    const Vector2Pod operator*(const Vector2Pod&) const; ///< Mul()。
    const Vector2Pod operator/(const Vector2Pod&) const; ///< Div()。
    const Vector2Pod operator-() const; ///< Neg()。
    Vector2Pod& operator+=(f32); ///< AddAssign()。
    Vector2Pod& operator-=(f32); ///< SubAssign()。
    Vector2Pod& operator*=(f32); ///< MulAssign()。
    Vector2Pod& operator/=(f32); ///< DivAssign()。
    Vector2Pod& operator+=(const Vector2Pod&); ///< AddAssign()。
    Vector2Pod& operator-=(const Vector2Pod&); ///< SubAssign()。
    Vector2Pod& operator*=(const Vector2Pod&); ///< MulAssign()。
    Vector2Pod& operator/=(const Vector2Pod&); ///< DivAssign()。
    //@}

    //============================================================
    /// @name 選択
    //@{
    const Vector2Pod Min(const Vector2Pod&)
        const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
    const Vector2Pod Max(const Vector2Pod&)
        const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
    //@}

    //============================================================
    /// @name クランプ
    //@{
    const Vector2Pod Clamp(const Vector2Pod& min, const Vector2Pod& max)
        const; ///< min以上aMax以下になるようにクランプする。
    const Vector2Pod ClampPositive()
        const; ///< Clamp( Zero() , Max() ) を取得する。
    const Vector2Pod ClampNegative()
        const; ///< Clamp( Min() , Zero() ) を取得する。
    //@}

    //============================================================
    /// @name 符号操作
    //@{
    const Vector2Pod Abs() const; ///< 各要素を正に置き換えたベクトルを取得。
    const Vector2Pod Neg() const; ///< 符号を反転させた結果を取得する。
    //@}

    //============================================================
    /// @name 長さ＆正規化
    //@{
    f32 SquareLength() const; ///< 長さの2乗を取得する。
    f32 Length() const; ///< 長さを取得する。
    f32 Distance(const Vector2Pod&) const; ///< あるベクトルとの距離を取得する。
    bool IsZero() const; ///< 長さが0か。許容誤差を許す。
    bool IsZeroStrict() const; ///< 長さが0か。許容誤差を許さない。
    bool IsUnit() const; ///< 正規化済みか。許容誤差を許す。
    const Vector2Pod Unit()
        const; ///< @brief 正規化したベクトルを取得する。 @details 長さ0のベクトルで正規化するとエラーになります。
    void
    UnitAssign(); ///< @brief 正規化する。 @details 長さ0のベクトルで正規化するとエラーになります。
    //@}

    //============================================================
    /// @name 内積・外積
    //@{
    f32 Dot(
        const Vector2Pod&) const; ///< あるベクトルとの内積(cosθ)を取得する。
    f32 Cross(
        const Vector2Pod&) const; ///< あるベクトルとの外積(sinθ)を取得とる。
    //@}

    //============================================================
    /// @name ユーティリティ
    //@{
    /// x,y形式の文字列に変換。
    const ShortString ToShortString() const;
    //@}
};

/// Vector2Pod のクラス版。
class Vector2 : public Vector2Pod {
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Vector2(); ///< Zero() で作成。
    Vector2(const Vector2Pod& xY); ///< コピーして作成。
    Vector2(f32 v); ///< 全要素同じ値で作成。
    Vector2(f32 x, f32 y); ///< XYを指定して作成。
    //@}
};

/// Vector2Pod のエイリアス。
typedef Vector2Pod Vec2;

/// Vector2Pod のエイリアス。
typedef Vector2Pod Vector2fPod;

/// Vec2 のエイリアス。
typedef Vec2 Vec2f;

/// Vector2 のエイリアス。
typedef Vector2 Vector2f;
//@}

} // namespace ae::base
#endif
// EOF
