// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// イメージのピクセルの並び方。
enum class ImageResourceTiling
{
    /// 無効値。
    Invalid,

    /// X=0から1つずつ1行ごとに並び方。
    Linear,

    /// GPUが扱いやすい並び方。
    Optimal,

    TERM,
};

} // namespace gfx_low
} // namespace ae
// EOF
