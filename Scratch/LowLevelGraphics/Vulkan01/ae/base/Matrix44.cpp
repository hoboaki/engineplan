// 文字コード：UTF-8
#include <ae/base/Matrix44.hpp>

#include <ae/base/Angle.hpp>
#include <ae/base/Console.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/Matrix34.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/Vector3.hpp>
#include <ae/base/Vector4.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Identity()
{
    // よく使うことになるのでstaticデータとして使い初期化は１回だけにする。
    static Matrix44Pod obj =
    {
        1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
    };
    return obj;
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Translate(
    const f32 aX,
    const f32 aY,
    const f32 aZ
    )
{
    return Matrix44(
        1, 0, 0, aX,
        0, 1, 0, aY,
        0, 0, 1, aZ,
        0, 0, 0, 1
        );
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Translate(
    const Vector3Pod& aVec
    )
{
    return Translate(aVec.x, aVec.y, aVec.z);
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Scale(
    const f32 aX,
    const f32 aY,
    const f32 aZ
    )
{
    return Matrix44(
        aX, 0, 0, 0,
        0, aY, 0, 0,
        0, 0, aZ, 0,
        0, 0, 0, 1
        );
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Scale(
    const Vector3Pod& aVec
    )
{
    return Scale(aVec.x, aVec.y, aVec.z);
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Rotate(
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

    return Matrix44(
        x*x*inv_c + c, xy*inv_c - zs, xz*inv_c + ys, 0,
        xy*inv_c + zs, y*y*inv_c + c, yz*inv_c - xs, 0,
        xz*inv_c - ys, yz*inv_c + xs, z*z*inv_c + c, 0,
        0, 0, 0, 1
        );
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Rotate(
    const Angle& aAngle,
    const Vector3Pod& aAxisVec
    )
{
    return Rotate(aAngle, aAxisVec.x, aAxisVec.y, aAxisVec.z);
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Ortho(
    const f32 aLeft,
    const f32 aTop,
    const f32 aRight,
    const f32 aBottom,
    const f32 aNear,
    const f32 aFar
    )
{
    AE_BASE_ASSERT_NOT_EQUALS(aLeft, aRight);
    AE_BASE_ASSERT_NOT_EQUALS(aTop, aBottom);
    AE_BASE_ASSERT_NOT_EQUALS(aNear, aFar);

    const f32 r_sub_l = aRight - aLeft;
    const f32 r_add_l = aRight + aLeft;
    const f32 t_sub_b = aTop - aBottom;
    const f32 t_add_b = aTop + aBottom;
    const f32 f_sub_n = aFar - aNear;
    const f32 f_add_n = aFar + aNear;
    return Matrix44(
        2 / r_sub_l, 0, 0, -r_add_l / r_sub_l,
        0, 2 / t_sub_b, 0, -t_add_b / t_sub_b,
        0, 0, -2 / f_sub_n, -f_add_n / f_sub_n,
        0, 0, 0, 1
        );
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Frustum(
    const f32 aLeft,
    const f32 aRight,
    const f32 aBottom,
    const f32 aTop,
    const f32 aNear,
    const f32 aFar
    )
{
    AE_BASE_ASSERT_NOT_EQUALS(aLeft, aRight);
    AE_BASE_ASSERT_NOT_EQUALS(aBottom, aTop);
    AE_BASE_ASSERT_NOT_EQUALS(aNear, aFar);

    const f32 l = aLeft;
    const f32 r = aRight;
    const f32 b = aBottom;
    const f32 t = aTop;
    const f32 n = aNear;
    const f32 f = aFar;
    const f32 n2 = 2 * aNear;
    return Matrix44(
        n2 / (r - l), 0, 0, (r + l) / (r - l),
        0, n2 / (t - b), 0, (-t + b) / (t - b),
        0, 0, -2 / (f - n), (f + n) / f - n,
        0, 0, 0, 1
        );
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::Perspective(
    const Angle& aFOVY,
    const f32 aAspect,
    const f32 aNear,
    const f32 aFar
    )
{
    AE_BASE_ASSERT_LESS(0, aFOVY.rad());
    AE_BASE_ASSERT_LESS(0, aAspect);
    AE_BASE_ASSERT_NOT_EQUALS(aNear, aFar);

    const f32 c = Math::CotF32(aFOVY);
    return Matrix44(
        c / aAspect, 0, 0, 0,
        0, c, 0, 0,
        0, 0, (aNear + aFar) / (aNear - aFar), (2 * aNear * aFar) / (aNear - aFar),
        0, 0, -1, 0
        );
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::LookAt(
    const Vector3Pod& aEyePos,
    const Vector3Pod& aTargetPos,
    const Vector3Pod& aUpVec
    )
{
    return Matrix34::LookAt(aEyePos, aTargetPos, aUpVec).toMatrix44();
}

//------------------------------------------------------------------------------
const Vector4Pod Matrix44Pod::x()const
{
    return Vector4(
        v[IndexXX],
        v[IndexXY],
        v[IndexXZ],
        v[IndexXW]
        );
}

//------------------------------------------------------------------------------
const Vector4Pod Matrix44Pod::y()const
{
    return Vector4(
        v[IndexYX],
        v[IndexYY],
        v[IndexYZ],
        v[IndexYW]
        );
}

//------------------------------------------------------------------------------
const Vector4Pod Matrix44Pod::z()const
{
    return Vector4(
        v[IndexZX],
        v[IndexZY],
        v[IndexZZ],
        v[IndexZW]
        );
}

//------------------------------------------------------------------------------
const Vector4Pod Matrix44Pod::w()const
{
    return Vector4(
        v[IndexWX],
        v[IndexWY],
        v[IndexWZ],
        v[IndexWW]
        );
}

//------------------------------------------------------------------------------
void Matrix44Pod::setX(const Vector4Pod& aVal)
{
    v[IndexXX] = aVal.x;
    v[IndexXY] = aVal.y;
    v[IndexXZ] = aVal.z;
    v[IndexXW] = aVal.w;
}

//------------------------------------------------------------------------------
void Matrix44Pod::setY(const Vector4Pod& aVal)
{
    v[IndexYX] = aVal.x;
    v[IndexYY] = aVal.y;
    v[IndexYZ] = aVal.z;
    v[IndexYW] = aVal.w;
}

//------------------------------------------------------------------------------
void Matrix44Pod::setZ(const Vector4Pod& aVal)
{
    v[IndexZX] = aVal.x;
    v[IndexZY] = aVal.y;
    v[IndexZZ] = aVal.z;
    v[IndexZW] = aVal.w;
}

//------------------------------------------------------------------------------
void Matrix44Pod::setW(const Vector4Pod& aVal)
{
    v[IndexWX] = aVal.x;
    v[IndexWY] = aVal.y;
    v[IndexWZ] = aVal.z;
    v[IndexWW] = aVal.w;
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::mul(const Matrix44Pod& aRHS)const
{
    Matrix44Pod mtx;

    // c0
    mtx.v[Index00] =
        this->v[Index00] * aRHS.v[Index00]
        + this->v[Index01] * aRHS.v[Index10]
        + this->v[Index02] * aRHS.v[Index20]
        + this->v[Index03] * aRHS.v[Index30];
    mtx.v[Index01] =
        this->v[Index00] * aRHS.v[Index01]
        + this->v[Index01] * aRHS.v[Index11]
        + this->v[Index02] * aRHS.v[Index21]
        + this->v[Index03] * aRHS.v[Index31];
    mtx.v[Index02] =
        this->v[Index00] * aRHS.v[Index02]
        + this->v[Index01] * aRHS.v[Index12]
        + this->v[Index02] * aRHS.v[Index22]
        + this->v[Index03] * aRHS.v[Index32];
    mtx.v[Index03] =
        this->v[Index00] * aRHS.v[Index03]
        + this->v[Index01] * aRHS.v[Index13]
        + this->v[Index02] * aRHS.v[Index23]
        + this->v[Index03] * aRHS.v[Index33];

    // c1
    mtx.v[Index10] =
        this->v[Index10] * aRHS.v[Index00]
        + this->v[Index11] * aRHS.v[Index10]
        + this->v[Index12] * aRHS.v[Index20]
        + this->v[Index13] * aRHS.v[Index30];
    mtx.v[Index11] =
        this->v[Index10] * aRHS.v[Index01]
        + this->v[Index11] * aRHS.v[Index11]
        + this->v[Index12] * aRHS.v[Index21]
        + this->v[Index13] * aRHS.v[Index31];
    mtx.v[Index12] =
        this->v[Index10] * aRHS.v[Index02]
        + this->v[Index11] * aRHS.v[Index12]
        + this->v[Index12] * aRHS.v[Index22]
        + this->v[Index13] * aRHS.v[Index32];
    mtx.v[Index13] =
        this->v[Index10] * aRHS.v[Index03]
        + this->v[Index11] * aRHS.v[Index13]
        + this->v[Index12] * aRHS.v[Index23]
        + this->v[Index13] * aRHS.v[Index33];

    // c2
    mtx.v[Index20] =
        this->v[Index20] * aRHS.v[Index00]
        + this->v[Index21] * aRHS.v[Index10]
        + this->v[Index22] * aRHS.v[Index20]
        + this->v[Index23] * aRHS.v[Index30];
    mtx.v[Index21] =
        this->v[Index20] * aRHS.v[Index01]
        + this->v[Index21] * aRHS.v[Index11]
        + this->v[Index22] * aRHS.v[Index21]
        + this->v[Index23] * aRHS.v[Index31];
    mtx.v[Index22] =
        this->v[Index20] * aRHS.v[Index02]
        + this->v[Index21] * aRHS.v[Index12]
        + this->v[Index22] * aRHS.v[Index22]
        + this->v[Index23] * aRHS.v[Index32];
    mtx.v[Index23] =
        this->v[Index20] * aRHS.v[Index03]
        + this->v[Index21] * aRHS.v[Index13]
        + this->v[Index22] * aRHS.v[Index23]
        + this->v[Index23] * aRHS.v[Index33];

    // c3
    mtx.v[Index30] =
        this->v[Index30] * aRHS.v[Index00]
        + this->v[Index31] * aRHS.v[Index10]
        + this->v[Index32] * aRHS.v[Index20]
        + this->v[Index33] * aRHS.v[Index30];
    mtx.v[Index31] =
        this->v[Index30] * aRHS.v[Index01]
        + this->v[Index31] * aRHS.v[Index11]
        + this->v[Index32] * aRHS.v[Index21]
        + this->v[Index33] * aRHS.v[Index31];
    mtx.v[Index32] =
        this->v[Index30] * aRHS.v[Index02]
        + this->v[Index31] * aRHS.v[Index12]
        + this->v[Index32] * aRHS.v[Index22]
        + this->v[Index33] * aRHS.v[Index32];
    mtx.v[Index33] =
        this->v[Index30] * aRHS.v[Index03]
        + this->v[Index31] * aRHS.v[Index13]
        + this->v[Index32] * aRHS.v[Index23]
        + this->v[Index33] * aRHS.v[Index33];

    return mtx;
}

//------------------------------------------------------------------------------
Matrix44Pod& Matrix44Pod::mulAssign(const Matrix44Pod& aRHS)
{
    *this = mul(aRHS);
    return *this;
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::operator*(const Matrix44Pod& aRHS)const
{
    return mul(aRHS);
}

//------------------------------------------------------------------------------
Matrix44Pod& Matrix44Pod::operator*=(const Matrix44Pod& aRHS)
{
    mulAssign(aRHS);
    return *this;
}

//------------------------------------------------------------------------------
const Matrix44Pod Matrix44Pod::invert()const
{
    const float c = 0.0f
        + v[Index00] * v[Index11] * v[Index22] * v[Index33] + v[Index00] * v[Index12] * v[Index23] * v[Index31] + v[Index00] * v[Index13] * v[Index21] * v[Index32]
        + v[Index01] * v[Index10] * v[Index23] * v[Index32] + v[Index01] * v[Index12] * v[Index20] * v[Index33] + v[Index01] * v[Index13] * v[Index22] * v[Index30]
        + v[Index02] * v[Index10] * v[Index21] * v[Index33] + v[Index02] * v[Index11] * v[Index23] * v[Index30] + v[Index02] * v[Index13] * v[Index20] * v[Index31]
        + v[Index03] * v[Index10] * v[Index22] * v[Index31] + v[Index03] * v[Index11] * v[Index20] * v[Index32] + v[Index03] * v[Index12] * v[Index21] * v[Index30]
        - v[Index00] * v[Index11] * v[Index23] * v[Index32] - v[Index00] * v[Index12] * v[Index21] * v[Index33] - v[Index00] * v[Index13] * v[Index22] * v[Index31]
        - v[Index01] * v[Index10] * v[Index22] * v[Index33] - v[Index01] * v[Index12] * v[Index23] * v[Index30] - v[Index01] * v[Index13] * v[Index20] * v[Index32]
        - v[Index02] * v[Index10] * v[Index23] * v[Index31] - v[Index02] * v[Index11] * v[Index20] * v[Index33] - v[Index02] * v[Index13] * v[Index21] * v[Index30]
        - v[Index03] * v[Index10] * v[Index21] * v[Index32] - v[Index03] * v[Index11] * v[Index22] * v[Index30] - v[Index03] * v[Index12] * v[Index20] * v[Index31];

    if (c == 0.0f) {
        AE_BASE_ASSERT_NOT_REACHED();
        return Identity();
    }

    Matrix44Pod b;
    b.v[Index00]
        = v[Index11] * v[Index22] * v[Index33] + v[Index12] * v[Index23] * v[Index31] + v[Index13] * v[Index21] * v[Index32]
        - v[Index11] * v[Index23] * v[Index32] - v[Index12] * v[Index21] * v[Index33] - v[Index13] * v[Index22] * v[Index31];
    b.v[Index01]
        = v[Index01] * v[Index23] * v[Index32] + v[Index02] * v[Index21] * v[Index33] + v[Index03] * v[Index22] * v[Index31]
        - v[Index01] * v[Index22] * v[Index33] - v[Index02] * v[Index23] * v[Index31] - v[Index03] * v[Index21] * v[Index32];
    b.v[Index02]
        = v[Index01] * v[Index12] * v[Index33] + v[Index02] * v[Index13] * v[Index31] + v[Index03] * v[Index11] * v[Index32]
        - v[Index01] * v[Index13] * v[Index32] - v[Index02] * v[Index11] * v[Index33] - v[Index03] * v[Index12] * v[Index31];
    b.v[Index03]
        = v[Index01] * v[Index13] * v[Index22] + v[Index02] * v[Index11] * v[Index23] + v[Index03] * v[Index12] * v[Index21]
        - v[Index01] * v[Index12] * v[Index23] - v[Index02] * v[Index13] * v[Index21] - v[Index03] * v[Index11] * v[Index22];
    b.v[Index10]
        = v[Index10] * v[Index23] * v[Index32] + v[Index12] * v[Index20] * v[Index33] + v[Index13] * v[Index22] * v[Index30]
        - v[Index10] * v[Index22] * v[Index33] - v[Index12] * v[Index23] * v[Index30] - v[Index13] * v[Index20] * v[Index32];
    b.v[Index11]
        = v[Index00] * v[Index22] * v[Index33] + v[Index02] * v[Index23] * v[Index30] + v[Index03] * v[Index20] * v[Index32]
        - v[Index00] * v[Index23] * v[Index32] - v[Index02] * v[Index20] * v[Index33] - v[Index03] * v[Index22] * v[Index30];
    b.v[Index12]
        = v[Index00] * v[Index13] * v[Index32] + v[Index02] * v[Index10] * v[Index33] + v[Index03] * v[Index12] * v[Index30]
        - v[Index00] * v[Index12] * v[Index33] - v[Index02] * v[Index13] * v[Index30] - v[Index03] * v[Index10] * v[Index32];
    b.v[Index13]
        = v[Index00] * v[Index12] * v[Index23] + v[Index02] * v[Index13] * v[Index20] + v[Index03] * v[Index10] * v[Index22]
        - v[Index00] * v[Index13] * v[Index22] - v[Index02] * v[Index10] * v[Index23] - v[Index03] * v[Index12] * v[Index20];
    b.v[Index20]
        = v[Index10] * v[Index21] * v[Index33] + v[Index11] * v[Index23] * v[Index30] + v[Index13] * v[Index20] * v[Index31]
        - v[Index10] * v[Index23] * v[Index31] - v[Index11] * v[Index20] * v[Index33] - v[Index13] * v[Index21] * v[Index30];
    b.v[Index21]
        = v[Index00] * v[Index23] * v[Index31] + v[Index01] * v[Index20] * v[Index33] + v[Index03] * v[Index21] * v[Index30]
        - v[Index00] * v[Index21] * v[Index33] - v[Index01] * v[Index23] * v[Index30] - v[Index03] * v[Index20] * v[Index31];
    b.v[Index22]
        = v[Index00] * v[Index11] * v[Index33] + v[Index01] * v[Index13] * v[Index30] + v[Index03] * v[Index10] * v[Index31]
        - v[Index00] * v[Index13] * v[Index31] - v[Index01] * v[Index10] * v[Index33] - v[Index03] * v[Index11] * v[Index30];
    b.v[Index23]
        = v[Index00] * v[Index13] * v[Index21] + v[Index01] * v[Index10] * v[Index23] + v[Index03] * v[Index11] * v[Index20]
        - v[Index00] * v[Index11] * v[Index23] - v[Index01] * v[Index13] * v[Index20] - v[Index03] * v[Index10] * v[Index21];
    b.v[Index30]
        = v[Index10] * v[Index22] * v[Index31] + v[Index11] * v[Index20] * v[Index32] + v[Index12] * v[Index31] * v[Index30]
        - v[Index10] * v[Index21] * v[Index32] - v[Index11] * v[Index22] * v[Index30] - v[Index12] * v[Index20] * v[Index31];
    b.v[Index31]
        = v[Index00] * v[Index21] * v[Index32] + v[Index01] * v[Index22] * v[Index30] + v[Index02] * v[Index20] * v[Index31]
        - v[Index00] * v[Index22] * v[Index31] - v[Index01] * v[Index20] * v[Index32] - v[Index02] * v[Index21] * v[Index30];
    b.v[Index32]
        = v[Index00] * v[Index12] * v[Index31] + v[Index01] * v[Index10] * v[Index32] + v[Index02] * v[Index11] * v[Index30]
        - v[Index00] * v[Index11] * v[Index32] - v[Index01] * v[Index12] * v[Index30] - v[Index02] * v[Index10] * v[Index31];
    b.v[Index33]
        = v[Index00] * v[Index11] * v[Index22] + v[Index01] * v[Index12] * v[Index20] + v[Index02] * v[Index10] * v[Index21]
        - v[Index00] * v[Index12] * v[Index21] - v[Index01] * v[Index10] * v[Index22] - v[Index02] * v[Index11] * v[Index20];

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
const Matrix44Pod Matrix44Pod::transpose()const
{
    return Matrix44(
        v[Index00], v[Index10], v[Index20], v[Index30],
        v[Index01], v[Index11], v[Index21], v[Index31],
        v[Index02], v[Index12], v[Index22], v[Index32],
        v[Index03], v[Index13], v[Index23], v[Index33]
        );
}

//------------------------------------------------------------------------------
void Matrix44Pod::dump()const
{
    AE_BASE_COUTFMT("Matrix44Pod::dump %p\n", this);
    AE_BASE_COUTFMT("( %f , %f , %f , %f )\n", v[Index00], v[Index01], v[Index02], v[Index03]);
    AE_BASE_COUTFMT("( %f , %f , %f , %f )\n", v[Index10], v[Index11], v[Index12], v[Index13]);
    AE_BASE_COUTFMT("( %f , %f , %f , %f )\n", v[Index20], v[Index21], v[Index22], v[Index23]);
    AE_BASE_COUTFMT("( %f , %f , %f , %f )\n", v[Index30], v[Index31], v[Index32], v[Index33]);
}

//------------------------------------------------------------------------------
Matrix44::Matrix44()
: Matrix44Pod(Identity())
{
}

//------------------------------------------------------------------------------
Matrix44::Matrix44(const Matrix44Pod& aObj)
: Matrix44Pod(aObj)
{
}

//------------------------------------------------------------------------------
Matrix44::Matrix44(
    const f32 aR0C0, const f32 aR0C1, const f32 aR0C2, const f32 aR0C3,
    const f32 aR1C0, const f32 aR1C1, const f32 aR1C2, const f32 aR1C3,
    const f32 aR2C0, const f32 aR2C1, const f32 aR2C2, const f32 aR2C3,
    const f32 aR3C0, const f32 aR3C1, const f32 aR3C2, const f32 aR3C3
    )
{
    v[Index00] = aR0C0;
    v[Index10] = aR1C0;
    v[Index20] = aR2C0;
    v[Index30] = aR3C0;
    v[Index01] = aR0C1;
    v[Index11] = aR1C1;
    v[Index21] = aR2C1;
    v[Index31] = aR3C1;
    v[Index02] = aR0C2;
    v[Index12] = aR1C2;
    v[Index22] = aR2C2;
    v[Index32] = aR3C2;
    v[Index03] = aR0C3;
    v[Index13] = aR1C3;
    v[Index23] = aR2C3;
    v[Index33] = aR3C3;
}

//------------------------------------------------------------------------------
Matrix44::Matrix44(
    const Vector4Pod& aX,
    const Vector4Pod& aY,
    const Vector4Pod& aZ,
    const Vector4Pod& aW
    )
{
    setX(aX);
    setY(aY);
    setZ(aZ);
    setW(aW);
}
}} // namespace
// EOF
