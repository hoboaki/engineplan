// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// CommandBuffer の状態を表す列挙値。
enum class CommandBufferState
{
    /// 初期状態。
    Initial,

    /// 記録中の状態。
    Recording,

    /// 記録が完了している状態。
    Recorded,

    TERM,
};

} // namespace ae::gfx_low
// EOF
