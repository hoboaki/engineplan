// 文字コード：UTF-8
#include <ae/gfx_low/DrawIndirectCallInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
DrawIndirectCallInfo& DrawIndirectCallInfo::SetCommandOffset(const int offset)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, offset);
    commandOffset_ = offset;
    return *this;
}

//------------------------------------------------------------------------------
DrawIndirectCallInfo& DrawIndirectCallInfo::SetCommandCount(const int count)
{
    AE_BASE_ASSERT_LESS_EQUALS(1, count);
    commandCount_ = count;
    return *this;
}

} // namespace ae::gfx_low
// EOF
