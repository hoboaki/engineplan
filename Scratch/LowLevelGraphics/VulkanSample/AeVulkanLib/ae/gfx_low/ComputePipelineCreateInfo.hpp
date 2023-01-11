// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumKeyArray.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/DescriptorSetSpecInfo.hpp>
#include <ae/gfx_low/PipelineShaderInfo.hpp>

namespace ae::gfx_low {
class Device;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ComputePipeline オブジェクト作成に必要な情報。
class ComputePipelineCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// 属する Device オブジェクトのポインタ。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須）
    ComputePipelineCreateInfo& SetDevice(gfx_low::Device* device)
    {
        device_.Reset(device);
        return *this;
    }

    /// シェーダー情報。（初期値：デフォルトコンストラクタの値）
    PipelineShaderInfo ShaderInfo() const { return shaderInfo_; }

    /// ShaderInfo() の設定。（設定必須）
    ComputePipelineCreateInfo& SetShaderInfo(
        const PipelineShaderInfo& shaderInfo)
    {
        shaderInfo_ = shaderInfo;
        return *this;
    }

    /// DescriptorSet の仕様情報。 （初期値：デフォルトコンストラクタの値）
    gfx_low::DescriptorSetSpecInfo DescriptorSetSpecInfo() const
    {
        return descriptorSetSpecInfo_;
    }

    /// DescriptorSetSpecInfo() の設定。
    ComputePipelineCreateInfo& SetDescriptorSetSpecInfo(
        const gfx_low::DescriptorSetSpecInfo& info)
    {
        descriptorSetSpecInfo_ = info;
        return *this;
    }
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    PipelineShaderInfo shaderInfo_;
    gfx_low::DescriptorSetSpecInfo descriptorSetSpecInfo_;
};

} // namespace ae::gfx_low
// EOF
