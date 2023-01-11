// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_QUATERNION_HPP)
#else
#define AE_BASE_INCLUDED_QUATERNION_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ShortString.hpp>

namespace ae::base {
class Angle;
struct Matrix34Pod;
struct Vector3Pod;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// @brief 32bit浮動小数のクォータニオンクラス。
class Quaternion {
public:
    //============================================================
    /// @name 変数
    //@{
    f32 x; ///< x。
    f32 y; ///< y。
    f32 z; ///< z。
    f32 w; ///< w。
    //@}

    //============================================================
    /// @name コンストラクタ
    //@{
    Quaternion(); ///< 単位クォータニオンの作成。
    Quaternion(f32 x, f32 y, f32 z, f32 w); ///< 各要素の値を指定して作成。
    Quaternion(
        const Vector3Pod& axis,
        const Angle& angle); ///< 任意軸回転用クォータニオンの作成。
    //@}

    //============================================================
    /// @name 計算
    //@{
    const Quaternion Mul(
        const Quaternion&) const; ///< 乗算した結果を得る。this x rhs。
    Quaternion& MulAssign(const Quaternion&); ///< 乗算。this x rhs。
    //@}

    //============================================================
    /// @name 変換
    //@{
    const Matrix34Pod ToRotateMatrix() const; ///< 回転行列に変換。
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Quaternion operator*(const Quaternion&) const; ///< mulのエイリアス。
    Quaternion& operator*=(const Quaternion&); ///< mulAssignのエイリアス。
    //@}

    //============================================================
    /// @name ユーティリティ
    //@{
    /// x,y,z,w形式の文字列に変換。
    const ShortString ToShortString() const;
    //@}
};
//@}

} // namespace ae::base
#endif
// EOF
