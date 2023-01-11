// 文字コード：UTF-8
#pragma once

#include <ae/base/Aabb2i.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// シザー矩形設定。
class ScissorSetting {
public:
    /// @name プロパティ
    //@{
    /// 矩形。
    base::Aabb2i Rect() const { return rect_; }

    /// Rect() の設定。
    ScissorSetting& SetRect(const base::Aabb2i& rect)
    {
        rect_ = rect;
        return *this;
    }
    //@}

private:
    base::Aabb2i rect_;
};

} // namespace ae::gfx_low
// EOF
