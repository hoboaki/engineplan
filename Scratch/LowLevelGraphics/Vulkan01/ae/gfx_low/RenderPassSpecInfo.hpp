// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/RenderTargetSpecInfo.hpp>
#include <array>

namespace ae {
namespace gfx_low {
class RenderTargetSpecInfo;
}
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// RenderPass の仕様情報。
class RenderPassSpecInfo {
public:
    /// @name プロパティ
    //@{
    /// RenderTarget の数。（初期値：0）
    int RenderTargetCount() const { return renderTargetCount_; }

    /// RenderTargetCount() の設定。
    /// @param renderTargetCount 0 以上。
    RenderPassSpecInfo& SetRenderTargetCount(int renderTargetCount);

    /// 全 RenderTarget の仕様情報がある配列の先頭アドレス。（初期値：nullptr）
    const RenderTargetSpecInfo* RenderTargetSpecInfos() const {
        return RenderTargetSpecInfos_.get();
    }

    /// RenderTarget の数と仕様の設定。
    RenderPassSpecInfo& SetRenderTargetSpecInfos(
        const RenderTargetSpecInfo* RenderTargetSpecInfos)
    {
        RenderTargetSpecInfos_.reset(RenderTargetSpecInfos);
        return *this;
    }
    //@}

private:
    int renderTargetCount_ = 0;
    base::Pointer<const RenderTargetSpecInfo> RenderTargetSpecInfos_;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
