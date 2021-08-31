// 文字コード：UTF-8
#include <ae/gfx_low/Queue.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/CommandBuffer.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/Event.hpp>
#include <ae/gfx_low/Fence.hpp>
#include <ae/gfx_low/Swapchain.hpp>
#include <ae/gfx_low/System.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
Queue::Queue(
    gfx_low::Device* device,
    const ::vk::Queue& queue,
    QueueKind kind,
    int operationCountMax,
    const ::vk::CommandPool& commandPool)
: device_(base::PtrToRef(device))
, nativeObject_(queue)
, kind_(kind)
, operations_(operationCountMax, device_.System().ObjectAllocator_())
, waitEvents_(operationCountMax, device_.System().ObjectAllocator_())
, signalEvents_(operationCountMax, device_.System().ObjectAllocator_())
, commandPool_(commandPool) {
}

//------------------------------------------------------------------------------
Queue::~Queue() {
}

//------------------------------------------------------------------------------
Queue& Queue::PushCommandExecute(CommandBuffer* commands) {
    // Present 済みでないことを確認
    bool pushedSwapchainPresent = false;
    for (const auto& op : operations_) {
        if (op.kind == OperationKind::SwapchainPresent) {
            pushedSwapchainPresent = true;
            break;
        }
    }
    AE_BASE_ASSERT(!pushedSwapchainPresent);

    operations_.Add(Operation{ OperationKind::CommandExecute, commands });
    return *this;
}

//------------------------------------------------------------------------------
Queue& Queue::PushSwapchainWait(Swapchain* swapchain) {
    operations_.Add(Operation{ OperationKind::SwapchainWait, swapchain });
    PushEventWait(&base::PtrToRef(swapchain).CurrentAcquireEvent_());
    return *this;
}

//------------------------------------------------------------------------------
Queue& Queue::PushSwapchainPresent(Swapchain* swapchain) {
    // PushSwapchainWait 済みであることを確認
    bool pushedSwapchainWait = false;
    for (const auto& op : operations_) {
        if (op.kind == OperationKind::SwapchainWait && op.ptr == swapchain) {
            pushedSwapchainWait = true;
            break;
        }
    }
    AE_BASE_ASSERT(pushedSwapchainWait);

    // CommandExecute が追加済ならそのコマンド終了時に送信する Signal
    // を登録しておきそれが完了するのを待ってから Present する
    for (const auto& op : operations_) {
        if (op.kind == OperationKind::CommandExecute) {
            PushEventSignal(
                &base::PtrToRef(swapchain).CurrentReadyToPresentEvent_());
            PushEventWait(
                &base::PtrToRef(swapchain).CurrentReadyToPresentEvent_());
            break;
        }
    }

    operations_.Add(Operation{ OperationKind::SwapchainPresent, swapchain });
    return *this;
}

//------------------------------------------------------------------------------
Queue& Queue::PushEventWait(Event* event) {
    operations_.Add(Operation{ OperationKind::EventWait, event });
    return *this;
}

//------------------------------------------------------------------------------
Queue& Queue::PushEventSignal(Event* event) {
    // １つ以上の CommandExecute が追加済みであることを確認
    bool pushedCommandExecute = false;
    for (const auto& op : operations_) {
        if (op.kind == OperationKind::CommandExecute) {
            pushedCommandExecute = true;
            break;
        }
    }
    AE_BASE_ASSERT(pushedCommandExecute);

    operations_.Add(Operation{ OperationKind::EventSignal, event });
    return *this;
}

//------------------------------------------------------------------------------
void Queue::Submit(Fence* fencePtr) {
    // １つずつコマンドを処理
    for (int opIdx = 0; opIdx < operations_.Count(); ++opIdx) {
        const auto& op = operations_[opIdx];
        switch (op.kind) {
        case OperationKind::NoOperation:
            // 何もしない
            break;

        case OperationKind::SwapchainWait:
            // 何もしない
            break;

        case OperationKind::SwapchainPresent: {
            // １つ以上の Wait があるはず。
            AE_BASE_ASSERT_LESS_EQUALS(1, waitEvents_.Count());

            // @todo 複数の Present 対応
            // 今は 1Submit につき 1Present しかサポートしない。
            AE_BASE_ASSERT_LESS(
                FindOperationIndex(OperationKind::SwapchainPresent, opIdx + 1),
                0);

            // Present 実行
            auto& swapchain = base::PtrToRef(static_cast<Swapchain*>(op.ptr));
            const uint32_t imageIndicies[] = { uint32_t(
                swapchain.CurrentBufferIndex_()) };
            const auto presentInfo =
                vk::PresentInfoKHR()
                    .setWaitSemaphoreCount(waitEvents_.Count())
                    .setPWaitSemaphores(&waitEvents_.First())
                    .setSwapchainCount(1)
                    .setPSwapchains(swapchain.InstancePtr_())
                    .setPImageIndices(imageIndicies);
            const auto result = nativeObject_.presentKHR(&presentInfo);
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
            AE_BASE_ASSERT(
                opIdx + 1 ==
                operations_.Count()); // 今は最後しかサポートしていない

            // Wait をクリア
            waitEvents_.Clear();
        } break;

        case OperationKind::EventWait:
            waitEvents_.Add(
                base::PtrToRef(static_cast<Event*>(op.ptr)).NativeObject_());
            break;

        case OperationKind::EventSignal:
            // EventSignal は CommandExecute
            // によって処理されているはずなので到達するはずがない
            AE_BASE_ASSERT_NOT_REACHED();
            break;

        case OperationKind::CommandExecute: {
            // @todo 複数コマンド実行対応
            // 今は１つしか対応しない
            AE_BASE_ASSERT_LESS(
                FindOperationIndex(OperationKind::CommandExecute, opIdx + 1),
                0);

            // 以降の Signal を回収
            for (int nextOpIdx = opIdx + 1; nextOpIdx < operations_.Count();
                 ++nextOpIdx) {
                auto& nextOp = operations_[nextOpIdx];
                if (nextOp.kind == OperationKind::EventSignal) {
                    signalEvents_.Add(
                        static_cast<Event*>(nextOp.ptr)->NativeObject_());
                    nextOp.kind = OperationKind::
                        NoOperation; // 処理したので NoOperation に変更
                }
            }

            // Fence 選択＆事前処理
            ::vk::Fence nativeFence;
            if (fencePtr != nullptr) {
                auto& fence = base::PtrToRef(fencePtr);
                nativeFence = fence.NativeObject_();
                fence.OnSubmit_();
            }

            // 送信
            const ::vk::PipelineStageFlags pipeStageFlags =
                ::vk::PipelineStageFlagBits::eColorAttachmentOutput;
            auto const submitInfo =
                ::vk::SubmitInfo()
                    .setPWaitDstStageMask(&pipeStageFlags)
                    .setWaitSemaphoreCount(waitEvents_.Count())
                    .setPWaitSemaphores(
                        waitEvents_.IsEmpty() ? nullptr : &waitEvents_.First())
                    .setCommandBufferCount(1)
                    .setPCommandBuffers(
                        &static_cast<CommandBuffer*>(op.ptr)->NativeObject_())
                    .setSignalSemaphoreCount(signalEvents_.Count())
                    .setPSignalSemaphores(
                        signalEvents_.IsEmpty() ? nullptr
                                                : &signalEvents_.First());
            {
                const auto result =
                    nativeObject_.submit(1, &submitInfo, nativeFence);
                AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
            }

            // 各イベントをクリア
            waitEvents_.Clear();
            signalEvents_.Clear();
            break;
        }

        default:
            AE_BASE_ASSERT_NOT_REACHED_MSGFMT(
                "Non supported operation kind (%d).",
                op.kind);
        }
    }

    // クリア
    operations_.Clear();
}

//------------------------------------------------------------------------------
int Queue::FindOperationIndex(const OperationKind kind, const int startIndex) {
    for (int i = startIndex; i < operations_.Count(); ++i) {
        if (operations_[i].kind == kind) {
            return i;
        }
    }
    return -1;
}

} // namespace gfx_low
} // namespace ae
// EOF
