// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>

namespace ae {
namespace gfx_low {
class SwapchainMaster;
}
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// Swapchain オブジェクト作成時に必要な情報。
/// @details
/// ImageCount の補足：
/// SetImageCount で指定した値とは異なる Swapchain が作られる場合があります。
/// 例えばデバイスが 2 以上を求めている場合に ImageCount を 1 と指定した場合、
/// Swapchain 作成時に　ImageCount は 2 に繰り上げられます。
class SwapchainCreateInfo {
public:
    /// @name スワップチェインが抱えるイメージの枚数（設定できる値:1以上、初期値：2）
    //@{
    int ImageCount() const { return imageCount_;  }
    SwapchainCreateInfo& SetImageCount(int imageCount);
    //@}

    /// @name イメージを sRGB フォーマットにするか（初期値：false）
    //@{
    bool IsSrgbFormat() const { return isSrgbFormat_; }
    SwapchainCreateInfo& SetIsSrgbFormat(bool isSrgbFormat)
    {
        isSrgbFormat_ = isSrgbFormat;
        return *this;
    }
    //@}

private:
    ::ae::base::Pointer<gfx_low::SwapchainMaster> swapchainMaster_;
    int imageCount_ = 2;
    bool isSrgbFormat_ = false;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
