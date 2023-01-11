// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/CompareOp.hpp>
#include <ae/gfx_low/StencilOpInfo.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// パイプラインのデプステスト・ステンシルテストに関する情報。
/// @todo DepthBoundsTest の情報。
class PipelineDepthStencilInfo {
public:
    /// @name プロパティ
    //@{
    /// デプステストを有効にするか。（初期値：false）
    bool DepthTestEnable() const { return depthTestEnable_; }

    /// DepthTestEnable() の設定。
    PipelineDepthStencilInfo& SetDepthTestEnable(bool enable)
    {
        depthTestEnable_ = enable;
        return *this;
    }

    /// デプスバッファへの書き込みを有効にするか。（初期値：false）
    bool DepthWriteEnable() const { return depthWriteEnable_; }

    /// DepthWriteEnable() の設定。
    PipelineDepthStencilInfo& SetDepthWriteEnable(bool enable)
    {
        depthWriteEnable_ = enable;
        return *this;
    }

    /// デプステストの比較演算。（初期値：Always）
    CompareOp DepthCompareOp() const { return depthCompareOp_; }

    /// DepthCompareOp() の設定。
    PipelineDepthStencilInfo& SetDepthCompareOp(CompareOp op);

    /// ステンシルテストを有効にするｋ。（初期値：false）
    bool StencilTestEnable() const { return stencilTestEnable_; }

    /// StencilTestEnable() の設定。
    PipelineDepthStencilInfo& SetStencilTestEnable(bool enable)
    {
        stencilTestEnable_ = enable;
        return *this;
    }

    /// ステンシル値のリードマスク。（初期値：0）
    uint8_t StencilReadMask() const { return stencilReadMask_; }

    /// StencilReadMask() の設定。
    PipelineDepthStencilInfo& SetStencilReadMask(uint8_t mask)
    {
        stencilReadMask_ = mask;
        return *this;
    }

    /// ステンシル値のライトマスク。（初期値：0）
    uint8_t StencilWriteMask() const { return stencilWriteMask_; }

    /// StencilWriteMask() の設定。
    PipelineDepthStencilInfo& SetStencilWriteMask(uint8_t mask)
    {
        stencilWriteMask_ = mask;
        return *this;
    }

    /// ステンシルの参照値。（初期値：0）
    uint8_t StencilReference() const { return stencilReference_; }

    /// StencilReference() の設定。
    PipelineDepthStencilInfo& SetStencilReference(uint8_t value)
    {
        stencilReference_ = value;
        return *this;
    }

    /// 表面に対するステンシル演算情報。（初期値：デフォルトコンストラクタの値）
    StencilOpInfo FrontFaceStencilOpInfo() const
    {
        return frontFaceStencilOpInfo_;
    }

    /// FrontFaceStencilOpInfo() の設定。
    PipelineDepthStencilInfo& SetFrontFaceStencilOpInfo(
        const StencilOpInfo& info)
    {
        frontFaceStencilOpInfo_ = info;
        return *this;
    }

    /// 裏面に対するステンシル演算情報。（初期値：デフォルトコンストラクタの値）
    StencilOpInfo BackFaceStencilOpInfo() const
    {
        return backFaceStencilOpInfo_;
    }

    /// BackFaceStencilOpInfo() の設定。
    PipelineDepthStencilInfo& SetBackFaceStencilOpInfo(
        const StencilOpInfo& info)
    {
        backFaceStencilOpInfo_ = info;
        return *this;
    }
    //@}

private:
    StencilOpInfo frontFaceStencilOpInfo_;
    StencilOpInfo backFaceStencilOpInfo_;
    CompareOp depthCompareOp_ = CompareOp::Never;
    uint8_t stencilReadMask_ = 0;
    uint8_t stencilWriteMask_ = 0;
    uint8_t stencilReference_ = 0;
    bool depthTestEnable_ = false;
    bool depthWriteEnable_ = false;
    bool stencilTestEnable_ = false;
};

} // namespace ae::gfx_low
// EOF
