// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class DescriptorSetSpecInfo;
class Device;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// DescriptorSetLayout 郡を扱うクラス。
/// @details
/// Buffer, Image, Sampler の順番で DescriptorSet 番号を確保する。
class InternalDescriptorSetLayouts {
public:
    /// @name 定数
    //@{
    /// DescriptorSetLayout の最大数。
    static constexpr int DescriptorSetLayoutsCountMax = 3;
    //@}

    /// @name コンストラクタとデストラクタ
    //@{
    InternalDescriptorSetLayouts(
        Device* device, const DescriptorSetSpecInfo& info);
    ~InternalDescriptorSetLayouts();
    //@}

    /// @name プロパティ
    //@{
    int DescriptorSetLayoutsCount() const { return descriptorSetLayoutsCount_; }

    const ::vk::DescriptorSetLayout* DescriptorSetLayouts() const {
        return &descriptorSetLayouts_[0];
    }
    //@}

private:
    gfx_low::Device& device_;
    std::array<::vk::DescriptorSetLayout, DescriptorSetLayoutsCountMax>
        descriptorSetLayouts_;
    int descriptorSetLayoutsCount_ = 0;
};

} // namespace gfx_low
} // namespace ae
// EOF
