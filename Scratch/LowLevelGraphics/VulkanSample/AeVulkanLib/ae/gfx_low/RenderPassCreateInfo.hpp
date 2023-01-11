// 文字コード：UTF-8
#pragma once

#include <ae/base/Aabb2i.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/RenderPassSpecInfo.hpp>

namespace ae::gfx_low {
class DepthStencilSetting;
class Device;
class RenderPassSpecInfo;
class RenderTargetSetting;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// RenderPass 作成に必要な情報。
class RenderPassCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// 属する Device。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須）
    RenderPassCreateInfo& SetDevice(gfx_low::Device* device)
    {
        device_.Reset(device);
        return *this;
    }

    /// RenderPass 仕様情報。（初期値：デフォルトコンストラクタの値）
    const RenderPassSpecInfo RenderPassSpecInfo() const
    {
        return renderPassSpecInfo_;
    }

    /// RenderPassSpecInfo() の設定。（設定必須）
    RenderPassCreateInfo& SetRenderPassSpecInfo(
        const gfx_low::RenderPassSpecInfo& specInfo)
    {
        renderPassSpecInfo_ = specInfo;
        return *this;
    }

    /// 全 RenderTarget 設定情報。（初期値：nullptr）
    const RenderTargetSetting* RenderTargetSettings() const
    {
        return renderTargetSettings_.Get();
    }

    /// RenderTargetSettings() の設定。
    /// @param settings RenderPassSpecInfo().RenderTargetCount()
    /// 長の配列ポインタ。
    RenderPassCreateInfo& SetRenderTargetSettings(
        const RenderTargetSetting* settings)
    {
        renderTargetSettings_.Reset(settings);
        return *this;
    }

    /// DepthStencil 設定情報。（初期値：nullptr）
    const DepthStencilSetting* DepthStencilSettingPtr() const
    {
        return depthStencilSettingPtr_.Get();
    }

    /// DepthStencilSettingPtr() の設定。
    /// @details
    /// RenderPassSpecInfo() で DepthStencil
    /// を使う仕様になっている場合は設定必須です。
    RenderPassCreateInfo& SetDepthStencilSettingPtr(
        const DepthStencilSetting* settingPtr)
    {
        depthStencilSettingPtr_.Reset(settingPtr);
        return *this;
    }

    /// 描画範囲。（初期値：Aabb2iデフォルトコンストラクタの値）
    base::Aabb2i RenderArea() const { return renderArea_; }

    /// RenderArea() の設定。
    RenderPassCreateInfo& SetRenderArea(const base::Aabb2i& renderArea)
    {
        renderArea_ = renderArea;
        return *this;
    }
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    gfx_low::RenderPassSpecInfo renderPassSpecInfo_;
    base::Pointer<const RenderTargetSetting> renderTargetSettings_;
    base::Pointer<const DepthStencilSetting> depthStencilSettingPtr_;
    base::Aabb2i renderArea_;
};

} // namespace ae::gfx_low

// EOF
