// 文字コード：UTF-8
#include <ae/gfx_low/Queue.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/Swapchain.hpp>
#include <ae/gfx_low/System.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
Queue::Queue(gfx_low::Device* device, const ::vk::Queue& queue, QueueKind kind,
    int operationCountMax, const ::vk::CommandPool& commandPool)
: device_(base::PtrToRef(device))
, queue_(queue)
, kind_(kind)
, operations_(operationCountMax, device_.System().InternalObjectAllocator())
, waitEvents_(operationCountMax, device_.System().InternalObjectAllocator())
, signalEvents_(operationCountMax, device_.System().InternalObjectAllocator())
, commandPool_(commandPool) {}

//------------------------------------------------------------------------------
Queue::~Queue() {}

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

    operations_.add(Operation{OperationKind::CommandExecute, commands});
    return *this;
}

//------------------------------------------------------------------------------
Queue& Queue::PushSwapchainWait(Swapchain* swapchain) {
    operations_.add(Operation{OperationKind::SwapchainWait, swapchain});
    PushEventWait(&base::PtrToRef(swapchain).InternalCurrentAcquireEvent());
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
    // を登録しておく
    for (const auto& op : operations_) {
        if (op.kind == OperationKind::CommandExecute) {
            PushEventSignal(&base::PtrToRef(swapchain)
                                 .InternalCurrentReadyToPresentEvent());
            break;
        }
    }

    operations_.add(Operation{OperationKind::SwapchainPresent, swapchain});
    return *this;
}

//------------------------------------------------------------------------------
Queue& Queue::PushEventWait(Event* event) {
    operations_.add(Operation{OperationKind::EventWait, event});
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

    operations_.add(Operation{OperationKind::EventSignal, event});
    return *this;
}

//------------------------------------------------------------------------------
void Queue::Submit(Fence* fencePtr) {
    // １つずつコマンドを処理
    for (int opIdx = 0; opIdx < operations_.count(); ++opIdx) {
        const auto& op = operations_[opIdx];
        switch (op.kind) {
        case OperationKind::SwapchainWait:
            // 何もしない
            break;

        case OperationKind::SwapchainPresent: {
            // １つ以上の Wait があるはず。
            AE_BASE_ASSERT_LESS_EQUALS(1, waitEvents_.count());

            // @todo 複数の Present
            // 今は 1Submit につき 1Present しかサポートしない。
            for (int aftOpIdx = opIdx + 1; aftOpIdx < operations_.count();
                 ++aftOpIdx) {
                AE_BASE_ASSERT(
                    operations_[opIdx].kind != OperationKind::SwapchainPresent);
            }

            // Present 実行
            auto& swapchain = base::PtrToRef(static_cast<Swapchain*>(op.ptr));
            const uint32_t imageIndicies[] = {
                uint32_t(swapchain.InternalCurrentBufferIndex())};
            const auto presentInfo =
                vk::PresentInfoKHR()
                    .setWaitSemaphoreCount(1)
                    .setPWaitSemaphores(&waitEvents_.first())
                    .setSwapchainCount(1)
                    .setPSwapchains(&swapchain.InternalInstance())
                    .setPImageIndices(imageIndicies);
            const auto result = queue_.presentKHR(&presentInfo);
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
            AE_BASE_ASSERT(
                opIdx + 1 ==
                operations_.count());  // 今は最後しかサポートしていない
        } break;

        case OperationKind::EventWait:
            waitEvents_.add(
                base::PtrToRef(static_cast<Event*>(op.ptr)).InternalInstance());
            break;

        case OperationKind::EventSignal:
            // EventSignal は CommandExecute
            // によって処理されているはずなので到達するはずがない
            AE_BASE_ASSERT_NOT_REACHED();
            break;

        default:
            AE_BASE_ASSERT_NOT_REACHED_MSGFMT(
                "Non supported operation kind (%d).", op.kind);
        }
    }
}

}  // namespace gfx_low
}  // namespace ae
// EOF
