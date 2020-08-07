// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class Device;
class GraphicsPipelineCreateInfo;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// グラフィックスパイプラインを扱うクラス。
class GraphicsPipeline {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    GraphicsPipeline(const GraphicsPipelineCreateInfo& createInfo);
    ~GraphicsPipeline();
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
    gfx_low::Device& device_;
    ::vk::Pipeline nativeObject_;
};

} // namespace gfx_low
} // namespace ae
// EOF
