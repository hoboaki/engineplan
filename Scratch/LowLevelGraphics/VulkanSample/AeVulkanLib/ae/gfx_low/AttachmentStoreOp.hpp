// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// RenderTargetImage・DepthStencilImage のストア操作を示す列挙値。
enum class AttachmentStoreOp
{
    /// 無効値。
    Invalid,

    /// 何もしない。読み取るだけのときに指定。
    DontCare,

    /// イメージに値を書き込む。
    Store,

    TERM,
};

} // namespace ae::gfx_low
// EOF
