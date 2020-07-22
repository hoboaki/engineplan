// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_COLOR4_HPP)
#else
#define AE_BASE_INCLUDED_COLOR4_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ShortString.hpp>

namespace ae {
namespace base {
struct Color3Pod;
struct Color4bPod;
struct Vector4Pod;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Util
//@{
/// 32bit浮動小数をRGBAの順に並べた色構造体。
struct Color4Pod
{
    //============================================================
    /// @name 定数取得
    //@{
    static const Color4Pod Zero();     ///< 0の色。
    static const Color4Pod One();      ///< R,G,B,Aが全て1の色。
    static const Color4Pod UnitR();    ///< Rだけ1の色。
    static const Color4Pod UnitG();    ///< Gだけ1の色。
    static const Color4Pod UnitB();    ///< Bだけ1の色。
    static const Color4Pod UnitA();    ///< Aだけ1の色。
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
    const Color3Pod toRGB()const;
    const Color3Pod toRRR()const;
    const Color3Pod toGGG()const;
    const Color3Pod toBBB()const;
    const Color3Pod toAAA()const;
    const Color4Pod toRRRR()const;
    const Color4Pod toGGGG()const;
    const Color4Pod toBBBB()const;
    const Color4Pod toAAAA()const;
    const Color4bPod toRGBAb()const;
    const Vector4Pod toVector4()const;
    //@}

    //============================================================
    /// @name 等価比較
    //@{
    bool equals(const Color4Pod&)const;       ///< 許容誤差を考慮した等価比較。。
    bool equalsStrict(const Color4Pod&)const; ///< 許容誤差を許容しない等価比較。
    //@}

    //============================================================
    /// @name 四則演算
    //@{
    const Color4Pod add(f32)const; ///< 各要素に値を加算した結果を取得する。
    const Color4Pod sub(f32)const; ///< 各要素から値を減算した結果を取得する。
    const Color4Pod mul(f32)const; ///< 各要素に値をかけた結果を取得する。
    const Color4Pod div(f32)const; ///< 各要素から値をわった結果を取得する。
    const Color4Pod add(const Color4Pod&)const; ///< 対応する値同士を加算した結果を取得する。
    const Color4Pod sub(const Color4Pod&)const; ///< 対応する値に対して減算した結果を取得する。
    const Color4Pod mul(const Color4Pod&)const; ///< 対応する値同士をかけた結果を取得する。
    const Color4Pod div(const Color4Pod&)const; ///< 対応する値に対して割り算をした結果を取得する。
    const Color4Pod neg()const; ///< 符号を反転させた結果を取得する。
    void addAssign(f32); ///< 各要素に値を加算する。
    void subAssign(f32); ///< 各要素から値を減算する。
    void mulAssign(f32); ///< 各要素に値をかける。
    void divAssign(f32); ///< 各要素から値をわる。
    void addAssign(const Color4Pod&); ///< 対応する値同士を加算する。
    void subAssign(const Color4Pod&); ///< 対応する値に対して減算する。
    void mulAssign(const Color4Pod&); ///< 対応する値同士をかける。
    void divAssign(const Color4Pod&); ///< 対応する値に対して割り算をする。       
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Color4Pod operator+(f32)const; ///< add()。
    const Color4Pod operator-(f32)const; ///< sub()。
    const Color4Pod operator*(f32)const; ///< mul()。
    const Color4Pod operator/(f32)const; ///< div()。
    const Color4Pod operator+(const Color4Pod&)const; ///< add()。
    const Color4Pod operator-(const Color4Pod&)const; ///< sub()。
    const Color4Pod operator*(const Color4Pod&)const; ///< mul()。
    const Color4Pod operator/(const Color4Pod&)const; ///< div()。
    const Color4Pod operator-()const; ///< negate()。
    Color4Pod& operator+=(f32); ///< addAssign()。
    Color4Pod& operator-=(f32); ///< subAssign()。
    Color4Pod& operator*=(f32); ///< mulAssign()。
    Color4Pod& operator/=(f32); ///< divAssign()。
    Color4Pod& operator+=(const Color4Pod&); ///< addAssign()。
    Color4Pod& operator-=(const Color4Pod&); ///< subAssign()。
    Color4Pod& operator*=(const Color4Pod&); ///< mulAssign()。
    Color4Pod& operator/=(const Color4Pod&); ///< divAssign()。
    //@}

    //============================================================
    /// @name ユーティリティ
    //@{
    /// r,g,b,a形式の文字列に変換。
    const ShortString toShortString()const;
    //@}
};

/// Color4Pod のクラス版。
class Color4 : public Color4Pod
{
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Color4(); ///< Zero() で作成。
    Color4(const Color4Pod& aRGBA); ///< コピーして作成。
    Color4(f32 aR, f32 aG, f32 aB, f32 aA); ///< RGBAを指定して作成。
    Color4(const Vector4Pod& aVec); ///< ベクトルのXYZWをRGBAとみなして作成。
    //@}
};
//@}

}} // namespace
#endif
// EOF
