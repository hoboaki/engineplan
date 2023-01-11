// 文字コード：UTF-8
#include <ae/gfx_low/DrawIndirectNormalCommand.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
DrawIndirectNormalCommand& DrawIndirectNormalCommand::SetVertexOffset(
    const int offset)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, offset);
    native_.firstVertex = offset;
    return *this;
}

//------------------------------------------------------------------------------
DrawIndirectNormalCommand& DrawIndirectNormalCommand::SetVertexCount(
    const int count)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    native_.vertexCount = count;
    return *this;
}

//------------------------------------------------------------------------------
DrawIndirectNormalCommand& DrawIndirectNormalCommand::SetInstanceOffset(
    const int offset)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, offset);
    native_.firstInstance = offset;
    return *this;
}

//------------------------------------------------------------------------------
DrawIndirectNormalCommand& DrawIndirectNormalCommand::SetInstanceCount(
    const int count)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    native_.instanceCount = count;
    return *this;
}

} // namespace ae::gfx_low
// EOF
