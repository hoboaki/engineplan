// 文字コード：UTF-8
#include <ae/gfx_low/DrawCallInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
DrawCallInfo& DrawCallInfo::SetPrimitiveTopologyKind(
    const gfx_low::PrimitiveTopologyKind kind) {
    AE_BASE_ASSERT_ENUM(kind, gfx_low::PrimitiveTopologyKind);
    AE_BASE_ASSERT(kind != gfx_low::PrimitiveTopologyKind::Invalid);
    primitiveTopologyKind_ = kind;
    return *this;
}

//------------------------------------------------------------------------------
DrawCallInfo& DrawCallInfo::SetVertexOffset(const int offset) {
    AE_BASE_ASSERT_LESS_EQUALS(0, offset);
    vertexOffset_ = offset;
    return *this;
}

//------------------------------------------------------------------------------
DrawCallInfo& DrawCallInfo::SetVertexCount(const int count) {
    AE_BASE_ASSERT_LESS_EQUALS(1, count);
    vertexCount_ = count;
    return *this;
}

//------------------------------------------------------------------------------
DrawCallInfo& DrawCallInfo::SetIndexOffset(const int offset) {
    AE_BASE_ASSERT_LESS_EQUALS(0, offset);
    indexOffset_ = offset;
    return *this;
}

//------------------------------------------------------------------------------
DrawCallInfo& DrawCallInfo::SetInstanceOffset(const int offset) {
    AE_BASE_ASSERT_LESS_EQUALS(0, offset);
    instanceOffset_ = offset;
    return *this;
}

//------------------------------------------------------------------------------
DrawCallInfo& DrawCallInfo::SetInstanceCount(const int count) {
    AE_BASE_ASSERT_LESS_EQUALS(1, count);
    instanceCount_ = count;
    return *this;
}

} // namespace gfx_low
} // namespace ae
// EOF
