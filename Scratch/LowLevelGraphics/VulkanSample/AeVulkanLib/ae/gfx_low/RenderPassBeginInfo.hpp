// 文字コード：UTF-8
#pragma once

#include <ae/base/Aabb2i.hpp>
#include <ae/base/Pointer.hpp>

namespace ae {
namespace gfx_low {
class RenderPass;
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
    /// 使用する RenderPass。（初期値：nullptr）
    const RenderPass* RenderPass() const {
        return renderPass_.Get();
    }

    /// RenderPass() の設定。（設定必須）
    RenderPassBeginInfo& SetRenderPass(
        const gfx_low::RenderPass* renderPass) {
        renderPass_.Reset(renderPass);
        return *this;
    }
    //@}

private:
    base::Pointer<const gfx_low::RenderPass> renderPass_;
};

} // namespace gfx_low
} // namespace ae

// EOF
