// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/InternalDescriptorSetLayouts.hpp>
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
    const ::vk::Pipeline NativeObject_() const { return nativeObject_; }

    ::vk::PipelineLayout PipelineLayout_() const { return pipelineLayout_; }
    //@}

private:
    gfx_low::Device& device_;
    InternalDescriptorSetLayouts descriptorSetLayouts_;
    ::vk::RenderPass renderPass_;
    ::vk::PipelineLayout pipelineLayout_;
    ::vk::Pipeline nativeObject_;
};

} // namespace gfx_low
} // namespace ae
// EOF
