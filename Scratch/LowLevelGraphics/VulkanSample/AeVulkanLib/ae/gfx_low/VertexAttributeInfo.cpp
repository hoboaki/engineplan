// 文字コード：UTF-8
#include <ae/gfx_low/VertexAttributeInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
VertexAttributeInfo& VertexAttributeInfo::SetFormat(const VertexFormat format)
{
    AE_BASE_ASSERT_ENUM(format, VertexFormat);
    AE_BASE_ASSERT(format != VertexFormat::Invalid);
    format_ = format;
    return *this;
}

//------------------------------------------------------------------------------
VertexAttributeInfo& VertexAttributeInfo::SetSlot(const int slot)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, slot);
    slot_ = slot;
    return *this;
}

//------------------------------------------------------------------------------
VertexAttributeInfo& VertexAttributeInfo::SetOffset(const int offset)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, offset);
    offset_ = offset;
    return *this;
}

} // namespace ae::gfx_low
// EOF
