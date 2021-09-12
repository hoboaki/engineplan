// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class RenderPass;
}
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// CommandBuffer::BeginRecord に必要な情報。
class CommandBufferBeginRecordInfo {
public:
    /// @name プロパティ
    //@{
    /// 描画用セカンダリコマンドバッファに引き継がれる描画パス。（初期値：nullptr）
    /// @details 
    /// CommandBufferFeature::Render を指定したセカンダリコマンドバッファにおいて設定必須。
    const RenderPass* InheritRenderPassPtr() const { return inheritRenderPassPtr_.Get(); }

    /// InheritRenderPassPtr() の設定。
    CommandBufferBeginRecordInfo& SetInheritRenderPassPtr(
        const RenderPass* infoPtr) {
        inheritRenderPassPtr_.Reset(infoPtr);
        return *this;
    }
    //@}

private:
    base::Pointer<const RenderPass> inheritRenderPassPtr_;
};

} // namespace gfx_low
} // namespace ae
// EOF
