// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/ResourceMemoryRegion.hpp>
#include <ae/gfx_low/VertexBufferLayoutInfo.hpp>

namespace ae {
namespace gfx_low {
class Device;
class BufferResource;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// VertexBufferView オブジェクト作成に必要な情報。
class VertexBufferViewCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// 属する Device オブジェクトのポインタ。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須）
    VertexBufferViewCreateInfo& SetDevice(gfx_low::Device* device) {
        device_.Reset(device);
        return *this;
    }

    /// 対象となる BufferResource のポインタ。（初期値：nullptr）
    BufferResource* Resource() const { return resource_.Get(); }

    /// BufferResource の設定。（設定必須）
    VertexBufferViewCreateInfo& SetResource(
        gfx_low::BufferResource* imageResource) {
        resource_.Reset(imageResource);
        return *this;
    }

    /// 参照するデータの範囲。（初期値：デフォルトコンストラクタの値）
    ResourceMemoryRegion Region() const { return region_; }

    /// Region() の設定。
    VertexBufferViewCreateInfo& SetRegion(const ResourceMemoryRegion& region) {
        region_ = region;
        return *this;
    }

    /// レイアウト情報。（初期値： デフォルトコンストラクタの値）
    VertexBufferLayoutInfo LayoutInfo() const { return layoutInfo_; }

    /// LayoutInfo() の設定。
    VertexBufferViewCreateInfo& SetLayoutInfo(
        const VertexBufferLayoutInfo& info) {
        layoutInfo_ = info;
        return *this;
    }
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    base::Pointer<gfx_low::BufferResource> resource_;
    ResourceMemoryRegion region_;
    VertexBufferLayoutInfo layoutInfo_;
};

} // namespace gfx_low
} // namespace ae
// EOF
