// 文字コード：UTF-8
#include <ae/gfx_low/DescriptorSetUpdateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
DescriptorSetUpdateInfo& DescriptorSetUpdateInfo::SetUniformBufferInfos(
    const int count,
    const UniformBufferDescriptorInfo* infos)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    if (0 < count) {
        AE_BASE_ASSERT_POINTER(infos);
    }
    uniformBufferInfoCount_ = count;
    uniformBufferInfos_.Reset(infos);
    return *this;
}

//------------------------------------------------------------------------------
DescriptorSetUpdateInfo& DescriptorSetUpdateInfo::SetStorageBufferInfos(
    const int count,
    const StorageBufferDescriptorInfo* infos)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    if (0 < count) {
        AE_BASE_ASSERT_POINTER(infos);
    }
    storageBufferInfoCount_ = count;
    storageBufferInfos_.Reset(infos);
    return *this;
}

//------------------------------------------------------------------------------
DescriptorSetUpdateInfo& DescriptorSetUpdateInfo::SetSampledImageInfos(
    const int count,
    const SampledImageDescriptorInfo* infos)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    if (0 < count) {
        AE_BASE_ASSERT_POINTER(infos);
    }
    sampledImageInfoCount_ = count;
    sampledImageInfos_.Reset(infos);
    return *this;
}

//------------------------------------------------------------------------------
DescriptorSetUpdateInfo& DescriptorSetUpdateInfo::SetStorageImageInfos(
    const int count,
    const StorageImageDescriptorInfo* infos)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    if (0 < count) {
        AE_BASE_ASSERT_POINTER(infos);
    }
    storageImageInfoCount_ = count;
    storageImageInfos_.Reset(infos);
    return *this;
}

//------------------------------------------------------------------------------
DescriptorSetUpdateInfo& DescriptorSetUpdateInfo::SetSamplerInfos(
    const int count,
    const SamplerDescriptorInfo* infos)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    if (0 < count) {
        AE_BASE_ASSERT_POINTER(infos);
    }
    samplerInfoCount_ = count;
    samplerInfos_.Reset(infos);
    return *this;
}

} // namespace ae::gfx_low
// EOF
