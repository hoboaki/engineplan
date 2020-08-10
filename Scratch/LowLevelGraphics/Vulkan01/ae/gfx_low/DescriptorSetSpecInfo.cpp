// 文字コード：UTF-8
#include <ae/gfx_low/DescriptorSetSpecInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
DescriptorSetSpecInfo& DescriptorSetSpecInfo::SetUniformBufferInfosCount(
    const int count) {
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    uniformBufferInfosCount_ = count;
    return *this;
}

//------------------------------------------------------------------------------
DescriptorSetSpecInfo& DescriptorSetSpecInfo::SetStorageBufferInfosCount(
    const int count) {
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    storageBufferInfosCount_ = count;
    return *this;
}

//------------------------------------------------------------------------------
DescriptorSetSpecInfo& DescriptorSetSpecInfo::SetSampledImageInfosCount(
    const int count) {
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    sampledImageInfosCount_ = count;
    return *this;
}

//------------------------------------------------------------------------------
DescriptorSetSpecInfo& DescriptorSetSpecInfo::SetStorageImageInfosCount(
    const int count) {
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    storageImageInfosCount_ = count;
    return *this;
}

//------------------------------------------------------------------------------
DescriptorSetSpecInfo& DescriptorSetSpecInfo::SetSamplerInfosCount(
    const int count) {
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    samplerInfosCount_ = count;
    return *this;
}

} // namespace gfx_low
} // namespace ae
// EOF
