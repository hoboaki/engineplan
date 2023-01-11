// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/ImageResourceSpecInfo.hpp>
#include <ae/gfx_low/ImageResourceState.hpp>
#include <ae/gfx_low/ResourceMemoryAddress.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class Device;
}

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ImageResource の作成に必要な情報。
class ImageResourceCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// 属する Device オブジェクトのポインタ。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須）
    ImageResourceCreateInfo& SetDevice(gfx_low::Device* device)
    {
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

    /// イメージデータのメモリアドレス。（初期値：IsValid() == false
    /// なアドレス）
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
    /// VkImage
    /// オブジェクト。こちらが指定されている場合はこれをそのまま使う。（初期値：nullptr）
    ::vk::Image* NativeObjectPtr_() const { return nativeObjectPtr_.Get(); }

    /// NativeObjectPtr_() の設定。
    /// @details 有効なオブジェクトを設定した場合は NativeFormat_()
    /// も設定する必要があります。
    ImageResourceCreateInfo& SetNativeObjectPtr_(::vk::Image* nativeObjectPtr)
    {
        nativeObjectPtr_.Reset(nativeObjectPtr);
        return *this;
    }

    /// NativeObjectPtr_() で指定した VkImage
    /// オブジェクトのフォーマット。（初期値：eUndefined）
    ::vk::Format NativeFormat_() const { return nativeFormat_; }

    /// NativeFormat_() の設定。
    ImageResourceCreateInfo& SetNativeFormat_(::vk::Format format)
    {
        nativeFormat_ = format;
        return *this;
    }

    /// NativeObjectPtr_() で指定した VkImage
    /// オブジェクトのミップマップレベル数。（初期値：1）
    int NativeObjectArrayLength_() const { return nativeObjectArrayLength_; }

    /// NativeObjectArrayLength_() の設定。
    /// @param levels 1以上。
    ImageResourceCreateInfo& SetNativeObjectArrayLength_(int arrayLength);

    /// NativeObjectPtr_() で指定した VkImage
    /// オブジェクトのミップマップレベル数。（初期値：1）
    int NativeObjectMipLevels_() const { return nativeObjectMipLevels_; }

    /// NativeObjectMipLevels_() の設定。
    /// @param levels 1以上。
    ImageResourceCreateInfo& SetNativeObjectMipLevels_(int levels);

    /// NativeObjectPtr_() で指定した VkImage オブジェクトがキューブイメージか。
    bool IsNativeObjectCubeImage_() const { return isNativeObjectCubeImage_; }

    /// IsNativeObjectCubeImage_() の設定。
    ImageResourceCreateInfo& SetIsNativeObjectCubeImage_(bool isCubeImage)
    {
        isNativeObjectCubeImage_ = isCubeImage;
        return *this;
    }

    /// VkImageCreateInfo へ変換。
    ::vk::ImageCreateInfo NativeCreateInfo_() const;
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    ImageResourceSpecInfo specInfo_;
    ResourceMemoryAddress dataAddress_;
    base::Pointer<::vk::Image> nativeObjectPtr_;
    ::vk::Format nativeFormat_ = ::vk::Format::eUndefined;
    int nativeObjectMipLevels_ = 1;
    int nativeObjectArrayLength_ = 1;
    bool isNativeObjectCubeImage_ = false;
};

} // namespace ae::gfx_low
// EOF
