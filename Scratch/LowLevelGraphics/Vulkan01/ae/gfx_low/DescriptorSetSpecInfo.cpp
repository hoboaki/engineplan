// 文字コード：UTF-8
#include <ae/gfx_low/DescriptorSetSpecInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/ShaderBindingInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
DescriptorSetSpecInfo& DescriptorSetSpecInfo::SetBindingInfos(
    const DescriptorKind kind, const int count, const ShaderBindingInfo* infosPtr) {
    AE_BASE_ASSERT_ENUM(kind, DescriptorKind);
    AE_BASE_ASSERT(kind != DescriptorKind::Invalid);
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    if (0 < count) {
        AE_BASE_ASSERT_POINTER(infosPtr);
    }

    infos_[kind].infosCount = count;
    infos_[kind].infos.Reset(infosPtr);
    return *this;
}

//------------------------------------------------------------------------------
int DescriptorSetSpecInfo::TotalBindingCount(
    const DescriptorKind kind) const {
    AE_BASE_ASSERT_ENUM(kind, DescriptorKind);
    AE_BASE_ASSERT(kind != DescriptorKind::Invalid);
    const auto& info = infos_[kind];
    int total = 0;
    for (int i = 0; i < info.infosCount; ++i) {
        total += info.infos.Get()[i].BindingElemCount();
    }
    return total;
}

} // namespace gfx_low
} // namespace ae
// EOF
