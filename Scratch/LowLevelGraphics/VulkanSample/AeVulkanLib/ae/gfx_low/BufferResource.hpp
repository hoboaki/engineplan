// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class Device;
class BufferResourceCreateInfo;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// バッファリソースを扱うクラス。
/// @details
/// バッファリソースはユニフォームバッファや頂点バッファなど
/// バッファ系リソースのメモリ領域にまつわる機能を提供します。
/// バッファリソースを GPU から識別できるようにするには
/// 追加で BufferView のオブジェクトが必要です。
class BufferResource {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    BufferResource(const BufferResourceCreateInfo& createInfo);
    ~BufferResource();
    //@}

    /// @name プロパティ
    //@{
    /// 所属する Device。
    gfx_low::Device& Device() const { return device_; }
    //@}

    /// @name 内部処理用機能
    //@{
    ::vk::Buffer& NativeObject_() { return nativeObject_; }
    const ::vk::Buffer& NativeObject_() const { return nativeObject_; }
    //@}

private:
    gfx_low::Device& device_;
    ::vk::Buffer nativeObject_;
    /// NativeObjectPtr を使って作ったか。
    bool isCreatedByNativeObjectPtr_;
};

} // namespace ae::gfx_low
// EOF
