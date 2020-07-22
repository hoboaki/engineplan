// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_VECTOR3I_HPP)
#else
#define AE_BASE_INCLUDED_VECTOR3I_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ShortString.hpp>

namespace ae {
namespace base {
struct Vector2iPod;
struct Vector3Pod;
struct Vector4iPod;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

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
    static const Vector3iPod Zero();     ///< 0ベクトル。
    static const Vector3iPod One();      ///< X,Y,Zが全て1のベクトル。
    static const Vector3iPod Min();      ///< 最小値のベクトル。
    static const Vector3iPod Max();      ///< 最大値のベクトル。
    static const Vector3iPod UnitX();    ///< X単位ベクトル。
    static const Vector3iPod UnitY();    ///< Y単位ベクトル。
    static const Vector3iPod UnitZ();    ///< Z単位ベクトル。
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
    const Vector2iPod toXY()const;
    const Vector2iPod toXX()const;
    const Vector2iPod toYY()const;
    const Vector2iPod toZZ()const;
    const Vector3iPod toX00()const;
    const Vector3iPod toXY0()const;
    const Vector3iPod to0Y0()const;
    const Vector3iPod to0YZ()const;
    const Vector3iPod to00Z()const;
    const Vector3iPod toXXX()const;
    const Vector3iPod toYYY()const;
    const Vector3iPod toZZZ()const;
    const Vector4iPod toXYZ0()const;
    const Vector4iPod toXXXX()const;
    const Vector4iPod toYYYY()const;
    const Vector4iPod toZZZZ()const;
    const Vector3Pod  toXYZf()const;
    //@}

    //============================================================
    /// @name 等価比較
    //@{
    bool equals(const Vector3iPod&)const;       ///< 等価比較。
    //@}

    //============================================================
    /// @name 四則演算
    //@{
    const Vector3iPod add(s32)const; ///< 各要素に値を加算した結果を取得する。
    const Vector3iPod sub(s32)const; ///< 各要素から値を減算した結果を取得する。
    const Vector3iPod mul(s32)const; ///< 各要素に値をかけた結果を取得する。
    const Vector3iPod div(s32)const; ///< 各要素から値をわった結果を取得する。
    const Vector3iPod add(const Vector3iPod&)const; ///< 対応する値同士を加算した結果を取得する。
    const Vector3iPod sub(const Vector3iPod&)const; ///< 対応する値に対して減算した結果を取得する。
    const Vector3iPod mul(const Vector3iPod&)const; ///< 対応する値同士をかけた結果を取得する。
    const Vector3iPod div(const Vector3iPod&)const; ///< 対応する値に対して割り算をした結果を取得する。
    void addAssign(s32); ///< 各要素に値を加算する。
    void subAssign(s32); ///< 各要素から値を減算する。
    void mulAssign(s32); ///< 各要素に値をかける。
    void divAssign(s32); ///< 各要素から値をわる。
    void addAssign(const Vector3iPod&); ///< 対応する値同士を加算する。
    void subAssign(const Vector3iPod&); ///< 対応する値に対して減算する。
    void mulAssign(const Vector3iPod&); ///< 対応する値同士をかける。
    void divAssign(const Vector3iPod&); ///< 対応する値に対して割り算をする。       
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Vector3iPod operator+(s32)const; ///< add()。
    const Vector3iPod operator-(s32)const; ///< sub()。
    const Vector3iPod operator*(s32)const; ///< mul()。
    const Vector3iPod operator/(s32)const; ///< div()。
    const Vector3iPod operator+(const Vector3iPod&)const; ///< add()。
    const Vector3iPod operator-(const Vector3iPod&)const; ///< sub()。
    const Vector3iPod operator*(const Vector3iPod&)const; ///< mul()。
    const Vector3iPod operator/(const Vector3iPod&)const; ///< div()。
    const Vector3iPod operator-()const; ///< neg()。
    Vector3iPod& operator+=(s32); ///< addAssign()。
    Vector3iPod& operator-=(s32); ///< subAssign()。
    Vector3iPod& operator*=(s32); ///< mulAssign()。
    Vector3iPod& operator/=(s32); ///< divAssign()。
    Vector3iPod& operator+=(const Vector3iPod&); ///< addAssign()。
    Vector3iPod& operator-=(const Vector3iPod&); ///< subAssign()。
    Vector3iPod& operator*=(const Vector3iPod&); ///< mulAssign()。
    Vector3iPod& operator/=(const Vector3iPod&); ///< divAssign()。
    //@}

    //============================================================
    /// @name 選択
    //@{
    const Vector3iPod min(const Vector3iPod&)const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
    const Vector3iPod max(const Vector3iPod&)const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
    //@}

    //============================================================
    /// @name クランプ
    //@{
    const Vector3iPod clamp(const Vector3iPod& aMin, const Vector3iPod& aMax)const; ///< aMin以上aMax以下になるようにクランプする。
    const Vector3iPod clampPositive()const; ///< clamp( Zero() , Max() ) を取得する。
    const Vector3iPod clampNegative()const; ///< clamp( Min() , Zero() ) を取得する。
    //@}

    //============================================================
    /// @name 符号
    //@{
    const Vector3iPod abs()const; ///< 各要素を正に置き換えたベクトルを取得。
    const Vector3iPod neg()const; ///< 符号を反転させた結果を取得する。
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
    /// x,y,z形式の文字列に変換。
    const ShortString toShortString()const;
    //@}
};

/// Vector3iPod のクラス版。
class Vector3i : public Vector3iPod
{
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Vector3i(); ///< Zero() で作成。
    Vector3i(const Vector3iPod& aXYZ); ///< コピーして作成。
    Vector3i(s32 aV); ///< 全要素同じ値で作成。
    Vector3i(const Vector2iPod& aXY, s32 aZ); ///< XYZを指定して作成。
    Vector3i(s32 aX, s32 aY, s32 aZ); ///< XYZを指定して作成。
    //@}
};

/// Vector3iPod のエイリアス。
typedef Vector3iPod Vec3i;
//@}

}} // namespace
#endif
// EOF
