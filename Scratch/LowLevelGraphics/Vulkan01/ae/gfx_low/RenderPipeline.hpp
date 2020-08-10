// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkHeader.hpp>
#include <array>

namespace ae {
namespace gfx_low {
class Device;
class RenderPipelineCreateInfo;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// レンダーパイプラインを扱うクラス。
class RenderPipeline {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    RenderPipeline(const RenderPipelineCreateInfo& createInfo);
    ~RenderPipeline();
    //@}

    /// @name プロパティ
    //@{
    /// 所属する Device。
    gfx_low::Device& Device() const { return device_; }
    //@}

    /// @name 内部処理用機能
    //@{
    ::vk::Pipeline& NativeObject_() { return nativeObject_; }
    //@}

private:
    static constexpr int DescriptorSetLayoutsCountMax_ = 3;

    gfx_low::Device& device_;
    std::array<::vk::DescriptorSetLayout, DescriptorSetLayoutsCountMax_>
        descriptorSetLayouts_;
    ::vk::PipelineLayout pipelineLayout_;
    ::vk::Pipeline nativeObject_;
    int descriptorSetLayoutsCount_ = 0;
};

} // namespace gfx_low
} // namespace ae
// EOF
