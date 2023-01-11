// 文字コード：UTF-8
#pragma once

#include <ae/base/Color4.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/AttachmentLoadOp.hpp>
#include <ae/gfx_low/AttachmentStoreOp.hpp>
#include <ae/gfx_low/ImageResourceState.hpp>

namespace ae::gfx_low {
class DepthStencilImageView;
}

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// RenderPass に設定する DepthStencil に関する設定情報。
class DepthStencilSetting {
public:
    /// @name プロパティ
    //@{
    /// DepthStencil イメージを指す DepthStencilImageView。（初期値：nullptr）
    gfx_low::DepthStencilImageView* DepthStencilImageView() const
    {
        return depthStencilImageView_.Get();
    }

    /// DepthStencilImageView() の設定。（設定必須）
    DepthStencilSetting& SetDepthStencilImageView(
        gfx_low::DepthStencilImageView* view)
    {
        depthStencilImageView_.Reset(view);
        return *this;
    }

    /// RenderPass 開始時点の DepthStencil イメージの状態。（初期値：Invalid）
    ImageResourceState InitialImageResourceState() const
    {
        return initialImageResourceState_;
    }

    /// InitialImageResourceState() の設定。（設定必須）
    DepthStencilSetting& SetInitialImageResourceState(ImageResourceState state);

    /// RenderPass 終了時点の DepthStencil イメージの状態。（初期値：Invalid）
    ImageResourceState FinalImageResourceState() const
    {
        return finalImageResourceState_;
    }

    /// FinalImageResourceState() の設定。（設定必須）
    DepthStencilSetting& SetFinalImageResourceState(ImageResourceState state);

    /// デプスのロードオペレーション。（初期値：Invalid）
    AttachmentLoadOp DepthLoadOp() const { return depthLoadOp_; }

    /// DepthLoadOp() の設定。（設定必須）
    DepthStencilSetting& SetDepthLoadOp(AttachmentLoadOp loadOp);

    /// デプスのストアオペレーション。（初期値：Invalid）
    AttachmentStoreOp DepthStoreOp() const { return depthStoreOp_; }

    /// DepthStoreOp() の設定。（設定必須）
    DepthStencilSetting& SetDepthStoreOp(AttachmentStoreOp storeOp);

    /// デプスのクリア値。（初期値：1.0f）
    float DepthClearValue() const { return depthClearValue_; }

    /// DepthClearValue() の設定。
    /// @param clearValue [0.0f, 1.0f]
    DepthStencilSetting& SetDepthClearValue(float clearValue);

    /// ステンシルのロードオペレーション。（初期値：Invalid）
    AttachmentLoadOp StencilLoadOp() const { return stencilLoadOp_; }

    /// DepthLoadOp() の設定。（設定必須）
    DepthStencilSetting& SetStencilLoadOp(AttachmentLoadOp loadOp);

    /// ステンシルのストアオペレーション。（初期値：Invalid）
    AttachmentStoreOp StencilStoreOp() const { return stencilStoreOp_; }

    /// DepthStoreOp() の設定。（設定必須）
    DepthStencilSetting& SetStencilStoreOp(AttachmentStoreOp storeOp);

    /// ステンシルのクリア値。（初期値：0）
    int StencilClearValue() const { return stencilClearValue_; }

    /// StencilClearValue() の設定。
    /// @param clearValue [0, 0xFF]
    DepthStencilSetting& SetStencilClearValue(int clearValue);
    //@}

private:
    base::Pointer<gfx_low::DepthStencilImageView> depthStencilImageView_;
    ImageResourceState initialImageResourceState_ = ImageResourceState::Invalid;
    ImageResourceState finalImageResourceState_ = ImageResourceState::Invalid;
    AttachmentLoadOp depthLoadOp_ = AttachmentLoadOp::Invalid;
    AttachmentStoreOp depthStoreOp_ = AttachmentStoreOp::Invalid;
    AttachmentLoadOp stencilLoadOp_ = AttachmentLoadOp::Invalid;
    AttachmentStoreOp stencilStoreOp_ = AttachmentStoreOp::Invalid;
    float depthClearValue_ = 1.0f;
    int stencilClearValue_ = 0;
};

} // namespace ae::gfx_low
// EOF
