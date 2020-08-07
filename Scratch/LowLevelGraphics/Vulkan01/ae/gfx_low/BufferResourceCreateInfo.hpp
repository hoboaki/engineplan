// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/BufferResourceSpecInfo.hpp>
#include <ae/gfx_low/ResourceMemoryAddress.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class Device;
}
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// BufferResource の作成に必要な情報。
class BufferResourceCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// 属する Device オブジェクトのポインタ。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須） 
    BufferResourceCreateInfo& SetDevice(gfx_low::Device* device) {
        device_.Reset(device);
        return *this;
    }

    /// データ構造に関する仕様情報。（初期値：デフォルトコンストラクタ値）
    BufferResourceSpecInfo SpecInfo() const { return specInfo_; }

    /// SpecInfo() の設定。 
    BufferResourceCreateInfo& SetSpecInfo(
        const BufferResourceSpecInfo& specInfo)
    {
        specInfo_ = specInfo;
        return *this;
    }

    /// イメージデータのメモリアドレス。（初期値：IsValid() == false なアドレス） 
    ResourceMemoryAddress DataAddress() const { return dataAddress_; }

    /// DataAddress() の設定。 
    BufferResourceCreateInfo& SetDataAddress(
        const ResourceMemoryAddress& dataAddress)
    {
        dataAddress_ = dataAddress;
        return *this;
    }

    //@}

    /// @name 内部処理用関数群
    //@{
    /// VkBuffer オブジェクト。こちらが指定されている場合はこれをそのまま使う。
    ::vk::Buffer* BufferPtr_() const { return bufferPtr_.Get(); }
    BufferResourceCreateInfo& SetBufferPtr_(::vk::Buffer* bufferPtr) {
        bufferPtr_.Reset(bufferPtr);
        return *this;
    }

    /// VkBufferCreateInfo へ変換。
    ::vk::BufferCreateInfo NativeCreateInfo_() const;
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    BufferResourceSpecInfo specInfo_;
    ResourceMemoryAddress dataAddress_;
    base::Pointer<::vk::Buffer> bufferPtr_;
};

} // namespace gfx_low
} // namespace ae
// EOF
