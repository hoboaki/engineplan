// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/BlendFactor.hpp>
#include <ae/gfx_low/BlendOp.hpp>
#include <ae/gfx_low/RenderTargetComponentBitSet.hpp>

namespace ae::gfx_low {
class RenderTargetBlendInfo;
}

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// １つの RenderTarget に設定されるブレンド処理に関する情報。
class RenderTargetBlendInfo {
public:
    /// @name プロパティ
    //@{
    /// ブレンド演算を有効にするか。（初期値：false）
    bool BlendOpEnable() const { return blendOpEnable_; }

    /// BlendOpEnable() の設定。
    RenderTargetBlendInfo& SetBlendOpEnable(bool enable)
    {
        blendOpEnable_ = enable;
        return *this;
    }

    /// SrcColor に対するブレンド係数。（初期値：Zero）
    BlendFactor SrcColorBlendFactor() const { return srcColorBlendFactor_; }

    /// SrcColorBlendFactor() の設定。
    RenderTargetBlendInfo& SetSrcColorBlendFactor(BlendFactor op);

    /// DstColor に対するブレンド係数。（初期値：Zero）
    BlendFactor DstColorBlendFactor() const { return dstColorBlendFactor_; }

    /// DstColorBlendFactor() の設定。
    RenderTargetBlendInfo& SetDstColorBlendFactor(BlendFactor op);

    /// カラーブレンド演算の演算方式。（初期値：Add）
    BlendOp ColorBlendOp() const { return colorBlendOp_; }

    /// ColorBlendOp() の設定。
    RenderTargetBlendInfo& SetColorBlendOp(BlendOp op);

    /// SrcAlpha に対するブレンド係数。（初期値：Zero）
    BlendFactor SrcAlphaBlendFactor() const { return srcAlphaBlendFactor_; }

    /// SrcAlphaBlendFactor() の設定。
    RenderTargetBlendInfo& SetSrcAlphaBlendFactor(BlendFactor op);

    /// DstAlpha に対するブレンド係数。（初期値：Zero）
    BlendFactor DstAlphaBlendFactor() const { return dstAlphaBlendFactor_; }

    /// DstAlphaBlendFactor() の設定。
    RenderTargetBlendInfo& SetDstAlphaBlendFactor(BlendFactor op);

    /// カラーブレンド演算の演算方式。（初期値：Add）
    BlendOp AlphaBlendOp() const { return alphaBlendOp_; }

    /// AlphaBlendOp() の設定。
    RenderTargetBlendInfo& SetAlphaBlendOp(BlendOp op);

    /// 書き込む要素のマスク。（初期値：AllOn）
    RenderTargetComponentBitSet WriteMask() const { return writeMask_; }

    /// WriteMask() の設定。
    RenderTargetBlendInfo& SetWriteMask(
        const RenderTargetComponentBitSet& mask)
    {
        writeMask_ = mask;
        return *this;
    }
    //@}

private:
    RenderTargetComponentBitSet writeMask_ =
        RenderTargetComponentBitSet::AllOn();
    BlendFactor srcColorBlendFactor_ = BlendFactor::Zero;
    BlendFactor dstColorBlendFactor_ = BlendFactor::Zero;
    BlendOp colorBlendOp_ = BlendOp::Add;
    BlendFactor srcAlphaBlendFactor_ = BlendFactor::Zero;
    BlendFactor dstAlphaBlendFactor_ = BlendFactor::Zero;
    BlendOp alphaBlendOp_ = BlendOp::Add;
    bool blendOpEnable_ = false;
};

} // namespace ae::gfx_low
// EOF
