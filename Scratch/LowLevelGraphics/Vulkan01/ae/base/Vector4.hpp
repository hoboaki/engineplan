// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_VECTOR4_HPP)
#else
#define AE_BASE_INCLUDED_VECTOR4_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ShortString.hpp>

namespace ae {
namespace base {
struct Vector2Pod;
struct Vector3Pod;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

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
    static const Vector4Pod Zero();     ///< 0ベクトル。
    static const Vector4Pod One();      ///< X,Y,Z,Wが全て1のベクトル。
    static const Vector4Pod Min();      ///< 最小値のベクトル。
    static const Vector4Pod Max();      ///< 最大値のベクトル。
    static const Vector4Pod UnitX();    ///< X単位ベクトル。
    static const Vector4Pod UnitY();    ///< Y単位ベクトル。
    static const Vector4Pod UnitZ();    ///< Z単位ベクトル。
    static const Vector4Pod UnitW();    ///< W単位ベクトル。
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
    const Vector2Pod toXY()const;
    const Vector2Pod toXX()const;
    const Vector2Pod toYY()const;
    const Vector2Pod toZZ()const;
    const Vector2Pod toWW()const;
    const Vector3Pod toXYZ()const;
    const Vector3Pod toXXX()const;
    const Vector3Pod toYYY()const;
    const Vector3Pod toZZZ()const;
    const Vector3Pod toWWW()const;
    const Vector4Pod toXYZ0()const;
    const Vector4Pod toXY0W()const;
    const Vector4Pod toXY00()const;
    const Vector4Pod toX0ZW()const;
    const Vector4Pod toX0Z0()const;
    const Vector4Pod toX00W()const;
    const Vector4Pod toX000()const;
    const Vector4Pod to0YZ0()const;
    const Vector4Pod to0Y0W()const;
    const Vector4Pod to0Y00()const;
    const Vector4Pod to00ZW()const;
    const Vector4Pod to00Z0()const;
    const Vector4Pod to000W()const;
    const Vector4Pod toXXXX()const;
    const Vector4Pod toYYYY()const;
    const Vector4Pod toZZZZ()const;
    const Vector4Pod toWWWW()const;
    //@}

    //============================================================
    /// @name 等価比較
    //@{
    bool equals(const Vector4Pod&)const;       ///< 許容誤差を考慮した等価比較。
    bool equalsStrict(const Vector4Pod&)const; ///< 許容誤差を許容しない等価比較。
    //@}

    //============================================================
    /// @name 四則演算
    //@{
    const Vector4Pod add(f32)const; ///< 各要素に値を加算した結果を取得する。
    const Vector4Pod sub(f32)const; ///< 各要素から値を減算した結果を取得する。
    const Vector4Pod mul(f32)const; ///< 各要素に値をかけた結果を取得する。
    const Vector4Pod div(f32)const; ///< 各要素から値をわった結果を取得する。
    const Vector4Pod add(const Vector4Pod&)const; ///< 対応する値同士を加算した結果を取得する。
    const Vector4Pod sub(const Vector4Pod&)const; ///< 対応する値に対して減算した結果を取得する。
    const Vector4Pod mul(const Vector4Pod&)const; ///< 対応する値同士をかけた結果を取得する。
    const Vector4Pod div(const Vector4Pod&)const; ///< 対応する値に対して割り算をした結果を取得する。
    void addAssign(f32); ///< 各要素に値を加算する。
    void subAssign(f32); ///< 各要素から値を減算する。
    void mulAssign(f32); ///< 各要素に値をかける。
    void divAssign(f32); ///< 各要素から値をわる。
    void addAssign(const Vector4Pod&); ///< 対応する値同士を加算する。
    void subAssign(const Vector4Pod&); ///< 対応する値に対して減算する。
    void mulAssign(const Vector4Pod&); ///< 対応する値同士をかける。
    void divAssign(const Vector4Pod&); ///< 対応する値に対して割り算をする。       
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Vector4Pod operator+(f32)const; ///< add()。
    const Vector4Pod operator-(f32)const; ///< sub()。
    const Vector4Pod operator*(f32)const; ///< mul()。
    const Vector4Pod operator/(f32)const; ///< div()。
    const Vector4Pod operator+(const Vector4Pod&)const; ///< add()。
    const Vector4Pod operator-(const Vector4Pod&)const; ///< sub()。
    const Vector4Pod operator*(const Vector4Pod&)const; ///< mul()。
    const Vector4Pod operator/(const Vector4Pod&)const; ///< div()。
    const Vector4Pod operator-()const; ///< neg()。
    Vector4Pod& operator+=(f32); ///< addAssign()。
    Vector4Pod& operator-=(f32); ///< subAssign()。
    Vector4Pod& operator*=(f32); ///< mulAssign()。
    Vector4Pod& operator/=(f32); ///< divAssign()。
    Vector4Pod& operator+=(const Vector4Pod&); ///< addAssign()。
    Vector4Pod& operator-=(const Vector4Pod&); ///< subAssign()。
    Vector4Pod& operator*=(const Vector4Pod&); ///< mulAssign()。
    Vector4Pod& operator/=(const Vector4Pod&); ///< divAssign()。
    //@}

    //============================================================
    /// @name 選択
    //@{
    const Vector4Pod min(const Vector4Pod&)const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
    const Vector4Pod max(const Vector4Pod&)const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
    //@}

    //============================================================
    /// @name クランプ
    //@{
    const Vector4Pod clamp(const Vector4Pod& aMin, const Vector4Pod& aMax)const; ///< aMin以上aMax以下になるようにクランプする。
    const Vector4Pod clampPositive()const; ///< clamp( Zero() , Max() ) を取得する。
    const Vector4Pod clampNegative()const; ///< clamp( Min() , Zero() ) を取得する。
    //@}

    //============================================================
    /// @name 符号操作
    //@{
    const Vector4Pod abs()const; ///< 各要素を正に置き換えたベクトルを取得。
    const Vector4Pod neg()const; ///< 符号を反転させた結果を取得する。
    //@}

    //============================================================
    /// @name 長さ＆正規化
    //@{
    f32  squareLength()const;                ///< 長さの2乗を取得する。
    f32  length()const;                      ///< 長さを取得する。
    f32  distance(const Vector4Pod&)const; ///< あるベクトルとの距離を取得する。
    bool isZero()const;                      ///< 長さが0か。許容誤差を許す。
    bool isZeroStrict()const;                ///< 長さが0か。許容誤差を許さない。
    bool isUnit()const;                      ///< 正規化済みか。許容誤差を許す。
    const Vector4Pod unit()const;            ///< @brief 正規化したベクトルを取得する。 @details 長さ0のベクトルで正規化するとエラーになります。
    void unitAssign();                       ///< @brief 正規化する。 @details 長さ0のベクトルで正規化するとエラーになります。
    //@}

    //============================================================
    /// @name 内積
    //@{
    f32 dot(const Vector4Pod&)const;                ///< あるベクトルとの内積を取得する。
    //@}

    //============================================================
    /// @name ユーティリティ
    //@{
    /// x,y,z,w形式の文字列に変換。
    const ShortString toShortString()const;
    //@}
};

/// Vector4Pod のクラス版。
class Vector4 : public Vector4Pod
{
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Vector4(); ///< Zero() で作成。
    Vector4(const Vector4Pod& aXYZW); ///< コピーして作成。
    Vector4(f32 aV); ///< 全要素同じ値で作成。
    Vector4(const Vector2Pod& aXY, f32 aZ, f32 aW); ///< XYZWを指定して作成。
    Vector4(const Vector3Pod& aXYZ, f32 aW); ///< XYZWを指定して作成。
    Vector4(f32 aX, f32 aY, f32 aZ, f32 aW); ///< XYZWを指定して作成。
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

}} // namespace
#endif
// EOF
