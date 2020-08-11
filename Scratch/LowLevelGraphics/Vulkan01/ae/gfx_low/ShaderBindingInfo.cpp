// 文字コード：UTF-8
#include <ae/gfx_low/ShaderBindingInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
ShaderBindingInfo& ShaderBindingInfo::SetBindingIndex(const int index) {
    AE_BASE_ASSERT_LESS_EQUALS(0, index);
    bindingIndex_ = index;
    return *this;
}


//------------------------------------------------------------------------------
ShaderBindingInfo& ShaderBindingInfo::SetBindingElemCount(const int count) {
    AE_BASE_ASSERT_LESS_EQUALS(1, count);
    bindingElemCount_ = count;
    return *this;
}

} // namespace gfx_low
} // namespace ae
// EOF
