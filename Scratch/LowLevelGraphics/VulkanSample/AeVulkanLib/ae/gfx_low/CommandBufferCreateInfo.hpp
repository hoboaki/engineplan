// 文字コード：UTF-8
#pragma once

#include <ae/base/BitSet.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/CommandBufferFeatureBitSet.hpp>
#include <ae/gfx_low/CommandBufferLevel.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class Device;
class Queue;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// CommandBuffer オブジェクト作成に必要な情報。
class CommandBufferCreateInfo {
public:
    /// 属する Device。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須）
    CommandBufferCreateInfo& SetDevice(gfx_low::Device* device)
    {
        device_.Reset(device);
        return *this;
    }

    /// 属する Queue。（初期値：nullptr）
    gfx_low::Queue* Queue() const { return queue_.Get(); }

    /// Queue() の設定。Level() == Primary の場合に設定必須。
    CommandBufferCreateInfo& SetQueue(gfx_low::Queue* queue)
    {
        queue_.Reset(queue);
        return *this;
    }

    /// CommandBuffer の階層レベル。（初期値：Primary）
    CommandBufferLevel Level() const { return level_; }

    /// Level() の設定。
    CommandBufferCreateInfo& SetLevel(CommandBufferLevel level);

    /// サポートする機能郡（初期値：全ビットtrue）
    CommandBufferFeatureBitSet Features() const { return features_; }

    /// Features() の設定。
    CommandBufferCreateInfo& SetFeatures(
        const CommandBufferFeatureBitSet& features)
    {
        features_ = features;
        return *this;
    }

    /// 記録できる RenderPass の最大数。 （初期値：0）
    int RenderPassCountMax() const { return renderPassCountMax_; }

    /// RenderPassCountMax() の設定。
    /// @param count 0以上。
    CommandBufferCreateInfo& SetRenderPassCountMax(int count);

private:
    base::Pointer<gfx_low::Device> device_;
    base::Pointer<gfx_low::Queue> queue_;
    CommandBufferLevel level_ = CommandBufferLevel::Primary;
    CommandBufferFeatureBitSet features_ = CommandBufferFeatureBitSet::AllOn();
    int renderPassCountMax_ = 0;
};

} // namespace ae::gfx_low
// EOF
