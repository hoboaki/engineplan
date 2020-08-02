// 文字コード：UTF-8
#pragma once

#include <ae/base/Extent3i.hpp>
#include <ae/gfx_low/ImageFormat.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// ImageResource のデータ構造仕様に関する情報。
class ImageResourceSpecInfo {
public:
    /// @name プロパティ
    //@{
    /// イメージフォーマット。
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
    //@}

private:
    ImageFormat format_;
    base::Extent3i extent_;
};

} // namespace gfx_low
} // namespace ae
// EOF
