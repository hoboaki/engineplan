// 文字コード：UTF-8
#include <ae/base/Matrix34.hpp>

// includes
#include <ae/base/Angle.hpp>
#include <ae/base/Console.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/Matrix44.hpp>
#include <ae/base/Quaternion.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/Vector3.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Identity()
{
    // よく使うことになるのでstaticデータとして使い初期化は１回だけにする。
    static Matrix34Pod obj = { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 };
    return obj;
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Translate(
    const f32 x,
    const f32 y,
    const f32 z)
{
    return Matrix34(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z);
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Translate(const Vector3Pod& vec)
{
    return Translate(vec.x, vec.y, vec.z);
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Scale(const f32 x, const f32 y, const f32 z)
{
    return Matrix34(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0);
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Scale(const Vector3Pod& vec)
{
    return Scale(vec.x, vec.y, vec.z);
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Rotate(
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

    return Matrix34(
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
        0);
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Rotate(
    const Angle& angle,
    const Vector3Pod& axisVec)
{
    return Rotate(angle, axisVec.x, axisVec.y, axisVec.z);
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::LookAt(
    const Vector3Pod& eyePos,
    const Vector3Pod& targetPos,
    const Vector3Pod& upVec)
{
    // toTargetUnit
    Vector3 toTarget = targetPos - eyePos;
    if (toTarget.IsZeroStrict()) {
        AE_BASE_ASSERT_NOT_REACHED();
        toTarget = Vector3Pod::UnitZ(); // fail safe code
    }
    const Vector3 toTargetUnit = toTarget.Unit();

    // upVecUnit
    Vector3Pod upVecUnit;
    if (upVec.IsZeroStrict()) {
        AE_BASE_ERROR_INVALID_VALUE(upVec);
        upVecUnit = Vector3::UnitY(); // fail safe code
    } else {
        upVecUnit = upVec.Unit();
    }

    // toTarget以外の軸を再作成
    const Vector3Pod s = toTargetUnit.Cross(upVecUnit).Unit();
    const Vector3Pod u = s.Cross(toTargetUnit).Unit();
    const Vector3Pod v = -toTargetUnit;

    // 平行移動
    const Vector3Pod invEyePos = -eyePos;
    const Vector3Pod t =
        Vector3(invEyePos.Dot(s), invEyePos.Dot(u), invEyePos.Dot(v));

    // 結果を返す
    Matrix34 mtx(
        Vector3(s.x, u.x, v.x),
        Vector3(s.y, u.y, v.y),
        Vector3(s.z, u.z, v.z),
        t);
    return mtx;
}

//------------------------------------------------------------------------------
const Vector3Pod Matrix34Pod::x() const
{
    return Vector3(v[IndexXX], v[IndexXY], v[IndexXZ]);
}

//------------------------------------------------------------------------------
const Vector3Pod Matrix34Pod::y() const
{
    return Vector3(v[IndexYX], v[IndexYY], v[IndexYZ]);
}

//------------------------------------------------------------------------------
const Vector3Pod Matrix34Pod::z() const
{
    return Vector3(v[IndexZX], v[IndexZY], v[IndexZZ]);
}

//------------------------------------------------------------------------------
const Vector3Pod Matrix34Pod::w() const
{
    return Vector3(v[IndexWX], v[IndexWY], v[IndexWZ]);
}

//------------------------------------------------------------------------------
void Matrix34Pod::SetX(const Vector3Pod& val)
{
    v[IndexXX] = val.x;
    v[IndexXY] = val.y;
    v[IndexXZ] = val.z;
}

//------------------------------------------------------------------------------
void Matrix34Pod::SetY(const Vector3Pod& val)
{
    v[IndexYX] = val.x;
    v[IndexYY] = val.y;
    v[IndexYZ] = val.z;
}

//------------------------------------------------------------------------------
void Matrix34Pod::SetZ(const Vector3Pod& val)
{
    v[IndexZX] = val.x;
    v[IndexZY] = val.y;
    v[IndexZZ] = val.z;
}

//------------------------------------------------------------------------------
void Matrix34Pod::SetW(const Vector3Pod& val)
{
    v[IndexWX] = val.x;
    v[IndexWY] = val.y;
    v[IndexWZ] = val.z;
}

//------------------------------------------------------------------------------
const Vector3Pod Matrix34Pod::Mul(const Vector3Pod& vec) const
{
    return Vector3(
        vec.x * v[IndexXX] + vec.y * v[IndexYX] + vec.z * v[IndexZX] +
            v[IndexWX],
        vec.x * v[IndexXY] + vec.y * v[IndexYY] + vec.z * v[IndexZY] +
            v[IndexWY],
        vec.x * v[IndexXZ] + vec.y * v[IndexYZ] + vec.z * v[IndexZZ] +
            v[IndexWZ]);
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Mul(const Matrix34Pod& rHS) const
{
    Matrix34Pod mtx;

    // c0
    mtx.v[Index00] = this->v[Index00] * rHS.v[Index00] +
                     this->v[Index01] * rHS.v[Index10] +
                     this->v[Index02] * rHS.v[Index20];
    mtx.v[Index01] = this->v[Index00] * rHS.v[Index01] +
                     this->v[Index01] * rHS.v[Index11] +
                     this->v[Index02] * rHS.v[Index21];
    mtx.v[Index02] = this->v[Index00] * rHS.v[Index02] +
                     this->v[Index01] * rHS.v[Index12] +
                     this->v[Index02] * rHS.v[Index22];
    mtx.v[Index03] = this->v[Index00] * rHS.v[Index03] +
                     this->v[Index01] * rHS.v[Index13] +
                     this->v[Index02] * rHS.v[Index23] + this->v[Index03];

    // c1
    mtx.v[Index10] = this->v[Index10] * rHS.v[Index00] +
                     this->v[Index11] * rHS.v[Index10] +
                     this->v[Index12] * rHS.v[Index20];
    mtx.v[Index11] = this->v[Index10] * rHS.v[Index01] +
                     this->v[Index11] * rHS.v[Index11] +
                     this->v[Index12] * rHS.v[Index21];
    mtx.v[Index12] = this->v[Index10] * rHS.v[Index02] +
                     this->v[Index11] * rHS.v[Index12] +
                     this->v[Index12] * rHS.v[Index22];
    mtx.v[Index13] = this->v[Index10] * rHS.v[Index03] +
                     this->v[Index11] * rHS.v[Index13] +
                     this->v[Index12] * rHS.v[Index23] + this->v[Index13];

    // c2
    mtx.v[Index20] = this->v[Index20] * rHS.v[Index00] +
                     this->v[Index21] * rHS.v[Index10] +
                     this->v[Index22] * rHS.v[Index20];
    mtx.v[Index21] = this->v[Index20] * rHS.v[Index01] +
                     this->v[Index21] * rHS.v[Index11] +
                     this->v[Index22] * rHS.v[Index21];
    mtx.v[Index22] = this->v[Index20] * rHS.v[Index02] +
                     this->v[Index21] * rHS.v[Index12] +
                     this->v[Index22] * rHS.v[Index22];
    mtx.v[Index23] = this->v[Index20] * rHS.v[Index03] +
                     this->v[Index21] * rHS.v[Index13] +
                     this->v[Index22] * rHS.v[Index23] + this->v[Index23];

    return mtx;
}

//------------------------------------------------------------------------------
Matrix34Pod& Matrix34Pod::MulAssign(const Matrix34Pod& rHS)
{
    *this = Mul(rHS);
    return *this;
}

//------------------------------------------------------------------------------
const Vector3Pod Matrix34Pod::operator*(const Vector3Pod& rHS) const
{
    return Mul(rHS);
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::operator*(const Matrix34Pod& rHS) const
{
    return Mul(rHS);
}

//------------------------------------------------------------------------------
Matrix34Pod& Matrix34Pod::operator*=(const Matrix34Pod& rHS)
{
    MulAssign(rHS);
    return *this;
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Invert() const
{
    const float c = 0.0f + v[Index00] * v[Index11] * v[Index22] +
                    v[Index01] * v[Index12] * v[Index20] +
                    v[Index02] * v[Index10] * v[Index21] -
                    v[Index00] * v[Index12] * v[Index21] -
                    v[Index01] * v[Index10] * v[Index22] -
                    v[Index02] * v[Index11] * v[Index20];

    if (c == 0.0f) {
        AE_BASE_ASSERT_NOT_REACHED();
        return Identity();
    }

    Matrix34Pod b;
    b.v[Index00] = v[Index11] * v[Index22] + v[Index12] * v[Index23] * 0 +
                   v[Index13] * v[Index21] * 0 - v[Index11] * v[Index23] * 0 -
                   v[Index12] * v[Index21] - v[Index13] * v[Index22] * 0;
    b.v[Index01] = v[Index01] * v[Index23] * 0 + v[Index02] * v[Index21] +
                   v[Index03] * v[Index22] * 0 - v[Index01] * v[Index22] -
                   v[Index02] * v[Index23] * 0 - v[Index03] * v[Index21] * 0;
    b.v[Index02] = v[Index01] * v[Index12] + v[Index02] * v[Index13] * 0 +
                   v[Index03] * v[Index11] * 0 - v[Index01] * v[Index13] * 0 -
                   v[Index02] * v[Index11] - v[Index03] * v[Index12] * 0;
    b.v[Index03] = v[Index01] * v[Index13] * v[Index22] +
                   v[Index02] * v[Index11] * v[Index23] +
                   v[Index03] * v[Index12] * v[Index21] -
                   v[Index01] * v[Index12] * v[Index23] -
                   v[Index02] * v[Index13] * v[Index21] -
                   v[Index03] * v[Index11] * v[Index22];
    b.v[Index10] = v[Index10] * v[Index23] * 0 + v[Index12] * v[Index20] +
                   v[Index13] * v[Index22] * 0 - v[Index10] * v[Index22] -
                   v[Index12] * v[Index23] * 0 - v[Index13] * v[Index20] * 0;
    b.v[Index11] = v[Index00] * v[Index22] + v[Index02] * v[Index23] * 0 +
                   v[Index03] * v[Index20] * 0 - v[Index00] * v[Index23] * 0 -
                   v[Index02] * v[Index20] - v[Index03] * v[Index22] * 0;
    b.v[Index12] = v[Index00] * v[Index13] * 0 + v[Index02] * v[Index10] +
                   v[Index03] * v[Index12] * 0 - v[Index00] * v[Index12] -
                   v[Index02] * v[Index13] * 0 - v[Index03] * v[Index10] * 0;
    b.v[Index13] = v[Index00] * v[Index12] * v[Index23] +
                   v[Index02] * v[Index13] * v[Index20] +
                   v[Index03] * v[Index10] * v[Index22] -
                   v[Index00] * v[Index13] * v[Index22] -
                   v[Index02] * v[Index10] * v[Index23] -
                   v[Index03] * v[Index12] * v[Index20];
    b.v[Index20] = v[Index10] * v[Index21] + v[Index11] * v[Index23] * 0 +
                   v[Index13] * v[Index20] * 0 - v[Index10] * v[Index23] * 0 -
                   v[Index11] * v[Index20] - v[Index13] * v[Index21] * 0;
    b.v[Index21] = v[Index00] * v[Index23] * 0 + v[Index01] * v[Index20] +
                   v[Index03] * v[Index21] * 0 - v[Index00] * v[Index21] -
                   v[Index01] * v[Index23] * 0 - v[Index03] * v[Index20] * 0;
    b.v[Index22] = v[Index00] * v[Index11] + v[Index01] * v[Index13] * 0 +
                   v[Index03] * v[Index10] * 0 - v[Index00] * v[Index13] * 0 -
                   v[Index01] * v[Index10] - v[Index03] * v[Index11] * 0;
    b.v[Index23] = v[Index00] * v[Index13] * v[Index21] +
                   v[Index01] * v[Index10] * v[Index23] +
                   v[Index03] * v[Index11] * v[Index20] -
                   v[Index00] * v[Index11] * v[Index23] -
                   v[Index01] * v[Index13] * v[Index20] -
                   v[Index03] * v[Index10] * v[Index21];

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

    return b;
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Transpose() const
{
    Matrix34Pod b;

    b.v[Index00] = v[Index00];
    b.v[Index01] = v[Index10];
    b.v[Index02] = v[Index20];
    b.v[Index03] = 0.0f;

    b.v[Index10] = v[Index01];
    b.v[Index11] = v[Index11];
    b.v[Index12] = v[Index21];
    b.v[Index13] = 0.0f;

    b.v[Index20] = v[Index02];
    b.v[Index21] = v[Index12];
    b.v[Index22] = v[Index22];
    b.v[Index23] = 0.0f;

    return b;
}

//------------------------------------------------------------------------------
const Quaternion Matrix34Pod::ToQuaternion() const
{
    Quaternion q;

    {
        const float tr = v[Index00] + v[Index11] + v[Index22] + 1.0f;
        if (1.0f <= tr) {
            float s = 0.5f / Math::SqrtF32(tr);
            q.w = 0.25f / s;
            q.x = (v[Index21] - v[Index12]) * s;
            q.y = (v[Index02] - v[Index20]) * s;
            q.z = (v[Index10] - v[Index01]) * s;
            return q;
        }
    }

    const float maxVal = v[Index22] < v[Index11] ? v[Index11] : v[Index22];
    if (maxVal < v[Index00]) {
        float s = Math::SqrtF32(v[Index00] - (v[Index11] + v[Index22]) + 1.0f);
        const float x = s * 0.5f;
        s = 0.5f / s;
        q.x = x;
        q.y = (v[Index10] + v[Index01]) * s;
        q.z = (v[Index02] + v[Index20]) * s;
        q.w = (v[Index21] - v[Index12]) * s;
        return q;
    } else if (maxVal == v[Index11]) {
        float s = Math::SqrtF32(v[Index11] - (v[Index22] + v[Index00]) + 1.0f);
        const float y = s * 0.5f;
        s = 0.5f / s;
        q.x = (v[Index10] + v[Index01]) * s;
        q.y = y;
        q.z = (v[Index21] + v[Index12]) * s;
        q.w = (v[Index02] - v[Index20]) * s;
        return q;
    } else {
        float s = Math::SqrtF32(v[Index22] - (v[Index00] + v[Index11]) + 1.0f);
        const float z = s * 0.5f;
        s = 0.5f / s;
        q.x = (v[Index02] + v[Index20]) * s;
        q.y = (v[Index21] + v[Index12]) * s;
        q.z = z;
        q.w = (v[Index10] - v[Index01]) * s;
        return q;
    }
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix34Pod::ToMatrix44() const
{
    return Matrix44(
        v[Index00],
        v[Index01],
        v[Index02],
        v[Index03],
        v[Index10],
        v[Index11],
        v[Index12],
        v[Index13],
        v[Index20],
        v[Index21],
        v[Index22],
        v[Index23],
        0,
        0,
        0,
        1);
}

//------------------------------------------------------------------------------
void Matrix34Pod::Dump() const
{
    AE_BASE_COUTFMT("Matrix34Pod::dump %p\n", this);
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
}

//------------------------------------------------------------------------------
Matrix34::Matrix34()
: Matrix34Pod(Identity())
{
}

//------------------------------------------------------------------------------
Matrix34::Matrix34(const Matrix34Pod& obj)
: Matrix34Pod(obj)
{
}

//------------------------------------------------------------------------------
Matrix34::Matrix34(
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
    const f32 r2C3)
{
    v[Index00] = r0C0;
    v[Index10] = r1C0;
    v[Index20] = r2C0;
    v[Index01] = r0C1;
    v[Index11] = r1C1;
    v[Index21] = r2C1;
    v[Index02] = r0C2;
    v[Index12] = r1C2;
    v[Index22] = r2C2;
    v[Index03] = r0C3;
    v[Index13] = r1C3;
    v[Index23] = r2C3;
}

//------------------------------------------------------------------------------
Matrix34::Matrix34(
    const Vector3Pod& x,
    const Vector3Pod& y,
    const Vector3Pod& z,
    const Vector3Pod& w)
{
    SetX(x);
    SetY(y);
    SetZ(z);
    SetW(w);
}

} // namespace ae::base
// EOF
