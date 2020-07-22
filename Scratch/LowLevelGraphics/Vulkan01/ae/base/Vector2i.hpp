// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_VECTOR2I_HPP)
#else
#define AE_BASE_INCLUDED_VECTOR2I_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ShortString.hpp>

namespace ae {
namespace base {
struct Vector2Pod;
struct Vector3iPod;
struct Vector4iPod;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

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
    static const Vector2iPod Zero();     ///< 0ベクトル。
    static const Vector2iPod One();      ///< X,Yが全て1のベクトル。
    static const Vector2iPod Min();      ///< 最小値のベクトル。
    static const Vector2iPod Max();      ///< 最大値のベクトル。
    static const Vector2iPod UnitX();    ///< X単位ベクトル。
    static const Vector2iPod UnitY();    ///< Y単位ベクトル。
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
    const Vector2iPod toX0()const;
    const Vector2iPod to0Y()const;
    const Vector2iPod toXX()const;
    const Vector2iPod toYX()const;
    const Vector2iPod toYY()const;
    const Vector3iPod toXY0()const;
    const Vector3iPod toXXX()const;
    const Vector3iPod toYYY()const;
    const Vector4iPod toXY00()const;
    const Vector4iPod toXXXX()const;
    const Vector4iPod toYYYY()const;
    const Vector2Pod  toXYf()const;
    //@}

    //============================================================
    /// @name 等価比較
    //@{
    bool equals(const Vector2iPod&)const;       ///< 等価比較。
    //@}

    //============================================================
    /// @name 四則演算
    //@{
    const Vector2iPod add(s32)const; ///< 各要素に値を加算した結果を取得する。
    const Vector2iPod sub(s32)const; ///< 各要素から値を減算した結果を取得する。
    const Vector2iPod mul(s32)const; ///< 各要素に値をかけた結果を取得する。
    const Vector2iPod div(s32)const; ///< 各要素から値をわった結果を取得する。
    const Vector2iPod add(const Vector2iPod&)const; ///< 対応する値同士を加算した結果を取得する。
    const Vector2iPod sub(const Vector2iPod&)const; ///< 対応する値に対して減算した結果を取得する。
    const Vector2iPod mul(const Vector2iPod&)const; ///< 対応する値同士をかけた結果を取得する。
    const Vector2iPod div(const Vector2iPod&)const; ///< 対応する値に対して割り算をした結果を取得する。
    void addAssign(s32); ///< 各要素に値を加算する。
    void subAssign(s32); ///< 各要素から値を減算する。
    void mulAssign(s32); ///< 各要素に値をかける。
    void divAssign(s32); ///< 各要素から値をわる。
    void addAssign(const Vector2iPod&); ///< 対応する値同士を加算する。
    void subAssign(const Vector2iPod&); ///< 対応する値に対して減算する。
    void mulAssign(const Vector2iPod&); ///< 対応する値同士をかける。
    void divAssign(const Vector2iPod&); ///< 対応する値に対して割り算をする。       
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Vector2iPod operator+(s32)const; ///< add()。
    const Vector2iPod operator-(s32)const; ///< sub()。
    const Vector2iPod operator*(s32)const; ///< mul()。
    const Vector2iPod operator/(s32)const; ///< div()。
    const Vector2iPod operator+(const Vector2iPod&)const; ///< add()。
    const Vector2iPod operator-(const Vector2iPod&)const; ///< sub()。
    const Vector2iPod operator*(const Vector2iPod&)const; ///< mul()。
    const Vector2iPod operator/(const Vector2iPod&)const; ///< div()。
    const Vector2iPod operator-()const; ///< neg()。
    Vector2iPod& operator+=(s32); ///< addAssign()。
    Vector2iPod& operator-=(s32); ///< subAssign()。
    Vector2iPod& operator*=(s32); ///< mulAssign()。
    Vector2iPod& operator/=(s32); ///< divAssign()。
    Vector2iPod& operator+=(const Vector2iPod&); ///< addAssign()。
    Vector2iPod& operator-=(const Vector2iPod&); ///< subAssign()。
    Vector2iPod& operator*=(const Vector2iPod&); ///< mulAssign()。
    Vector2iPod& operator/=(const Vector2iPod&); ///< divAssign()。
    //@}

    //============================================================
    /// @name 選択
    //@{
    const Vector2iPod min(const Vector2iPod&)const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
    const Vector2iPod max(const Vector2iPod&)const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
    //@}

    //============================================================
    /// @name クランプ
    //@{
    const Vector2iPod clamp(const Vector2iPod& aMin, const Vector2iPod& aMax)const; ///< aMin以上aMax以下になるようにクランプする。
    const Vector2iPod clampPositive()const; ///< clamp( Zero() , Max() ) を取得する。
    const Vector2iPod clampNegative()const; ///< clamp( Min() , Zero() ) を取得する。
    //@}

    //============================================================
    /// @name 符号
    //@{
    const Vector2iPod abs()const; ///< 各要素を正に置き換えたベクトルを取得。
    const Vector2iPod neg()const; ///< 符号を反転させた結果を取得する。
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
    /// x,y形式の文字列に変換。
    const ShortString toShortString()const;
    //@}
};

/// Vector2iPod のクラス版。
class Vector2i : public Vector2iPod
{
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Vector2i(); ///< Zero() で作成。
    Vector2i(const Vector2iPod& aXY); ///< コピーして作成。
    Vector2i(s32 aV); ///< 全要素同じ値で作成。
    Vector2i(s32 aX, s32 aY); ///< XYを指定して作成。
    //@}
};

/// Vector2iPod のエイリアス。
typedef Vector2iPod Vec2i;
//@}

}} // namespace
#endif
// EOF
