// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// 頂点属性のフォーマット。
/// @details
enum class VertexFormat
{
    /// 無効値。
    Invalid,

    // 8bit 系
    Sint8x1,
    Sint8x2,
    Sint8x3,
    Sint8x4,

    Snorm8x1,
    Snorm8x2,
    Snorm8x3,
    Snorm8x4,

    Uint8x1,
    Uint8x2,
    Uint8x3,
    Uint8x4,

    Unorm8x1,
    Unorm8x2,
    Unorm8x3,
    Unorm8x4,

    // 16bit 系
    Sfloat16x1,
    Sfloat16x2,
    Sfloat16x3,
    Sfloat16x4,

    Sint16x1,
    Sint16x2,
    Sint16x3,
    Sint16x4,

    Snorm16x1,
    Snorm16x2,
    Snorm16x3,
    Snorm16x4,

    Uint16x1,
    Uint16x2,
    Uint16x3,
    Uint16x4,

    Unorm16x1,
    Unorm16x2,
    Unorm16x3,
    Unorm16x4,

    // 32bit 系
    Sfloat32x1,
    Sfloat32x2,
    Sfloat32x3,
    Sfloat32x4,

    Sint32x1,
    Sint32x2,
    Sint32x3,
    Sint32x4,

    Uint32x1,
    Uint32x2,
    Uint32x3,
    Uint32x4,

    // 16bit パッキング
    UnormB4G4R4A4,

    // 32bit パッキング
    SnormR10G10B10A2,
    UnormR10G10B10A2,

    TERM,
};

} // namespace ae::gfx_low
// EOF
