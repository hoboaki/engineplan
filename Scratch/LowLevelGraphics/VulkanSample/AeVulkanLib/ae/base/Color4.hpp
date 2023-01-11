// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_COLOR4_HPP)
#else
#define AE_BASE_INCLUDED_COLOR4_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ShortString.hpp>

namespace ae::base {
struct Color3Pod;
struct Color4bPod;
struct Vector4Pod;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Util
//@{
/// 32bit浮動小数をRGBAの順に並べた色構造体。
struct Color4Pod
{
    //============================================================
    /// @name 定数取得
    //@{
    static const Color4Pod Zero(); ///< 0の色。
    static const Color4Pod One(); ///< R,G,B,Aが全て1の色。
    static const Color4Pod UnitR(); ///< Rだけ1の色。
    static const Color4Pod UnitG(); ///< Gだけ1の色。
    static const Color4Pod UnitB(); ///< Bだけ1の色。
    static const Color4Pod UnitA(); ///< Aだけ1の色。
    //@}

    //============================================================
    /// @name 変数
    //@{
    f32 r; ///< r。
    f32 g; ///< g。
    f32 b; ///< b。
    f32 a; ///< a。
    //@}

    //============================================================
    /// @name 変換
    //@{
    const Color3Pod ToRGB() const;
    const Color3Pod ToRRR() const;
    const Color3Pod ToGGG() const;
    const Color3Pod ToBBB() const;
    const Color3Pod ToAAA() const;
    const Color4Pod ToRRRR() const;
    const Color4Pod ToGGGG() const;
    const Color4Pod ToBBBB() const;
    const Color4Pod ToAAAA() const;
    const Color4bPod ToRGBAb() const;
    const Vector4Pod ToVector4() const;
    //@}

    //============================================================
    /// @name 等価比較
    //@{
    bool Equals(const Color4Pod&) const; ///< 許容誤差を考慮した等価比較。。
    bool EqualsStrict(
        const Color4Pod&) const; ///< 許容誤差を許容しない等価比較。
    //@}

    //============================================================
    /// @name 四則演算
    //@{
    const Color4Pod Add(f32) const; ///< 各要素に値を加算した結果を取得する。
    const Color4Pod Sub(f32) const; ///< 各要素から値を減算した結果を取得する。
    const Color4Pod Mul(f32) const; ///< 各要素に値をかけた結果を取得する。
    const Color4Pod Div(f32) const; ///< 各要素から値をわった結果を取得する。
    const Color4Pod Add(
        const Color4Pod&) const; ///< 対応する値同士を加算した結果を取得する。
    const Color4Pod Sub(
        const Color4Pod&) const; ///< 対応する値に対して減算した結果を取得する。
    const Color4Pod Mul(
        const Color4Pod&) const; ///< 対応する値同士をかけた結果を取得する。
    const Color4Pod Div(const Color4Pod&)
        const; ///< 対応する値に対して割り算をした結果を取得する。
    const Color4Pod Neg() const; ///< 符号を反転させた結果を取得する。
    void AddAssign(f32); ///< 各要素に値を加算する。
    void SubAssign(f32); ///< 各要素から値を減算する。
    void MulAssign(f32); ///< 各要素に値をかける。
    void DivAssign(f32); ///< 各要素から値をわる。
    void AddAssign(const Color4Pod&); ///< 対応する値同士を加算する。
    void SubAssign(const Color4Pod&); ///< 対応する値に対して減算する。
    void MulAssign(const Color4Pod&); ///< 対応する値同士をかける。
    void DivAssign(const Color4Pod&); ///< 対応する値に対して割り算をする。
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Color4Pod operator+(f32) const; ///< Add()。
    const Color4Pod operator-(f32) const; ///< Sub()。
    const Color4Pod operator*(f32) const; ///< Mul()。
    const Color4Pod operator/(f32) const; ///< Div()。
    const Color4Pod operator+(const Color4Pod&) const; ///< Add()。
    const Color4Pod operator-(const Color4Pod&) const; ///< Sub()。
    const Color4Pod operator*(const Color4Pod&) const; ///< Mul()。
    const Color4Pod operator/(const Color4Pod&) const; ///< Div()。
    const Color4Pod operator-() const; ///< Negate()。
    Color4Pod& operator+=(f32); ///< AddAssign()。
    Color4Pod& operator-=(f32); ///< SubAssign()。
    Color4Pod& operator*=(f32); ///< MulAssign()。
    Color4Pod& operator/=(f32); ///< DivAssign()。
    Color4Pod& operator+=(const Color4Pod&); ///< AddAssign()。
    Color4Pod& operator-=(const Color4Pod&); ///< SubAssign()。
    Color4Pod& operator*=(const Color4Pod&); ///< MulAssign()。
    Color4Pod& operator/=(const Color4Pod&); ///< DivAssign()。
    //@}

    //============================================================
    /// @name ユーティリティ
    //@{
    /// r,g,b,a形式の文字列に変換。
    const ShortString ToShortString() const;
    //@}
};

/// Color4Pod のクラス版。
class Color4 : public Color4Pod {
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Color4(); ///< Zero() で作成。
    Color4(const Color4Pod& rGBA); ///< コピーして作成。
    Color4(f32 r, f32 g, f32 b, f32 a); ///< RGBAを指定して作成。
    Color4(const Vector4Pod& vec); ///< ベクトルのXYZWをRGBAとみなして作成。
    //@}
};
//@}

} // namespace ae::base
#endif
// EOF
