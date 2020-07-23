// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class Device;
class RenderTargetViewCreateInfo;
}
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// レンダリングパイプラインにおける１枚の描画対象を扱うデスクリプタ。
class RenderTargetView {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    RenderTargetView(const RenderTargetViewCreateInfo& createInfo);
    ~RenderTargetView();
    //@}

    /// @name プロパティ
    //@{
    /// 所属する Device。
    gfx_low::Device& Device() const { return device_; }
    //@}

private:
    gfx_low::Device& device_;
    ::vk::ImageView imageView_;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
