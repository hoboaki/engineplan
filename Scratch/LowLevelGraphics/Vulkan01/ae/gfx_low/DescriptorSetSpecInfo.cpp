// 文字コード：UTF-8
#include <ae/gfx_low/DescriptorSetSpecInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
DescriptorSetSpecInfo& DescriptorSetSpecInfo::SetUniformBufferCount(
    const int count) {
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    uniformBufferCount_ = count;
    return *this;
}

//------------------------------------------------------------------------------
DescriptorSetSpecInfo& DescriptorSetSpecInfo::SetStorageBufferCount(
    const int count) {
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    storageBufferCount_ = count;
    return *this;
}

//------------------------------------------------------------------------------
DescriptorSetSpecInfo& DescriptorSetSpecInfo::SetSampledImageCount(
    const int count) {
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    sampledImageCount_ = count;
    return *this;
}

//------------------------------------------------------------------------------
DescriptorSetSpecInfo& DescriptorSetSpecInfo::SetStorageImageCount(
    const int count) {
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    storageImageCount_ = count;
    return *this;
}

} // namespace gfx_low
} // namespace ae
// EOF
