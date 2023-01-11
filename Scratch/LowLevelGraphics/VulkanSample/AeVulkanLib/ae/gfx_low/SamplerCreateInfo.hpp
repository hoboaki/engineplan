// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/CompareOp.hpp>
#include <ae/gfx_low/SamplerAddressMode.hpp>
#include <ae/gfx_low/SamplerBorderColor.hpp>
#include <ae/gfx_low/SamplerMinMagFilter.hpp>
#include <ae/gfx_low/SamplerMipmapMode.hpp>

namespace ae::gfx_low {
class Device;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// Sampler オブジェクト作成に必要な情報。
class SamplerCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// 属する Device オブジェクトのポインタ。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須）
    SamplerCreateInfo& SetDevice(gfx_low::Device* device)
    {
        device_.Reset(device);
        return *this;
    }

    /// 縮小サンプリングの動作。（初期値：Nearest）
    SamplerMinMagFilter MinFilter() const { return minFilter_; }

    /// MinFilter() の設定。
    SamplerCreateInfo& SetMinFilter(SamplerMinMagFilter filter);

    /// 拡大サンプリングの動作。（初期値：Nearest）
    SamplerMinMagFilter MagFilter() const { return magFilter_; }

    /// MinFilter() の設定。
    SamplerCreateInfo& SetMagFilter(SamplerMinMagFilter filter);

    /// ミップマップサンプリングの動作。（初期値：Nearest）
    SamplerMipmapMode MipmapMode() const { return mipmapMode_; }

    /// MipmapMode() の設定。
    SamplerCreateInfo& SetMipmapMode(SamplerMipmapMode mode);

    /// U座標サンプリングアドレスの決定方法。（初期値：ClampToEdge）
    SamplerAddressMode AddressModeU() const { return addressModeU_; }

    /// AddressModeU() の設定。
    SamplerCreateInfo& SetAddressModeU(SamplerAddressMode mode);

    /// V座標サンプリングアドレスの決定方法。（初期値：ClampToEdge）
    SamplerAddressMode AddressModeV() const { return addressModeV_; }

    /// AddressModeV() の設定。
    SamplerCreateInfo& SetAddressModeV(SamplerAddressMode mode);

    /// W座標サンプリングアドレスの決定方法。（初期値：ClampToEdge）
    SamplerAddressMode AddressModeW() const { return addressModeW_; }

    /// AddressModeW() の設定。
    SamplerCreateInfo& SetAddressModeW(SamplerAddressMode mode);

    /// SamplerAddressMode::ClampToBorder
    /// 時に採用する色。（初期値：OpaqueWhite）
    SamplerBorderColor BorderColor() const { return borderColor_; }

    /// BorderColor() の設定。
    SamplerCreateInfo& SetBorderColor(SamplerBorderColor color);

    /// Anisotropy サンプリングを有効にするか。（初期値：false）
    bool AnisotropyEnable() const { return anisotropyEnable_; }

    /// AnisotropyEnable() の設定。
    SamplerCreateInfo& SetAnisotropyEnable(bool enable)
    {
        anisotropyEnable_ = enable;
        return *this;
    }

    /// Anisotropy サンプリングのパラメータ。（初期値：1）
    int MaxAnisotropy() const { return maxAnisotropy_; }

    /// MaxAnisotropy() の設定。
    /// @param anisotropy [1,16]
    SamplerCreateInfo& SetMaxAnisotropy(int maxAnisotropy);

    /// 比較動作を有効にするか。（初期値：false）
    bool CompareEnable() const { return compareEnable_; }

    /// CompareEnable() の設定。
    SamplerCreateInfo& SetCompareEnable(bool enable)
    {
        compareEnable_ = enable;
        return *this;
    }

    /// 比較動作時の演算方法。（初期値：Always）
    gfx_low::CompareOp CompareOp() const { return compareOp_; }

    /// CompareOp() の設定。
    SamplerCreateInfo& SetCompareOp(gfx_low::CompareOp op);

    /// Lod 最小値。（初期値：0.0f）
    float MinLod() const { return minLod_; }

    /// MinLod() の設定。
    SamplerCreateInfo& SetMinLod(float lod)
    {
        minLod_ = lod;
        return *this;
    }

    /// Lod 最大値。（初期値：0.0f）
    float MaxLod() const { return maxLod_; }

    /// MaxLod() の設定。
    SamplerCreateInfo& SetMaxLod(float lod)
    {
        maxLod_ = lod;
        return *this;
    }

    /// サンプリングアドレスを 0～1
    /// 空間ではなくイメージサイズ空間で行うか。（初期値：false）
    bool UnnormalizedCoordinates() const { return unnormalizedCordinates_; }

    /// UnnormalizedCoordinates() の設定。
    SamplerCreateInfo& SetUnnormalizedCoordinates(bool unnormalizedCordinates)
    {
        unnormalizedCordinates_ = unnormalizedCordinates;
        return *this;
    }
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    SamplerMinMagFilter minFilter_ = SamplerMinMagFilter::Nearest;
    SamplerMinMagFilter magFilter_ = SamplerMinMagFilter::Nearest;
    SamplerMipmapMode mipmapMode_ = SamplerMipmapMode::Nearest;
    SamplerAddressMode addressModeU_ = SamplerAddressMode::ClampToEdge;
    SamplerAddressMode addressModeV_ = SamplerAddressMode::ClampToEdge;
    SamplerAddressMode addressModeW_ = SamplerAddressMode::ClampToEdge;
    SamplerBorderColor borderColor_ = SamplerBorderColor::OpaqueWhite;
    gfx_low::CompareOp compareOp_ = CompareOp::Always;
    int maxAnisotropy_ = 1;
    float minLod_ = 0.0f;
    float maxLod_ = 0.0f;
    bool anisotropyEnable_ = false;
    bool compareEnable_ = false;
    bool unnormalizedCordinates_ = false;
};

} // namespace ae::gfx_low
// EOF
