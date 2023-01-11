// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_VECTOR3_HPP)
#else
#define AE_BASE_INCLUDED_VECTOR3_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ShortString.hpp>

namespace ae::base {
struct Vector2Pod;
struct Vector4Pod;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// @brief 浮動小数型3次元ベクトル構造体。
/// @details
/// 使用頻度のことを考えて Vec3 という名前でもアクセスできます。
/// メモリ配置は32bit浮動小数が先頭からx,y,zの順番に並んでいます。
struct Vector3Pod
{
    //============================================================
    /// @name 定数取得
    //@{
    static const Vector3Pod Zero(); ///< 0ベクトル。
    static const Vector3Pod One(); ///< X,Y,Zが全て1のベクトル。
    static const Vector3Pod Min(); ///< 最小値のベクトル。
    static const Vector3Pod Max(); ///< 最大値のベクトル。
    static const Vector3Pod UnitX(); ///< X単位ベクトル。
    static const Vector3Pod UnitY(); ///< Y単位ベクトル。
    static const Vector3Pod UnitZ(); ///< Z単位ベクトル。
    static const Vector3Pod NegUnitX(); ///< -X単位ベクトル。
    static const Vector3Pod NegUnitY(); ///< -Y単位ベクトル。
    static const Vector3Pod NegUnitZ(); ///< -Z単位ベクトル。
    //@}

    //============================================================
    /// @name 変数
    //@{
    f32 x; ///< x。
    f32 y; ///< y。
    f32 z; ///< z。
    //@}

    //============================================================
    /// @name 変換
    //@{
    const Vector2Pod ToXY() const;
    const Vector2Pod ToXX() const;
    const Vector2Pod ToYY() const;
    const Vector2Pod ToZZ() const;
    const Vector3Pod ToX00() const;
    const Vector3Pod ToXY0() const;
    const Vector3Pod To0Y0() const;
    const Vector3Pod To0YZ() const;
    const Vector3Pod To00Z() const;
    const Vector3Pod ToXXX() const;
    const Vector3Pod ToYYY() const;
    const Vector3Pod ToZZZ() const;
    const Vector4Pod ToXYZ0() const;
    const Vector4Pod ToXXXX() const;
    const Vector4Pod ToYYYY() const;
    const Vector4Pod ToZZZZ() const;
    //@}

    //============================================================
    /// @name 等価比較
    //@{
    bool Equals(const Vector3Pod&) const; ///< 許容誤差を考慮した等価比較。
    bool EqualsStrict(
        const Vector3Pod&) const; ///< 許容誤差を許容しない等価比較。
    //@}

    //============================================================
    /// @name 四則演算
    //@{
    const Vector3Pod Add(f32) const; ///< 各要素に値を加算した結果を取得する。
    const Vector3Pod Sub(f32) const; ///< 各要素から値を減算した結果を取得する。
    const Vector3Pod Mul(f32) const; ///< 各要素に値をかけた結果を取得する。
    const Vector3Pod Div(f32) const; ///< 各要素から値をわった結果を取得する。
    const Vector3Pod Add(
        const Vector3Pod&) const; ///< 対応する値同士を加算した結果を取得する。
    const Vector3Pod Sub(const Vector3Pod&)
        const; ///< 対応する値に対して減算した結果を取得する。
    const Vector3Pod Mul(
        const Vector3Pod&) const; ///< 対応する値同士をかけた結果を取得する。
    const Vector3Pod Div(const Vector3Pod&)
        const; ///< 対応する値に対して割り算をした結果を取得する。
    void AddAssign(f32); ///< 各要素に値を加算する。
    void SubAssign(f32); ///< 各要素から値を減算する。
    void MulAssign(f32); ///< 各要素に値をかける。
    void DivAssign(f32); ///< 各要素から値をわる。
    void AddAssign(const Vector3Pod&); ///< 対応する値同士を加算する。
    void SubAssign(const Vector3Pod&); ///< 対応する値に対して減算する。
    void MulAssign(const Vector3Pod&); ///< 対応する値同士をかける。
    void DivAssign(const Vector3Pod&); ///< 対応する値に対して割り算をする。
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Vector3Pod operator+(f32) const; ///< Add()。
    const Vector3Pod operator-(f32) const; ///< Sub()。
    const Vector3Pod operator*(f32) const; ///< Mul()。
    const Vector3Pod operator/(f32) const; ///< Div()。
    const Vector3Pod operator+(const Vector3Pod&) const; ///< Add()。
    const Vector3Pod operator-(const Vector3Pod&) const; ///< Sub()。
    const Vector3Pod operator*(const Vector3Pod&) const; ///< Mul()。
    const Vector3Pod operator/(const Vector3Pod&) const; ///< Div()。
    const Vector3Pod operator-() const; ///< Neg()。
    Vector3Pod& operator+=(f32); ///< AddAssign()。
    Vector3Pod& operator-=(f32); ///< SubAssign()。
    Vector3Pod& operator*=(f32); ///< MulAssign()。
    Vector3Pod& operator/=(f32); ///< DivAssign()。
    Vector3Pod& operator+=(const Vector3Pod&); ///< AddAssign()。
    Vector3Pod& operator-=(const Vector3Pod&); ///< SubAssign()。
    Vector3Pod& operator*=(const Vector3Pod&); ///< MulAssign()。
    Vector3Pod& operator/=(const Vector3Pod&); ///< DivAssign()。
    //@}

    //============================================================
    /// @name 選択
    //@{
    const Vector3Pod Min(const Vector3Pod&)
        const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
    const Vector3Pod Max(const Vector3Pod&)
        const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
    //@}

    //============================================================
    /// @name クランプ
    //@{
    const Vector3Pod Clamp(const Vector3Pod& min, const Vector3Pod& max)
        const; ///< min以上aMax以下になるようにクランプする。
    const Vector3Pod ClampPositive()
        const; ///< Clamp( Zero() , Max() ) を取得する。
    const Vector3Pod ClampNegative()
        const; ///< Clamp( Min() , Zero() ) を取得する。
    //@}

    //============================================================
    /// @name 符号操作
    //@{
    const Vector3Pod Abs() const; ///< 各要素を正に置き換えたベクトルを取得。
    const Vector3Pod Neg() const; ///< 符号を反転させた結果を取得する。
    //@}

    //============================================================
    /// @name 長さ＆正規化
    //@{
    f32 SquareLength() const; ///< 長さの2乗を取得する。
    f32 Length() const; ///< 長さを取得する。
    f32 Distance(const Vector3Pod&) const; ///< あるベクトルとの距離を取得する。
    bool IsZero() const; ///< 長さが0か。許容誤差を許す。
    bool IsZeroStrict() const; ///< 長さが0か。許容誤差を許さない。
    bool IsUnit() const; ///< 正規化済みか。許容誤差を許す。
    const Vector3Pod Unit()
        const; ///< @brief 正規化したベクトルを取得する。 @details 長さ0のベクトルで正規化するとエラーになります。
    void
    UnitAssign(); ///< @brief 正規化する。 @details 長さ0のベクトルで正規化するとエラーになります。
    //@}

    //============================================================
    /// @name 内積・外積
    //@{
    f32 Dot(const Vector3Pod&) const; ///< あるベクトルとの内積を取得する。
    const Vector3Pod Cross(
        const Vector3Pod&) const; ///< あるベクトルとの外積を取得とる。
    //@}

    //============================================================
    /// @name ユーティリティ
    //@{
    /// x,y,z形式の文字列に変換。
    const ShortString ToShortString() const;
    //@}
};

/// Vector3Pod のクラス版。
class Vector3 : public Vector3Pod {
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Vector3(); ///< Zero() で作成。
    Vector3(const Vector3Pod& xYZ); ///< コピーして作成。
    Vector3(f32 v); ///< 全要素同じ値で作成。
    Vector3(const Vector2Pod& xY, f32 z); ///< XYZを指定して作成。
    Vector3(f32 x, f32 y, f32 z); ///< XYZを指定して作成。
    //@}
};

/// Vector3Pod のエイリアス。
typedef Vector3Pod Vec3;

/// Vector3Pod のエイリアス。
typedef Vector3Pod Vector3fPod;

/// Vec3 のエイリアス。
typedef Vec3 Vec3f;

/// Vector3 のエイリアス。
typedef Vector3 Vector3f;
//@}

} // namespace ae::base
#endif
// EOF
