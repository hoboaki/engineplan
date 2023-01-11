// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/PolygonFrontFace.hpp>
#include <ae/gfx_low/RasterizeCullMode.hpp>
#include <ae/gfx_low/RasterizeFillMode.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// パイプラインのラスタライザに関する情報。
/// @todo DepthBias MultiSample などの情報。
class PipelineRasterizerInfo {
public:
    /// @name プロパティ
    //@{
    /// 面カリングモード。（初期値：None）
    RasterizeCullMode CullMode() const { return cullMode_; }

    /// RasterizeCullMode() の設定。
    PipelineRasterizerInfo& SetCullMode(RasterizeCullMode mode);

    /// ポリゴンフィルモード。（初期値：Solid）
    RasterizeFillMode FillMode() const { return fillMode_; }

    /// FillMode() の設定。
    PipelineRasterizerInfo& SetFillMode(RasterizeFillMode mode);

    /// 表面解釈の方法。（初期値：Invalid）
    PolygonFrontFace FrontFace() const { return frontFace_; }

    /// FrontFace() の設定。（設定必須）
    PipelineRasterizerInfo& SetFrontFace(PolygonFrontFace frontFace);

    /// 線幅。（初期値：1.0f）
    /// @details
    /// PrimitiveTopology が Line 系のときの描画やワイヤーフレーム描画の際に使われます。
    float LineWidth() const { return lineWidth_; }

    /// LineWidth() の設定。
    /// @param width 0以上。
    PipelineRasterizerInfo& SetLineWidth(float lineWidth);
    //@}

private:
    RasterizeCullMode cullMode_ = RasterizeCullMode::None;
    RasterizeFillMode fillMode_ = RasterizeFillMode::Solid;
    PolygonFrontFace frontFace_ = PolygonFrontFace::Invalid;
    float lineWidth_ = 1.0f;
};

} // namespace ae::gfx_low
// EOF
