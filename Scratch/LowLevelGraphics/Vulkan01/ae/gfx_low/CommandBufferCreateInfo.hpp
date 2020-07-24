// 文字コード：UTF-8
#pragma once

#include <ae/base/BitSet.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/CommandBufferFeatureBitSet.hpp>
#include <ae/gfx_low/CommandBufferLevel.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class Device;
class Queue;
}  // namespace gfx_low
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// CommandBuffer オブジェクト作成に必要な情報。
class CommandBufferCreateInfo {
public:
    /// @name 属する Device オブジェクトのポインタ（設定必須、初期値：nullptr）
    //@{
    gfx_low::Device* Device() const { return device_.get(); }
    CommandBufferCreateInfo& SetDevice(gfx_low::Device* device) {
        device_.reset(device);
        return *this;
    }
    //@}

    /// @name 属する Queue オブジェクトのポインタ（Level() == Primary の場合に設定必須、初期値：nullptr）
    //@{
    gfx_low::Queue* Queue() const { return queue_.get(); }
    CommandBufferCreateInfo& SetQueue(gfx_low::Queue* queue) {
        queue_.reset(queue);
        return *this;
    }
    //@}

    /// @name CommandBuffer の階層レベル（初期値：Primary）
    //@{
    CommandBufferLevel Level() const { return level_; }
    CommandBufferCreateInfo& SetLevel(CommandBufferLevel level);
    //@}

    /// @name サポートする機能郡（初期値：全ビットtrue）
    //@{
    CommandBufferFeatureBitSet Features() const { return features_; }
    CommandBufferCreateInfo& SetFeatures(
        const CommandBufferFeatureBitSet& features)
    {
        features_ = features;
        return *this;
    }
    //@}

private:
    base::Pointer<gfx_low::Device> device_;
    base::Pointer<gfx_low::Queue> queue_;
    CommandBufferLevel level_ = CommandBufferLevel::Primary;
    CommandBufferFeatureBitSet features_ = CommandBufferFeatureBitSet::AllOn();
};

}  // namespace gfx_low
}  // namespace ae
// EOF
