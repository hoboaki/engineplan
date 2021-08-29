// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/ResourceMemoryRegion.hpp>

namespace ae {
namespace gfx_low {
class Device;
class BufferResource;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// UniformBufferView オブジェクト作成に必要な情報。
class UniformBufferViewCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// 属する Device オブジェクトのポインタ。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須）
    UniformBufferViewCreateInfo& SetDevice(gfx_low::Device* device) {
        device_.Reset(device);
        return *this;
    }

    /// 対象となる BufferResource のポインタ。（初期値：nullptr）
    BufferResource* Resource() const { return resource_.Get(); }

    /// BufferResource の設定。（設定必須）
    UniformBufferViewCreateInfo& SetResource(
        gfx_low::BufferResource* imageResource) {
        resource_.Reset(imageResource);
        return *this;
    }

    /// 参照するデータの範囲。（初期値：デフォルトコンストラクタの値）
    ResourceMemoryRegion Region() const { return region_; }

    /// Region() の設定。
    UniformBufferViewCreateInfo& SetRegion(const ResourceMemoryRegion& region) {
        region_ = region;
        return *this;
    }
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    base::Pointer<gfx_low::BufferResource> resource_;
    ResourceMemoryRegion region_;
};

} // namespace gfx_low
} // namespace ae
// EOF
