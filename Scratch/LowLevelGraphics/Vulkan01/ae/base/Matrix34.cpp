// 文字コード：UTF-8
#include <ae/base/Matrix34.hpp>

#include <ae/base/Angle.hpp>
#include <ae/base/Console.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/Quaternion.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/Vector3.hpp>
#include <ae/base/Matrix44.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Identity()
{
    // よく使うことになるのでstaticデータとして使い初期化は１回だけにする。
    static Matrix34Pod obj =
    {
        1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0
    };
    return obj;
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Translate(
    const f32 aX,
    const f32 aY,
    const f32 aZ
    )
{
    return Matrix34(
        1, 0, 0, aX,
        0, 1, 0, aY,
        0, 0, 1, aZ
        );
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Translate(
    const Vector3Pod& aVec
    )
{
    return Translate(aVec.x, aVec.y, aVec.z);
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Scale(
    const f32 aX,
    const f32 aY,
    const f32 aZ
    )
{
    return Matrix34(
        aX, 0, 0, 0,
        0, aY, 0, 0,
        0, 0, aZ, 0
        );
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Scale(
    const Vector3Pod& aVec
    )
{
    return Scale(aVec.x, aVec.y, aVec.z);
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Rotate(
    const Angle& aAngle,
    const f32 aAxisX,
    const f32 aAxisY,
    const f32 aAxisZ
    )
{
    const f32 c = Math::CosF32(aAngle);
    const f32 s = Math::SinF32(aAngle);
    const f32 inv_c = 1.0f - c;
    const f32 x = aAxisX;
    const f32 y = aAxisY;
    const f32 z = aAxisZ;
    const f32 xy = x*y;
    const f32 xz = x*z;
    const f32 yz = y*z;
    const f32 xs = x*s;
    const f32 ys = y*s;
    const f32 zs = z*s;

    return Matrix34(
        x*x*inv_c + c, xy*inv_c - zs, xz*inv_c + ys, 0,
        xy*inv_c + zs, y*y*inv_c + c, yz*inv_c - xs, 0,
        xz*inv_c - ys, yz*inv_c + xs, z*z*inv_c + c, 0
        );
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::Rotate(
    const Angle& aAngle,
    const Vector3Pod& aAxisVec
    )
{
    return Rotate(aAngle, aAxisVec.x, aAxisVec.y, aAxisVec.z);
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::LookAt(
    const Vector3Pod& aEyePos,
    const Vector3Pod& aTargetPos,
    const Vector3Pod& aUpVec
    )
{
    // toTargetUnit
    Vector3 toTarget = aTargetPos - aEyePos;
    if (toTarget.isZeroStrict()) {
        AE_BASE_ASSERT_NOT_REACHED();
        toTarget = Vector3Pod::UnitZ(); // fail safe code
    }
    const Vector3 toTargetUnit = toTarget.unit();

    // upVecUnit
    Vector3Pod upVecUnit;
    if (aUpVec.isZeroStrict()) {
        AE_BASE_ERROR_INVALID_VALUE(aUpVec);
        upVecUnit = Vector3::UnitY(); // fail safe code
    }
    else
    {
        upVecUnit = aUpVec.unit();
    }

    // toTarget以外の軸を再作成
    const Vector3Pod s = toTargetUnit.cross(upVecUnit).unit();
    const Vector3Pod u = s.cross(toTargetUnit).unit();
    const Vector3Pod v = -toTargetUnit;

    // 平行移動
    const Vector3Pod invEyePos = -aEyePos;
    const Vector3Pod t = Vector3(
        invEyePos.dot(s),
        invEyePos.dot(u),
        invEyePos.dot(v)
        );

    // 結果を返す
    Matrix34 mtx(
        Vector3(s.x, u.x, v.x),
        Vector3(s.y, u.y, v.y),
        Vector3(s.z, u.z, v.z),
        t
    );
    return mtx;
}

//------------------------------------------------------------------------------
const Vector3Pod Matrix34Pod::x()const
{
    return Vector3(
        v[IndexXX],
        v[IndexXY],
        v[IndexXZ]
        );
}

//------------------------------------------------------------------------------
const Vector3Pod Matrix34Pod::y()const
{
    return Vector3(
        v[IndexYX],
        v[IndexYY],
        v[IndexYZ]
        );
}

//------------------------------------------------------------------------------
const Vector3Pod Matrix34Pod::z()const
{
    return Vector3(
        v[IndexZX],
        v[IndexZY],
        v[IndexZZ]
        );
}

//------------------------------------------------------------------------------
const Vector3Pod Matrix34Pod::w()const
{
    return Vector3(
        v[IndexWX],
        v[IndexWY],
        v[IndexWZ]
        );
}

//------------------------------------------------------------------------------
void Matrix34Pod::setX(const Vector3Pod& aVal)
{
    v[IndexXX] = aVal.x;
    v[IndexXY] = aVal.y;
    v[IndexXZ] = aVal.z;
}

//------------------------------------------------------------------------------
void Matrix34Pod::setY(const Vector3Pod& aVal)
{
    v[IndexYX] = aVal.x;
    v[IndexYY] = aVal.y;
    v[IndexYZ] = aVal.z;
}

//------------------------------------------------------------------------------
void Matrix34Pod::setZ(const Vector3Pod& aVal)
{
    v[IndexZX] = aVal.x;
    v[IndexZY] = aVal.y;
    v[IndexZZ] = aVal.z;
}

//------------------------------------------------------------------------------
void Matrix34Pod::setW(const Vector3Pod& aVal)
{
    v[IndexWX] = aVal.x;
    v[IndexWY] = aVal.y;
    v[IndexWZ] = aVal.z;
}

//------------------------------------------------------------------------------
const Vector3Pod Matrix34Pod::mul(const Vector3Pod& aVec)const
{
    return Vector3(
        aVec.x * v[IndexXX] + aVec.y * v[IndexYX] + aVec.z * v[IndexZX] + v[IndexWX],
        aVec.x * v[IndexXY] + aVec.y * v[IndexYY] + aVec.z * v[IndexZY] + v[IndexWY],
        aVec.x * v[IndexXZ] + aVec.y * v[IndexYZ] + aVec.z * v[IndexZZ] + v[IndexWZ]
        );
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::mul(const Matrix34Pod& aRHS)const
{
    Matrix34Pod mtx;

    // c0
    mtx.v[Index00] =
        this->v[Index00] * aRHS.v[Index00]
        + this->v[Index01] * aRHS.v[Index10]
        + this->v[Index02] * aRHS.v[Index20];
    mtx.v[Index01] =
        this->v[Index00] * aRHS.v[Index01]
        + this->v[Index01] * aRHS.v[Index11]
        + this->v[Index02] * aRHS.v[Index21];
    mtx.v[Index02] =
        this->v[Index00] * aRHS.v[Index02]
        + this->v[Index01] * aRHS.v[Index12]
        + this->v[Index02] * aRHS.v[Index22];
    mtx.v[Index03] =
        this->v[Index00] * aRHS.v[Index03]
        + this->v[Index01] * aRHS.v[Index13]
        + this->v[Index02] * aRHS.v[Index23]
        + this->v[Index03];

    // c1
    mtx.v[Index10] =
        this->v[Index10] * aRHS.v[Index00]
        + this->v[Index11] * aRHS.v[Index10]
        + this->v[Index12] * aRHS.v[Index20];
    mtx.v[Index11] =
        this->v[Index10] * aRHS.v[Index01]
        + this->v[Index11] * aRHS.v[Index11]
        + this->v[Index12] * aRHS.v[Index21];
    mtx.v[Index12] =
        this->v[Index10] * aRHS.v[Index02]
        + this->v[Index11] * aRHS.v[Index12]
        + this->v[Index12] * aRHS.v[Index22];
    mtx.v[Index13] =
        this->v[Index10] * aRHS.v[Index03]
        + this->v[Index11] * aRHS.v[Index13]
        + this->v[Index12] * aRHS.v[Index23]
        + this->v[Index13];

    // c2
    mtx.v[Index20] =
        this->v[Index20] * aRHS.v[Index00]
        + this->v[Index21] * aRHS.v[Index10]
        + this->v[Index22] * aRHS.v[Index20];
    mtx.v[Index21] =
        this->v[Index20] * aRHS.v[Index01]
        + this->v[Index21] * aRHS.v[Index11]
        + this->v[Index22] * aRHS.v[Index21];
    mtx.v[Index22] =
        this->v[Index20] * aRHS.v[Index02]
        + this->v[Index21] * aRHS.v[Index12]
        + this->v[Index22] * aRHS.v[Index22];
    mtx.v[Index23] =
        this->v[Index20] * aRHS.v[Index03]
        + this->v[Index21] * aRHS.v[Index13]
        + this->v[Index22] * aRHS.v[Index23]
        + this->v[Index23];

    return mtx;
}

//------------------------------------------------------------------------------
Matrix34Pod& Matrix34Pod::mulAssign(const Matrix34Pod& aRHS)
{
    *this = mul(aRHS);
    return *this;
}

//------------------------------------------------------------------------------
const Vector3Pod Matrix34Pod::operator*(const Vector3Pod& aRHS)const
{
    return mul(aRHS);
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::operator*(const Matrix34Pod& aRHS)const
{
    return mul(aRHS);
}

//------------------------------------------------------------------------------
Matrix34Pod& Matrix34Pod::operator*=(const Matrix34Pod& aRHS)
{
    mulAssign(aRHS);
    return *this;
}

//------------------------------------------------------------------------------
const Matrix34Pod Matrix34Pod::invert()const
{
    const float c = 0.0f
        + v[Index00] * v[Index11] * v[Index22]
        + v[Index01] * v[Index12] * v[Index20]
        + v[Index02] * v[Index10] * v[Index21]
        - v[Index00] * v[Index12] * v[Index21]
        - v[Index01] * v[Index10] * v[Index22]
        - v[Index02] * v[Index11] * v[Index20];

    if (c == 0.0f) {
        AE_BASE_ASSERT_NOT_REACHED();
        return Identity();
    }

    Matrix34Pod b;
    b.v[Index00]
        = v[Index11] * v[Index22] + v[Index12] * v[Index23] * 0 + v[Index13] * v[Index21] * 0
        - v[Index11] * v[Index23] * 0 - v[Index12] * v[Index21] - v[Index13] * v[Index22] * 0;
    b.v[Index01]
        = v[Index01] * v[Index23] * 0 + v[Index02] * v[Index21] + v[Index03] * v[Index22] * 0
        - v[Index01] * v[Index22] - v[Index02] * v[Index23] * 0 - v[Index03] * v[Index21] * 0;
    b.v[Index02]
        = v[Index01] * v[Index12] + v[Index02] * v[Index13] * 0 + v[Index03] * v[Index11] * 0
        - v[Index01] * v[Index13] * 0 - v[Index02] * v[Index11] - v[Index03] * v[Index12] * 0;
    b.v[Index03]
        = v[Index01] * v[Index13] * v[Index22] + v[Index02] * v[Index11] * v[Index23] + v[Index03] * v[Index12] * v[Index21]
        - v[Index01] * v[Index12] * v[Index23] - v[Index02] * v[Index13] * v[Index21] - v[Index03] * v[Index11] * v[Index22];
    b.v[Index10]
        = v[Index10] * v[Index23] * 0 + v[Index12] * v[Index20] + v[Index13] * v[Index22] * 0
        - v[Index10] * v[Index22] - v[Index12] * v[Index23] * 0 - v[Index13] * v[Index20] * 0;
    b.v[Index11]
        = v[Index00] * v[Index22] + v[Index02] * v[Index23] * 0 + v[Index03] * v[Index20] * 0
        - v[Index00] * v[Index23] * 0 - v[Index02] * v[Index20] - v[Index03] * v[Index22] * 0;
    b.v[Index12]
        = v[Index00] * v[Index13] * 0 + v[Index02] * v[Index10] + v[Index03] * v[Index12] * 0
        - v[Index00] * v[Index12] - v[Index02] * v[Index13] * 0 - v[Index03] * v[Index10] * 0;
    b.v[Index13]
        = v[Index00] * v[Index12] * v[Index23] + v[Index02] * v[Index13] * v[Index20] + v[Index03] * v[Index10] * v[Index22]
        - v[Index00] * v[Index13] * v[Index22] - v[Index02] * v[Index10] * v[Index23] - v[Index03] * v[Index12] * v[Index20];
    b.v[Index20]
        = v[Index10] * v[Index21] + v[Index11] * v[Index23] * 0 + v[Index13] * v[Index20] * 0
        - v[Index10] * v[Index23] * 0 - v[Index11] * v[Index20] - v[Index13] * v[Index21] * 0;
    b.v[Index21]
        = v[Index00] * v[Index23] * 0 + v[Index01] * v[Index20] + v[Index03] * v[Index21] * 0
        - v[Index00] * v[Index21] - v[Index01] * v[Index23] * 0 - v[Index03] * v[Index20] * 0;
    b.v[Index22]
        = v[Index00] * v[Index11] + v[Index01] * v[Index13] * 0 + v[Index03] * v[Index10] * 0
        - v[Index00] * v[Index13] * 0 - v[Index01] * v[Index10] - v[Index03] * v[Index11] * 0;
    b.v[Index23]
        = v[Index00] * v[Index13] * v[Index21] + v[Index01] * v[Index10] * v[Index23] + v[Index03] * v[Index11] * v[Index20]
        - v[Index00] * v[Index11] * v[Index23] - v[Index01] * v[Index13] * v[Index20] - v[Index03] * v[Index10] * v[Index21];

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
const Matrix34Pod Matrix34Pod::transpose()const
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
const Quaternion Matrix34Pod::toQuaternion()const
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

    const float maxVal = v[Index22] < v[Index11]
        ? v[Index11]
        : v[Index22]
        ;
    if (maxVal < v[Index00]) {
        float s = Math::SqrtF32(v[Index00] - (v[Index11] + v[Index22]) + 1.0f);
        const float x = s * 0.5f;
        s = 0.5f / s;
        q.x = x;
        q.y = (v[Index10] + v[Index01]) * s;
        q.z = (v[Index02] + v[Index20]) * s;
        q.w = (v[Index21] - v[Index12]) * s;
        return q;
    }
    else if (maxVal == v[Index11]) {
        float s = Math::SqrtF32(v[Index11] - (v[Index22] + v[Index00]) + 1.0f);
        const float y = s * 0.5f;
        s = 0.5f / s;
        q.x = (v[Index10] + v[Index01]) * s;
        q.y = y;
        q.z = (v[Index21] + v[Index12]) * s;
        q.w = (v[Index02] - v[Index20]) * s;
        return q;
    }
    else
    {
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
const Matrix44Pod Matrix34Pod::toMatrix44()const
{
    return Matrix44(
        v[Index00], v[Index01], v[Index02], v[Index03],
        v[Index10], v[Index11], v[Index12], v[Index13],
        v[Index20], v[Index21], v[Index22], v[Index23],
        0, 0, 0, 1
        );
}

//------------------------------------------------------------------------------
void Matrix34Pod::dump()const
{
    AE_BASE_COUTFMT("Matrix34Pod::dump %p\n", this);
    AE_BASE_COUTFMT("( %f , %f , %f , %f )\n", v[Index00], v[Index01], v[Index02], v[Index03]);
    AE_BASE_COUTFMT("( %f , %f , %f , %f )\n", v[Index10], v[Index11], v[Index12], v[Index13]);
    AE_BASE_COUTFMT("( %f , %f , %f , %f )\n", v[Index20], v[Index21], v[Index22], v[Index23]);
}

//------------------------------------------------------------------------------
Matrix34::Matrix34()
: Matrix34Pod(Identity())
{
}

//------------------------------------------------------------------------------
Matrix34::Matrix34(const Matrix34Pod& aObj)
: Matrix34Pod(aObj)
{
}

//------------------------------------------------------------------------------
Matrix34::Matrix34(
    const f32 aR0C0, const f32 aR0C1, const f32 aR0C2, const f32 aR0C3,
    const f32 aR1C0, const f32 aR1C1, const f32 aR1C2, const f32 aR1C3,
    const f32 aR2C0, const f32 aR2C1, const f32 aR2C2, const f32 aR2C3
    )
{
    v[Index00] = aR0C0;
    v[Index10] = aR1C0;
    v[Index20] = aR2C0;
    v[Index01] = aR0C1;
    v[Index11] = aR1C1;
    v[Index21] = aR2C1;
    v[Index02] = aR0C2;
    v[Index12] = aR1C2;
    v[Index22] = aR2C2;
    v[Index03] = aR0C3;
    v[Index13] = aR1C3;
    v[Index23] = aR2C3;
}

//------------------------------------------------------------------------------
Matrix34::Matrix34(
    const Vector3Pod& aX,
    const Vector3Pod& aY,
    const Vector3Pod& aZ,
    const Vector3Pod& aW
    )
{
    setX(aX);
    setY(aY);
    setZ(aZ);
    setW(aW);
}

}} // namespace
// EOF
