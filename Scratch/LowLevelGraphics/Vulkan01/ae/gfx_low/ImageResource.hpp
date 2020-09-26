// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class Device;
class ImageResourceCreateInfo;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// イメージリソースを扱うクラス。
/// @details
/// イメージリソースはイメージのメモリ領域にまつわる機能を提供します。
/// イメージリソースを GPU から識別できるようにするには
/// 追加で ImageView や RenderTargetImageView 等のオブジェクトが必要です。
class ImageResource {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    ImageResource(const ImageResourceCreateInfo& createInfo);
    ~ImageResource();
    //@}

    /// @name プロパティ
    //@{
    /// 所属する Device。
    gfx_low::Device& Device() const { return device_; }
    //@}

    /// @name 内部処理用機能
    //@{
    ::vk::Image& NativeObject_() { return nativeObject_; }
    ::vk::Format NativeFormat_() const { return nativeFormat_; }
    //@}

private:
    gfx_low::Device& device_;
    ::vk::Image nativeObject_;
    ::vk::Format nativeFormat_;
    /// ImagePtr を使って作ったか。
    bool isCreatedByNativeObjectPtr_;
};

} // namespace gfx_low
} // namespace ae
// EOF
