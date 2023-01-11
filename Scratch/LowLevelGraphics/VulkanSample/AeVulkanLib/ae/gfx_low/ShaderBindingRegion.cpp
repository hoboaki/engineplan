// 文字コード：UTF-8
#include <ae/gfx_low/ShaderBindingRegion.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
ShaderBindingRegion& ShaderBindingRegion::SetBindingIndex(const int index)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, index);
    bindingIndex_ = index;
    return *this;
}

//------------------------------------------------------------------------------
ShaderBindingRegion& ShaderBindingRegion::SetElemOffset(const int offset)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, offset);
    elemOffset_ = offset;
    return *this;
}

//------------------------------------------------------------------------------
ShaderBindingRegion& ShaderBindingRegion::SetElemCount(const int count)
{
    AE_BASE_ASSERT_LESS_EQUALS(1, count);
    elemCount_ = count;
    return *this;
}

} // namespace ae::gfx_low
// EOF
