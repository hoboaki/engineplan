// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_ANGLE_HPP)
#else
#define AE_BASE_INCLUDED_ANGLE_HPP

#include <ae/base/BuiltinTypes.hpp>

namespace ae::base {
struct DegreePod;
struct RadianPod;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// 角度を示すクラス。
class Angle {
public:
    /// @name コンストラクタ
    //@{
    Angle(); ///< 0度で作成。
    Angle(const DegreePod&); ///< Degreeで作成。
    Angle(const RadianPod&); ///< Radianで作成。
    //@}

    /// @name 角度の取得
    //@{
    f32 Rad() const; ///< radianで取得。
    f32 Deg() const; ///< degreeで取得。
    //@}

private:
    f32 rad_;
};
//@}

} // namespace ae::base
#endif
// EOF
