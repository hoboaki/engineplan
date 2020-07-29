// 文字コード：UTF-8
#pragma once

namespace {}

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// ImageResource の状態。
/// @details
/// ImageResource は使用する場面に応じて適切な状態に切り替える必要があります。
/// 例えば、RenderTargetImage として使う場合は RenderTargetImage
/// 状態に設定する必要がありますが 同じイメージを Present として使うためには
/// PresentSrc に切り替える必要があります。
enum class ImageResourceState {
    /// 無効値。
    Invalid,

    /// 特定の状態を示さない状態。
    Unknown,

    /// RenderPass の RenderTarget として Read/Write される状態。
    RenderTarget,

    /// Swapchain の Present 元として使われる状態。
    PresentSrc,

    /// RenderPass の DepthStencil として Read/Write される状態。
    // DepthStencil,

    /// RenderPass の DepthStencil として Read のみされる状態。
    // DepthStencilReadOnly,

    TERM,
};

}  // namespace gfx_low
}  // namespace ae
// EOF