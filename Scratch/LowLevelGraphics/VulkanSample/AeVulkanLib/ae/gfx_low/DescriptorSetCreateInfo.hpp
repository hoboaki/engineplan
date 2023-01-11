// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/DescriptorSetSpecInfo.hpp>

namespace ae::gfx_low {
class Device;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// DescriptorSet オブジェクト作成に必要な情報。
class DescriptorSetCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// 属する Device。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須）
    DescriptorSetCreateInfo& SetDevice(gfx_low::Device* device)
    {
        device_.Reset(device);
        return *this;
    }

    /// 仕様情報。（初期値：デフォルトコンストラクタの値）
    DescriptorSetSpecInfo SpecInfo() const { return specInfo_; }

    /// SpecInfo() の設定。
    DescriptorSetCreateInfo& SetSpecInfo(const DescriptorSetSpecInfo& info)
    {
        specInfo_ = info;
        return *this;
    }
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    DescriptorSetSpecInfo specInfo_;
};

} // namespace ae::gfx_low
// EOF
