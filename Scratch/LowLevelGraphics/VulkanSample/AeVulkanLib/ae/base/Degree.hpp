// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_DEGREE_HPP)
#else
#define AE_BASE_INCLUDED_DEGREE_HPP

#include <ae/base/BuiltInTypes.hpp>

namespace ae::base {
class Angle;
struct RadianPod;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// 度を扱う構造体。
struct DegreePod
{
    f32 value; ///< 度の値。

    /// @name 変換
    //@{
    const Angle ToAngle() const; ///< 角度に変換。
    const RadianPod ToRadian() const; ///< ラジアンに変換。
    //@}
};

/// DegreePod のクラス版。
class Degree : public DegreePod {
public:
    /// @name コンストラクタ
    //@{
    Degree(); ///< 0度を作成。
    Degree(float degree); ///< 値を指定して作成。
    Degree(const DegreePod& val); ///< コピーして作成。
    //@}
};
//@}

} // namespace ae::base
#endif
// EOF
