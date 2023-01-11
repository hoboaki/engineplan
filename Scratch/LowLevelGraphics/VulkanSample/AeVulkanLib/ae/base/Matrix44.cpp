// 文字コード：UTF-8
#include <ae/base/Matrix44.hpp>

// includes
#include <ae/base/Angle.hpp>
#include <ae/base/Console.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/Matrix34.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/Vector3.hpp>
#include <ae/base/Vector4.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Identity()
{
    // よく使うことになるのでstaticデータとして使い初期化は１回だけにする。
    static Matrix44Pod obj = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    return obj;
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Translate(
    const f32 x,
    const f32 y,
    const f32 z)
{
    return Matrix44(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1);
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Translate(const Vector3Pod& vec)
{
    return Translate(vec.x, vec.y, vec.z);
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Scale(const f32 x, const f32 y, const f32 z)
{
    return Matrix44(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1);
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Scale(const Vector3Pod& vec)
{
    return Scale(vec.x, vec.y, vec.z);
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Rotate(
    const Angle& angle,
    const f32 axisX,
    const f32 axisY,
    const f32 axisZ)
{
    const f32 c = Math::CosF32(angle);
    const f32 s = Math::SinF32(angle);
    const f32 inv_c = 1.0f - c;
    const f32 x = axisX;
    const f32 y = axisY;
    const f32 z = axisZ;
    const f32 xy = x * y;
    const f32 xz = x * z;
    const f32 yz = y * z;
    const f32 xs = x * s;
    const f32 ys = y * s;
    const f32 zs = z * s;

    return Matrix44(
        x * x * inv_c + c,
        xy * inv_c - zs,
        xz * inv_c + ys,
        0,
        xy * inv_c + zs,
        y * y * inv_c + c,
        yz * inv_c - xs,
        0,
        xz * inv_c - ys,
        yz * inv_c + xs,
        z * z * inv_c + c,
        0,
        0,
        0,
        0,
        1);
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Rotate(
    const Angle& angle,
    const Vector3Pod& axisVec)
{
    return Rotate(angle, axisVec.x, axisVec.y, axisVec.z);
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Ortho(
    const f32 left,
    const f32 top,
    const f32 right,
    const f32 bottom,
    const f32 near,
    const f32 far)
{
    AE_BASE_ASSERT_NOT_EQUALS(left, right);
    AE_BASE_ASSERT_NOT_EQUALS(top, bottom);
    AE_BASE_ASSERT_NOT_EQUALS(near, far);

    const f32 r_sub_l = right - left;
    const f32 r_add_l = right + left;
    const f32 t_sub_b = top - bottom;
    const f32 t_add_b = top + bottom;
    const f32 f_sub_n = far - near;
    return Matrix44(
        2 / r_sub_l,
        0,
        0,
        r_add_l / r_sub_l,
        0,
        2 / t_sub_b,
        0,
        t_add_b / t_sub_b,
        0,
        0,
        -1 / f_sub_n,
        -near / f_sub_n,
        0,
        0,
        0,
        1);
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Frustum(
    const f32 left,
    const f32 right,
    const f32 bottom,
    const f32 top,
    const f32 near,
    const f32 far)
{
    AE_BASE_ASSERT_NOT_EQUALS(left, right);
    AE_BASE_ASSERT_NOT_EQUALS(bottom, top);
    AE_BASE_ASSERT_NOT_EQUALS(near, far);

    const f32 l = left;
    const f32 r = right;
    const f32 b = bottom;
    const f32 t = top;
    const f32 n = near;
    const f32 f = far;
    const f32 n2 = 2 * near;
    return Matrix44(
        n2 / (r - l),
        0,
        0,
        (r + l) / (r - l),
        0,
        n2 / (t - b),
        0,
        (-t + b) / (t - b),
        0,
        0,
        -2 / (f - n),
        (f + n) / f - n,
        0,
        0,
        0,
        1);
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Perspective(
    const Angle& fOVY,
    const f32 aspect,
    const f32 near,
    const f32 far)
{
    AE_BASE_ASSERT_LESS(0, fOVY.Rad());
    AE_BASE_ASSERT_LESS(0, aspect);
    AE_BASE_ASSERT_NOT_EQUALS(near, far);

    const f32 c = Math::CotF32(fOVY);
    return Matrix44(
        c / aspect,
        0,
        0,
        0,
        0,
        c,
        0,
        0,
        0,
        0,
        far / (near - far),
        -(near * far) / (far - near),
        0,
        0,
        -1,
        0);
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::LookAt(
    const Vector3Pod& eyePos,
    const Vector3Pod& targetPos,
    const Vector3Pod& upVec)
{
    return Matrix34::LookAt(eyePos, targetPos, upVec).ToMatrix44();
}

//------------------------------------------------------------------------------
const Vector4Pod Matrix44Pod::x() const
{
    return Vector4(v[IndexXX], v[IndexXY], v[IndexXZ], v[IndexXW]);
}

//------------------------------------------------------------------------------
const Vector4Pod Matrix44Pod::y() const
{
    return Vector4(v[IndexYX], v[IndexYY], v[IndexYZ], v[IndexYW]);
}

//------------------------------------------------------------------------------
const Vector4Pod Matrix44Pod::z() const
{
    return Vector4(v[IndexZX], v[IndexZY], v[IndexZZ], v[IndexZW]);
}

//------------------------------------------------------------------------------
const Vector4Pod Matrix44Pod::w() const
{
    return Vector4(v[IndexWX], v[IndexWY], v[IndexWZ], v[IndexWW]);
}

//------------------------------------------------------------------------------
void Matrix44Pod::SetX(const Vector4Pod& val)
{
    v[IndexXX] = val.x;
    v[IndexXY] = val.y;
    v[IndexXZ] = val.z;
    v[IndexXW] = val.w;
}

//------------------------------------------------------------------------------
void Matrix44Pod::SetY(const Vector4Pod& val)
{
    v[IndexYX] = val.x;
    v[IndexYY] = val.y;
    v[IndexYZ] = val.z;
    v[IndexYW] = val.w;
}

//------------------------------------------------------------------------------
void Matrix44Pod::SetZ(const Vector4Pod& val)
{
    v[IndexZX] = val.x;
    v[IndexZY] = val.y;
    v[IndexZZ] = val.z;
    v[IndexZW] = val.w;
}

//------------------------------------------------------------------------------
void Matrix44Pod::SetW(const Vector4Pod& val)
{
    v[IndexWX] = val.x;
    v[IndexWY] = val.y;
    v[IndexWZ] = val.z;
    v[IndexWW] = val.w;
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Mul(const Matrix44Pod& rHS) const
{
    Matrix44Pod mtx;

    // c0
    mtx.v[Index00] =
        this->v[Index00] * rHS.v[Index00] + this->v[Index01] * rHS.v[Index10] +
        this->v[Index02] * rHS.v[Index20] + this->v[Index03] * rHS.v[Index30];
    mtx.v[Index01] =
        this->v[Index00] * rHS.v[Index01] + this->v[Index01] * rHS.v[Index11] +
        this->v[Index02] * rHS.v[Index21] + this->v[Index03] * rHS.v[Index31];
    mtx.v[Index02] =
        this->v[Index00] * rHS.v[Index02] + this->v[Index01] * rHS.v[Index12] +
        this->v[Index02] * rHS.v[Index22] + this->v[Index03] * rHS.v[Index32];
    mtx.v[Index03] =
        this->v[Index00] * rHS.v[Index03] + this->v[Index01] * rHS.v[Index13] +
        this->v[Index02] * rHS.v[Index23] + this->v[Index03] * rHS.v[Index33];

    // c1
    mtx.v[Index10] =
        this->v[Index10] * rHS.v[Index00] + this->v[Index11] * rHS.v[Index10] +
        this->v[Index12] * rHS.v[Index20] + this->v[Index13] * rHS.v[Index30];
    mtx.v[Index11] =
        this->v[Index10] * rHS.v[Index01] + this->v[Index11] * rHS.v[Index11] +
        this->v[Index12] * rHS.v[Index21] + this->v[Index13] * rHS.v[Index31];
    mtx.v[Index12] =
        this->v[Index10] * rHS.v[Index02] + this->v[Index11] * rHS.v[Index12] +
        this->v[Index12] * rHS.v[Index22] + this->v[Index13] * rHS.v[Index32];
    mtx.v[Index13] =
        this->v[Index10] * rHS.v[Index03] + this->v[Index11] * rHS.v[Index13] +
        this->v[Index12] * rHS.v[Index23] + this->v[Index13] * rHS.v[Index33];

    // c2
    mtx.v[Index20] =
        this->v[Index20] * rHS.v[Index00] + this->v[Index21] * rHS.v[Index10] +
        this->v[Index22] * rHS.v[Index20] + this->v[Index23] * rHS.v[Index30];
    mtx.v[Index21] =
        this->v[Index20] * rHS.v[Index01] + this->v[Index21] * rHS.v[Index11] +
        this->v[Index22] * rHS.v[Index21] + this->v[Index23] * rHS.v[Index31];
    mtx.v[Index22] =
        this->v[Index20] * rHS.v[Index02] + this->v[Index21] * rHS.v[Index12] +
        this->v[Index22] * rHS.v[Index22] + this->v[Index23] * rHS.v[Index32];
    mtx.v[Index23] =
        this->v[Index20] * rHS.v[Index03] + this->v[Index21] * rHS.v[Index13] +
        this->v[Index22] * rHS.v[Index23] + this->v[Index23] * rHS.v[Index33];

    // c3
    mtx.v[Index30] =
        this->v[Index30] * rHS.v[Index00] + this->v[Index31] * rHS.v[Index10] +
        this->v[Index32] * rHS.v[Index20] + this->v[Index33] * rHS.v[Index30];
    mtx.v[Index31] =
        this->v[Index30] * rHS.v[Index01] + this->v[Index31] * rHS.v[Index11] +
        this->v[Index32] * rHS.v[Index21] + this->v[Index33] * rHS.v[Index31];
    mtx.v[Index32] =
        this->v[Index30] * rHS.v[Index02] + this->v[Index31] * rHS.v[Index12] +
        this->v[Index32] * rHS.v[Index22] + this->v[Index33] * rHS.v[Index32];
    mtx.v[Index33] =
        this->v[Index30] * rHS.v[Index03] + this->v[Index31] * rHS.v[Index13] +
        this->v[Index32] * rHS.v[Index23] + this->v[Index33] * rHS.v[Index33];

    return mtx;
}

//------------------------------------------------------------------------------
Matrix44Pod& Matrix44Pod::MulAssign(const Matrix44Pod& rHS)
{
    *this = Mul(rHS);
    return *this;
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::operator*(const Matrix44Pod& rHS) const
{
    return Mul(rHS);
}

//------------------------------------------------------------------------------
Matrix44Pod& Matrix44Pod::operator*=(const Matrix44Pod& rHS)
{
    MulAssign(rHS);
    return *this;
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Invert() const
{
    const float c = 0.0f + v[Index00] * v[Index11] * v[Index22] * v[Index33] +
                    v[Index00] * v[Index12] * v[Index23] * v[Index31] +
                    v[Index00] * v[Index13] * v[Index21] * v[Index32] +
                    v[Index01] * v[Index10] * v[Index23] * v[Index32] +
                    v[Index01] * v[Index12] * v[Index20] * v[Index33] +
                    v[Index01] * v[Index13] * v[Index22] * v[Index30] +
                    v[Index02] * v[Index10] * v[Index21] * v[Index33] +
                    v[Index02] * v[Index11] * v[Index23] * v[Index30] +
                    v[Index02] * v[Index13] * v[Index20] * v[Index31] +
                    v[Index03] * v[Index10] * v[Index22] * v[Index31] +
                    v[Index03] * v[Index11] * v[Index20] * v[Index32] +
                    v[Index03] * v[Index12] * v[Index21] * v[Index30] -
                    v[Index00] * v[Index11] * v[Index23] * v[Index32] -
                    v[Index00] * v[Index12] * v[Index21] * v[Index33] -
                    v[Index00] * v[Index13] * v[Index22] * v[Index31] -
                    v[Index01] * v[Index10] * v[Index22] * v[Index33] -
                    v[Index01] * v[Index12] * v[Index23] * v[Index30] -
                    v[Index01] * v[Index13] * v[Index20] * v[Index32] -
                    v[Index02] * v[Index10] * v[Index23] * v[Index31] -
                    v[Index02] * v[Index11] * v[Index20] * v[Index33] -
                    v[Index02] * v[Index13] * v[Index21] * v[Index30] -
                    v[Index03] * v[Index10] * v[Index21] * v[Index32] -
                    v[Index03] * v[Index11] * v[Index22] * v[Index30] -
                    v[Index03] * v[Index12] * v[Index20] * v[Index31];

    if (c == 0.0f) {
        AE_BASE_ASSERT_NOT_REACHED();
        return Identity();
    }

    Matrix44Pod b;
    b.v[Index00] = v[Index11] * v[Index22] * v[Index33] +
                   v[Index12] * v[Index23] * v[Index31] +
                   v[Index13] * v[Index21] * v[Index32] -
                   v[Index11] * v[Index23] * v[Index32] -
                   v[Index12] * v[Index21] * v[Index33] -
                   v[Index13] * v[Index22] * v[Index31];
    b.v[Index01] = v[Index01] * v[Index23] * v[Index32] +
                   v[Index02] * v[Index21] * v[Index33] +
                   v[Index03] * v[Index22] * v[Index31] -
                   v[Index01] * v[Index22] * v[Index33] -
                   v[Index02] * v[Index23] * v[Index31] -
                   v[Index03] * v[Index21] * v[Index32];
    b.v[Index02] = v[Index01] * v[Index12] * v[Index33] +
                   v[Index02] * v[Index13] * v[Index31] +
                   v[Index03] * v[Index11] * v[Index32] -
                   v[Index01] * v[Index13] * v[Index32] -
                   v[Index02] * v[Index11] * v[Index33] -
                   v[Index03] * v[Index12] * v[Index31];
    b.v[Index03] = v[Index01] * v[Index13] * v[Index22] +
                   v[Index02] * v[Index11] * v[Index23] +
                   v[Index03] * v[Index12] * v[Index21] -
                   v[Index01] * v[Index12] * v[Index23] -
                   v[Index02] * v[Index13] * v[Index21] -
                   v[Index03] * v[Index11] * v[Index22];
    b.v[Index10] = v[Index10] * v[Index23] * v[Index32] +
                   v[Index12] * v[Index20] * v[Index33] +
                   v[Index13] * v[Index22] * v[Index30] -
                   v[Index10] * v[Index22] * v[Index33] -
                   v[Index12] * v[Index23] * v[Index30] -
                   v[Index13] * v[Index20] * v[Index32];
    b.v[Index11] = v[Index00] * v[Index22] * v[Index33] +
                   v[Index02] * v[Index23] * v[Index30] +
                   v[Index03] * v[Index20] * v[Index32] -
                   v[Index00] * v[Index23] * v[Index32] -
                   v[Index02] * v[Index20] * v[Index33] -
                   v[Index03] * v[Index22] * v[Index30];
    b.v[Index12] = v[Index00] * v[Index13] * v[Index32] +
                   v[Index02] * v[Index10] * v[Index33] +
                   v[Index03] * v[Index12] * v[Index30] -
                   v[Index00] * v[Index12] * v[Index33] -
                   v[Index02] * v[Index13] * v[Index30] -
                   v[Index03] * v[Index10] * v[Index32];
    b.v[Index13] = v[Index00] * v[Index12] * v[Index23] +
                   v[Index02] * v[Index13] * v[Index20] +
                   v[Index03] * v[Index10] * v[Index22] -
                   v[Index00] * v[Index13] * v[Index22] -
                   v[Index02] * v[Index10] * v[Index23] -
                   v[Index03] * v[Index12] * v[Index20];
    b.v[Index20] = v[Index10] * v[Index21] * v[Index33] +
                   v[Index11] * v[Index23] * v[Index30] +
                   v[Index13] * v[Index20] * v[Index31] -
                   v[Index10] * v[Index23] * v[Index31] -
                   v[Index11] * v[Index20] * v[Index33] -
                   v[Index13] * v[Index21] * v[Index30];
    b.v[Index21] = v[Index00] * v[Index23] * v[Index31] +
                   v[Index01] * v[Index20] * v[Index33] +
                   v[Index03] * v[Index21] * v[Index30] -
                   v[Index00] * v[Index21] * v[Index33] -
                   v[Index01] * v[Index23] * v[Index30] -
                   v[Index03] * v[Index20] * v[Index31];
    b.v[Index22] = v[Index00] * v[Index11] * v[Index33] +
                   v[Index01] * v[Index13] * v[Index30] +
                   v[Index03] * v[Index10] * v[Index31] -
                   v[Index00] * v[Index13] * v[Index31] -
                   v[Index01] * v[Index10] * v[Index33] -
                   v[Index03] * v[Index11] * v[Index30];
    b.v[Index23] = v[Index00] * v[Index13] * v[Index21] +
                   v[Index01] * v[Index10] * v[Index23] +
                   v[Index03] * v[Index11] * v[Index20] -
                   v[Index00] * v[Index11] * v[Index23] -
                   v[Index01] * v[Index13] * v[Index20] -
                   v[Index03] * v[Index10] * v[Index21];
    b.v[Index30] = v[Index10] * v[Index22] * v[Index31] +
                   v[Index11] * v[Index20] * v[Index32] +
                   v[Index12] * v[Index31] * v[Index30] -
                   v[Index10] * v[Index21] * v[Index32] -
                   v[Index11] * v[Index22] * v[Index30] -
                   v[Index12] * v[Index20] * v[Index31];
    b.v[Index31] = v[Index00] * v[Index21] * v[Index32] +
                   v[Index01] * v[Index22] * v[Index30] +
                   v[Index02] * v[Index20] * v[Index31] -
                   v[Index00] * v[Index22] * v[Index31] -
                   v[Index01] * v[Index20] * v[Index32] -
                   v[Index02] * v[Index21] * v[Index30];
    b.v[Index32] = v[Index00] * v[Index12] * v[Index31] +
                   v[Index01] * v[Index10] * v[Index32] +
                   v[Index02] * v[Index11] * v[Index30] -
                   v[Index00] * v[Index11] * v[Index32] -
                   v[Index01] * v[Index12] * v[Index30] -
                   v[Index02] * v[Index10] * v[Index31];
    b.v[Index33] = v[Index00] * v[Index11] * v[Index22] +
                   v[Index01] * v[Index12] * v[Index20] +
                   v[Index02] * v[Index10] * v[Index21] -
                   v[Index00] * v[Index12] * v[Index21] -
                   v[Index01] * v[Index10] * v[Index22] -
                   v[Index02] * v[Index11] * v[Index20];

    b.v[Index00] /= c;
    b.v[Index01] /= c;
    b.v[Index02] /= c;
    b.v[Index03] /= c;
    b.v[Index10] /= c;
    b.v[Index11] /= c;
    b.v[Index12] /= c;
    b.v[Index13] /= c;
    b.v[Index20] /= c;
    b.v[Index21] /= c;
    b.v[Index22] /= c;
    b.v[Index23] /= c;
    b.v[Index30] /= c;
    b.v[Index31] /= c;
    b.v[Index32] /= c;
    b.v[Index33] /= c;

    return b;
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Transpose() const
{
    return Matrix44(
        v[Index00],
        v[Index10],
        v[Index20],
        v[Index30],
        v[Index01],
        v[Index11],
        v[Index21],
        v[Index31],
        v[Index02],
        v[Index12],
        v[Index22],
        v[Index32],
        v[Index03],
        v[Index13],
        v[Index23],
        v[Index33]);
}

//------------------------------------------------------------------------------
void Matrix44Pod::Dump() const
{
    AE_BASE_COUTFMT("Matrix44Pod::dump %p\n", this);
    AE_BASE_COUTFMT(
        "( %f , %f , %f , %f )\n",
        v[Index00],
        v[Index01],
        v[Index02],
        v[Index03]);
    AE_BASE_COUTFMT(
        "( %f , %f , %f , %f )\n",
        v[Index10],
        v[Index11],
        v[Index12],
        v[Index13]);
    AE_BASE_COUTFMT(
        "( %f , %f , %f , %f )\n",
        v[Index20],
        v[Index21],
        v[Index22],
        v[Index23]);
    AE_BASE_COUTFMT(
        "( %f , %f , %f , %f )\n",
        v[Index30],
        v[Index31],
        v[Index32],
        v[Index33]);
}

//------------------------------------------------------------------------------
Matrix44::Matrix44()
: Matrix44Pod(Identity())
{
}

//------------------------------------------------------------------------------
Matrix44::Matrix44(const Matrix44Pod& obj)
: Matrix44Pod(obj)
{
}

//------------------------------------------------------------------------------
Matrix44::Matrix44(
    const f32 r0C0,
    const f32 r0C1,
    const f32 r0C2,
    const f32 r0C3,
    const f32 r1C0,
    const f32 r1C1,
    const f32 r1C2,
    const f32 r1C3,
    const f32 r2C0,
    const f32 r2C1,
    const f32 r2C2,
    const f32 r2C3,
    const f32 r3C0,
    const f32 r3C1,
    const f32 r3C2,
    const f32 r3C3)
{
    v[Index00] = r0C0;
    v[Index10] = r1C0;
    v[Index20] = r2C0;
    v[Index30] = r3C0;
    v[Index01] = r0C1;
    v[Index11] = r1C1;
    v[Index21] = r2C1;
    v[Index31] = r3C1;
    v[Index02] = r0C2;
    v[Index12] = r1C2;
    v[Index22] = r2C2;
    v[Index32] = r3C2;
    v[Index03] = r0C3;
    v[Index13] = r1C3;
    v[Index23] = r2C3;
    v[Index33] = r3C3;
}

//------------------------------------------------------------------------------
Matrix44::Matrix44(
    const Vector4Pod& x,
    const Vector4Pod& y,
    const Vector4Pod& z,
    const Vector4Pod& w)
{
    SetX(x);
    SetY(y);
    SetZ(z);
    SetW(w);
}

} // namespace ae::base
// EOF
