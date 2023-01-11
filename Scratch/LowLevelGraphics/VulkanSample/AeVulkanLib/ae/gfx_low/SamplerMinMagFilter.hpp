// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// １枚のMipLevelテクスチャからサンプリングするときの値の取得方法。
enum class SamplerMinMagFilter
{
    /// 無効値。
    Invalid,

    /// 最寄りのサンプル値をそのまま取得。
    Nearest,

    /// 複数のサンプル値を補間して取得。
    Linear,

    TERM,
};

} // namespace ae::gfx_low
// EOF
