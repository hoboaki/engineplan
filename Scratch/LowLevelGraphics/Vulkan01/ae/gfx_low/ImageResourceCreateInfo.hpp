// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class Device;
}
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// ImageResource の作成に必要な情報。
class ImageResourceCreateInfo
{
public:
    /// @name 属する Device オブジェクトのポインタ（設定必須、初期値：nullptr）
    //@{
    gfx_low::Device* Device() const { return device_.get(); }
    ImageResourceCreateInfo& SetDevice(gfx_low::Device* system) {
        device_.reset(system);
        return *this;
    }
    //@}

    /// @name 内部処理用関数群
    //@{
    /// VkImage オブジェクト。こちらが指定されている場合はこれをそのまま使う。
    ::vk::Image* InternalImagePtr() const { return imagePtr_.get(); }
    ImageResourceCreateInfo& InternalSetImagePtr(::vk::Image* imagePtr) {
        imagePtr_.reset(imagePtr);
        return *this;
    }
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    base::Pointer<::vk::Image> imagePtr_;
};

}
}  // namespace ae
// EOF
