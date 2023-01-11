// 文字コード：UTF-8
#include <ae/base/Quaternion.hpp>

// includes
#include <ae/base/Angle.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/Matrix34.hpp>
#include <ae/base/Radian.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/ScalerTypes.hpp>
#include <ae/base/Vector3.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
Quaternion::Quaternion()
: x(0)
, y(0)
, z(0)
, w(1.0f)
{
}

//------------------------------------------------------------------------------
Quaternion::Quaternion(const f32 x, const f32 y, const f32 z, const f32 w)
: x(x)
, y(y)
, z(z)
, w(w)
{
}

//------------------------------------------------------------------------------
Quaternion::Quaternion(const Vector3Pod& axis, const Angle& angle)
: x()
, y()
, z()
, w()
{
    const Vector3 normalizedAxis =
        axis.IsZeroStrict() ? Vector3() : axis.Unit();
    const Radian halfAngle = angle.Rad() * 0.5f;
    const f32 cosHalfAngle = Math::CosF32(halfAngle);
    const f32 sinHalfAngle = Math::SinF32(halfAngle);
    x = normalizedAxis.x * sinHalfAngle;
    y = normalizedAxis.y * sinHalfAngle;
    z = normalizedAxis.z * sinHalfAngle;
    w = cosHalfAngle;
}

//------------------------------------------------------------------------------
const Quaternion Quaternion::Mul(const Quaternion& rhs) const
{
    Quaternion quat(*this);
    quat.MulAssign(rhs);
    return quat;
}

//------------------------------------------------------------------------------
Quaternion& Quaternion::MulAssign(const Quaternion& rhs)
{
    const Quaternion& lhs = *this;
    *this = Quaternion(
        lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x,
        lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w,
        lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z);
    return *this;
}

//------------------------------------------------------------------------------
const Matrix34Pod Quaternion::ToRotateMatrix() const
{
    const f32 lenSrc = Math::SqrtF32(w * w + x * x + y * y + z * z);
    if (lenSrc == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return Matrix34::Identity();
    }

    const f32 len = 2.0f / (lenSrc * lenSrc);
    const f32 x2 = x * x * len;
    const f32 y2 = y * y * len;
    const f32 z2 = z * z * len;
    const f32 xy = x * y * len;
    const f32 yz = y * z * len;
    const f32 zx = z * x * len;
    const f32 xw = x * w * len;
    const f32 yw = y * w * len;
    const f32 zw = z * w * len;

    Matrix34 mtx;
    mtx.v[Matrix34::Index00] = 1.0f - y2 - z2;
    mtx.v[Matrix34::Index10] = xy + zw;
    mtx.v[Matrix34::Index20] = zx - yw;
    mtx.v[Matrix34::Index01] = xy - zw;
    mtx.v[Matrix34::Index11] = 1.0f - z2 - x2;
    mtx.v[Matrix34::Index21] = yz + xw;
    mtx.v[Matrix34::Index02] = zx + yw;
    mtx.v[Matrix34::Index12] = yz - xw;
    mtx.v[Matrix34::Index22] = 1.0f - x2 - y2;
    return mtx;
}

//------------------------------------------------------------------------------
const Quaternion Quaternion::operator*(const Quaternion& rhs) const
{
    return Mul(rhs);
}

//------------------------------------------------------------------------------
Quaternion& Quaternion::operator*=(const Quaternion& rhs)
{
    MulAssign(rhs);
    return *this;
}

//------------------------------------------------------------------------------
const ::ae::base::ShortString Quaternion::ToShortString() const
{
    return ::ae::base::ShortString::FromFormat(
        "%s,%s,%s,%s",
        F32(x).ToShortString().ReadPtr(),
        F32(y).ToShortString().ReadPtr(),
        F32(z).ToShortString().ReadPtr(),
        F32(w).ToShortString().ReadPtr());
}

} // namespace ae::base
// EOF
