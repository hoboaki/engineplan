// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumKeyArray.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class DescriptorSetSpecInfo;
class Device;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// PushConstantRange 郡を扱うクラス。
/// @details
/// Buffer, Image, Sampler の順番で DescriptorSet 番号を確保する。
class InternalPushConstantRanges {
public:
    /// @name 定数
    //@{
    /// PushConstantRange の最大数。
    static constexpr int PushConstantRangesCountMax = 3;
    //@}

    /// @name コンストラクタとデストラクタ
    //@{
    explicit InternalPushConstantRanges(const DescriptorSetSpecInfo& info);
    //@}

    /// @name プロパティ
    //@{
    int PushConstantRangeCount() const { return pushConstantRangeCount_; }

    const ::vk::PushConstantRange* PushConstantRanges() const
    {
        return &pushConstantRanges_[0];
    }
    //@}

private:
    const int pushConstantRangeCount_ = 0;
    size_t totalSize_ = {};
    std::array<::vk::PushConstantRange, PushConstantRangesCountMax>
        pushConstantRanges_ = {};
};

} // namespace ae::gfx_low
// EOF
