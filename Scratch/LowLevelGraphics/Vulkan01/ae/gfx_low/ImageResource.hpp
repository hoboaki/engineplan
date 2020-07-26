// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class Device;
class ImageResourceCreateInfo;
}
}

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// イメージリソースを扱うクラス。
/// @details
/// イメージリソースはイメージのメモリ領域にまつわる機能を提供します。
/// イメージリソースを GPU から識別できるようにするには
/// 追加で ImageView や RenderTargetImageView 等のオブジェクトが必要です。
class ImageResource
{
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
    ::vk::Image& InternalInstance() { return image_; }
    //@}

private:
    gfx_low::Device& device_;
    ::vk::Image image_;
};

}
}  // namespace ae
// EOF
