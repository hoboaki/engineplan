// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_VECTOR4_HPP)
#else
#define AE_BASE_INCLUDED_VECTOR4_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ShortString.hpp>

namespace ae::base {
struct Vector2Pod;
struct Vector3Pod;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// @brief 浮動小数型4次元ベクトル構造体。
/// @details
/// 使用頻度のことを考えて Vec4 という名前でもアクセスできます。
/// メモリ配置は32bit浮動小数が先頭からx,y,z,wの順番に並んでいます。
struct Vector4Pod
{
    //============================================================
    /// @name 定数取得
    //@{
    static const Vector4Pod Zero(); ///< 0ベクトル。
    static const Vector4Pod One(); ///< X,Y,Z,Wが全て1のベクトル。
    static const Vector4Pod Min(); ///< 最小値のベクトル。
    static const Vector4Pod Max(); ///< 最大値のベクトル。
    static const Vector4Pod UnitX(); ///< X単位ベクトル。
    static const Vector4Pod UnitY(); ///< Y単位ベクトル。
    static const Vector4Pod UnitZ(); ///< Z単位ベクトル。
    static const Vector4Pod UnitW(); ///< W単位ベクトル。
    static const Vector4Pod NegUnitX(); ///< -X単位ベクトル。
    static const Vector4Pod NegUnitY(); ///< -Y単位ベクトル。
    static const Vector4Pod NegUnitZ(); ///< -Z単位ベクトル。
    static const Vector4Pod NegUnitW(); ///< -W単位ベクトル。
    //@}
    //============================================================
    /// @name 変数
    //@{
    f32 x; ///< x。
    f32 y; ///< y。
    f32 z; ///< z。
    f32 w; ///< w。
    //@}

    //============================================================
    /// @name 変換
    //@{
    const Vector2Pod ToXY() const;
    const Vector2Pod ToXX() const;
    const Vector2Pod ToYY() const;
    const Vector2Pod ToZZ() const;
    const Vector2Pod ToWW() const;
    const Vector3Pod ToXYZ() const;
    const Vector3Pod ToXXX() const;
    const Vector3Pod ToYYY() const;
    const Vector3Pod ToZZZ() const;
    const Vector3Pod ToWWW() const;
    const Vector4Pod ToXYZ0() const;
    const Vector4Pod ToXY0W() const;
    const Vector4Pod ToXY00() const;
    const Vector4Pod ToX0ZW() const;
    const Vector4Pod ToX0Z0() const;
    const Vector4Pod ToX00W() const;
    const Vector4Pod ToX000() const;
    const Vector4Pod To0YZ0() const;
    const Vector4Pod To0Y0W() const;
    const Vector4Pod To0Y00() const;
    const Vector4Pod To00ZW() const;
    const Vector4Pod To00Z0() const;
    const Vector4Pod To000W() const;
    const Vector4Pod ToXXXX() const;
    const Vector4Pod ToYYYY() const;
    const Vector4Pod ToZZZZ() const;
    const Vector4Pod ToWWWW() const;
    //@}

    //============================================================
    /// @name 等価比較
    //@{
    bool Equals(const Vector4Pod&) const; ///< 許容誤差を考慮した等価比較。
    bool EqualsStrict(
        const Vector4Pod&) const; ///< 許容誤差を許容しない等価比較。
    //@}

    //============================================================
    /// @name 四則演算
    //@{
    const Vector4Pod Add(f32) const; ///< 各要素に値を加算した結果を取得する。
    const Vector4Pod Sub(f32) const; ///< 各要素から値を減算した結果を取得する。
    const Vector4Pod Mul(f32) const; ///< 各要素に値をかけた結果を取得する。
    const Vector4Pod Div(f32) const; ///< 各要素から値をわった結果を取得する。
    const Vector4Pod Add(
        const Vector4Pod&) const; ///< 対応する値同士を加算した結果を取得する。
    const Vector4Pod Sub(const Vector4Pod&)
        const; ///< 対応する値に対して減算した結果を取得する。
    const Vector4Pod Mul(
        const Vector4Pod&) const; ///< 対応する値同士をかけた結果を取得する。
    const Vector4Pod Div(const Vector4Pod&)
        const; ///< 対応する値に対して割り算をした結果を取得する。
    void AddAssign(f32); ///< 各要素に値を加算する。
    void SubAssign(f32); ///< 各要素から値を減算する。
    void MulAssign(f32); ///< 各要素に値をかける。
    void DivAssign(f32); ///< 各要素から値をわる。
    void AddAssign(const Vector4Pod&); ///< 対応する値同士を加算する。
    void SubAssign(const Vector4Pod&); ///< 対応する値に対して減算する。
    void MulAssign(const Vector4Pod&); ///< 対応する値同士をかける。
    void DivAssign(const Vector4Pod&); ///< 対応する値に対して割り算をする。
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Vector4Pod operator+(f32) const; ///< Add()。
    const Vector4Pod operator-(f32) const; ///< Sub()。
    const Vector4Pod operator*(f32) const; ///< Mul()。
    const Vector4Pod operator/(f32) const; ///< Div()。
    const Vector4Pod operator+(const Vector4Pod&) const; ///< Add()。
    const Vector4Pod operator-(const Vector4Pod&) const; ///< Sub()。
    const Vector4Pod operator*(const Vector4Pod&) const; ///< Mul()。
    const Vector4Pod operator/(const Vector4Pod&) const; ///< Div()。
    const Vector4Pod operator-() const; ///< Neg()。
    Vector4Pod& operator+=(f32); ///< AddAssign()。
    Vector4Pod& operator-=(f32); ///< SubAssign()。
    Vector4Pod& operator*=(f32); ///< MulAssign()。
    Vector4Pod& operator/=(f32); ///< DivAssign()。
    Vector4Pod& operator+=(const Vector4Pod&); ///< AddAssign()。
    Vector4Pod& operator-=(const Vector4Pod&); ///< SubAssign()。
    Vector4Pod& operator*=(const Vector4Pod&); ///< MulAssign()。
    Vector4Pod& operator/=(const Vector4Pod&); ///< DivAssign()。
    //@}

    //============================================================
    /// @name 選択
    //@{
    const Vector4Pod Min(const Vector4Pod&)
        const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
    const Vector4Pod Max(const Vector4Pod&)
        const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
    //@}

    //============================================================
    /// @name クランプ
    //@{
    const Vector4Pod Clamp(const Vector4Pod& min, const Vector4Pod& max)
        const; ///< min以上aMax以下になるようにクランプする。
    const Vector4Pod ClampPositive()
        const; ///< Clamp( Zero() , Max() ) を取得する。
    const Vector4Pod ClampNegative()
        const; ///< Clamp( Min() , Zero() ) を取得する。
    //@}

    //============================================================
    /// @name 符号操作
    //@{
    const Vector4Pod Abs() const; ///< 各要素を正に置き換えたベクトルを取得。
    const Vector4Pod Neg() const; ///< 符号を反転させた結果を取得する。
    //@}

    //============================================================
    /// @name 長さ＆正規化
    //@{
    f32 SquareLength() const; ///< 長さの2乗を取得する。
    f32 Length() const; ///< 長さを取得する。
    f32 Distance(const Vector4Pod&) const; ///< あるベクトルとの距離を取得する。
    bool IsZero() const; ///< 長さが0か。許容誤差を許す。
    bool IsZeroStrict() const; ///< 長さが0か。許容誤差を許さない。
    bool IsUnit() const; ///< 正規化済みか。許容誤差を許す。
    const Vector4Pod Unit()
        const; ///< @brief 正規化したベクトルを取得する。 @details 長さ0のベクトルで正規化するとエラーになります。
    void
    UnitAssign(); ///< @brief 正規化する。 @details 長さ0のベクトルで正規化するとエラーになります。
    //@}

    //============================================================
    /// @name 内積
    //@{
    f32 Dot(const Vector4Pod&) const; ///< あるベクトルとの内積を取得する。
    //@}

    //============================================================
    /// @name ユーティリティ
    //@{
    /// x,y,z,w形式の文字列に変換。
    const ShortString ToShortString() const;
    //@}
};

/// Vector4Pod のクラス版。
class Vector4 : public Vector4Pod {
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Vector4(); ///< Zero() で作成。
    Vector4(const Vector4Pod& xYZW); ///< コピーして作成。
    Vector4(f32 v); ///< 全要素同じ値で作成。
    Vector4(const Vector2Pod& xY, f32 z, f32 w); ///< XYZWを指定して作成。
    Vector4(const Vector3Pod& xYZ, f32 w); ///< XYZWを指定して作成。
    Vector4(f32 x, f32 y, f32 z, f32 w); ///< XYZWを指定して作成。
    //@}
};

/// Vector4Pod のエイリアス。
typedef Vector4Pod Vec4;

/// Vector4Pod のエイリアス。
typedef Vector4Pod Vector4fPod;

/// Vec4 のエイリアス。
typedef Vec4 Vec4f;

/// Vector4 のエイリアス。
typedef Vector4 Vector4f;
//@}

} // namespace ae::base
#endif
// EOF
