// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/VertexStepRate.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// 頂点バッファのメモリレイアウトに関する情報。
class VertexBufferLayoutInfo {
public:
    /// @name プロパティ
    //@{
    /// 要素間のバイト距離。（初期値：0）
    int Stride() const { return stride_; }

    /// Stride() の設定。
    /// @param stride 0以上。
    VertexBufferLayoutInfo& SetStride(int stride);

    /// データ参照位置を移動する単位。（初期値：Vertex）
    VertexStepRate StepRate() const { return stepRate_; }

    /// StepRate() の設定。
    VertexBufferLayoutInfo& SetStepRate(VertexStepRate stepRate);
    //@}

private:
    int stride_ = 0;
    VertexStepRate stepRate_ = VertexStepRate::Vertex;
};

} // namespace ae::gfx_low
// EOF
