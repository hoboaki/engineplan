// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumKeyArray.hpp>
#include <ae/gfx_low/DescriptorKind.hpp>
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
        Device* device,
        const DescriptorSetSpecInfo& info);
    ~InternalDescriptorSetLayouts();
    //@}

    /// @name プロパティ
    //@{
    int DescriptorSetLayoutCount() const { return descriptorSetLayoutCount_; }

    const ::vk::DescriptorSetLayout* DescriptorSetLayouts() const {
        return &descriptorSetLayouts_[0];
    }

    /// 指定の DescriptorKind に対応する DescriptorSetLayouts のインデックス値を取得。
    /// @return 存在しない場合は負の値を返す。
    int DescriptorSetLayoutIndex(DescriptorKind kind) const;
    //@}

private:
    gfx_low::Device& device_;
    std::array<::vk::DescriptorSetLayout, DescriptorSetLayoutsCountMax>
        descriptorSetLayouts_;
    int descriptorSetLayoutCount_ = 0;
    base::EnumKeyArray<DescriptorKind, int> descriptorSetLayoutIndexes_;
};

} // namespace gfx_low
} // namespace ae
// EOF
