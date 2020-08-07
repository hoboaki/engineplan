// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>

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

    /// 参照するデータアドレスのオフセット値。（初期値：0）
    size_t Offset() const { return offset_; }

    /// Offset() の設定。
    /// @param offset [0, Resource() のデータサイズ)
    UniformBufferViewCreateInfo& SetOffset(size_t offset) {
        offset_ = offset;
        return *this;
    }

    /// 参照するデータのオフセットアドレスからのサイズ。 （初期値：0）
    size_t Size() const { return size_; }

    /// Size() の設定
    /// @param size Offset() + size が Resource() のデータサイズ以下となる値。
    UniformBufferViewCreateInfo& SetSize(size_t size)
    {
        size_ = size;
        return *this;;
    }


private:
    base::Pointer<gfx_low::Device> device_;
    base::Pointer<gfx_low::BufferResource> resource_;
    size_t offset_ = 0;
    size_t size_ = 0;
    
};

} // namespace gfx_low
} // namespace ae
// EOF
