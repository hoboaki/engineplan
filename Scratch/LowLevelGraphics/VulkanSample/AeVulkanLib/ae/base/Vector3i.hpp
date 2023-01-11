// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_VECTOR3I_HPP)
#else
#define AE_BASE_INCLUDED_VECTOR3I_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ShortString.hpp>

namespace ae::base {
struct Vector2iPod;
struct Vector3Pod;
struct Vector4iPod;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// @brief 整数型3次元ベクトル構造体。
/// @details
/// 使用頻度のことを考えて Vec3i という名前でもアクセスできます。
/// メモリ配置は32bit符号有り整数が先頭からx,y,zの順番に並んでいます。
struct Vector3iPod
{
    //============================================================
    /// @name 定数取得
    //@{
    static const Vector3iPod Zero(); ///< 0ベクトル。
    static const Vector3iPod One(); ///< X,Y,Zが全て1のベクトル。
    static const Vector3iPod Min(); ///< 最小値のベクトル。
    static const Vector3iPod Max(); ///< 最大値のベクトル。
    static const Vector3iPod UnitX(); ///< X単位ベクトル。
    static const Vector3iPod UnitY(); ///< Y単位ベクトル。
    static const Vector3iPod UnitZ(); ///< Z単位ベクトル。
    static const Vector3iPod NegUnitX(); ///< -X単位ベクトル。
    static const Vector3iPod NegUnitY(); ///< -Y単位ベクトル。
    static const Vector3iPod NegUnitZ(); ///< -Z単位ベクトル。
    //@}

    //============================================================
    /// @name 変数
    //@{
    s32 x; ///< x。
    s32 y; ///< y。
    s32 z; ///< z。
    //@}

    //============================================================
    /// @name 変換
    //@{
    const Vector2iPod ToXY() const;
    const Vector2iPod ToXX() const;
    const Vector2iPod ToYY() const;
    const Vector2iPod ToZZ() const;
    const Vector3iPod ToX00() const;
    const Vector3iPod ToXY0() const;
    const Vector3iPod To0Y0() const;
    const Vector3iPod To0YZ() const;
    const Vector3iPod To00Z() const;
    const Vector3iPod ToXXX() const;
    const Vector3iPod ToYYY() const;
    const Vector3iPod ToZZZ() const;
    const Vector4iPod ToXYZ0() const;
    const Vector4iPod ToXXXX() const;
    const Vector4iPod ToYYYY() const;
    const Vector4iPod ToZZZZ() const;
    const Vector3Pod ToXYZf() const;
    //@}

    //============================================================
    /// @name 等価比較
    //@{
    bool Equals(const Vector3iPod&) const; ///< 等価比較。
    //@}

    //============================================================
    /// @name 四則演算
    //@{
    const Vector3iPod Add(s32) const; ///< 各要素に値を加算した結果を取得する。
    const Vector3iPod Sub(
        s32) const; ///< 各要素から値を減算した結果を取得する。
    const Vector3iPod Mul(s32) const; ///< 各要素に値をかけた結果を取得する。
    const Vector3iPod Div(s32) const; ///< 各要素から値をわった結果を取得する。
    const Vector3iPod Add(
        const Vector3iPod&) const; ///< 対応する値同士を加算した結果を取得する。
    const Vector3iPod Sub(const Vector3iPod&)
        const; ///< 対応する値に対して減算した結果を取得する。
    const Vector3iPod Mul(
        const Vector3iPod&) const; ///< 対応する値同士をかけた結果を取得する。
    const Vector3iPod Div(const Vector3iPod&)
        const; ///< 対応する値に対して割り算をした結果を取得する。
    void AddAssign(s32); ///< 各要素に値を加算する。
    void SubAssign(s32); ///< 各要素から値を減算する。
    void MulAssign(s32); ///< 各要素に値をかける。
    void DivAssign(s32); ///< 各要素から値をわる。
    void AddAssign(const Vector3iPod&); ///< 対応する値同士を加算する。
    void SubAssign(const Vector3iPod&); ///< 対応する値に対して減算する。
    void MulAssign(const Vector3iPod&); ///< 対応する値同士をかける。
    void DivAssign(const Vector3iPod&); ///< 対応する値に対して割り算をする。
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Vector3iPod operator+(s32) const; ///< Add()。
    const Vector3iPod operator-(s32) const; ///< Sub()。
    const Vector3iPod operator*(s32) const; ///< Mul()。
    const Vector3iPod operator/(s32) const; ///< Div()。
    const Vector3iPod operator+(const Vector3iPod&) const; ///< Add()。
    const Vector3iPod operator-(const Vector3iPod&) const; ///< Sub()。
    const Vector3iPod operator*(const Vector3iPod&) const; ///< Mul()。
    const Vector3iPod operator/(const Vector3iPod&) const; ///< Div()。
    const Vector3iPod operator-() const; ///< Neg()。
    Vector3iPod& operator+=(s32); ///< AddAssign()。
    Vector3iPod& operator-=(s32); ///< SubAssign()。
    Vector3iPod& operator*=(s32); ///< MulAssign()。
    Vector3iPod& operator/=(s32); ///< DivAssign()。
    Vector3iPod& operator+=(const Vector3iPod&); ///< AddAssign()。
    Vector3iPod& operator-=(const Vector3iPod&); ///< SubAssign()。
    Vector3iPod& operator*=(const Vector3iPod&); ///< MulAssign()。
    Vector3iPod& operator/=(const Vector3iPod&); ///< DivAssign()。
    //@}

    //============================================================
    /// @name 選択
    //@{
    const Vector3iPod Min(const Vector3iPod&)
        const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
    const Vector3iPod Max(const Vector3iPod&)
        const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
    //@}

    //============================================================
    /// @name クランプ
    //@{
    const Vector3iPod Clamp(const Vector3iPod& min, const Vector3iPod& max)
        const; ///< min以上aMax以下になるようにクランプする。
    const Vector3iPod ClampPositive()
        const; ///< Clamp( Zero() , Max() ) を取得する。
    const Vector3iPod ClampNegative()
        const; ///< Clamp( Min() , Zero() ) を取得する。
    //@}

    //============================================================
    /// @name 符号
    //@{
    const Vector3iPod Abs() const; ///< 各要素を正に置き換えたベクトルを取得。
    const Vector3iPod Neg() const; ///< 符号を反転させた結果を取得する。
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
    /// x,y,z形式の文字列に変換。
    const ShortString ToShortString() const;
    //@}
};

/// Vector3iPod のクラス版。
class Vector3i : public Vector3iPod {
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Vector3i(); ///< Zero() で作成。
    Vector3i(const Vector3iPod& xYZ); ///< コピーして作成。
    Vector3i(s32 v); ///< 全要素同じ値で作成。
    Vector3i(const Vector2iPod& xY, s32 z); ///< XYZを指定して作成。
    Vector3i(s32 x, s32 y, s32 z); ///< XYZを指定して作成。
    //@}
};

/// Vector3iPod のエイリアス。
typedef Vector3iPod Vec3i;
//@}

} // namespace ae::base
#endif
// EOF
