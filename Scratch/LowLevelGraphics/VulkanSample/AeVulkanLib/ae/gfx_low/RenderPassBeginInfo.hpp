// 文字コード：UTF-8
#pragma once

#include <ae/base/Aabb2i.hpp>
#include <ae/base/Pointer.hpp>

namespace ae::gfx_low {
class RenderPass;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// BeginRenderPass 関数実行に必要な情報。
class RenderPassBeginInfo {
public:
    /// @name プロパティ
    //@{
    /// 使用する RenderPass。（初期値：nullptr）
    const RenderPass* RenderPass() const { return renderPass_.Get(); }

    /// RenderPass() の設定。（設定必須）
    RenderPassBeginInfo& SetRenderPass(const gfx_low::RenderPass* renderPass)
    {
        renderPass_.Reset(renderPass);
        return *this;
    }

    /// セカンダリコマンドバッファを使用するか。（初期値：false）
    /// @details
    /// true の場合、この描画パスにおいて一部を除く全てのコマンドは
    /// セカンダリコマンドバッファによって実行する必要があります。
    bool UseSecondaryCommandBuffers() const
    {
        return useSecondaryCommandBuffers_;
    }

    /// UseSecondaryCommandBuffers() の設定。
    RenderPassBeginInfo& SetUseSecondaryCommandBuffers(bool use)
    {
        useSecondaryCommandBuffers_ = use;
        return *this;
    }
    //@}

private:
    base::Pointer<const gfx_low::RenderPass> renderPass_;
    bool useSecondaryCommandBuffers_ = false;
};

} // namespace ae::gfx_low

// EOF
