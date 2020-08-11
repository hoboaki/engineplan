// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/base/RuntimeMarray.hpp>
#include <ae/gfx_low/CommandBufferFeatureBitSet.hpp>
#include <ae/gfx_low/CommandBufferLevel.hpp>
#include <ae/gfx_low/CommandBufferState.hpp>
#include <ae/gfx_low/Event.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class CommandBufferCreateInfo;
class DescriptorSet;
class Device;
class DrawCallInfo;
class RenderPassBeginInfo;
class RenderPipeline;
class Queue;
class ScissorSetting;
class ViewportSetting;
} // namespace gfx_low
} // namespace ae

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
/// 関数の頭に ```Cmd``` とついているものがコマンドを追加する関数です。
/// コマンドの追加をする前に BeginRecord() を必ず呼び、最後に EndRecord()
/// を呼ぶようにしてください。 また、BeginRecord()
/// を呼ぶと以前登録されたコマンドは削除されます。
/// そのため、コマンドバッファのインスタンスがが GPU で処理されている最中に
/// BeginRecord() すると GPU の動作が停止する可能性があるため注意してください。
///
/// ・コマンドの種類と呼び出しタイミングの制約について
/// コマンドの追加は Features() で指定されている機能に限定されます。
/// Render に関するコマンドについては BeginRenderPass() EndRenderPass() の間で、
/// Compute に関するコマンドについては BeginComputePass() EndComputePass()
/// の間でのみ実行できます。 どちらかの Begin/End 区間中にもう片方の Begin/End
/// を呼ぶことはできません。 例えば BeginRenderPass() を呼び EndRenderPass()
/// を呼ぶ前に BeginComputePass() をすることはできません。必ず End
/// してから新しく Begin してください。 Copy については Begin/End
/// の宣言は不要ですが、Render や Compute の Begin/End
/// 期間中には実行できません。
///
/// ・Primary と Secondary について
/// CommandBufferLevel::Primary は Queue::PushExecute() の引数に渡せますが
/// CommandBufferLevel::Secondary はできません。
/// その代わり、Primary のコマンドバッファの Call() の引数に渡せます。
/// Secondary は createInfo の SetFeatureFlags() で Render か Compute
/// のどちらか１つを設定する必要があります。
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

    /// 現在の状態。
    CommandBufferState State() const { return state_; }
    //@}

    /// @name 記録開始・終了処理
    //@{
    /// 記録済みの情報をリセットして記録を開始する。
    void BeginRecord();

    /// 記録を終了する。
    void EndRecord();

    /// 記録済みの情報があればリセットする。
    /// @details BeginRecord() / EndRecord() の間では呼べません。
    void Reset();
    //@}

    /// @name Render コマンド追加の開始・終了
    //@{
    /// Render コマンド郡の開始コマンド。
    /// @details
    /// 開始・終了コマンドに詳細ついてはクラスの説明を参照してください。
    void CmdBeginRenderPass(const RenderPassBeginInfo& info);

    /// Render コマンド群の終了コマンド。
    /// @details
    /// 開始・終了コマンドに詳細ついてはクラスの説明を参照してください。
    void CmdEndRenderPass();
    //@}

    /// @name Render & Compute 共通コマンド郡
    //@{
    /// デスクリプタセットを設定。
    /// @details
    /// パイプライン設定前に呼ぶことはできません。
    void CmdSetDescriptorSet(const DescriptorSet& descriptorSet);
    //@}

    /// @name Render コマンド郡
    //@{
    /// レンダーパイプラインを設定。
    /// @details CmdBeginRenderPass を呼んでから Draw 系コマンドを積む前に
    /// 必ず設定する必要があります。
    void CmdSetRenderPipeline(const RenderPipeline& pipeline);

    /// ビューポートの設定。
    /// @param count settings の配列長。
    /// @param settings 設定値の配列。
    /// @details
    /// count は CmdBeginRenderPass で指定した RenderTarget
    /// の数と等しい必要があります。
    void CmdSetViewports(int count, const ViewportSetting* settings);

    /// シザーの設定。
    /// @param count settings の配列長。
    /// @param settings 設定値の配列。
    /// @details
    /// count は CmdBeginRenderPass で指定した RenderTarget
    /// の数と等しい必要があります。
    void CmdSetScissors(int count, const ScissorSetting* settings);

    /// 設定済のレンダーパイプラインに基づいてドローコールをする。
    void CmdDraw(const DrawCallInfo& info);
    //@}

    /// @name 内部処理用機能
    //@{
    ::vk::CommandBuffer& NativeObject_() { return nativeObject_; }

    Event& CompleteEvent_() { return completeEvent_; }
    //@}

private:
    struct RenderPassProperty {
        ::vk::RenderPass renderPass;
        ::vk::Framebuffer framebuffer;
    };

    gfx_low::Device& device_;
    const base::Pointer<Queue> queuePtr_;
    const CommandBufferLevel level_;
    const CommandBufferFeatureBitSet features_;
    ::vk::CommandBuffer nativeObject_;
    Event completeEvent_;
    CommandBufferState state_ = CommandBufferState::Initial;
    CommandBufferFeatureBitSet activePass_;
    base::RuntimeMarray<RenderPassProperty> renderPassProperties_;
    base::Pointer<const RenderPipeline> currentRenderPipeline_;
};

} // namespace gfx_low
} // namespace ae
// EOF
