// 文字コード：UTF-8
#include <ae/gfx_low/InternalPushConstantRanges.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/DescriptorSetSpecInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/DirectConstantInfo.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/ShaderBindingInfo.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
InternalPushConstantRanges::InternalPushConstantRanges(
    const DescriptorSetSpecInfo& info)
: pushConstantRangeCount_(info.DirectConstantInfoCount())
{
    // 内容チェック
    info.Validate_();

    // 情報生成
    for (int i = 0; i < pushConstantRangeCount_; ++i) {
        const auto& directConstantInfo = info.DirectConstantInfos()[i];
        auto& range = pushConstantRanges_[i];
        range.setOffset(uint32_t(totalSize_));
        range.setSize(uint32_t(directConstantInfo.Size()));
        range.setStageFlags(
            InternalEnumUtil::ToShaderStageFlags(directConstantInfo.Stages()));
        totalSize_ = directConstantInfo.Size();
    }
}

} // namespace ae::gfx_low
// EOF
