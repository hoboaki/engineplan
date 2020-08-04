// 文字コード：UTF-8
#pragma once

#include <ae/base/Aabb2i.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/RenderPassSpecInfo.hpp>

namespace ae {
namespace gfx_low {
class DepthStencilSetting;
class RenderPassSpecInfo;
class RenderTargetSetting;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// BeginRenderPass 関数実行に必要な情報。
class RenderPassBeginInfo {
public:
    /// @name プロパティ
    //@{
    /// RenderPass 仕様情報。（初期値：デフォルトコンストラクタの値）
    const RenderPassSpecInfo RenderPassSpecInfo() const {
        return renderPassSpecInfo_;
    }

    /// RenderPassSpecInfo() の設定。（設定必須）
    RenderPassBeginInfo& SetRenderPassSpecInfo(
        const gfx_low::RenderPassSpecInfo& specInfo) {
        renderPassSpecInfo_ = specInfo;
        return *this;
    }

    /// 全 RenderTarget 設定情報。（初期値：nullptr）
    const RenderTargetSetting* RenderTargetSettings() const {
        return renderTargetSettings_.Get();
    }

    /// RenderTargetSettings() の設定。
    /// @param settings RenderPassSpecInfo().RenderTargetCount()
    /// 長の配列ポインタ。
    RenderPassBeginInfo& SetRenderTargetSettings(
        const RenderTargetSetting* settings) {
        renderTargetSettings_.Reset(settings);
        return *this;
    }

    /// DepthStencil 設定情報。（初期値：nullptr）
    const DepthStencilSetting* DepthStencilSettingPtr() const {
        return depthStencilSettingPtr_.Get();
    }

    /// DepthStencilSettingPtr() の設定。
    /// @details
    /// RenderPassSpecInfo() で DepthStencil
    /// を使う仕様になっている場合は設定必須です。
    RenderPassBeginInfo& SetDepthStencilSettingPtr(
        const DepthStencilSetting* settingPtr) {
        depthStencilSettingPtr_.Reset(settingPtr);
        return *this;
    }

    /// 描画範囲。（初期値：Aabb2iデフォルトコンストラクタの値）
    base::Aabb2i RenderArea() const { return renderArea_; }

    /// RenderArea() の設定。
    RenderPassBeginInfo& SetRenderArea(const base::Aabb2i& renderArea) {
        renderArea_ = renderArea;
        return *this;
    }
    //@}

private:
    gfx_low::RenderPassSpecInfo renderPassSpecInfo_;
    base::Pointer<const RenderTargetSetting> renderTargetSettings_;
    base::Pointer<const DepthStencilSetting> depthStencilSettingPtr_;
    base::Aabb2i renderArea_;
};

} // namespace gfx_low
} // namespace ae

// EOF
