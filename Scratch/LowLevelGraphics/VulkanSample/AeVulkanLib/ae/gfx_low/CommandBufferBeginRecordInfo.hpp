// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class RenderPassBeginInfo;
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
    /// 描画用セカンダリコマンドバッファに引き継がれる描画パス情報。（初期値：nullptr）
    /// @details 
    /// CommandBufferFeature::Render を指定したセカンダリコマンドバッファにおいて設定必須。
    const RenderPassBeginInfo* InheritRenderPassBeginInfoPtr() const { return inheritRenderPassBeginInfoPtr_.Get(); }

    /// InheritRenderPassBeginInfoPtr() の設定。
    CommandBufferBeginRecordInfo& SetInheritRenderPassBeginInfoPtr(
        const RenderPassBeginInfo* infoPtr) {
        inheritRenderPassBeginInfoPtr_.Reset(infoPtr);
        return *this;
    }
    //@}

private:
    base::Pointer<const RenderPassBeginInfo> inheritRenderPassBeginInfoPtr_;
};

} // namespace gfx_low
} // namespace ae
// EOF
