// 文字コード：UTF-8
#pragma once

#include <ae/base/Extent3i.hpp>
#include <ae/base/Pointer.hpp>
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

/// ImageResource の作成に必要な情報。
class ImageResourceCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// 属する Device オブジェクトのポインタ。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須） 
    ImageResourceCreateInfo& SetDevice(gfx_low::Device* device) {
        device_.Reset(device);
        return *this;
    }

    /// イメージ範囲。（初期値：0,0,0） 
    base::Extent3i Extent() const { return extent_; }

    /// 2次元用 Extent() の設定。
    ImageResourceCreateInfo& SetExtent(const base::Extent2iPod& extent) {
        extent_ = base::Extent3i(extent, 1);
        return *this;
    }

    /// Extent() の設定。
    /// @details 2次元イメージの場合は depth に 1 を入れてください。
    ImageResourceCreateInfo& SetExtent(const base::Extent3iPod& extent)
    {
        extent_ = extent;
        return *this;
    }

    /// イメージデータのメモリアドレス。（初期値：IsValid() == false なアドレス） 
    ResourceMemoryAddress DataAddress() const { return dataAddress_; }

    /// DataAddress() の設定。 
    ImageResourceCreateInfo& SetDataAddress(
        const ResourceMemoryAddress& dataAddress)
    {
        dataAddress_ = dataAddress;
        return *this;
    }

    //@}

    /// @name 内部処理用関数群
    //@{
    /// VkImage オブジェクト。こちらが指定されている場合はこれをそのまま使う。
    ::vk::Image* ImagePtr_() const { return imagePtr_.Get(); }
    ImageResourceCreateInfo& SetImagePtr_(::vk::Image* imagePtr) {
        imagePtr_.Reset(imagePtr);
        return *this;
    }
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    base::Extent3i extent_;
    ResourceMemoryAddress dataAddress_;
    base::Pointer<::vk::Image> imagePtr_;
};

} // namespace gfx_low
} // namespace ae
// EOF
