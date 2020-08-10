// 文字コード：UTF-8
#include <ae/base/EntryPoint.hpp>

// includes
#include <ae/base/Angle.hpp>
#include <ae/base/AppEvent.hpp>
#include <ae/base/Application.hpp>
#include <ae/base/ArrayLength.hpp>
#include <ae/base/Color4b.hpp>
#include <ae/base/Console.hpp>
#include <ae/base/Degree.hpp>
#include <ae/base/Display.hpp>
#include <ae/base/Extent2.hpp>
#include <ae/base/Extent2i.hpp>
#include <ae/base/Matrix44.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/SdkHeader.hpp>
#include <ae/base/Vector3.hpp>
#include <ae/gfx_low/BufferResource.hpp>
#include <ae/gfx_low/BufferResourceCreateInfo.hpp>
#include <ae/gfx_low/CommandBuffer.hpp>
#include <ae/gfx_low/CommandBufferCreateInfo.hpp>
#include <ae/gfx_low/DepthStencilImageView.hpp>
#include <ae/gfx_low/DepthStencilImageViewCreateInfo.hpp>
#include <ae/gfx_low/DepthStencilSetting.hpp>
#include <ae/gfx_low/DepthStencilSpecInfo.hpp>
#include <ae/gfx_low/DescriptorSet.hpp>
#include <ae/gfx_low/DescriptorSetCreateInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/DeviceCreateInfo.hpp>
#include <ae/gfx_low/Fence.hpp>
#include <ae/gfx_low/FenceCreateInfo.hpp>
#include <ae/gfx_low/ImageResource.hpp>
#include <ae/gfx_low/ImageResourceCreateInfo.hpp>
#include <ae/gfx_low/Queue.hpp>
#include <ae/gfx_low/QueueCreateInfo.hpp>
#include <ae/gfx_low/RenderPassBeginInfo.hpp>
#include <ae/gfx_low/RenderPassSpecInfo.hpp>
#include <ae/gfx_low/RenderPipeline.hpp>
#include <ae/gfx_low/RenderPipelineCreateInfo.hpp>
#include <ae/gfx_low/RenderTargetBlendInfo.hpp>
#include <ae/gfx_low/RenderTargetSetting.hpp>
#include <ae/gfx_low/ResourceMemory.hpp>
#include <ae/gfx_low/ResourceMemoryAllocInfo.hpp>
#include <ae/gfx_low/ResourceMemoryRequirements.hpp>
#include <ae/gfx_low/ScissorSetting.hpp>
#include <ae/gfx_low/ShaderBindingInfo.hpp>
#include <ae/gfx_low/ShaderModuleResource.hpp>
#include <ae/gfx_low/ShaderModuleResourceCreateInfo.hpp>
#include <ae/gfx_low/Swapchain.hpp>
#include <ae/gfx_low/SwapchainCreateInfo.hpp>
#include <ae/gfx_low/SwapchainMaster.hpp>
#include <ae/gfx_low/SwapchainMasterCreateInfo.hpp>
#include <ae/gfx_low/System.hpp>
#include <ae/gfx_low/SystemCreateInfo.hpp>
#include <ae/gfx_low/UniformBufferView.hpp>
#include <ae/gfx_low/UniformBufferViewCreateinfo.hpp>
#include <ae/gfx_low/UniqueResourceMemory.hpp>
#include <ae/gfx_low/ViewportSetting.hpp>
#include <memory>

extern int WINAPI DemoWinMain(
    HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow);

//------------------------------------------------------------------------------
namespace {

struct fUniformDataType {
    float mvp[4][4];
    float position[12 * 3][4];
    float attr[12 * 3][4];
};

// clang-format off
const float fPositionData[] = {
    -1.0f,-1.0f,-1.0f,  // -X side
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,

    -1.0f,-1.0f,-1.0f,  // -Z side
     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,

    -1.0f,-1.0f,-1.0f,  // -Y side
     1.0f,-1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,

    -1.0f, 1.0f,-1.0f,  // +Y side
    -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,

     1.0f, 1.0f,-1.0f,  // +X side
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,

    -1.0f, 1.0f, 1.0f,  // +Z side
    -1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
};

const float fUvBufferData[] = {
    0.0f, 1.0f,  // -X side
    1.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f,

    1.0f, 1.0f,  // -Z side
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,

    1.0f, 0.0f,  // -Y side
    1.0f, 1.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    1.0f, 0.0f,  // +Y side
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    1.0f, 0.0f,  // +X side
    0.0f, 0.0f,
    0.0f, 1.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,

    0.0f, 0.0f,  // +Z side
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
};

const uint32_t fVertShaderCode[] = {
#include "uv_as_color.vert.inc"
};

const uint32_t fFragShaderCode[] = {
#include "uv_as_color.frag.inc"
};
// clang-format on

} // namespace

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
    display.Show();

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

        // 更にデバッグダンプ
        AE_BASE_COUTFMT_LINE("IsDeviceLocalMemoryShared: %d",
            gfxLowDevice->IsDeviceLocalMemoryShared() ? 1 : 0);

        // メモリ確保テスト
        {
            ::ae::gfx_low::ResourceMemory memory;

            // 確保できる前提のコード
            memory = gfxLowDevice->AllocResourceMemory(
                ::ae::gfx_low::ResourceMemoryAllocInfo()
                    .SetKind(::ae::gfx_low::ResourceMemoryKind::DeviceLocal)
                    .SetSize(4096));
            gfxLowDevice->FreeResourceMemory(memory);
            memory = gfxLowDevice->AllocResourceMemory(
                ::ae::gfx_low::ResourceMemoryAllocInfo()
                    .SetKind(::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
                    .SetSize(4096));
            gfxLowDevice->FreeResourceMemory(memory);
            memory = gfxLowDevice->AllocResourceMemory(
                ::ae::gfx_low::ResourceMemoryAllocInfo()
                    .SetKind(::ae::gfx_low::ResourceMemoryKind::SharedCached)
                    .SetSize(4096));
            gfxLowDevice->FreeResourceMemory(memory);

            // 確保に失敗する前提のコード
            memory = gfxLowDevice->TryToAllocResourceMemory(
                ::ae::gfx_low::ResourceMemoryAllocInfo()
                    .SetKind(::ae::gfx_low::ResourceMemoryKind::DeviceLocal)
                    .SetSize(1024ull * 1024ull * 1024ull * 1024ull * 1024ull));
            AE_BASE_ASSERT(!memory.IsValid());
        }
    }
    auto& queue = gfxLowDevice->Queue(0);

    // Swapchain の作成
    ::std::unique_ptr<::ae::gfx_low::SwapchainMaster> swapchainMaster;
    {
        auto& createInfo = ::ae::gfx_low::SwapchainMasterCreateInfo()
                               .SetDevice(gfxLowDevice.get())
                               .SetScreen(&display.MainScreen())
                               .SetSwapchainCountMax(1);
        swapchainMaster.reset(new ::ae::gfx_low::SwapchainMaster(createInfo));
    }
    const int swapchainImageCount = 3;
    auto swapchain = swapchainMaster->CreateSwapchain(
        ae::gfx_low::SwapchainCreateInfo().SetImageCount(swapchainImageCount));

    // DepthBuffer 作成
    const auto depthBufferFormat = ::ae::gfx_low::ImageFormat::D32Sfloat;
    ::ae::gfx_low::UniqueResourceMemory depthBufferMemory;
    ::std::unique_ptr<::ae::gfx_low::ImageResource> depthBufferImage;
    ::std::unique_ptr<::ae::gfx_low::DepthStencilImageView> depthBufferView;
    {
        const auto specInfo =
            ::ae::gfx_low::ImageResourceSpecInfo()
                .SetKind(::ae::gfx_low::ImageResourceKind::Image2d)
                .SetFormat(depthBufferFormat)
                .SetTiling(::ae::gfx_low::ImageResourceTiling::Optimal)
                .SetExtent(::ae::base::Extent2i(display.MainScreen().Width(),
                    display.MainScreen().Height()))
                .SetUsageBitSet(::ae::gfx_low::ImageResourceUsageBitSet().Set(
                    ::ae::gfx_low::ImageResourceUsage::DepthStencilImage,
                    true));
        depthBufferMemory.Reset(gfxLowDevice.get(),
            ::ae::gfx_low::ResourceMemoryAllocInfo()
                .SetKind(::ae::gfx_low::ResourceMemoryKind::DeviceLocal)
                .SetParams(
                    gfxLowDevice->CalcResourceMemoryRequirements(specInfo)));
        depthBufferImage.reset(new ::ae::gfx_low::ImageResource(
            ::ae::gfx_low::ImageResourceCreateInfo()
                .SetDevice(gfxLowDevice.get())
                .SetSpecInfo(specInfo)
                .SetDataAddress(*depthBufferMemory)));
        depthBufferView.reset(new ::ae::gfx_low::DepthStencilImageView(
            ::ae::gfx_low::DepthStencilImageViewCreateInfo()
                .SetDevice(gfxLowDevice.get())
                .SetResource(depthBufferImage.get())
                .SetKind(::ae::gfx_low::ImageViewKind::Image2d)
                .SetFormat(depthBufferFormat)));
    }

    // CommandBuffer の作成
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::CommandBuffer> commandBuffers(
        swapchainImageCount);
    for (int i = 0; i < commandBuffers.CountMax(); ++i) {
        commandBuffers.Add(::ae::gfx_low::CommandBufferCreateInfo()
                               .SetDevice(gfxLowDevice.get())
                               .SetQueue(&queue)
                               .SetRenderPassCountMax(16));
    }

    // Fence の作成
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::Fence> fences(
        swapchainImageCount);
    for (int i = 0; i < fences.CountMax(); ++i) {
        fences.Add(
            ::ae::gfx_low::FenceCreateInfo().SetDevice(gfxLowDevice.get()));
    }

    // Shader の作成
    ::ae::gfx_low::UniqueResourceMemory vertShaderMemory;
    std::unique_ptr<::ae::gfx_low::ShaderModuleResource> vertShader;
    ::ae::gfx_low::UniqueResourceMemory fragShaderMemory;
    std::unique_ptr<::ae::gfx_low::ShaderModuleResource> fragShader;
    {
        const auto size = sizeof(fVertShaderCode);
        const auto specInfo =
            ::ae::gfx_low::ShaderModuleResourceSpecInfo().SetSize(size);
        vertShaderMemory.Reset(gfxLowDevice.get(),
            ::ae::gfx_low::ResourceMemoryAllocInfo()
                .SetKind(::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
                .SetParams(
                    gfxLowDevice->CalcResourceMemoryRequirements(specInfo)));
        std::memcpy(gfxLowDevice->MapResourceMemory(*vertShaderMemory,
                        ::ae::gfx_low::ResourceMemoryRegion().SetSize(size)),
            fVertShaderCode, size);
        gfxLowDevice->UnmapResourceMemory(*vertShaderMemory);
        vertShader.reset(new ::ae::gfx_low::ShaderModuleResource(
            ::ae::gfx_low::ShaderModuleResourceCreateInfo()
                .SetDevice(gfxLowDevice.get())
                .SetSpecInfo(specInfo)
                .SetDataAddress(*vertShaderMemory)));
    }
    {
        const auto size = sizeof(fFragShaderCode);
        const auto specInfo =
            ::ae::gfx_low::ShaderModuleResourceSpecInfo().SetSize(size);
        fragShaderMemory.Reset(gfxLowDevice.get(),
            ::ae::gfx_low::ResourceMemoryAllocInfo()
                .SetKind(::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
                .SetParams(
                    gfxLowDevice->CalcResourceMemoryRequirements(specInfo)));
        std::memcpy(gfxLowDevice->MapResourceMemory(*fragShaderMemory,
                        ::ae::gfx_low::ResourceMemoryRegion().SetSize(size)),
            fFragShaderCode, size);
        gfxLowDevice->UnmapResourceMemory(*fragShaderMemory);
        fragShader.reset(new ::ae::gfx_low::ShaderModuleResource(
            ::ae::gfx_low::ShaderModuleResourceCreateInfo()
                .SetDevice(gfxLowDevice.get())
                .SetSpecInfo(specInfo)
                .SetDataAddress(*fragShaderMemory)));
    }

    // UniformBuffer の作成
    ::ae::gfx_low::UniqueResourceMemory uniformBufferMemory;
    ::std::unique_ptr<::ae::gfx_low::BufferResource> uniformBufferResource;
    ::std::unique_ptr<::ae::gfx_low::UniformBufferView> uniformBufferView;
    {
        const auto specInfo =
            ::ae::gfx_low::BufferResourceSpecInfo()
                .SetSize(sizeof(fUniformDataType))
                .SetUsageBitSet(::ae::gfx_low::BufferResourceUsageBitSet().Set(
                    ::ae::gfx_low::BufferResourceUsage::UniformBuffer, true));
        const auto region = ::ae::gfx_low::ResourceMemoryRegion().SetSize(
            sizeof(fUniformDataType));
        uniformBufferMemory.Reset(gfxLowDevice.get(),
            ::ae::gfx_low::ResourceMemoryAllocInfo()
                .SetKind(::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
                .SetParams(
                    gfxLowDevice->CalcResourceMemoryRequirements(specInfo)));
        uniformBufferResource.reset(new ::ae::gfx_low::BufferResource(
            ::ae::gfx_low::BufferResourceCreateInfo()
                .SetDevice(gfxLowDevice.get())
                .SetSpecInfo(specInfo)
                .SetDataAddress(*uniformBufferMemory)));
        uniformBufferView.reset(new ::ae::gfx_low::UniformBufferView(
            ::ae::gfx_low::UniformBufferViewCreateInfo()
                .SetDevice(gfxLowDevice.get())
                .SetResource(uniformBufferResource.get())
                .SetRegion(region)));

        // データ設定
        {
            // vec3 eye = {0.0f, 3.0f, 5.0f};
            // vec3 origin = {0, 0, 0};
            // vec3 up = {0.0f, 1.0f, 0.0};
            // mat4x4_perspective(projection_matrix,
            //    (float)degreesToRadians(45.0f), 1.0f, 0.1f, 100.0f);
            // mat4x4_look_at(view_matrix, eye, origin, up);
            // mat4x4_identity(model_matrix);
            // projection_matrix[1][1] *= -1;  // Flip projection matrix from GL
            // to Vulkan orientation.

            auto proj = ::ae::base::Matrix44::Perspective(
                ::ae::base::Angle(::ae::base::Degree(45.0f)),
                1.0f, // aspect
                0.1f, // near
                100.0f // far
            );
            proj.m[1][1] *= -1.0f;
            auto view = ::ae::base::Matrix44::LookAt(
                ::ae::base::Vector3(0.0f, 3.0f, 5.0f), // eyePos
                ::ae::base::Vector3::Zero(), // targetPos
                ::ae::base::Vector3::UnitY() // upVec
            );
            auto model = ::ae::base::Matrix44::Identity();
            auto vp = proj * view;
            auto mvp = vp * model;

            fUniformDataType data;
            memcpy(data.mvp, &mvp, sizeof(mvp));
            for (int i = 0; i < 12 * 3; ++i) {
                data.position[i][0] = fPositionData[i * 3];
                data.position[i][1] = fPositionData[i * 3 + 1];
                data.position[i][2] = fPositionData[i * 3 + 2];
                data.position[i][3] = 1.0f;
                data.attr[i][0] = fUvBufferData[2 * i];
                data.attr[i][1] = fUvBufferData[2 * i + 1];
                data.attr[i][2] = 0;
                data.attr[i][3] = 0;
            }

            void* mappedMemory = gfxLowDevice->MapResourceMemory(
                uniformBufferMemory->NativeObject_(), region);
            std::memcpy(mappedMemory, &data, sizeof(data));
            gfxLowDevice->UnmapResourceMemory(
                uniformBufferMemory->NativeObject_());
        }
    }

    // RenderPassSpecInfo の作成
    const ::ae::gfx_low::RenderTargetSpecInfo renderTargetSpecInfos[] = {
        swapchain->RenderTargetSpecInfo(),
    };
    const int renderTargetCount = AE_BASE_ARRAY_LENGTH(renderTargetSpecInfos);
    const auto depthStencilSpecInfo =
        ::ae::gfx_low::DepthStencilSpecInfo().SetImageFormat(depthBufferFormat);
    const auto renderPassSpecInfo =
        ::ae::gfx_low::RenderPassSpecInfo()
            .SetRenderTargetCount(renderTargetCount)
            .SetRenderTargetSpecInfos(renderTargetSpecInfos)
            .SetDepthStencilSpecInfoPtr(&depthStencilSpecInfo);

    // DescriptorSetSpecInfo の作成
    const ::ae::gfx_low::ShaderBindingInfo uniformBufferBindingInfos[] = {
        ::ae::gfx_low::ShaderBindingInfo()
            .SetStages(
                ::ae::gfx_low::ShaderBindingStageBitSet()
                    .Set(::ae::gfx_low::ShaderBindingStage::Vertex, true)
                    .Set(::ae::gfx_low::ShaderBindingStage::Fragment, true))
            .SetBindingIndex(0)};
    const auto descriptorSetSpecInfo =
        ::ae::gfx_low::DescriptorSetSpecInfo().SetBindingInfos(
            ::ae::gfx_low::DescriptorKind::UniformBuffer,
            AE_BASE_ARRAY_LENGTH(uniformBufferBindingInfos),
            uniformBufferBindingInfos);

    // DescriptorSet の作成
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::DescriptorSet> descriptorSets(
        swapchainImageCount);
    for (int i = 0; i < swapchainImageCount; ++i) {
        descriptorSets.Add(::ae::gfx_low::DescriptorSetCreateInfo()
                               .SetDevice(gfxLowDevice.get())
                               .SetSpecInfo(descriptorSetSpecInfo));
    }

    // GraphicsPipeline 生成
    std::unique_ptr<::ae::gfx_low::RenderPipeline> pipeline;
    {
        const ::ae::gfx_low::RenderTargetBlendInfo blendInfos[] = {
            ::ae::gfx_low::RenderTargetBlendInfo(),
        };
        AE_BASE_ARRAY_LENGTH_CHECK(
            blendInfos, AE_BASE_ARRAY_LENGTH(renderTargetSpecInfos));

        pipeline.reset(new ::ae::gfx_low::RenderPipeline(
            ::ae::gfx_low::RenderPipelineCreateInfo()
                .SetDevice(gfxLowDevice.get())
                .SetRenderPassSpecInfo(renderPassSpecInfo)
                .SetShaderInfo(::ae::gfx_low::RenderPipelineShaderStage::Vertex,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(vertShader.get())
                        .SetEntryPointNamePtr("main"))
                .SetDescriptorSetSpecInfo(descriptorSetSpecInfo)
                .SetShaderInfo(
                    ::ae::gfx_low::RenderPipelineShaderStage::Fragment,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(fragShader.get())
                        .SetEntryPointNamePtr("main"))
                .SetPrimitiveTopologyKind(
                    ::ae::gfx_low::PrimitiveTopologyKind::TriangleList)
                .SetRasterizerInfo(
                    ::ae::gfx_low::PipelineRasterizerInfo().SetFrontFace(
                        ::ae::gfx_low::PolygonFrontFace::CounterClockwise))
                .SetDepthStencilInfo(
                    ::ae::gfx_low::PipelineDepthStencilInfo()
                        .SetDepthTestEnable(true)
                        .SetDepthWriteEnable(true)
                        .SetDepthCompareOp(::ae::gfx_low::CompareOp::LessEqual))
                .SetBlendInfo(::ae::gfx_low::PipelineBlendInfo()
                                  .SetRenderTargetBlendInfos(blendInfos))));
    }

    // メインループ
    int bufferIndex = 0;
    while (app->ReceiveEvent() == ::ae::base::AppEvent::Update) {
        // ディスプレイが閉じてたら終了
        if (display.IsClosed()) {
            app->Quit();
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
                                ::ae::gfx_low::ImageResourceState::PresentSrc)
                            .SetClearColor(
                                ::ae::base::Color4b(0x7f, 0xbf, 0xff, 0xff)
                                    .ToRGBAf()),
                    };
                const auto depthStencilSetting =
                    ::ae::gfx_low::DepthStencilSetting()
                        .SetDepthStencilImageView(depthBufferView.get())
                        .SetInitialImageResourceState(
                            ::ae::gfx_low::ImageResourceState::Unknown)
                        .SetFinalImageResourceState(
                            ::ae::gfx_low::ImageResourceState::DepthStencil)
                        .SetDepthLoadOp(::ae::gfx_low::AttachmentLoadOp::Clear)
                        .SetDepthStoreOp(
                            ::ae::gfx_low::AttachmentStoreOp::Store)
                        .SetDepthClearValue(0.0f)
                        .SetStencilLoadOp(
                            ::ae::gfx_low::AttachmentLoadOp::Clear)
                        .SetStencilStoreOp(
                            ::ae::gfx_low::AttachmentStoreOp::Store)
                        .SetStencilClearValue(0);

                cmd.CmdBeginRenderPass(
                    ::ae::gfx_low::RenderPassBeginInfo()
                        .SetRenderPassSpecInfo(renderPassSpecInfo)
                        .SetRenderTargetSettings(renderTargetSettings)
                        .SetDepthStencilSettingPtr(&depthStencilSetting)
                        .SetRenderArea(
                            ::ae::base::Aabb2i(::ae::base::Vector2i::Zero(),
                                display.MainScreen().Extent())));

                // Viewport
                {
                    const ::ae::gfx_low::ViewportSetting settings[] = {
                        ::ae::gfx_low::ViewportSetting().SetRect(
                            ::ae::base::Aabb2(::ae::base::Vector2::Zero(),
                                display.MainScreen().Extent().ToExtent2())),
                    };
                    AE_BASE_ARRAY_LENGTH_CHECK(settings, renderTargetCount);
                    cmd.CmdSetViewports(renderTargetCount, settings);
                }

                // Scissor
                {
                    const ::ae::gfx_low::ScissorSetting settings[] = {
                        ::ae::gfx_low::ScissorSetting().SetRect(
                            ::ae::base::Aabb2i(::ae::base::Vector2i::Zero(),
                                display.MainScreen().Extent())),
                    };
                    AE_BASE_ARRAY_LENGTH_CHECK(settings, renderTargetCount);
                    cmd.CmdSetScissors(renderTargetCount, settings);
                }

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
