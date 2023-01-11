// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// デスクリプタの種類を示す列挙値。
enum class DescriptorKind
{
    /// 無効値。
    Invalid,

    /// ユニフォームバッファ。
    UniformBuffer,

    /// ストレージバッファ。
    StorageBuffer,

    /// 読み取りイメージ。
    SampledImage,

    /// 書き込みイメージ。
    StorageImage,

    /// サンプラー。
    Sampler,

    TERM,
};

} // namespace ae::gfx_low
// EOF
