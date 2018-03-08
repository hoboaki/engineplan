// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_VECTOR2_HPP)
#else
#define AE_BASE_INCLUDED_VECTOR2_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ShortString.hpp>

namespace ae {
namespace base {
struct Vector2Pod;
struct Vector3Pod;
struct Vector4Pod;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Math
//@{
/// Vector2Podのエイリアス。
typedef Vector2Pod Vec2;

/// @brief 浮動小数型2次元ベクトル構造体。
/// @details 
/// 使用頻度のことを考えて Vec2 という名前でもアクセスできます。
/// メモリ配置は32bit浮動小数が先頭からx,yの順番に並んでいます。
struct Vector2Pod
{
    //============================================================
    /// @name 定数取得
    //@{
    static const Vector2Pod Zero();     ///< 0ベクトル。
    static const Vector2Pod One();      ///< X,Yが全て1のベクトル。
    static const Vector2Pod Min();      ///< 最小値のベクトル。
    static const Vector2Pod Max();      ///< 最大値のベクトル。
    static const Vector2Pod UnitX();    ///< X単位ベクトル。
    static const Vector2Pod UnitY();    ///< Y単位ベクトル。
    static const Vector2Pod NegUnitX(); ///< -X単位ベクトル。
    static const Vector2Pod NegUnitY(); ///< -Y単位ベクトル。
    //@}

    //============================================================
    /// @name 変数
    //@{
    f32 x; ///< x。
    f32 y; ///< y。
    //@}

    //============================================================
    /// @name 変換
    //@{
    const Vector2Pod toX0()const;
    const Vector2Pod to0Y()const;
    const Vector2Pod toXX()const;
    const Vector2Pod toYX()const;
    const Vector2Pod toYY()const;
    const Vector3Pod toXY0()const;
    const Vector3Pod toXXX()const;
    const Vector3Pod toYYY()const;
    const Vector4Pod toXY00()const;
    const Vector4Pod toXXXX()const;
    const Vector4Pod toYYYY()const;
    //@}

    //============================================================
    /// @name 等価比較
    //@{
    bool equals(const Vector2Pod&)const;       ///< 許容誤差を考慮した等価比較。
    bool equalsStrict(const Vector2Pod&)const; ///< 許容誤差を許容しない等価比較。
    //@}

    //============================================================
    /// @name 四則演算
    //@{
    const Vector2Pod add(f32)const; ///< 各要素に値を加算した結果を取得する。
    const Vector2Pod sub(f32)const; ///< 各要素から値を減算した結果を取得する。
    const Vector2Pod mul(f32)const; ///< 各要素に値をかけた結果を取得する。
    const Vector2Pod div(f32)const; ///< 各要素から値をわった結果を取得する。
    const Vector2Pod add(const Vector2Pod&)const; ///< 対応する値同士を加算した結果を取得する。
    const Vector2Pod sub(const Vector2Pod&)const; ///< 対応する値に対して減算した結果を取得する。
    const Vector2Pod mul(const Vector2Pod&)const; ///< 対応する値同士をかけた結果を取得する。
    const Vector2Pod div(const Vector2Pod&)const; ///< 対応する値に対して割り算をした結果を取得する。
    void addAssign(f32); ///< 各要素に値を加算する。
    void subAssign(f32); ///< 各要素から値を減算する。
    void mulAssign(f32); ///< 各要素に値をかける。
    void divAssign(f32); ///< 各要素から値をわる。
    void addAssign(const Vector2Pod&); ///< 対応する値同士を加算する。
    void subAssign(const Vector2Pod&); ///< 対応する値に対して減算する。
    void mulAssign(const Vector2Pod&); ///< 対応する値同士をかける。
    void divAssign(const Vector2Pod&); ///< 対応する値に対して割り算をする。       
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Vector2Pod operator+(f32)const; ///< add()。
    const Vector2Pod operator-(f32)const; ///< sub()。
    const Vector2Pod operator*(f32)const; ///< mul()。
    const Vector2Pod operator/(f32)const; ///< div()。
    const Vector2Pod operator+(const Vector2Pod&)const; ///< add()。
    const Vector2Pod operator-(const Vector2Pod&)const; ///< sub()。
    const Vector2Pod operator*(const Vector2Pod&)const; ///< mul()。
    const Vector2Pod operator/(const Vector2Pod&)const; ///< div()。
    const Vector2Pod operator-()const; ///< neg()。
    Vector2Pod& operator+=(f32); ///< addAssign()。
    Vector2Pod& operator-=(f32); ///< subAssign()。
    Vector2Pod& operator*=(f32); ///< mulAssign()。
    Vector2Pod& operator/=(f32); ///< divAssign()。
    Vector2Pod& operator+=(const Vector2Pod&); ///< addAssign()。
    Vector2Pod& operator-=(const Vector2Pod&); ///< subAssign()。
    Vector2Pod& operator*=(const Vector2Pod&); ///< mulAssign()。
    Vector2Pod& operator/=(const Vector2Pod&); ///< divAssign()。
    //@}

    //============================================================
    /// @name 選択
    //@{
    const Vector2Pod min(const Vector2Pod&)const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
    const Vector2Pod max(const Vector2Pod&)const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
    //@}

    //============================================================
    /// @name クランプ
    //@{
    const Vector2Pod clamp(const Vector2Pod& aMin, const Vector2Pod& aMax)const; ///< aMin以上aMax以下になるようにクランプする。
    const Vector2Pod clampPositive()const; ///< clamp( Zero() , Max() ) を取得する。
    const Vector2Pod clampNegative()const; ///< clamp( Min() , Zero() ) を取得する。
    //@}

    //============================================================
    /// @name 符号操作
    //@{
    const Vector2Pod abs()const; ///< 各要素を正に置き換えたベクトルを取得。
    const Vector2Pod neg()const; ///< 符号を反転させた結果を取得する。
    //@}

    //============================================================
    /// @name 長さ＆正規化
    //@{
    f32  squareLength()const;                ///< 長さの2乗を取得する。
    f32  length()const;                      ///< 長さを取得する。
    f32  distance(const Vector2Pod&)const; ///< あるベクトルとの距離を取得する。
    bool isZero()const;                      ///< 長さが0か。許容誤差を許す。
    bool isZeroStrict()const;                ///< 長さが0か。許容誤差を許さない。
    bool isUnit()const;                      ///< 正規化済みか。許容誤差を許す。
    const Vector2Pod unit()const;            ///< @brief 正規化したベクトルを取得する。 @details 長さ0のベクトルで正規化するとエラーになります。
    void unitAssign();                       ///< @brief 正規化する。 @details 長さ0のベクトルで正規化するとエラーになります。
    //@}

    //============================================================
    /// @name 内積・外積
    //@{
    f32 dot(const Vector2Pod&)const;     ///< あるベクトルとの内積(cosθ)を取得する。
    f32 cross(const Vector2Pod&)const;   ///< あるベクトルとの外積(sinθ)を取得とる。
    //@}

    //============================================================
    /// @name ユーティリティ
    //@{
    /// x,y形式の文字列に変換。
    const ShortString toShortString()const;
    //@}
};

/// Vector2Pod のクラス版。
class Vector2 : public Vector2Pod
{
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Vector2(); ///< Zero() で作成。
    Vector2(const Vector2Pod& aXY); ///< コピーして作成。
    Vector2(f32 aV); ///< 全要素同じ値で作成。
    Vector2(f32 aX, f32 aY); ///< XYを指定して作成。
    //@}
};

/// Vector2Pod のエイリアス。
typedef Vector2Pod Vec2;

/// Vector2Pod のエイリアス。
typedef Vector2Pod Vector2fPod;

/// Vec2 のエイリアス。
typedef Vec2 Vec2f;

/// Vector2 のエイリアス。
typedef Vector2 Vector2f;
//@}

}} // namespace
#endif
// EOF
