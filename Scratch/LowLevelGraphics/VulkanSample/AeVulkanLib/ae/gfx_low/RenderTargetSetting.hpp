// 文字コード：UTF-8
#pragma once

#include <ae/base/Color4.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/AttachmentLoadOp.hpp>
#include <ae/gfx_low/AttachmentStoreOp.hpp>
#include <ae/gfx_low/ImageResourceState.hpp>

namespace ae::gfx_low {
class RenderTargetImageView;
}

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// RenderPass に設定する RenderTarget に関する設定情報。
class RenderTargetSetting {
public:
    /// @name プロパティ
    //@{
    /// RenderTarget イメージを指す RenderTargetImageView。（初期値：nullptr）
    gfx_low::RenderTargetImageView* RenderTargetImageView() const
    {
        return renderTargetImageView_.Get();
    }

    /// RenderTargetImageView() の設定。（設定必須）
    RenderTargetSetting& SetRenderTargetImageView(
        gfx_low::RenderTargetImageView* view)
    {
        renderTargetImageView_.Reset(view);
        return *this;
    }

    /// RenderPass 開始時点の RenderTarget イメージの状態。（初期値：Invalid）
    ImageResourceState InitialImageResourceState() const
    {
        return initialImageResourceState_;
    }

    /// InitialImageResourceState() の設定。（設定必須）
    RenderTargetSetting& SetInitialImageResourceState(ImageResourceState state);

    /// RenderPass 終了時点の RenderTarget イメージの状態。（初期値：Invalid）
    ImageResourceState FinalImageResourceState() const
    {
        return finalImageResourceState_;
    }

    /// FinalImageResourceState() の設定。（設定必須）
    RenderTargetSetting& SetFinalImageResourceState(ImageResourceState state);

    /// ロードオペレーション。（初期値：Invalid）
    AttachmentLoadOp LoadOp() const { return loadOp_; }

    /// LoadOp() の設定。（設定必須）
    RenderTargetSetting& SetLoadOp(AttachmentLoadOp loadOp);

    /// ストアオペレーション。（初期値：Invalid）
    AttachmentStoreOp StoreOp() const { return storeOp_; }

    /// StoreOp() の設定。（設定必須）
    RenderTargetSetting& SetStoreOp(AttachmentStoreOp storeOp);

    /// クリアカラー。（初期値：Zero()）
    base::Color4Pod ClearColor() const { return clearColor_; }

    /// ClearColor() の設定。
    RenderTargetSetting& SetClearColor(const base::Color4Pod& clearColor)
    {
        clearColor_ = clearColor;
        return *this;
    }
    //@}

private:
    base::Pointer<gfx_low::RenderTargetImageView> renderTargetImageView_;
    ImageResourceState initialImageResourceState_ = ImageResourceState::Invalid;
    ImageResourceState finalImageResourceState_ = ImageResourceState::Invalid;
    AttachmentLoadOp loadOp_ = AttachmentLoadOp::Invalid;
    AttachmentStoreOp storeOp_ = AttachmentStoreOp::Invalid;
    base::Color4Pod clearColor_ = base::Color4Pod::Zero();
};

} // namespace ae::gfx_low
// EOF
