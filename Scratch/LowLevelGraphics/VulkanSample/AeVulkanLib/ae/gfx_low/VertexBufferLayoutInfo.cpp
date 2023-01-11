// 文字コード：UTF-8
#include <ae/gfx_low/VertexBufferLayoutInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
VertexBufferLayoutInfo& VertexBufferLayoutInfo::SetStride(const int stride)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, stride);
    stride_ = stride;
    return *this;
}

//------------------------------------------------------------------------------
VertexBufferLayoutInfo& VertexBufferLayoutInfo::SetStepRate(
    const VertexStepRate stepRate)
{
    AE_BASE_ASSERT_ENUM(stepRate, VertexStepRate);
    AE_BASE_ASSERT(stepRate != VertexStepRate::Invalid);
    stepRate_ = stepRate;
    return *this;
}

} // namespace ae::gfx_low
// EOF
