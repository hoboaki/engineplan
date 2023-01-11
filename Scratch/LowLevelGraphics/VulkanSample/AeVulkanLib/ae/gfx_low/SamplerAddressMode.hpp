// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// テクスチャサンプリング時のサンプリングアドレスの決め方。
enum class SamplerAddressMode
{
    /// 無効値。
    Invalid,

    /// 0 ～ 1 の範囲で繰り返す。
    Repeat,

    /// 0 ～ 1 は 0 ～ 1 で、1 ～ 2 は 1 ～ 0 に、といったように交互に反転する。
    MirroredRepeat,

    /// 0より小さい値は0に、1より大きい値は1にクランプする。
    ClampToEdge,

    /// 0より小さい値や1より大きい値の場合　BorderColor プロパティで指定された色をサンプリング結果の値として使用する。
    ClampToBorder,

    TERM,
};

} // namespace ae::gfx_low
// EOF
