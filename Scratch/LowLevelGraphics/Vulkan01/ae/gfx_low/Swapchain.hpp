// 文字コード：UTF-8
#pragma once

#include <ae/base/Placement.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/base/RuntimeArray.hpp>
#include <ae/gfx_low/Event.hpp>
#include <ae/gfx_low/ImageResource.hpp>
#include <ae/gfx_low/RenderTargetView.hpp>
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
    /// @name デストラクタ
    //@{
    ~Swapchain();
    //@}

    /// @name プロパティ
    //@{
    /// 所属する SwapchainMaster。
    gfx_low::SwapchainMaster& SwapchainMaster() const {
        return swapchainMaster_.ref();
    }
    //@}

    /// @name バッファ制御
    //@{
    /// 新しいバックバッファの要求をする。
    /// @details
    /// この関数が呼ばれるとアクティブなバックバッファが新しいものに切り替わります。
    /// 本関数を呼んだあと、Queue::PushSwapchainWait() を必ず呼ぶようにしてください。
    void AcquireNextImage();

    /// アクティブなバックバッファを指す RenderTargetView を取得。
    RenderTargetView& CurrentRenderTargetView() const {
        return frameProperties_[currentFrameIndex_].RenderTargetView.ref();
    }
    //@}

    /// @name 内部処理用機能
    //@{
    /// 無効な UniqueId 値。
    static const int InternalInvalidUniqueId = 0;

    /// 初期化。
    void InternalInitialize(gfx_low::SwapchainMaster* swapchainMaster,
        const ::vk::SwapchainKHR& swapchain, uint32_t uniqueId, int minImageCount,
        ::vk::Format imageFormat);

    /// 後始末。
    void InternalFinalize();

    /// 初期化済みか。
    bool InternalIsInitialized() const { return swapchainMaster_.isValid(); }

    ::vk::SwapchainKHR InternalInstance() const { return swapchain_; }

    Event& InternalCurrentAcquireEvent() {
        return *frameProperties_[currentFrameIndex_].AcquireEvent;
    }

    Event& InternalCurrentReadyToPresentEvent() {
        return *frameProperties_[currentFrameIndex_].ReadyToPresentEvent;
    }

    int InternalCurrentBufferIndex() const { return currentFrameIndex_; }

    /// ユニークID。古くなった Handle の Valid 判定で使う。
    uint32_t InternalUniqueId() const { return uniqueId_; }
    //@}

protected:
    /// ユーザーが誤って生成する事故を防ぐための protected-ctor。
    Swapchain() {}

private:
    /// １フレームあたりのプロパティ。
    class FrameProperty {
    public:
        /// バックバッファ化同期用イベント。
        base::Placement<Event> AcquireEvent;

        /// Present 処理可能状態同期用イベント。
        base::Placement<Event> ReadyToPresentEvent;

        /// イメージリソース。
        base::Placement<ImageResource> ImageResource;

        /// レンダーターゲットビュー。
        base::Placement<RenderTargetView> RenderTargetView;

        /// @todo ImageView の追加。
    };

    ::ae::base::Pointer<gfx_low::SwapchainMaster> swapchainMaster_;
    ::vk::SwapchainKHR swapchain_;
    ::ae::base::RuntimeArray<FrameProperty> frameProperties_;
    uint32_t uniqueId_ = InternalInvalidUniqueId;
    int currentFrameIndex_ = int(); // 初期化直後は負の値が入っている
};

}  // namespace gfx_low
}  // namespace ae
// EOF
