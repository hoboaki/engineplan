// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumKeyArray.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/GraphicsPipelineShaderStage.hpp>
#include <ae/gfx_low/PipelineShaderInfo.hpp>
#include <ae/gfx_low/PipelineRasterizerInfo.hpp>
#include <ae/gfx_low/PrimitiveTopologyKind.hpp>

namespace ae {
namespace gfx_low {
class Device;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// GraphicsPipeline オブジェクト作成に必要な情報。
class GraphicsPipelineCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// 属する Device オブジェクトのポインタ。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須）
    GraphicsPipelineCreateInfo& SetDevice(gfx_low::Device* device) {
        device_.Reset(device);
        return *this;
    }

    /// 指定シェーダーステージのシェーダー情報。
    PipelineShaderInfo ShaderInfo(GraphicsPipelineShaderStage stage) const;

    /// ShaderInfo() の設定。
    GraphicsPipelineCreateInfo& SetShaderInfo(GraphicsPipelineShaderStage stage,
        const PipelineShaderInfo& shaderInfo);


    /// プリミティブトポロジの種類。（初期値：Invalid）
    gfx_low::PrimitiveTopologyKind PrimitiveTopologyKind() const {
        return primitiveTopologyKind_;
    }

    /// PrimitiveTopologyKind() の設定。
    GraphicsPipelineCreateInfo& SetPrimitiveTopologyKind(
        gfx_low::PrimitiveTopologyKind kind);

    /// ラスタライザ情報。（初期値：デフォルトコンストラクタの値）
    PipelineRasterizerInfo RasterizerInfo() const { return rasterizerInfo_; }

    /// RasterizerInfo() の設定。
    GraphicsPipelineCreateInfo& SetRasterizerInfo(
        const PipelineRasterizerInfo& info)
    {
        rasterizerInfo_ = info;
        return *this;
    }
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    base::EnumKeyArray<GraphicsPipelineShaderStage, PipelineShaderInfo>
        shaderInfos_;
    gfx_low::PrimitiveTopologyKind primitiveTopologyKind_ =
        PrimitiveTopologyKind::Invalid;
    PipelineRasterizerInfo rasterizerInfo_;
};

} // namespace gfx_low
} // namespace ae
// EOF
