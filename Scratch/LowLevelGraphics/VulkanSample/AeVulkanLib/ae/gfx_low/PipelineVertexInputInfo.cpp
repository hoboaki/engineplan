// 文字コード：UTF-8
#include <ae/gfx_low/PipelineVertexInputInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
PipelineVertexInputInfo& PipelineVertexInputInfo::SetBufferCount(
    const int count)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    bufferCount_ = count;
    return *this;
}

//------------------------------------------------------------------------------
PipelineVertexInputInfo& PipelineVertexInputInfo::SetAttributeCount(
    const int count)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    attributeCount_ = count;
    return *this;
}

} // namespace ae::gfx_low
// EOF
