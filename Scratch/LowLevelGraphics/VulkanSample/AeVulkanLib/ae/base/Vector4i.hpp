// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_VECTOR4I_HPP)
#else
#define AE_BASE_INCLUDED_VECTOR4I_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ShortString.hpp>

namespace ae::base {
struct Vector2iPod;
struct Vector3iPod;
struct Vector4Pod;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// @brief 整数型4次元ベクトル構造体。
/// @details
/// 使用頻度のことを考えて Vec4i という名前でもアクセスできます。
/// メモリ配置は32bit符号有り整数が先頭からx,y,z,wの順番に並んでいます。
struct Vector4iPod
{
    //============================================================
    /// @name 定数取得
    //@{
    static const Vector4iPod Zero(); ///< 0ベクトル。
    static const Vector4iPod One(); ///< X,Y,Z,Wが全て1のベクトル。
    static const Vector4iPod Min(); ///< 最小値のベクトル。
    static const Vector4iPod Max(); ///< 最大値のベクトル。
    static const Vector4iPod UnitX(); ///< X単位ベクトル。
    static const Vector4iPod UnitY(); ///< Y単位ベクトル。
    static const Vector4iPod UnitZ(); ///< Z単位ベクトル。
    static const Vector4iPod UnitW(); ///< W単位ベクトル。
    static const Vector4iPod NegUnitX(); ///< -X単位ベクトル。
    static const Vector4iPod NegUnitY(); ///< -Y単位ベクトル。
    static const Vector4iPod NegUnitZ(); ///< -Z単位ベクトル。
    static const Vector4iPod NegUnitW(); ///< -W単位ベクトル。
    //@}

    //============================================================
    /// @name 変数
    //@{
    s32 x; ///< x。
    s32 y; ///< y。
    s32 z; ///< z。
    s32 w; ///< z。
    //@}

    //============================================================
    /// @name 変換
    //@{
    const Vector2iPod ToXY() const;
    const Vector2iPod ToXX() const;
    const Vector2iPod ToYY() const;
    const Vector2iPod ToZZ() const;
    const Vector2iPod ToWW() const;
    const Vector3iPod ToXYZ() const;
    const Vector3iPod ToXXX() const;
    const Vector3iPod ToYYY() const;
    const Vector3iPod ToZZZ() const;
    const Vector3iPod ToWWW() const;
    const Vector4iPod ToXYZ0() const;
    const Vector4iPod ToXY0W() const;
    const Vector4iPod ToXY00() const;
    const Vector4iPod ToX0ZW() const;
    const Vector4iPod ToX0Z0() const;
    const Vector4iPod ToX00W() const;
    const Vector4iPod ToX000() const;
    const Vector4iPod To0YZ0() const;
    const Vector4iPod To0Y0W() const;
    const Vector4iPod To0Y00() const;
    const Vector4iPod To00ZW() const;
    const Vector4iPod To00Z0() const;
    const Vector4iPod To000W() const;
    const Vector4iPod ToXXXX() const;
    const Vector4iPod ToYYYY() const;
    const Vector4iPod ToZZZZ() const;
    const Vector4iPod ToWWWW() const;
    const Vector4Pod ToXYZWf() const;
    //@}

    //============================================================
    /// @name 等価比較
    //@{
    bool Equals(const Vector4iPod&) const; ///< 等価比較。
    //@}

    //============================================================
    /// @name 四則演算
    //@{
    const Vector4iPod Add(s32) const; ///< 各要素に値を加算した結果を取得する。
    const Vector4iPod Sub(
        s32) const; ///< 各要素から値を減算した結果を取得する。
    const Vector4iPod Mul(s32) const; ///< 各要素に値をかけた結果を取得する。
    const Vector4iPod Div(s32) const; ///< 各要素から値をわった結果を取得する。
    const Vector4iPod Add(
        const Vector4iPod&) const; ///< 対応する値同士を加算した結果を取得する。
    const Vector4iPod Sub(const Vector4iPod&)
        const; ///< 対応する値に対して減算した結果を取得する。
    const Vector4iPod Mul(
        const Vector4iPod&) const; ///< 対応する値同士をかけた結果を取得する。
    const Vector4iPod Div(const Vector4iPod&)
        const; ///< 対応する値に対して割り算をした結果を取得する。
    void AddAssign(s32); ///< 各要素に値を加算する。
    void SubAssign(s32); ///< 各要素から値を減算する。
    void MulAssign(s32); ///< 各要素に値をかける。
    void DivAssign(s32); ///< 各要素から値をわる。
    void AddAssign(const Vector4iPod&); ///< 対応する値同士を加算する。
    void SubAssign(const Vector4iPod&); ///< 対応する値に対して減算する。
    void MulAssign(const Vector4iPod&); ///< 対応する値同士をかける。
    void DivAssign(const Vector4iPod&); ///< 対応する値に対して割り算をする。
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Vector4iPod operator+(s32) const; ///< Add()。
    const Vector4iPod operator-(s32) const; ///< Sub()。
    const Vector4iPod operator*(s32) const; ///< Mul()。
    const Vector4iPod operator/(s32) const; ///< Div()。
    const Vector4iPod operator+(const Vector4iPod&) const; ///< Add()。
    const Vector4iPod operator-(const Vector4iPod&) const; ///< Sub()。
    const Vector4iPod operator*(const Vector4iPod&) const; ///< Mul()。
    const Vector4iPod operator/(const Vector4iPod&) const; ///< Div()。
    const Vector4iPod operator-() const; ///< Neg()。
    Vector4iPod& operator+=(s32); ///< AddAssign()。
    Vector4iPod& operator-=(s32); ///< SubAssign()。
    Vector4iPod& operator*=(s32); ///< MulAssign()。
    Vector4iPod& operator/=(s32); ///< DivAssign()。
    Vector4iPod& operator+=(const Vector4iPod&); ///< AddAssign()。
    Vector4iPod& operator-=(const Vector4iPod&); ///< SubAssign()。
    Vector4iPod& operator*=(const Vector4iPod&); ///< MulAssign()。
    Vector4iPod& operator/=(const Vector4iPod&); ///< DivAssign()。
    //@}

    //============================================================
    /// @name 選択
    //@{
    const Vector4iPod Min(const Vector4iPod&)
        const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
    const Vector4iPod Max(const Vector4iPod&)
        const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
    //@}

    //============================================================
    /// @name クランプ
    //@{
    const Vector4iPod Clamp(const Vector4iPod& min, const Vector4iPod& max)
        const; ///< min以上aMax以下になるようにクランプする。
    const Vector4iPod ClampPositive()
        const; ///< Clamp( Zero() , Max() ) を取得する。
    const Vector4iPod ClampNegative()
        const; ///< Clamp( Min() , Zero() ) を取得する。
    //@}

    //============================================================
    /// @name 符号
    //@{
    const Vector4iPod Abs() const; ///< 各要素を正に置き換えたベクトルを取得。
    const Vector4iPod Neg() const; ///< 符号を反転させた結果を取得する。
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
    /// x,y,z,w形式の文字列に変換。
    const ShortString ToShortString() const;
    //@}
};

/// Vector4iPod のクラス版。
class Vector4i : public Vector4iPod {
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Vector4i(); ///< Zero() で作成。
    Vector4i(const Vector4iPod& xYZW); ///< コピーして作成。
    Vector4i(s32 v); ///< 全要素同じ値で作成。
    Vector4i(const Vector2iPod& xY, s32 z, s32 w); ///< XYZWを指定して作成。
    Vector4i(const Vector3iPod& xYZ, s32 w); ///< XYZWを指定して作成。
    Vector4i(s32 x, s32 y, s32 z, s32 w); ///< XYZWを指定して作成。
    //@}
};

/// Vector4iPod のエイリアス。
typedef Vector4iPod Vec4i;
//@}

} // namespace ae::base
#endif
// EOF
