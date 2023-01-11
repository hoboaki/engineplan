// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumKeyArray.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/DescriptorSetSpecInfo.hpp>
#include <ae/gfx_low/PipelineBlendInfo.hpp>
#include <ae/gfx_low/PipelineDepthStencilInfo.hpp>
#include <ae/gfx_low/PipelineRasterizerInfo.hpp>
#include <ae/gfx_low/PipelineShaderInfo.hpp>
#include <ae/gfx_low/PipelineVertexInputInfo.hpp>
#include <ae/gfx_low/PrimitiveTopologyKind.hpp>
#include <ae/gfx_low/RenderPassSpecInfo.hpp>
#include <ae/gfx_low/RenderPipelineShaderStage.hpp>

namespace ae::gfx_low {
class Device;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// RenderPipeline オブジェクト作成に必要な情報。
class RenderPipelineCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// 属する Device オブジェクトのポインタ。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須）
    RenderPipelineCreateInfo& SetDevice(gfx_low::Device* device)
    {
        device_.Reset(device);
        return *this;
    }

    /// RenderPass の仕様情報。 （初期値：デフォルトコンストラクタの値）
    gfx_low::RenderPassSpecInfo RenderPassSpecInfo() const
    {
        return renderPassSpecInfo_;
    }

    /// RenderPassSpecInfo() の設定。（設定必須）
    RenderPipelineCreateInfo& SetRenderPassSpecInfo(
        const gfx_low::RenderPassSpecInfo& info)
    {
        renderPassSpecInfo_ = info;
        return *this;
    }

    /// 指定シェーダーステージのシェーダー情報。（初期値：デフォルトコンストラクタの値）
    PipelineShaderInfo ShaderInfo(RenderPipelineShaderStage stage) const;

    /// ShaderInfo() の設定。（設定必須）
    RenderPipelineCreateInfo& SetShaderInfo(
        RenderPipelineShaderStage stage,
        const PipelineShaderInfo& shaderInfo);

    /// DescriptorSet の仕様情報。 （初期値：デフォルトコンストラクタの値）
    gfx_low::DescriptorSetSpecInfo DescriptorSetSpecInfo() const
    {
        return descriptorSetSpecInfo_;
    }

    /// DescriptorSetSpecInfo() の設定。
    RenderPipelineCreateInfo& SetDescriptorSetSpecInfo(
        const gfx_low::DescriptorSetSpecInfo& info)
    {
        descriptorSetSpecInfo_ = info;
        return *this;
    }

    /// 頂点入力情報。（初期値：デフォルトコンストラクタの値）
    PipelineVertexInputInfo VertexInputInfo() const { return vertexInputInfo_; }

    /// VertexInfo() の設定。
    RenderPipelineCreateInfo& SetVertexInputInfo(
        const PipelineVertexInputInfo& info)
    {
        vertexInputInfo_ = info;
        return *this;
    }

    /// プリミティブトポロジの種類。（初期値：Invalid）
    gfx_low::PrimitiveTopologyKind PrimitiveTopologyKind() const
    {
        return primitiveTopologyKind_;
    }

    /// PrimitiveTopologyKind() の設定。
    RenderPipelineCreateInfo& SetPrimitiveTopologyKind(
        gfx_low::PrimitiveTopologyKind kind);

    /// ラスタライザ情報。（初期値：デフォルトコンストラクタの値）
    PipelineRasterizerInfo RasterizerInfo() const { return rasterizerInfo_; }

    /// RasterizerInfo() の設定。
    RenderPipelineCreateInfo& SetRasterizerInfo(
        const PipelineRasterizerInfo& info)
    {
        rasterizerInfo_ = info;
        return *this;
    }

    /// デプステスト・ステンシルテスト情報。（初期値：デフォルトコンストラクタの値）
    PipelineDepthStencilInfo DepthStencilInfo() const
    {
        return depthStencilInfo_;
    }

    /// DepthStencilInfo() の設定。
    RenderPipelineCreateInfo& SetDepthStencilInfo(
        const PipelineDepthStencilInfo& info)
    {
        depthStencilInfo_ = info;
        return *this;
    }

    /// ブレンド処理の情報。（初期値：デフォルトコンストラクタの値）
    PipelineBlendInfo BlendInfo() const { return blendInfo_; }

    /// BlendInfo() の設定。
    RenderPipelineCreateInfo& SetBlendInfo(const PipelineBlendInfo& info)
    {
        blendInfo_ = info;
        return *this;
    }
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    gfx_low::RenderPassSpecInfo renderPassSpecInfo_;
    base::EnumKeyArray<RenderPipelineShaderStage, PipelineShaderInfo>
        shaderInfos_;
    gfx_low::DescriptorSetSpecInfo descriptorSetSpecInfo_;
    PipelineVertexInputInfo vertexInputInfo_;
    PipelineRasterizerInfo rasterizerInfo_;
    PipelineDepthStencilInfo depthStencilInfo_;
    PipelineBlendInfo blendInfo_;
    gfx_low::PrimitiveTopologyKind primitiveTopologyKind_ =
        PrimitiveTopologyKind::Invalid;
};

} // namespace ae::gfx_low
// EOF
