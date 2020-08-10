// 文字コード：UTF-8
#pragma once

#include <ae/base/Aabb2.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// ビューポート設定。
class ViewportSetting {
public:
    /// @name プロパティ
    //@{
    /// ビューポート範囲。
    base::Aabb2 Rect() const { return rect_; }

    /// Rect() の設定。
    ViewportSetting& SetRect(const base::Aabb2& rect) {
        rect_ = rect;
        return *this;
    }

    /// 深度範囲の最小値。 
    float DepthMin() const
    { 
        return depthMin_;
    }

    /// 深度範囲の最大値。
    float DepthMax() const { return depthMax_; }

    /// DepthMin() と DepthMax() の設定。
    /// @param depthMin [0.0f, 1.0f]。
    /// @param depthMax [0.0f, 1.0f] かつ depthMin <= depthMax。
    ViewportSetting& SetDepthRange(float depthMin, float depthMax);
    //@}

private:
    base::Aabb2 rect_;
    float depthMin_ = 0.0f;
    float depthMax_ = 1.0f;
};

} // namespace gfx_low
} // namespace ae
// EOF
