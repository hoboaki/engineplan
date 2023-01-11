// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_MATRIX44_HPP)
#else
#define AE_BASE_INCLUDED_MATRIX44_HPP

#include <ae/base/BuiltInTypes.hpp>

namespace ae::base {
class Angle;
struct Vector3Pod;
struct Vector4Pod;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// @brief 4x4の32bit浮動小数行列構造体。
/// @details
/// 使用頻度のことを考えて Mtx44 という名前でもアクセスできます。
/// 配列の並びはOpenGL準拠にしてあります。
/// @code
///    c0  c1   c2   c3
/// r0 [0] [4]  [8] [12]
/// r1 [1] [5]  [9] [13]
/// r2 [2] [6] [10] [14]
/// r3 [3] [7] [11] [15]
/// @endcode
///
/// DirectXの並びは行ベースになりますが演算上はどちらでも変わりません。
/// (例：Translateのx,y,z値はどちらも12,13,14番にくる。)
struct Matrix44Pod
{
    //============================================================
    /// @name インデックス値
    //@{
    enum
    {
        Index00 = 0, ///< [0][0]
        Index10 = 1, ///< [1][0]
        Index20 = 2, ///< [2][0]
        Index30 = 3, ///< [3][0]
        Index01 = 4, ///< [0][1]
        Index11 = 5, ///< [1][1]
        Index21 = 6, ///< [2][1]
        Index31 = 7, ///< [3][1]
        Index02 = 8, ///< [0][2]
        Index12 = 9, ///< [1][2]
        Index22 = 10, ///< [2][2]
        Index32 = 11, ///< [3][2]
        Index03 = 12, ///< [0][3]
        Index13 = 13, ///< [1][3]
        Index23 = 14, ///< [2][3]
        Index33 = 15, ///< [3][3]
        IndexXX = Index00, ///< [0][0]
        IndexXY = Index10, ///< [1][0]
        IndexXZ = Index20, ///< [2][0]
        IndexXW = Index30, ///< [3][0]
        IndexYX = Index01, ///< [0][1]
        IndexYY = Index11, ///< [1][1]
        IndexYZ = Index21, ///< [2][1]
        IndexYW = Index31, ///< [3][1]
        IndexZX = Index02, ///< [0][2]
        IndexZY = Index12, ///< [1][2]
        IndexZZ = Index22, ///< [2][2]
        IndexZW = Index32, ///< [3][2]
        IndexWX = Index03, ///< [0][3]
        IndexWY = Index13, ///< [1][3]
        IndexWZ = Index23, ///< [2][3]
        IndexWW = Index33, ///< [3][3]
    };
    //@}

    //============================================================
    /// @name 行列の作成
    //@{
    static const Matrix44Pod Identity(); ///< 単位行列の作成。
    static const Matrix44Pod Translate(
        f32 x,
        f32 y,
        f32 z); ///< 平行移動行列の作成。
    static const Matrix44Pod Translate(
        const Vector3Pod& vec); ///< 平行移動行列の作成。
    static const Matrix44Pod Scale(
        f32 x,
        f32 y,
        f32 z); ///< 拡大縮小行列の作成。
    static const Matrix44Pod Scale(
        const Vector3Pod& vec); ///< 拡大縮小行列の作成。
    static const Matrix44Pod Rotate(
        const Angle&,
        f32 axisX,
        f32 axisY,
        f32 axisZ); ///< 回転行列の作成。
    static const Matrix44Pod Rotate(
        const Angle&,
        const Vector3Pod& axis); ///< 回転行列の作成。

    /// 正射影行列の作成。（Depthは[0, 1]の範囲）
    static const Matrix44Pod Ortho(
        f32 left,
        f32 top,
        f32 right,
        f32 bottom,
        f32 near,
        f32 far);

    /// 透視射影行列(Frustum)の作成。（Depthは[-1, 1]の範囲、[0, 1]に要修正で動作確認もほぼできていない）
    static const Matrix44Pod Frustum(
        f32 left,
        f32 right,
        f32 bottom,
        f32 top,
        f32 near,
        f32 far);

    /// @brief 透視射影行列(Perspective)の作成。（Depthは[0, 1]の範囲）
    /// @param fOVY   Y方向の画角。0 < fOVY。
    /// @param aspect 横/縦のアスペクト比。4:3なら1.333。0 < aspect。
    /// @param near   Near値。
    /// @param far    Far値。
    static const Matrix44Pod Perspective(
        const Angle& fOVY,
        f32 aspect,
        f32 near,
        f32 far);

    /// @brief 視野変換行列の作成。
    /// @param eyePos 目の位置。
    /// @param targetPos 注視点。
    /// @param upVec 上方向のベクトル。isZeroなベクトルを渡してはいけない。
    /// @param eyePos != targetPosである必要がある。
    static const Matrix44Pod LookAt(
        const Vector3Pod& eyePos,
        const Vector3Pod& targetPos,
        const Vector3Pod& upVec);
    //@}

    //============================================================
    /// @name 変数
    //@{
    union
    {
        f32 v[16]; ///< 1次元配列。
        f32 m[4][4]; ///< 2次元配列。
    };
    //@}

    //============================================================
    /// @name XYZWアクセス（1列ごとにX,Y,Z,Wが割り当てられているとする）
    //@{
    const Vector4Pod x() const;
    const Vector4Pod y() const;
    const Vector4Pod z() const;
    const Vector4Pod w() const;
    void SetX(const Vector4Pod&);
    void SetY(const Vector4Pod&);
    void SetZ(const Vector4Pod&);
    void SetW(const Vector4Pod&);
    //@}

    //============================================================
    /// @name 乗算（引数が同じオブジェクトでも問題無し）
    //@{
    const Matrix44Pod Mul(
        const Matrix44Pod&) const; ///< 乗算した結果を得る。this x rhs。
    Matrix44Pod& MulAssign(
        const Matrix44Pod&); ///< 乗算し結果を代入する。this = this x rhs。
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Matrix44Pod operator*(const Matrix44Pod&) const; ///< Mul()。
    Matrix44Pod& operator*=(const Matrix44Pod&); ///< MulAssign()。
    //@}

    //============================================================
    /// @name 変換
    //@{
    const Matrix44Pod Invert() const; ///< 逆行列を取得する。
    const Matrix44Pod Transpose() const; ///< 転置行列を取得する。
    //@}

    //============================================================
    /// @name デバッグ
    //@{
    void Dump() const;
    //@}
};

/// Matrix44Pod のクラス版。
class Matrix44 : public Matrix44Pod {
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Matrix44(); ///< 単位行列で初期化。
    /// 全要素を指定して作成。
    Matrix44(
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
        f32 r2c3,
        f32 r3c0,
        f32 r3c1,
        f32 r3c2,
        f32 r3c3);
    Matrix44(
        const Vector4Pod& x,
        const Vector4Pod& y,
        const Vector4Pod& z,
        const Vector4Pod& w); ///< X,Y,Z,Wを指定して作成。
    Matrix44(const Matrix44Pod&); ///< コピーして作成。
    //@}
};

/// Matrix44Pod のエイリアス。
typedef Matrix44Pod Mtx44;
//@}

} // namespace ae::base
#endif
// EOF
