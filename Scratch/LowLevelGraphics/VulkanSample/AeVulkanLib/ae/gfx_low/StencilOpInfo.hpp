// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/CompareOp.hpp>
#include <ae/gfx_low/StencilOp.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ステンシルテストの演算に関する情報。
class StencilOpInfo {
public:
    /// @name プロパティ
    //@{
    /// ステンシルテスト失敗時の動作。（初期値：Keep）
    StencilOp FailOp() const { return failOp_; }

    /// FailOp() の設定。
    StencilOpInfo& SetFailOp(StencilOp op);

    /// デプステスト失敗時の動作。（初期値：Keep）
    StencilOp DepthFailOp() const { return depthFailOp_; }

    /// DepthFailOp() の設定。
    StencilOpInfo& SetDepthFailOp(StencilOp op);

    /// ステンシルテスト通貨時の動作。（初期値：Keep）
    StencilOp PassOp() const { return passOp_; }

    /// PassOp() の設定。
    StencilOpInfo& SetPassOp(StencilOp op);

    /// ステンシルテストの比較演算方法。（初期値：Never）
    gfx_low::CompareOp CompareOp() const { return compareOp_; }

    /// CompareOp() の設定。
    StencilOpInfo& SetCompareOp(gfx_low::CompareOp op);
    //@}

private:
    StencilOp failOp_ = StencilOp::Keep;
    StencilOp depthFailOp_ = StencilOp::Keep;
    StencilOp passOp_ = StencilOp::Keep;
    gfx_low::CompareOp compareOp_ = CompareOp::Never;
};

} // namespace ae::gfx_low
// EOF
