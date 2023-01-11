// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class RenderPass;
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
    /// 描画用セカンダリコマンドバッファに引き継がれる描画パス。（初期値：nullptr）
    /// @details
    /// CommandBufferFeature::Render を指定したセカンダリコマンドバッファにおいて設定必須。
    const RenderPass* InheritRenderPassPtr() const
    {
        return inheritRenderPassPtr_.Get();
    }

    /// InheritRenderPassPtr() の設定。
    CommandBufferBeginRecordInfo& SetInheritRenderPassPtr(
        const RenderPass* infoPtr)
    {
        inheritRenderPassPtr_.Reset(infoPtr);
        return *this;
    }

    /// 描画用セカンダリコマンドバッファに引き継がれるビューポート設定。（初期値：nullptr）
    /// @details
    /// CommandBufferFeature::Render を指定したセカンダリコマンドバッファにおいて設定必須。
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
    /// CommandBufferFeature::Render を指定したセカンダリコマンドバッファにおいて設定必須。
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
    base::Pointer<const RenderPass> inheritRenderPassPtr_;
    base::Pointer<const ViewportSetting> inheritViewportSettingsPtr_;
    base::Pointer<const ScissorSetting> inheritScissorSettingsPtr_;
};

} // namespace ae::gfx_low
// EOF
