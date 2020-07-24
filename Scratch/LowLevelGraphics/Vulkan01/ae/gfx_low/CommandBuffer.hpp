// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/CommandBufferFeatureBitSet.hpp>
#include <ae/gfx_low/CommandBufferLevel.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class CommandBufferCreateInfo;
class Device;
class Queue;
}  // namespace gfx_low
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// GPUが処理するコマンドを扱うコマンドバッファ。
/// @details
/// コマンドバッファはGPUが処理するコマンドをCPUで生成する機能を提供します。
///
///
/// ・コマンドの実行について
/// コマンドの実行は Queue::PushExecute() でできます。
/// 実行できる Queue は createInfo で渡した Queue に制限され、他の Queue
/// に渡すことは出来ません。
///
/// ・BeginRecord/EndRecord について
/// コマンドの登録をする前に BeginRecord() を必ず呼び、最後に EndRecord()
/// を呼ぶようにしてください。 また、BeginRecord()
/// を呼ぶと以前登録されたコマンドは削除されます。
/// そのため、コマンドバッファのインスタンスがが GPU で処理されている最中に
/// BeginRecord() すると GPU の動作が停止する可能性があるため注意してください。
///
/// ・Primary と Secondary について
/// CommandBufferLevel::Primary は Queue::PushExecute() の引数に渡せますが
/// CommandBufferLevel::Secondary はできません。
/// その代わり、Primary のコマンドバッファの Call() の引数に渡せます。
/// Secondary は createInfo の SetFeatureFlags() で Render か Compute
/// のどちらか１つを設定するひつようがあります。
class CommandBuffer {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    CommandBuffer(const CommandBufferCreateInfo& createInfo);
    ~CommandBuffer();
    //@}

    /// @name プロパティ
    //@{
    /// 所属する Device。
    gfx_low::Device& Device() const { return device_; }   
    
    /// 階層レベル。   
    CommandBufferLevel Level() const { return level_; }

    /// サポートしている機能郡。 
    CommandBufferFeatureBitSet Features() const { return features_; }
    //@}

private:
    gfx_low::Device& device_;
    const base::Pointer<Queue> queuePtr_;
    const CommandBufferLevel level_;
    const CommandBufferFeatureBitSet features_;
    ::vk::CommandBuffer commandBuffer_;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
