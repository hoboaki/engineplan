// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <array>

namespace ae::gfx_low {
class DepthStencilSpecInfo;
class RenderTargetSpecInfo;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

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
    const RenderTargetSpecInfo* RenderTargetSpecInfos() const
    {
        return renderTargetSpecInfos_.Get();
    }

    /// RenderTarget の数と仕様の設定。
    RenderPassSpecInfo& SetRenderTargetSpecInfos(
        const RenderTargetSpecInfo* renderTargetSpecInfos)
    {
        renderTargetSpecInfos_.Reset(renderTargetSpecInfos);
        return *this;
    }

    /// DepthStencil の仕様情報のポインタ。（初期値：nullptr）
    const DepthStencilSpecInfo* DepthStencilSpecInfoPtr() const
    {
        return depthStencilSpecInfoPtr_.Get();
    }

    /// DepthStencilSpecInfo() の設定。
    /// @param specInfoPtr nullptr を指定すると DepthStencil
    /// を使わない扱いになる。
    RenderPassSpecInfo& SetDepthStencilSpecInfoPtr(
        const DepthStencilSpecInfo* sptecInfoPtr)
    {
        depthStencilSpecInfoPtr_.Reset(sptecInfoPtr);
        return *this;
    }
    //@}

private:
    int renderTargetCount_ = 0;
    base::Pointer<const RenderTargetSpecInfo> renderTargetSpecInfos_;
    base::Pointer<const DepthStencilSpecInfo> depthStencilSpecInfoPtr_;
};

} // namespace ae::gfx_low
// EOF
