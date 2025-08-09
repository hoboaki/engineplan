// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/RenderPassSpecInfo.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class DepthStencilSetting;
class RenderTargetSetting;
class ScissorSetting;
class ViewportSetting;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// CommandBuffer::BeginRecord に必要な情報。
class CommandBufferBeginRecordInfo {
public:
    /// @name プロパティ
    //@{
    /// 描画用セカンダリコマンドバッファが動作想定している RenderPass 仕様情報。（初期値：デフォルトコンストラクタの値）
    /// @details
    /// CommandBufferFeature::Render を指定したセカンダリコマンドバッファにおいて設定必須です。
    /// 設定値は呼び出し元のプライマリコマンドバッファの設定と合わせる必要があります。
    const RenderPassSpecInfo RenderPassSpecInfo() const
    {
        return renderPassSpecInfo_;
    }

    /// RenderPassSpecInfo() の設定。
    CommandBufferBeginRecordInfo& SetRenderPassSpecInfo(const gfx_low::RenderPassSpecInfo& info)
    {
        renderPassSpecInfo_ = info;
        return *this;
    }

    /// 描画用セカンダリコマンドバッファが動作想定している RenderPass の全 RenderTarget 設定情報。（初期値：nullptr）
    /// @details
    /// CommandBufferFeature::Render を指定したセカンダリコマンドバッファにおいて設定必須です。
    /// 設定値は呼び出し元のプライマリコマンドバッファの設定と合わせる必要があります。
    const RenderTargetSetting* RenderTargetSettingsPtr() const
    {
        return renderTargetSettingsPtr_.Get();
    }

    /// RenderTargetSettingsPtr() の設定。
    /// @param settings RenderPassSpecInfo().RenderTargetCount() 長の配列ポインタ。
    CommandBufferBeginRecordInfo& SetRenderTargetSettingsPtr(const RenderTargetSetting* settings)
    {
        renderTargetSettingsPtr_.Reset(settings);
        return *this;
    }

    /// 描画用セカンダリコマンドバッファが動作想定している RenderPass のDepthStencil 設定情報。（初期値：nullptr）
    /// @details
    /// RenderPassSpecInfo() で DepthStencil を使う仕様になっている場合は設定必須です。
    const DepthStencilSetting* DepthStencilSettingPtr() const
    {
        return depthStencilSettingPtr_.Get();
    }

    /// DepthStencilSettingPtr() の設定。
    CommandBufferBeginRecordInfo& SetDepthStencilSettingPtr(const DepthStencilSetting* settingPtr)
    {
        depthStencilSettingPtr_.Reset(settingPtr);
        return *this;
    }

    /// 描画用セカンダリコマンドバッファに引き継がれるビューポート設定。（初期値：nullptr）
    /// @details
    /// CommandBufferFeature::Render を指定したセカンダリコマンドバッファにおいて設定必須です。
    /// 設定値は呼び出し元のプライマリコマンドバッファの設定と合わせる必要があります。
    const ViewportSetting* InheritViewportSettingsPtr() const
    {
        return inheritViewportSettingsPtr_.Get();
    }

    /// SetInheritViewportSettingsPtr() の設定。
    CommandBufferBeginRecordInfo& SetInheritViewportSettingsPtr(
        const ViewportSetting* ptr)
    {
        inheritViewportSettingsPtr_.Reset(ptr);
        return *this;
    }

    /// 描画用セカンダリコマンドバッファに引き継がれるシザー設定。（初期値：nullptr）
    /// @details
    /// CommandBufferFeature::Render を指定したセカンダリコマンドバッファにおいて設定必須です。
    /// 設定値は呼び出し元のプライマリコマンドバッファの設定と合わせる必要があります。
    const ScissorSetting* InheritScissorSettingsPtr() const
    {
        return inheritScissorSettingsPtr_.Get();
    }

    /// SetInheritScissorSettingsPtr() の設定。
    CommandBufferBeginRecordInfo& SetInheritScissorSettingsPtr(
        const ScissorSetting* ptr)
    {
        inheritScissorSettingsPtr_.Reset(ptr);
        return *this;
    }
    //@}

private:
    gfx_low::RenderPassSpecInfo renderPassSpecInfo_;
    base::Pointer<const RenderTargetSetting> renderTargetSettingsPtr_;
    base::Pointer<const DepthStencilSetting> depthStencilSettingPtr_;
    base::Pointer<const ViewportSetting> inheritViewportSettingsPtr_;
    base::Pointer<const ScissorSetting> inheritScissorSettingsPtr_;
};

} // namespace ae::gfx_low
// EOF
