// 文字コード：UTF-8
#pragma once

#include <ae/base/RuntimeArray.hpp>
#include <ae/gfx_low/SdkHeader.hpp>
#include <ae/gfx_low/Swapchain.hpp>
#include <ae/gfx_low/SwapchainHandle.hpp>

namespace ae {
namespace base {
class Screen;
}
}  // namespace ae
namespace ae {
namespace gfx_low {
class Device;
class SwapchainCreateInfo;
class Swapchain;
class SwapchainMasterCreateInfo;
}  // namespace gfx_low
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// スワップチェインを管理するクラス。
/// @details
/// スワップチェインが使用するメモリ管理や、作り直し機能を提供し、
/// Surface の概念があるプラットフォームでは Surface の生成・破棄も行います。
///
/// ::ae::base::Screen １つにつき１つの SwapchainMaster を作る必要があります。
///
/// 本オブジェクトを破棄する時点で存在する Swapchain は自動的に破棄されます。
class SwapchainMaster {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    SwapchainMaster(const SwapchainMasterCreateInfo& createInfo);
    ~SwapchainMaster();
    //@}

    /// @name プロパティ
    //@{
    ///  コンストラクタで渡した Device オブジェクト。
    Device& Device() const { return device_; }
    //@}

    /// @name Swapchain の作成・破棄
    //@{
    /// Swapchain を作成。
    /// @param oldSwapchain 新規作成する Swapchain に Present
    /// 情報などを引き継ぎつつ破棄をする Swapchain。無効なハンドルを渡した場合、引き継ぎなどは行わない。
    /// @details 
    /// oldSwapchain はこの関数呼び出し後 IsValid() == false となり使えなくなります。
    SwapchainHandle CreateSwapchain(const SwapchainCreateInfo& createInfo,
        const SwapchainHandle& oldSwapchain = SwapchainHandle());

    /// 指定の Swapchain を破棄。
    void DestroySwapchain(const SwapchainHandle& swapchain);
    //@}

private:
    class SwapchainEntity : public Swapchain {
    public:
        SwapchainEntity() {}
    };

    uint32_t AcquireUniqueId();
    void DestroySwapchainInstance(::vk::SwapchainKHR instance);

    gfx_low::Device& device_;
    base::Screen& screen_;
    ::vk::SurfaceKHR surface_;
    ::ae::base::RuntimeArray<SwapchainEntity> swapchains_;
    uint32_t lastAcquireUniqueId_ = 0;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
