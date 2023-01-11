// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// RenderTargetImage・DepthStencilImage のロード操作を示す列挙値。
enum class AttachmentLoadOp
{
    /// 無効値。
    Invalid,

    /// Load も Clear もしない。ブレンドせず書き込むだけの場合に使用。
    DontCare,

    /// イメージの値を読み込む。
    Load,

    /// クリアカラーの値を読み込む。
    Clear,

    TERM,
};

} // namespace ae::gfx_low
// EOF
