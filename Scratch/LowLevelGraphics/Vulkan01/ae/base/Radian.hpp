// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_RADIAN_HPP)
#else
#define AE_BASE_INCLUDED_RADIAN_HPP

#include <ae/base/BuiltInTypes.hpp>

namespace ae {
namespace base {
class  Angle;
struct DegreePod;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Math
//@{
/// ラジアンを扱う構造体。
struct RadianPod
{
    f32 value; ///< ラジアン。

    /// @name 変換
    //@{
    const Angle     toAngle()const;  ///< 角度に変換。
    const DegreePod toDegree()const; ///< 度に変換。
    //@}
};

/// RadianPod のクラス版。
class Radian : public RadianPod
{
public:
    /// @name コンストラクタ
    //@{
    Radian(); ///< 0度を作成。
    Radian(float aRadian); ///< 値を指定して作成。
    Radian(const RadianPod& aVal); ///< コピーして作成。
    //@}
};
//@}

}} // namespace
#endif
// EOF
