// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_VECTOR3_HPP)
#else
#define AE_BASE_INCLUDED_VECTOR3_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ShortString.hpp>

namespace ae {
namespace base {
struct Vector2Pod;
struct Vector4Pod;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

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
    static const Vector3Pod Zero();     ///< 0ベクトル。
    static const Vector3Pod One();      ///< X,Y,Zが全て1のベクトル。
    static const Vector3Pod Min();      ///< 最小値のベクトル。
    static const Vector3Pod Max();      ///< 最大値のベクトル。
    static const Vector3Pod UnitX();    ///< X単位ベクトル。
    static const Vector3Pod UnitY();    ///< Y単位ベクトル。
    static const Vector3Pod UnitZ();    ///< Z単位ベクトル。
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
    const Vector2Pod toXY()const;
    const Vector2Pod toXX()const;
    const Vector2Pod toYY()const;
    const Vector2Pod toZZ()const;
    const Vector3Pod toX00()const;
    const Vector3Pod toXY0()const;
    const Vector3Pod to0Y0()const;
    const Vector3Pod to0YZ()const;
    const Vector3Pod to00Z()const;
    const Vector3Pod toXXX()const;
    const Vector3Pod toYYY()const;
    const Vector3Pod toZZZ()const;
    const Vector4Pod toXYZ0()const;
    const Vector4Pod toXXXX()const;
    const Vector4Pod toYYYY()const;
    const Vector4Pod toZZZZ()const;
    //@}

    //============================================================
    /// @name 等価比較
    //@{
    bool equals(const Vector3Pod&)const;       ///< 許容誤差を考慮した等価比較。
    bool equalsStrict(const Vector3Pod&)const; ///< 許容誤差を許容しない等価比較。
    //@}

    //============================================================
    /// @name 四則演算
    //@{
    const Vector3Pod add(f32)const; ///< 各要素に値を加算した結果を取得する。
    const Vector3Pod sub(f32)const; ///< 各要素から値を減算した結果を取得する。
    const Vector3Pod mul(f32)const; ///< 各要素に値をかけた結果を取得する。
    const Vector3Pod div(f32)const; ///< 各要素から値をわった結果を取得する。
    const Vector3Pod add(const Vector3Pod&)const; ///< 対応する値同士を加算した結果を取得する。
    const Vector3Pod sub(const Vector3Pod&)const; ///< 対応する値に対して減算した結果を取得する。
    const Vector3Pod mul(const Vector3Pod&)const; ///< 対応する値同士をかけた結果を取得する。
    const Vector3Pod div(const Vector3Pod&)const; ///< 対応する値に対して割り算をした結果を取得する。
    void addAssign(f32); ///< 各要素に値を加算する。
    void subAssign(f32); ///< 各要素から値を減算する。
    void mulAssign(f32); ///< 各要素に値をかける。
    void divAssign(f32); ///< 各要素から値をわる。
    void addAssign(const Vector3Pod&); ///< 対応する値同士を加算する。
    void subAssign(const Vector3Pod&); ///< 対応する値に対して減算する。
    void mulAssign(const Vector3Pod&); ///< 対応する値同士をかける。
    void divAssign(const Vector3Pod&); ///< 対応する値に対して割り算をする。       
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Vector3Pod operator+(f32)const; ///< add()。
    const Vector3Pod operator-(f32)const; ///< sub()。
    const Vector3Pod operator*(f32)const; ///< mul()。
    const Vector3Pod operator/(f32)const; ///< div()。
    const Vector3Pod operator+(const Vector3Pod&)const; ///< add()。
    const Vector3Pod operator-(const Vector3Pod&)const; ///< sub()。
    const Vector3Pod operator*(const Vector3Pod&)const; ///< mul()。
    const Vector3Pod operator/(const Vector3Pod&)const; ///< div()。
    const Vector3Pod operator-()const; ///< neg()。
    Vector3Pod& operator+=(f32); ///< addAssign()。
    Vector3Pod& operator-=(f32); ///< subAssign()。
    Vector3Pod& operator*=(f32); ///< mulAssign()。
    Vector3Pod& operator/=(f32); ///< divAssign()。
    Vector3Pod& operator+=(const Vector3Pod&); ///< addAssign()。
    Vector3Pod& operator-=(const Vector3Pod&); ///< subAssign()。
    Vector3Pod& operator*=(const Vector3Pod&); ///< mulAssign()。
    Vector3Pod& operator/=(const Vector3Pod&); ///< divAssign()。
    //@}

    //============================================================
    /// @name 選択
    //@{
    const Vector3Pod min(const Vector3Pod&)const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
    const Vector3Pod max(const Vector3Pod&)const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
    //@}

    //============================================================
    /// @name クランプ
    //@{
    const Vector3Pod clamp(const Vector3Pod& aMin, const Vector3Pod& aMax)const; ///< aMin以上aMax以下になるようにクランプする。
    const Vector3Pod clampPositive()const; ///< clamp( Zero() , Max() ) を取得する。
    const Vector3Pod clampNegative()const; ///< clamp( Min() , Zero() ) を取得する。
    //@}

    //============================================================
    /// @name 符号操作
    //@{
    const Vector3Pod abs()const; ///< 各要素を正に置き換えたベクトルを取得。
    const Vector3Pod neg()const; ///< 符号を反転させた結果を取得する。
    //@}

    //============================================================
    /// @name 長さ＆正規化
    //@{
    f32  squareLength()const;                ///< 長さの2乗を取得する。
    f32  length()const;                      ///< 長さを取得する。
    f32  distance(const Vector3Pod&)const; ///< あるベクトルとの距離を取得する。
    bool isZero()const;                      ///< 長さが0か。許容誤差を許す。
    bool isZeroStrict()const;                ///< 長さが0か。許容誤差を許さない。
    bool isUnit()const;                      ///< 正規化済みか。許容誤差を許す。
    const Vector3Pod unit()const;            ///< @brief 正規化したベクトルを取得する。 @details 長さ0のベクトルで正規化するとエラーになります。
    void unitAssign();                       ///< @brief 正規化する。 @details 長さ0のベクトルで正規化するとエラーになります。
    //@}

    //============================================================
    /// @name 内積・外積
    //@{
    f32 dot(const Vector3Pod&)const;                ///< あるベクトルとの内積を取得する。
    const Vector3Pod cross(const Vector3Pod&)const; ///< あるベクトルとの外積を取得とる。
    //@}

    //============================================================
    /// @name ユーティリティ
    //@{
    /// x,y,z形式の文字列に変換。
    const ShortString toShortString()const;
    //@}
};

/// Vector3Pod のクラス版。
class Vector3 : public Vector3Pod
{
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Vector3(); ///< Zero() で作成。
    Vector3(const Vector3Pod& aXYZ); ///< コピーして作成。
    Vector3(f32 aV); ///< 全要素同じ値で作成。
    Vector3(const Vector2Pod& aXY, f32 aZ); ///< XYZを指定して作成。
    Vector3(f32 aX, f32 aY, f32 aZ); ///< XYZを指定して作成。
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

}} // namespace
#endif
// EOF
