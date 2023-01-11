// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/base/Vector4.hpp>
#include <ae/gfx_low/LogicOp.hpp>

namespace ae::gfx_low {
class RenderTargetBlendInfo;
}

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// パイプラインのブレンド処理に関する情報。
/// @details
/// ・論理演算の設定について
/// DirectX 12 では RenderTargetBlendInfo の単位で可能、
/// Vulkan では不可能だったため制限の厳しいほうにあわせた。
class PipelineBlendInfo {
public:
    /// @name プロパティ
    //@{
    /// 論理演算を有効にするか。（初期値：false）
    bool LogicOpEnable() const { return logicOpEnable_; }

    /// LogicOpEnable() の設定。
    PipelineBlendInfo& SetLogicOpEnable(bool enable)
    {
        logicOpEnable_ = enable;
        return *this;
    }

    /// 論理演算の演算方式。（初期値：Clear）
    gfx_low::LogicOp LogicOp() const { return logicOp_; }

    /// LogicOp() の設定。
    PipelineBlendInfo& SetLogicOp(gfx_low::LogicOp op);

    /// ブレンド係数で使われる定数値。（初期値：0）
    base::Vector4Pod BlendConstant() const { return blendConstant_; }

    /// BlendConstant() の設定。
    PipelineBlendInfo& SetBlendConstant(const base::Vector4Pod& constant)
    {
        blendConstant_ = constant;
        return *this;
    }

    /// 各 RenderTarget 毎の BlendInfo の配列ポインタ。（初期値：nullptr）
    const RenderTargetBlendInfo* RenderTargetBlendInfos() const
    {
        return renderTargetBlendInfos_.Get();
    }

    /// RenderTargetBlendInfos() の設定。
    /// @param infos RenderPassSpecInfo::RenderTargetCount() 長の配列ポインタ。
    PipelineBlendInfo& SetRenderTargetBlendInfos(
        const RenderTargetBlendInfo* infos)
    {
        renderTargetBlendInfos_.Reset(infos);
        return *this;
    }
    //@}

private:
    base::Pointer<const RenderTargetBlendInfo> renderTargetBlendInfos_;
    base::Vector4Pod blendConstant_ = {};
    gfx_low::LogicOp logicOp_ = LogicOp::Clear;
    bool logicOpEnable_ = false;
};

} // namespace ae::gfx_low
// EOF
