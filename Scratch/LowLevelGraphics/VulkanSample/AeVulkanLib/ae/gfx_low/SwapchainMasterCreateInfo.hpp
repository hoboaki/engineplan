// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/base/SdkHeader.hpp>

namespace ae::base {
class Screen;
}
namespace ae::gfx_low {
class Device;
}

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// SwapchainMaster オブジェクト作成に必要な情報。
class SwapchainMasterCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// 属する Device オブジェクトのポインタ。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須）
    SwapchainMasterCreateInfo& SetDevice(gfx_low::Device* device)
    {
        device_.Reset(device);
        return *this;
    }

    /// 作成可能な Swapchain の最大作成数。（初期値：1）
    int SwapchainCountMax() const { return swapchainCountMax_; }

    /// SwapchainCountMax() の設定。
    /// @param count 1以上。
    SwapchainMasterCreateInfo& SetSwapchainCountMax(int count);

    /// 実装ライブラリ固有の拡張情報。（初期値：nullptr）
    void* ExtInfoPtr() { return extInfoPtr_; }

    /// ExtInfoPtr() の設定。
    SwapchainMasterCreateInfo& SetExtInfoPtr(void* ptr) { extInfoPtr_ = ptr; }

    /// 対象 Surface を持つ Screen。（初期値：nullptr）
    base::Screen* Screen() const { return screen_.Get(); }

    /// Screen() の設定。（設定必須）
    SwapchainMasterCreateInfo& SetScreen(base::Screen* screen)
    {
        screen_.Reset(screen);
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
    void* extInfoPtr_ = nullptr;
    ::ae::base::Pointer<base::Screen> screen_;
    int swapchainCountMax_ = 1;
};

} // namespace ae::gfx_low
// EOF
