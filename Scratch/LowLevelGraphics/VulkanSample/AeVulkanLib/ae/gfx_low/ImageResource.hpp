// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class Device;
class ImageResourceCreateInfo;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

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
    const ::vk::Image& NativeObject_() const { return nativeObject_; }
    ::vk::Format NativeFormat_() const { return nativeFormat_; }
    int MipLevels_() const { return mipLevels_; }
    int ArrayLength_() const { return arrayLength_; }
    bool IsCubeMapImage_() const { return isCubeMapImage_; }
    //@}

private:
    gfx_low::Device& device_;
    ::vk::Image nativeObject_;
    ::vk::Format nativeFormat_;
    int mipLevels_;
    int arrayLength_;
    /// ImagePtr を使って作ったか。
    bool isCreatedByNativeObjectPtr_;
    bool isCubeMapImage_;
};

} // namespace ae::gfx_low
// EOF
