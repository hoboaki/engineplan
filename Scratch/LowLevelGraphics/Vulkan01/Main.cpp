// 文字コード：UTF-8
#include <ae/base/AppEvent.hpp>
#include <ae/base/Application.hpp>
#include <ae/base/Color4b.hpp>
#include <ae/base/Console.hpp>
#include <ae/base/Display.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/SdkHeader.hpp>
#include <ae/gfx_low/CommandBuffer.hpp>
#include <ae/gfx_low/CommandBufferCreateInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/DeviceCreateInfo.hpp>
#include <ae/gfx_low/Fence.hpp>
#include <ae/gfx_low/FenceCreateInfo.hpp>
#include <ae/gfx_low/Queue.hpp>
#include <ae/gfx_low/QueueCreateInfo.hpp>
#include <ae/gfx_low/RenderPassBeginInfo.hpp>
#include <ae/gfx_low/RenderPassSpecInfo.hpp>
#include <ae/gfx_low/RenderTargetSetting.hpp>
#include <ae/gfx_low/Swapchain.hpp>
#include <ae/gfx_low/SwapchainCreateInfo.hpp>
#include <ae/gfx_low/SwapchainMaster.hpp>
#include <ae/gfx_low/SwapchainMasterCreateInfo.hpp>
#include <ae/gfx_low/System.hpp>
#include <ae/gfx_low/SystemCreateInfo.hpp>
#include <memory>

extern int WINAPI DemoWinMain(
    HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow);

//------------------------------------------------------------------------------
int aemain(::ae::base::Application* app) {
#if 0
    return DemoWinMain((HINSTANCE)GetModuleHandle(0), nullptr, nullptr, 0);
#else
    // コンソール出力
    AE_BASE_COUT_LINE_WITH_TIME("Adel runtime start.");

    // ディスプレイの作成
    ::ae::base::Display display =
        ::ae::base::Display(::ae::base::DisplayContext());

    // ディスプレイの表示
    display.show();

    // グラフィックスシステムインスタンス作成
    ::std::unique_ptr<::ae::gfx_low::System> gfxLowSystem(
        new ::ae::gfx_low::System(
            ::ae::gfx_low::SystemCreateInfo().SetDebugLevel(
                ::ae::gfx_low::SystemDebugLevel::Normal)));

    // Device & Queue 作成
    ::std::unique_ptr<::ae::gfx_low::Device> gfxLowDevice;
    {
        // デバッグダンプ
        gfxLowSystem->DumpAllPhysicalDeviceInfo();

        // Queue の作成情報を用意
        const int queueCount = 1;
        ::ae::gfx_low::QueueCreateInfo queueCreateInfos[queueCount];
        queueCreateInfos[0] =
            ::ae::gfx_low::QueueCreateInfo()
                .SetKind(::ae::gfx_low::QueueKind::Normal)
                .SetPriority(::ae::gfx_low::QueuePriority::Normal)
                .SetOperationCountMax(32);

        // Device の作成
        gfxLowDevice.reset(new ::ae::gfx_low::Device(
            ::ae::gfx_low::DeviceCreateInfo()
                .SetSystem(gfxLowSystem.get())
                .SetQueueCreateInfos(queueCount, queueCreateInfos)));
    }
    auto& queue = gfxLowDevice->Queue(0);

    // Swapchain の作成
    ::std::unique_ptr<::ae::gfx_low::SwapchainMaster> swapchainMaster;
    {
        auto& createInfo = ::ae::gfx_low::SwapchainMasterCreateInfo()
                               .SetDevice(gfxLowDevice.get())
                               .SetScreen(&display.mainScreen())
                               .SetSwapchainCountMax(1);
        swapchainMaster.reset(new ::ae::gfx_low::SwapchainMaster(createInfo));
    }
    const int swapchainImageCount = 3;
    auto swapchain = swapchainMaster->CreateSwapchain(
        ae::gfx_low::SwapchainCreateInfo().SetImageCount(swapchainImageCount));

    // CommandBuffer の作成
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::CommandBuffer> commandBuffers(
        swapchainImageCount);
    for (int i = 0; i < commandBuffers.countMax(); ++i) {
        commandBuffers.add(::ae::gfx_low::CommandBufferCreateInfo()
                               .SetDevice(gfxLowDevice.get())
                               .SetQueue(&queue));
    }

    // Fence の作成
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::Fence> fences(
        swapchainImageCount);
    for (int i = 0; i < fences.countMax(); ++i) {
        fences.add(
            ::ae::gfx_low::FenceCreateInfo().SetDevice(gfxLowDevice.get()));
    }

    // メインループ
    int bufferIndex = 0;
    while (app->receiveEvent() == ::ae::base::AppEvent::Update) {
        // ディスプレイが閉じてたら終了
        if (display.isClosed()) {
            app->quit();
            continue;
        }

        // 前回実行したコマンドの終了保証
        auto& fence = fences[bufferIndex];
        fence.Wait();

        // Swapchain バッファ確保要求
        swapchain->AcquireNextImage();

        // コマンドバッファ作成
        auto& cmd = commandBuffers[bufferIndex];
        cmd.BeginRecord();
        {
            // クリアカラー参考
            // https://www.colordic.org/colorscheme/7005
            {
                const ::ae::gfx_low::RenderTargetSpecInfo
                    renderTargetSpecInfos[] = {
                        swapchain->RenderTargetSpecInfo(),
                    };
                const ::ae::gfx_low::RenderTargetSetting
                    renderTargetSettings[] = {
                        ::ae::gfx_low::RenderTargetSetting()
                            .SetRenderTargetImageView(
                                &swapchain->CurrentRenderTargetImageView())
                            .SetLoadOp(::ae::gfx_low::AttachmentLoadOp::Clear)
                            .SetStoreOp(::ae::gfx_low::AttachmentStoreOp::Store)
                            .SetInitialImageResourceState(
                                ::ae::gfx_low::ImageResourceState::Unknown)
                            .SetFinalImageResourceState(
                                ::ae::gfx_low::ImageResourceState::RenderTarget)
                            .SetClearColor(
                                ::ae::base::Color4b(0x7f, 0xbf, 0xff, 0xff)
                                    .toRGBAf()),
                    };

                cmd.CmdBeginRenderPass(
                    ::ae::gfx_low::RenderPassBeginInfo()
                        .SetRenderPassSpecInfo(
                            ::ae::gfx_low::RenderPassSpecInfo()
                                .SetRenderTargetCount(1)
                                .SetRenderTargetSpecInfos(
                                    renderTargetSpecInfos))
                        .SetRenderTargetSettings(renderTargetSettings)
                        .SetRenderArea(
                            ::ae::base::Aabb2i(::ae::base::Vector2i::Zero(),
                                display.mainScreen().width(),
                                display.mainScreen().height())));
                cmd.CmdEndRenderPass();
            }
        }
        cmd.EndRecord();

        // Swapchain バッファ確保同期
        queue.PushSwapchainWait(&swapchain.Ref());

        // コマンド実行
        queue.PushCommandExecute(&cmd);

        // Swapchain 提出
        queue.PushSwapchainPresent(&swapchain.Ref());

        // GPU送信
        queue.Submit(&fence);

        // バッファを進める
        bufferIndex = (bufferIndex + 1) % swapchainImageCount;
    }

    // GPU 完了同期
    for (auto& fence : fences) {
        fence.Wait();
    }

    return 0;
#endif
}
// EOF
