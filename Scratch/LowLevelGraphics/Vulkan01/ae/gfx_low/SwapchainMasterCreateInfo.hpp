// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/base/SdkHeader.hpp>

namespace ae {
namespace base {
class Screen;
}
}
namespace ae {
namespace gfx_low {
class Device;
}
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// SwapchainMaster オブジェクト作成に必要な情報。
class SwapchainMasterCreateInfo {
public:
    /// @name 属する Device オブジェクトのポインタ（設定必須、初期値：nullptr）
    //@{
    gfx_low::Device* Device() const { return device_.get(); }
    SwapchainMasterCreateInfo& SetDevice(gfx_low::Device* system) {
        device_.reset(system);
        return *this;
    }
    //@}

    /// @name 作成可能な Swapchain の最大作成数（設定可能な値：1以上、初期値：1）
    //@{
    int SwapchainCountMax() const { return swapchainCountMax_; }
    SwapchainMasterCreateInfo& SetSwapchainCountMax(int count);
    //@}

    /// @name 実装ライブラリ固有の拡張情報（初期値：nullptr）
    //@{
    void* ExtInfoPtr() { return extInfoPtr_; }
    SwapchainMasterCreateInfo& SetExtInfoPtr(void* ptr) { extInfoPtr_ = ptr; }
    //@}
    
    /// @name 対象 Surface を持つ Screen（設定必須、初期値：nullptr）
    //@{
    base::Screen* Screen() const { return screen_.get(); }
    SwapchainMasterCreateInfo& SetScreen(base::Screen* display) {
        screen_.reset(display);
        return *this;
    }
    //@}

    // メモ：
    // 将来的に、Swapchain が確保しうる最大バッファ情報などをここに入れる。
    // そうしておくと SwapchainMaster 生成時に Swapchain
    // のバッファをあらかじめ確保でき Swapchain
    // を作りなおしが発生してもメモリ断片化がおきなくなる。
    // 仮想アドレスがあれば気にしなくてもいい説もあるけども、こういう設計ができる口は用意しておきたい。

private:
    ::ae::base::Pointer<gfx_low::Device> device_;
    void* extInfoPtr_;
    ::ae::base::Pointer<base::Screen> screen_;
    int swapchainCountMax_ = 1;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
