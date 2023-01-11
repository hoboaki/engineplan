// 文字コード：UTF-8
#include <ae/gfx_low/DrawCallInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
DrawCallInfo& DrawCallInfo::SetVertexOffset(const int offset)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, offset);
    vertexOffset_ = offset;
    return *this;
}

//------------------------------------------------------------------------------
DrawCallInfo& DrawCallInfo::SetVertexCount(const int count)
{
    AE_BASE_ASSERT_LESS_EQUALS(1, count);
    vertexCount_ = count;
    return *this;
}

//------------------------------------------------------------------------------
DrawCallInfo& DrawCallInfo::SetIndexOffset(const int offset)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, offset);
    indexOffset_ = offset;
    return *this;
}

//------------------------------------------------------------------------------
DrawCallInfo& DrawCallInfo::SetInstanceOffset(const int offset)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, offset);
    instanceOffset_ = offset;
    return *this;
}

//------------------------------------------------------------------------------
DrawCallInfo& DrawCallInfo::SetInstanceCount(const int count)
{
    AE_BASE_ASSERT_LESS_EQUALS(1, count);
    instanceCount_ = count;
    return *this;
}

} // namespace ae::gfx_low
// EOF
