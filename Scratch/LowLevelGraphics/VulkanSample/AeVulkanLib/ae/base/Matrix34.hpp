// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_MATRIX34_HPP)
#else
#define AE_BASE_INCLUDED_MATRIX34_HPP

#include <ae/base/BuiltInTypes.hpp>

namespace ae::base {
class Angle;
class Quaternion;
struct Matrix44Pod;
struct Vector3Pod;
struct Vector4Pod;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// @brief 3x4の32bit浮動小数行列構造体。
/// @details
/// 使用頻度のことを考えて Mtx34 という名前でもアクセスできます。
/// 配列の並びはOpenGL準拠にしてあります。
/// @code
///    c0  c1   c2   c3
/// r0 [0] [3]  [6]  [9]
/// r1 [1] [4]  [7] [10]
/// r2 [2] [5]  [8] [11]
/// @endcode
struct Matrix34Pod
{
    //============================================================
    /// @name インデックス値
    //@{
    enum
    {
        Index00 = 0, ///< [0][0]
        Index10 = 1, ///< [1][0]
        Index20 = 2, ///< [2][0]
        Index01 = 3, ///< [0][1]
        Index11 = 4, ///< [1][1]
        Index21 = 5, ///< [2][1]
        Index02 = 6, ///< [0][2]
        Index12 = 7, ///< [1][2]
        Index22 = 8, ///< [2][2]
        Index03 = 9, ///< [0][3]
        Index13 = 10, ///< [1][3]
        Index23 = 11, ///< [2][3]
        IndexXX = Index00, ///< [0][0]
        IndexXY = Index10, ///< [1][0]
        IndexXZ = Index20, ///< [2][0]
        IndexYX = Index01, ///< [0][1]
        IndexYY = Index11, ///< [1][1]
        IndexYZ = Index21, ///< [2][1]
        IndexZX = Index02, ///< [0][2]
        IndexZY = Index12, ///< [1][2]
        IndexZZ = Index22, ///< [2][2]
        IndexWX = Index03, ///< [0][3]
        IndexWY = Index13, ///< [1][3]
        IndexWZ = Index23, ///< [2][3]
    };
    //@}

    //============================================================
    /// @name 行列の作成
    //@{
    static const Matrix34Pod Identity(); ///< 単位行列の作成。
    static const Matrix34Pod Translate(
        f32 x,
        f32 y,
        f32 z); ///< 平行移動行列の作成。
    static const Matrix34Pod Translate(
        const Vector3Pod& vec); ///< 平行移動行列の作成。
    static const Matrix34Pod Scale(
        f32 x,
        f32 y,
        f32 z); ///< 拡大縮小行列の作成。
    static const Matrix34Pod Scale(
        const Vector3Pod& vec); ///< 拡大縮小行列の作成。
    static const Matrix34Pod Rotate(
        const Angle&,
        f32 axisX,
        f32 axisY,
        f32 axisZ); ///< 回転行列の作成。
    static const Matrix34Pod Rotate(
        const Angle&,
        const Vector3Pod& axis); ///< 回転行列の作成。

    /// @brief 視野変換行列の作成。
    /// @param eyePos 目の位置。
    /// @param targetPos 注視点。
    /// @param upVec 上方向のベクトル。isZeroなベクトルを渡してはいけない。
    /// @details eyePos != targetPosである必要があります。
    static const Matrix34Pod LookAt(
        const Vector3Pod& eyePos,
        const Vector3Pod& targetPos,
        const Vector3Pod& upVec);
    //@}

    //============================================================
    /// @name 変数
    //@{
    union
    {
        f32 v[12]; ///< 1次元配列。
    };
    //@}

    //============================================================
    /// @name XYZWアクセス（1列ごとにX,Y,Z,Wが割り当てられているとする）
    //@{
    const Vector3Pod x() const;
    const Vector3Pod y() const;
    const Vector3Pod z() const;
    const Vector3Pod w() const;
    void SetX(const Vector3Pod&);
    void SetY(const Vector3Pod&);
    void SetZ(const Vector3Pod&);
    void SetW(const Vector3Pod&);
    //@}

    //============================================================
    /// @name 乗算（引数が同じオブジェクトでも問題無し）
    //@{
    const Vector3Pod Mul(const Vector3Pod&)
        const; ///< @brief 乗算した結果を得る。 @details 4行目は0,0,0,1として計算する。
    const Matrix34Pod Mul(const Matrix34Pod&)
        const; ///< @brief 乗算した結果を得る。 @details this x rhs。4行目は0,0,0,1として計算する。
    Matrix34Pod& MulAssign(
        const Matrix34Pod&); ///< @brief 乗算し結果を代入する。@details  this = this x rhs。4行目は0,0,0,1として計算する。
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Vector3Pod operator*(
        const Vector3Pod&) const; ///< Mul() のエイリアス。
    const Matrix34Pod operator*(
        const Matrix34Pod&) const; ///< Mul() のエイリアス。
    Matrix34Pod& operator*=(const Matrix34Pod&); ///< MulAssign() のエイリアス。
    //@}

    //============================================================
    /// @name 変換
    //@{
    const Matrix34Pod Invert()
        const; ///< 逆行列を取得する。4行目は0,0,0,1として作成する。
    const Matrix34Pod Transpose()
        const; ///< 転置行列を取得する。4行目は0,0,0,1として作成する。
    const Quaternion ToQuaternion()
        const; ///< 3x3の部分をクォータニオンに変換する。
    const Matrix44Pod ToMatrix44()
        const; ///< 4x4に変換する。4行目は0,0,0,1として作成する。
    //@}

    //============================================================
    /// @name デバッグ
    //@{
    void Dump() const;
    //@}
};

/// Matrix34Pod のクラス版。
class Matrix34 : public Matrix34Pod {
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Matrix34(); ///< 単位行列で初期化。
    /// 全要素を指定して作成。
    Matrix34(
        f32 r0c0,
        f32 r0c1,
        f32 r0c2,
        f32 r0c3,
        f32 r1c0,
        f32 r1c1,
        f32 r1c2,
        f32 r1c3,
        f32 r2c0,
        f32 r2c1,
        f32 r2c2,
        f32 r2c3);
    Matrix34(
        const Vector3Pod& x,
        const Vector3Pod& y,
        const Vector3Pod& z,
        const Vector3Pod& w); ///< X,Y,Z,Wを指定して作成。
    Matrix34(const Matrix34Pod&); ///< コピーして作成。
    //@}
};

/// Matrix34Pod のエイリアス。
typedef Matrix34Pod Mtx34;
//@}

} // namespace ae::base
#endif
// EOF
