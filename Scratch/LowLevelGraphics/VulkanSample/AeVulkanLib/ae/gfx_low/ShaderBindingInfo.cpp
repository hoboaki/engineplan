// 文字コード：UTF-8
#include <ae/gfx_low/ShaderBindingInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
ShaderBindingInfo& ShaderBindingInfo::SetBindingIndex(const int index)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, index);
    bindingIndex_ = index;
    return *this;
}

//------------------------------------------------------------------------------
ShaderBindingInfo& ShaderBindingInfo::SetElemCount(const int count)
{
    AE_BASE_ASSERT_LESS_EQUALS(1, count);
    elemCount_ = count;
    return *this;
}

} // namespace ae::gfx_low
// EOF
