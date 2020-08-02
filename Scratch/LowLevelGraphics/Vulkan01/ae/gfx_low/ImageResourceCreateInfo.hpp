// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/ImageResourceSpecInfo.hpp>
#include <ae/gfx_low/ImageResourceState.hpp>
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

    /// データ構造に関する仕様情報。（初期値：デフォルトコンストラクタ値）
    ImageResourceSpecInfo SpecInfo() const { return specInfo_; }

    /// SpecInfo() の設定。 
    ImageResourceCreateInfo& SetSpecInfo(
        const ImageResourceSpecInfo& specInfo)
    {
        specInfo_ = specInfo;
        return *this;
    }

    /// 初期状態。（初期値：Unknown）
    ImageResourceState InitialState() const { return initialState_; }

    /// InitialState() の設定。 
    ImageResourceCreateInfo& SetInitialState(ImageResourceState state);

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

    /// VkImageCreateInfo へ変換。
    ::vk::ImageCreateInfo NativeCreateInfo_() const;
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    ImageResourceSpecInfo specInfo_;
    ImageResourceState initialState_ = ImageResourceState::Unknown;
    ResourceMemoryAddress dataAddress_;
    base::Pointer<::vk::Image> imagePtr_;
};

} // namespace gfx_low
} // namespace ae
// EOF
