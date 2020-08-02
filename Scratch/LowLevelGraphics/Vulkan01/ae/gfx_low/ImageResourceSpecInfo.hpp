// 文字コード：UTF-8
#pragma once

#include <ae/base/Extent3i.hpp>
#include <ae/gfx_low/ImageFormat.hpp>
#include <ae/gfx_low/ImageKind.hpp>
#include <ae/gfx_low/ImageResourceUsageBitSet.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// ImageResource のデータ構造仕様に関する情報。
class ImageResourceSpecInfo {
public:
    /// @name プロパティ
    //@{
    /// イメージの種類。（初期値：Invalid）
    ImageKind Kind() const { return kind_; }

    /// Kind() の設定。
    ImageResourceSpecInfo& SetKind(ImageKind kind);

    /// イメージフォーマット。（初期値：Invalid)
    ImageFormat Format() const { return format_; }

    /// Format() の設定。
    ImageResourceSpecInfo& SetFormat(ImageFormat format);

    /// イメージ範囲。（初期値：0,0,0）
    base::Extent3i Extent() const { return extent_; }

    /// 2次元用 Extent() の設定。
    ImageResourceSpecInfo& SetExtent(const base::Extent2iPod& extent) {
        extent_ = base::Extent3i(extent, 1);
        return *this;
    }

    /// Extent() の設定。
    /// @details 2次元イメージの場合は depth に 1 を入れてください。
    ImageResourceSpecInfo& SetExtent(const base::Extent3iPod& extent) {
        extent_ = extent;
        return *this;
    }

    /// ミップマップレベル。（初期値：1） 
    int MipLevels() const { return mipLevels_; }

    /// MipLevels() の設定。
    /// @param mipLevels 1以上。
    ImageResourceSpecInfo& SetMipLevels(int mipLevels);

    /// テクスチャ配列の配列長。（初期値：1）
    int ArrayLength() const { return arrayLength_; }

    /// ArrayLength() の設定。
    /// @param arrayLength 1以上。
    ImageResourceSpecInfo& SetArrayLength(int arrayLength);

    /// 使用方法を示すビットセット。（初期値：全てOff）
    ImageResourceUsageBitSet UsageBitSet() const { return usageBitSet_; }

    /// UsageBitSet() の設定。（設定必須）
    ImageResourceSpecInfo& SetUsageBitSet(
        const ImageResourceUsageBitSet& usageBitSet) {
        usageBitSet_ = usageBitSet;
        return *this;
    }
    //@}

private:
    ImageKind kind_ = ImageKind::Invalid;
    ImageFormat format_ = ImageFormat::Invalid;
    base::Extent3i extent_;
    int mipLevels_ = 1;
    int arrayLength_ = 1;
    ImageResourceUsageBitSet usageBitSet_;
};

} // namespace gfx_low
} // namespace ae
// EOF
