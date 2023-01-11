// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeMarray.hpp>
#include <ae/gfx_low/QueueKind.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class CommandBuffer;
class Device;
class Event;
class Fence;
class Swapchain;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// キューを扱うクラス。
/// @details
/// キューはグラフィックスデバイスへのコマンドの送信やスワップチェインへの転送機能などを提供します。
/// キューに対する操作は順番に蓄積され、 Submit()
/// が呼ばれたタイミングで蓄積済の操作の実行を開始します。
///
/// キューの作成は Device と一緒に作成されます。
/// 作成されたキューは Device::Queue() で取得できます。
class Queue {
public:
    /// @name プロパティ
    //@{
    /// 所属する Device。
    gfx_low::Device& Device() const { return device_; }

    /// Queue の種類。
    QueueKind Kind() const { return kind_; }
    //@}

    /// @name CommandBuffer 操作
    //@{
    /// 指定の CommandBuffer に記録済のコマンド郡を実行する。
    Queue& PushCommandExecute(CommandBuffer* commands);
    //@}

    /// @name Swapchain 操作
    //@{
    /// Swapchain で Acquire したバッファが使用できる状態になるまで待つ。
    Queue& PushSwapchainWait(Swapchain* swapchain);

    /// Swapchain で Acquire したバッファを Screen に転送要求を出す。
    /// @param swapchain PushSwapchainWait で渡した swapchain オブジェクト。
    /// @details
    /// Present を呼んだあとは Submit() するまで PushCommandBuffer()
    /// が呼べない制約があります。 また、Present を呼ぶ前は PushSwapchainWait()
    /// を呼んでおく必要があります。
    Queue& PushSwapchainPresent(Swapchain* swapchain);
    //@}

    /// @name 同期操作
    //@{
    /// 指定の Event オブジェクトでシグナルを受信するまで待つ。
    Queue& PushEventWait(Event* event);

    /// 指定の Event オブジェクトにシグナルを送信する。
    /// @details
    /// これを呼ぶ前に１回以上の PushCommandExecute() を呼ぶ必要があります。
    Queue& PushEventSignal(Event* event);
    //@}

    /// @name 送信
    //@{
    /// 追加済の全操作を GPU に送信する。
    /// @param fencePtr 全操作が終了したときに Signal が送信される Fence
    /// オブジェクト。nullptr を指定した場合は何もしない。
    void Submit(Fence* fencePtr);
    //@}

    /// @name 内部処理用機能
    //@{
    /// 内部処理用コンストラクタ。アプリケーション側からの呼び出しは禁止。
    Queue(
        gfx_low::Device* device,
        const ::vk::Queue& queue,
        QueueKind kind,
        int queueFamilyIndex,
        int operationCountMax);

    ~Queue();

    ::vk::Queue NativeObject_() { return nativeObject_; }
    int QueueFamilyIndex_() const { return queueFamilyIndex_; }
    //@}

private:
    enum class OperationKind
    {
        NoOperation,
        SwapchainWait,
        SwapchainPresent,
        EventWait,
        EventSignal,
        CommandExecute,
        TERM,
    };

    struct Operation
    {
        OperationKind kind;
        void* ptr;
    };

    /// 指定の Kind
    /// の操作が詰まれている最初のインデックスを取得する。見つからない場合は負の値を返す。
    int FindOperationIndex(OperationKind kind, int startIndex = 0);

    gfx_low::Device& device_;
    ::vk::Queue nativeObject_;
    const QueueKind kind_;
    const int queueFamilyIndex_;
    base::RuntimeMarray<Operation> operations_;
    base::RuntimeMarray<::vk::CommandBuffer> executeCommands_;
    base::RuntimeMarray<::vk::Semaphore> waitEvents_;
    base::RuntimeMarray<::vk::Semaphore> signalEvents_;
};

} // namespace ae::gfx_low
// EOF
