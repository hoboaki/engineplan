// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/RenderTargetSpec.hpp>
#include <array>

namespace ae {
namespace gfx_low {
class RenderTargetSpec;
}
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// RenderPass の仕様情報。
class RenderPassSpec {
public:
    /// @name プロパティ
    //@{
    /// RenderTarget の数。（初期値：0）
    int RenderTargetCount() const { return renderTargetCount_; }

    /// RenderTargetCount() の設定。
    /// @param renderTargetCount 0 以上。
    RenderPassSpec& SetRenderTargetCount(int renderTargetCount);

    /// 全 RenderTarget の仕様情報がある配列の先頭アドレス。（初期値：nullptr）
    const RenderTargetSpec* RenderTargetSpecs() const {
        return renderTargetSpecs_.get();
    }

    /// RenderTarget の数と仕様の設定。
    RenderPassSpec& SetRenderTargetSpecs(
        const RenderTargetSpec* renderTargetSpecs)
    {
        renderTargetSpecs_.reset(renderTargetSpecs);
        return *this;
    }
    //@}

private:
    int renderTargetCount_ = 0;
    base::Pointer<const RenderTargetSpec> renderTargetSpecs_;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
