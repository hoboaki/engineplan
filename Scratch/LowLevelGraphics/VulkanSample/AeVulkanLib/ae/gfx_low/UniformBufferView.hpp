// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/ResourceMemoryRegion.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class BufferResource;
class Device;
class UniformBufferViewCreateInfo;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ユニフォームバッファ用ビューデスクリプタ。
class UniformBufferView {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    UniformBufferView(const UniformBufferViewCreateInfo& createInfo);
    ~UniformBufferView();
    //@}

    /// @name プロパティ
    //@{
    /// 所属する Device。
    gfx_low::Device& Device() const { return device_; }
    //@}

    /// @name 内部処理用機能
    //@{
    BufferResource& BufferResource_() { return bufferResource_; }
    const BufferResource& BufferResource_() const { return bufferResource_; }
    ResourceMemoryRegion Region_() const { return region_; }
    //@}

private:
    gfx_low::Device& device_;
    gfx_low::BufferResource& bufferResource_;
    const ResourceMemoryRegion region_;
};

} // namespace ae::gfx_low
// EOF
