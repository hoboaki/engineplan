// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class SwapchainMaster;
}
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// スワップチェインを扱うクラス。
/// @details
/// スワップチェインは最終的に生成されたイメージを Screen
/// に転送する機能を提供します。 スワップチェインは Screen
/// に転送する用のイメージバッファを複数所持することで
/// アプリケーションは画面に表示されていないバッファに対して描画することが可能となります。
///
/// 本オブジェクトの生成は SwapchainMaster::createSwapchain()
/// で行い、SwapchainHandle を経由でアクセスします。
class Swapchain {
public:
    /// @name プロパティ
    //@{
    /// 所属する SwapchainMaster。
    SwapchainMaster& swapchainMaster() const { return swapchainMaster_.ref(); }
    //@}

    /// @name 内部処理用機能
    //@{
    /// 無効な UniqueId 値。
    static const int InvalidUniqueId = 0;

    /// 初期化。
    void InternalInitialize(SwapchainMaster* swapchainMaster,
        const ::vk::SwapchainKHR& swapchain, uint32_t uniqueId) {
        swapchainMaster_.reset(swapchainMaster);
        swapchain_ = swapchain;
        uniqueId_ = uniqueId_;
    }

    /// 初期化済みか。
    bool InternalIsInitialized() const { return swapchainMaster_.isValid(); }

    ::vk::SwapchainKHR InternalInstance() const { return swapchain_; }

    /// ユニークID。古くなった Handle の Valid 判定で使う。
    uint32_t InternalUniqueId() const { return uniqueId_; }
    //@}

protected:
    /// ユーザーが誤って生成する事故を防ぐための protected-ctor。
    Swapchain() {}

private:
    ::ae::base::Pointer<SwapchainMaster> swapchainMaster_;
    ::vk::SwapchainKHR swapchain_;
    uint32_t uniqueId_ = InvalidUniqueId;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
