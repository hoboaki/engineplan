// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/ResourceMemoryAddress.hpp>
#include <ae/gfx_low/SdkHeader.hpp>
#include <ae/gfx_low/ShaderModuleResourceSpecInfo.hpp>

namespace ae::gfx_low {
class Device;
}

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ShaderModuleResource の作成に必要な情報。
class ShaderModuleResourceCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// 属する Device オブジェクトのポインタ。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須）
    ShaderModuleResourceCreateInfo& SetDevice(gfx_low::Device* device)
    {
        device_.Reset(device);
        return *this;
    }

    /// データ構造に関する仕様情報。（初期値：デフォルトコンストラクタ値）
    ShaderModuleResourceSpecInfo SpecInfo() const { return specInfo_; }

    /// SpecInfo() の設定。
    ShaderModuleResourceCreateInfo& SetSpecInfo(
        const ShaderModuleResourceSpecInfo& specInfo)
    {
        specInfo_ = specInfo;
        return *this;
    }

    /// バイトコードデータのメモリアドレス。（初期値：IsValid() == false
    /// なアドレス）
    /// @details
    /// ShaderModuleResource
    /// 作成時点でこのアドレスに有効なバイトコードデータが可能されている必要があります。
    ResourceMemoryAddress DataAddress() const { return dataAddress_; }

    /// DataAddress() の設定。
    ShaderModuleResourceCreateInfo& SetDataAddress(
        const ResourceMemoryAddress& dataAddress)
    {
        dataAddress_ = dataAddress;
        return *this;
    }

    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    ShaderModuleResourceSpecInfo specInfo_;
    ResourceMemoryAddress dataAddress_;
};

} // namespace ae::gfx_low
// EOF
