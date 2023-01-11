// 文字コード：UTF-8
#include <ae/base/Math.hpp>

// includes
#include <ae/base/Angle.hpp>
#include <ae/base/DivideCheck.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <cmath>

//------------------------------------------------------------------------------
namespace ae::base {
//------------------------------------------------------------------------------
namespace {

const float tEPSILON = 0.000001f;
}
//------------------------------------------------------------------------------
f32 Math::ClampF32(const f32 value, const f32 min, const f32 max)
{
    AE_BASE_ASSERT_LESS_EQUALS(min, max);
    if (value < min) {
        return min;
    }
    if (max < value) {
        return max;
    }
    return value;
}

//------------------------------------------------------------------------------
bool Math::IsInRangeF32(const f32 value, const f32 min, const f32 max)
{
    return (min - tEPSILON) <= value && value <= (max + tEPSILON);
}

//------------------------------------------------------------------------------
bool Math::IsEqualsF32(const f32 val1, const f32 val2)
{
    return IsInRangeF32(val1, val2, val2);
}

//------------------------------------------------------------------------------
bool Math::IsLessEqualsF32(const f32 lhs, const f32 rhs)
{
    return lhs <= (rhs + tEPSILON);
}

//------------------------------------------------------------------------------
bool Math::IsLessF32(const f32 lhs, const f32 rhs)
{
    return lhs < (rhs - tEPSILON);
}

//------------------------------------------------------------------------------
bool Math::IsZeroF32(const f32 val)
{
    return IsEqualsF32(val, 0);
}

//------------------------------------------------------------------------------
f32 Math::SinF32(const Angle& angle)
{
    using namespace std;
    return f32(sinf(angle.Rad()));
}

//------------------------------------------------------------------------------
f32 Math::CosF32(const Angle& angle)
{
    using namespace std;
    return f32(cosf(angle.Rad()));
}

//------------------------------------------------------------------------------
f32 Math::TanF32(const Angle& angle)
{
    using namespace std;
    return f32(tanf(angle.Rad()));
}

//------------------------------------------------------------------------------
f32 Math::CecF32(const Angle& angle)
{
    return AE_BASE_DIV(1, SinF32(angle));
}

//------------------------------------------------------------------------------
f32 Math::SecF32(const Angle& angle)
{
    return AE_BASE_DIV(1, CosF32(angle));
}

//------------------------------------------------------------------------------
f32 Math::CotF32(const Angle& angle)
{
    return AE_BASE_DIV(1, TanF32(angle));
}

//------------------------------------------------------------------------------
f32 Math::SqrtF32(const f32 val)
{
    using namespace std;
    return f32(sqrtf(val));
}

//------------------------------------------------------------------------------
f32 Math::CeilF32(const f32 val)
{
    using namespace std;
    return f32(ceil(val));
}

//------------------------------------------------------------------------------
f32 Math::FloorF32(const f32 val)
{
    using namespace std;
    return f32(floor(val));
}

} // namespace ae::base
// EOF
