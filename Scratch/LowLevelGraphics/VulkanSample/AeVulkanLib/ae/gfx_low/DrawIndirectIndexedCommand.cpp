// 文字コード：UTF-8
#include <ae/gfx_low/DrawIndirectIndexedCommand.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
DrawIndirectIndexedCommand& DrawIndirectIndexedCommand::SetIndexOffset(
    const int offset)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, offset);
    native_.firstIndex = offset;
    return *this;
}

//------------------------------------------------------------------------------
DrawIndirectIndexedCommand& DrawIndirectIndexedCommand::SetVertexOffset(
    const int offset)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, offset);
    native_.vertexOffset = offset;
    return *this;
}

//------------------------------------------------------------------------------
DrawIndirectIndexedCommand& DrawIndirectIndexedCommand::SetVertexCount(
    const int count)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    native_.indexCount = count;
    return *this;
}

//------------------------------------------------------------------------------
DrawIndirectIndexedCommand& DrawIndirectIndexedCommand::SetInstanceOffset(
    const int offset)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, offset);
    native_.firstInstance = offset;
    return *this;
}

//------------------------------------------------------------------------------
DrawIndirectIndexedCommand& DrawIndirectIndexedCommand::SetInstanceCount(
    const int count)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    native_.instanceCount = count;
    return *this;
}

} // namespace ae::gfx_low
// EOF
