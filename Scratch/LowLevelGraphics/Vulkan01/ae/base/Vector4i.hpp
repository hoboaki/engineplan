// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_VECTOR4I_HPP)
#else
#define AE_BASE_INCLUDED_VECTOR4I_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ShortString.hpp>

namespace ae {
namespace base {
struct Vector2iPod;
struct Vector3iPod;
struct Vector4Pod;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

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
    static const Vector4iPod Zero();     ///< 0ベクトル。
    static const Vector4iPod One();      ///< X,Y,Z,Wが全て1のベクトル。
    static const Vector4iPod Min();      ///< 最小値のベクトル。
    static const Vector4iPod Max();      ///< 最大値のベクトル。
    static const Vector4iPod UnitX();    ///< X単位ベクトル。
    static const Vector4iPod UnitY();    ///< Y単位ベクトル。
    static const Vector4iPod UnitZ();    ///< Z単位ベクトル。
    static const Vector4iPod UnitW();    ///< W単位ベクトル。
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
    const Vector2iPod toXY()const;
    const Vector2iPod toXX()const;
    const Vector2iPod toYY()const;
    const Vector2iPod toZZ()const;
    const Vector2iPod toWW()const;
    const Vector3iPod toXYZ()const;
    const Vector3iPod toXXX()const;
    const Vector3iPod toYYY()const;
    const Vector3iPod toZZZ()const;
    const Vector3iPod toWWW()const;
    const Vector4iPod toXYZ0()const;
    const Vector4iPod toXY0W()const;
    const Vector4iPod toXY00()const;
    const Vector4iPod toX0ZW()const;
    const Vector4iPod toX0Z0()const;
    const Vector4iPod toX00W()const;
    const Vector4iPod toX000()const;
    const Vector4iPod to0YZ0()const;
    const Vector4iPod to0Y0W()const;
    const Vector4iPod to0Y00()const;
    const Vector4iPod to00ZW()const;
    const Vector4iPod to00Z0()const;
    const Vector4iPod to000W()const;
    const Vector4iPod toXXXX()const;
    const Vector4iPod toYYYY()const;
    const Vector4iPod toZZZZ()const;
    const Vector4iPod toWWWW()const;
    const Vector4Pod  toXYZWf()const;
    //@}

    //============================================================
    /// @name 等価比較
    //@{
    bool equals(const Vector4iPod&)const;       ///< 等価比較。
    //@}

    //============================================================
    /// @name 四則演算
    //@{
    const Vector4iPod add(s32)const; ///< 各要素に値を加算した結果を取得する。
    const Vector4iPod sub(s32)const; ///< 各要素から値を減算した結果を取得する。
    const Vector4iPod mul(s32)const; ///< 各要素に値をかけた結果を取得する。
    const Vector4iPod div(s32)const; ///< 各要素から値をわった結果を取得する。
    const Vector4iPod add(const Vector4iPod&)const; ///< 対応する値同士を加算した結果を取得する。
    const Vector4iPod sub(const Vector4iPod&)const; ///< 対応する値に対して減算した結果を取得する。
    const Vector4iPod mul(const Vector4iPod&)const; ///< 対応する値同士をかけた結果を取得する。
    const Vector4iPod div(const Vector4iPod&)const; ///< 対応する値に対して割り算をした結果を取得する。
    void addAssign(s32); ///< 各要素に値を加算する。
    void subAssign(s32); ///< 各要素から値を減算する。
    void mulAssign(s32); ///< 各要素に値をかける。
    void divAssign(s32); ///< 各要素から値をわる。
    void addAssign(const Vector4iPod&); ///< 対応する値同士を加算する。
    void subAssign(const Vector4iPod&); ///< 対応する値に対して減算する。
    void mulAssign(const Vector4iPod&); ///< 対応する値同士をかける。
    void divAssign(const Vector4iPod&); ///< 対応する値に対して割り算をする。       
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Vector4iPod operator+(s32)const; ///< add()。
    const Vector4iPod operator-(s32)const; ///< sub()。
    const Vector4iPod operator*(s32)const; ///< mul()。
    const Vector4iPod operator/(s32)const; ///< div()。
    const Vector4iPod operator+(const Vector4iPod&)const; ///< add()。
    const Vector4iPod operator-(const Vector4iPod&)const; ///< sub()。
    const Vector4iPod operator*(const Vector4iPod&)const; ///< mul()。
    const Vector4iPod operator/(const Vector4iPod&)const; ///< div()。
    const Vector4iPod operator-()const; ///< neg()。
    Vector4iPod& operator+=(s32); ///< addAssign()。
    Vector4iPod& operator-=(s32); ///< subAssign()。
    Vector4iPod& operator*=(s32); ///< mulAssign()。
    Vector4iPod& operator/=(s32); ///< divAssign()。
    Vector4iPod& operator+=(const Vector4iPod&); ///< addAssign()。
    Vector4iPod& operator-=(const Vector4iPod&); ///< subAssign()。
    Vector4iPod& operator*=(const Vector4iPod&); ///< mulAssign()。
    Vector4iPod& operator/=(const Vector4iPod&); ///< divAssign()。
    //@}

    //============================================================
    /// @name 選択
    //@{
    const Vector4iPod min(const Vector4iPod&)const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
    const Vector4iPod max(const Vector4iPod&)const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
    //@}

    //============================================================
    /// @name クランプ
    //@{
    const Vector4iPod clamp(const Vector4iPod& aMin, const Vector4iPod& aMax)const; ///< aMin以上aMax以下になるようにクランプする。
    const Vector4iPod clampPositive()const; ///< clamp( Zero() , Max() ) を取得する。
    const Vector4iPod clampNegative()const; ///< clamp( Min() , Zero() ) を取得する。
    //@}

    //============================================================
    /// @name 符号
    //@{
    const Vector4iPod abs()const; ///< 各要素を正に置き換えたベクトルを取得。
    const Vector4iPod neg()const; ///< 符号を反転させた結果を取得する。
    bool isPositive()const; ///< 各要素が0以上か。
    //@}

    //============================================================
    /// @name 長さ
    //@{
    bool isZero()const;                      ///< 全てが0か。
    //@}

    //============================================================
    /// @name ユーティリティ
    //@{
    /// x,y,z,w形式の文字列に変換。
    const ShortString toShortString()const;
    //@}
};

/// Vector4iPod のクラス版。
class Vector4i : public Vector4iPod
{
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Vector4i(); ///< Zero() で作成。
    Vector4i(const Vector4iPod& aXYZW); ///< コピーして作成。
    Vector4i(s32 aV); ///< 全要素同じ値で作成。
    Vector4i(const Vector2iPod& aXY, s32 aZ, s32 aW); ///< XYZWを指定して作成。
    Vector4i(const Vector3iPod& aXYZ, s32 aW); ///< XYZWを指定して作成。
    Vector4i(s32 aX, s32 aY, s32 aZ, s32 aW); ///< XYZWを指定して作成。
    //@}
};

/// Vector4iPod のエイリアス。
typedef Vector4iPod Vec4i;
//@}

}} // namespace
#endif
// EOF
