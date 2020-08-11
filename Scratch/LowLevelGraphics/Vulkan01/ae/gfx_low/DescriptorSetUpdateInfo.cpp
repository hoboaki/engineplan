// 文字コード：UTF-8
#include <ae/gfx_low/DescriptorSetUpdateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
DescriptorSetUpdateInfo& DescriptorSetUpdateInfo::SetUniformBufferInfos(
    const int count, const UniformBufferDescriptorInfo* infos) {
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    if (0 < count) {
        AE_BASE_ASSERT_POINTER(infos);
    }
    uniformBufferInfosCount_ = count;
    uniformBufferInfos_.Reset(infos);
    return *this;
}

} // namespace gfx_low
} // namespace ae
// EOF
