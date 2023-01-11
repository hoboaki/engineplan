// 文字コード：UTF-8
#include <ae/gfx_low/DescriptorSetSpecInfo.hpp>

// includes
#include <ae/base/Math.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/DirectConstantInfo.hpp>
#include <ae/gfx_low/ShaderBindingInfo.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
DescriptorSetSpecInfo& DescriptorSetSpecInfo::SetBindingInfos(
    const DescriptorKind kind,
    const int count,
    const ShaderBindingInfo* infosPtr)
{
    AE_BASE_ASSERT_ENUM(kind, DescriptorKind);
    AE_BASE_ASSERT(kind != DescriptorKind::Invalid);
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    if (0 < count) {
        AE_BASE_ASSERT_POINTER(infosPtr);
    }

    bindingInfos_[kind].infoCount = count;
    bindingInfos_[kind].infos.Reset(infosPtr);
    return *this;
}

//------------------------------------------------------------------------------
int DescriptorSetSpecInfo::TotalBindingCount(const DescriptorKind kind) const
{
    AE_BASE_ASSERT_ENUM(kind, DescriptorKind);
    AE_BASE_ASSERT(kind != DescriptorKind::Invalid);
    const auto& info = bindingInfos_[kind];
    int total = 0;
    for (int i = 0; i < info.infoCount; ++i) {
        total += info.infos.Get()[i].ElemCount();
    }
    return total;
}

//------------------------------------------------------------------------------
int DescriptorSetSpecInfo::MaxBindingIndex(const DescriptorKind kind) const
{
    AE_BASE_ASSERT_ENUM(kind, DescriptorKind);
    AE_BASE_ASSERT(kind != DescriptorKind::Invalid);
    const auto& info = bindingInfos_[kind];
    int result = -1;
    for (int i = 0; i < info.infoCount; ++i) {
        result =
            ::ae::base::Math::Max(result, info.infos.Get()[i].BindingIndex());
    }
    return result;
}

//------------------------------------------------------------------------------
DescriptorSetSpecInfo& DescriptorSetSpecInfo::SetDirectConstantInfos(
    const int count,
    const DirectConstantInfo* infosPtr)
{
    AE_BASE_ASSERT_LESS_EQUALS(0, count);
    if (0 < count) {
        AE_BASE_ASSERT_POINTER(infosPtr);
    }

    directConstantInfoCount_ = count;
    directConstantInfos_.Reset(infosPtr);

    // 設定時の内容チェック
    Validate_();

    return *this;
}

//------------------------------------------------------------------------------
void DescriptorSetSpecInfo::Validate_() const
{
    ShaderBindingStageBitSet stages;
    if (0 < directConstantInfoCount_) {
        // Stage重複確認
        AE_BASE_ASSERT_POINTER(directConstantInfos_.Get());
        for (int i = 0; i < directConstantInfoCount_; ++i) {
            const auto& info = directConstantInfos_.Get()[i];
            AE_BASE_ASSERT_EQUALS((stages.bits_ & info.Stages().bits_), 0);
            stages.bits_ |= info.Stages().bits_;
        }
    }
}

} // namespace ae::gfx_low
// EOF
