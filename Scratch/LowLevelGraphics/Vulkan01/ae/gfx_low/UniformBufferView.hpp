// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkHeader.hpp>
#include <ae/gfx_low/UniformBufferViewCreateinfo.hpp>

namespace ae {
namespace gfx_low {
class Device;
class UniformBufferViewCreateInfo;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

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
    size_t Offset_() { return offset_; }
    size_t Size_() { return size_; }
    //@}

private:
    gfx_low::Device& device_;
    gfx_low::BufferResource& bufferResource_;
    const size_t offset_;
    const size_t size_;
};

} // namespace gfx_low
} // namespace ae
// EOF
