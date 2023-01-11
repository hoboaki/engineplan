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
#include <ae/base/Matrix34.hpp>
#include <ae/base/Matrix44.hpp>
#include <ae/base/Quaternion.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/SdkHeader.hpp>
#include <ae/base/Vector3.hpp>
#include <ae/gfx_low/BufferResource.hpp>
#include <ae/gfx_low/BufferResourceCreateInfo.hpp>
#include <ae/gfx_low/CommandBuffer.hpp>
#include <ae/gfx_low/CommandBufferCreateInfo.hpp>
#include <ae/gfx_low/ComputePassBeginInfo.hpp>
#include <ae/gfx_low/ComputePipeline.hpp>
#include <ae/gfx_low/ComputePipelineCreateInfo.hpp>
#include <ae/gfx_low/CopyBufferToImageInfo.hpp>
#include <ae/gfx_low/DepthStencilSetting.hpp>
#include <ae/gfx_low/DepthStencilSpecInfo.hpp>
#include <ae/gfx_low/DescriptorSet.hpp>
#include <ae/gfx_low/DescriptorSetCreateInfo.hpp>
#include <ae/gfx_low/DescriptorSetUpdateInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/DispatchCallInfo.hpp>
#include <ae/gfx_low/DrawCallInfo.hpp>
#include <ae/gfx_low/Fence.hpp>
#include <ae/gfx_low/FenceCreateInfo.hpp>
#include <ae/gfx_low/ImageResource.hpp>
#include <ae/gfx_low/ImageResourceBarrierInfo.hpp>
#include <ae/gfx_low/ImageResourceCreateInfo.hpp>
#include <ae/gfx_low/ImageSubresourceDataInfo.hpp>
#include <ae/gfx_low/ImageSubresourceLocation.hpp>
#include <ae/gfx_low/Queue.hpp>
#include <ae/gfx_low/RenderPass.hpp>
#include <ae/gfx_low/RenderPassBeginInfo.hpp>
#include <ae/gfx_low/RenderPassCreateInfo.hpp>
#include <ae/gfx_low/RenderPassSpecInfo.hpp>
#include <ae/gfx_low/RenderPipeline.hpp>
#include <ae/gfx_low/RenderPipelineCreateInfo.hpp>
#include <ae/gfx_low/RenderTargetBlendInfo.hpp>
#include <ae/gfx_low/RenderTargetSetting.hpp>
#include <ae/gfx_low/ResourceMemory.hpp>
#include <ae/gfx_low/ResourceMemoryAllocInfo.hpp>
#include <ae/gfx_low/ResourceMemoryRequirements.hpp>
#include <ae/gfx_low/SampledImageDescriptorInfo.hpp>
#include <ae/gfx_low/SampledImageView.hpp>
#include <ae/gfx_low/SampledImageViewCreateInfo.hpp>
#include <ae/gfx_low/Sampler.hpp>
#include <ae/gfx_low/SamplerCreateInfo.hpp>
#include <ae/gfx_low/SamplerDescriptorInfo.hpp>
#include <ae/gfx_low/ScissorSetting.hpp>
#include <ae/gfx_low/ShaderBindingInfo.hpp>
#include <ae/gfx_low/StorageImageDescriptorInfo.hpp>
#include <ae/gfx_low/StorageImageView.hpp>
#include <ae/gfx_low/StorageImageViewCreateInfo.hpp>
#include <ae/gfx_low/Swapchain.hpp>
#include <ae/gfx_low/SwapchainHandle.hpp>
#include <ae/gfx_low/System.hpp>
#include <ae/gfx_low/SystemCreateInfo.hpp>
#include <ae/gfx_low/UniformBufferDescriptorInfo.hpp>
#include <ae/gfx_low/UniqueResourceMemory.hpp>
#include <ae/gfx_low/VertexAttributeInfo.hpp>
#include <ae/gfx_low/ViewportSetting.hpp>
#include <aesk/GeometryCube.hpp>
#include <aesk/GfxBasicKit.hpp>
#include <aesk/Shader.hpp>
#include <aesk/UniformBuffer.hpp>
#include <aesk/VertexBuffer.hpp>
#include <memory>

//------------------------------------------------------------------------------
namespace {

struct fUniformDataType
{
    float mvp[4][4];
};

const int fThreadsPerThreadGroupX = 16;
const int fThreadsPerThreadGroupY = 16;

const uint32_t fCompShaderCode[] = {
#include "Shader.comp.inc"
};

const uint32_t fVertShaderCode[] = {
#include "Shader.vert.inc"
};

const uint32_t fFragShaderCode[] = {
#include "Shader.frag.inc"
};

// clang-format on

} // namespace

//------------------------------------------------------------------------------
int aemain(::ae::base::Application* app)
{
    // コンソール出力
    AE_BASE_COUT_LINE_WITH_TIME("Adel runtime start.");

    // ディスプレイの作成
    ::ae::base::Display display =
        ::ae::base::Display(::ae::base::DisplayContext()
                                .SetWindowTitle("AeVulkan05 - Storage Image")
                                .SetIsResizableWindow(true));

    // ディスプレイの表示
    display.Show();

    // 基本キット
    ::aesk::GfxBasicKit gfxKit(&display);

    // Shader の作成
    ::aesk::Shader compShader(
        &gfxKit,
        fCompShaderCode,
        sizeof(fCompShaderCode));
    ::aesk::Shader vertShader(
        &gfxKit,
        fVertShaderCode,
        sizeof(fVertShaderCode));
    ::aesk::Shader fragShader(
        &gfxKit,
        fFragShaderCode,
        sizeof(fFragShaderCode));

    // VertexBuffer の作成
    ::aesk::GeometryCube geometryCube;
    const auto vertexBufferLayoutInfo =
        ::ae::gfx_low::VertexBufferLayoutInfo().SetStride(geometryCube.Stride());
    const ::ae::gfx_low::VertexAttributeInfo vertexAttrInfos[] = {
        ::ae::gfx_low::VertexAttributeInfo()
            .SetFormat(::ae::gfx_low::VertexFormat::Sfloat32x3)
            .SetOffset(geometryCube.OffsetPosition()),
        ::ae::gfx_low::VertexAttributeInfo()
            .SetFormat(::ae::gfx_low::VertexFormat::Sfloat32x2)
            .SetOffset(geometryCube.OffsetUv0()),
    };
    ::aesk::VertexBuffer vertexBuffer(
        &gfxKit.Device(),
        geometryCube.Data().Size(),
        vertexBufferLayoutInfo);
    vertexBuffer.StoreToResourceMemory(geometryCube.Data());

    // ポリゴンに貼り付けるテクスチャの作成（画像の内容はコンピュートシェーダーで作成）
    ::ae::gfx_low::UniqueResourceMemory textureMemory;
    ::std::unique_ptr<::ae::gfx_low::ImageResource> textureImage;
    ::std::unique_ptr<::ae::gfx_low::SampledImageView> textureView;
    ::std::unique_ptr<::ae::gfx_low::StorageImageView> storageTextureView;
    const auto textureImageExtent = ::ae::base::Extent2i(512, 512);
    {
        const auto format = ::ae::gfx_low::ImageFormat::R8G8B8A8Unorm;
        const auto baseSpecInfo =
            ::ae::gfx_low::ImageResourceSpecInfo()
                .SetKind(::ae::gfx_low::ImageResourceKind::Image2d)
                .SetFormat(format)
                .SetExtent(textureImageExtent);
        ::ae::gfx_low::ImageSubresourceDataInfo dataInfo;

        // メモ：
        // コンピュートシェーダーでイメージの内容を作成するので
        // デバイスメモリが共有か否かは関係ない
        const auto specInfo =
            ::ae::gfx_low::ImageResourceSpecInfo(baseSpecInfo)
                .SetTiling(::ae::gfx_low::ImageResourceTiling::Optimal)
                .SetUsageBitSet(
                    ::ae::gfx_low::ImageResourceUsageBitSet()
                        .Set(
                            ::ae::gfx_low::ImageResourceUsage::SampledImage,
                            true)
                        .Set(
                            ::ae::gfx_low::ImageResourceUsage::StorageImage,
                            true));
        textureMemory.Reset(
            &gfxKit.Device(),
            ::ae::gfx_low::ResourceMemoryAllocInfo()
                .SetKind(::ae::gfx_low::ResourceMemoryKind::DeviceLocal)
                .SetParams(
                    gfxKit.Device().CalcResourceMemoryRequirements(specInfo)));
        textureImage.reset(new ::ae::gfx_low::ImageResource(
            ::ae::gfx_low::ImageResourceCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetSpecInfo(specInfo)
                .SetDataAddress(textureMemory->Address())));

        // サンプラー用イメージビューの作成
        textureView.reset(new ::ae::gfx_low::SampledImageView(
            ::ae::gfx_low::SampledImageViewCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetResource(textureImage.get())
                .SetKind(::ae::gfx_low::ImageViewKind::Image2d)
                .SetFormat(format)));

        // ストレージ用イメージビューの作成
        storageTextureView.reset(new ::ae::gfx_low::StorageImageView(
            ::ae::gfx_low::StorageImageViewCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetResource(textureImage.get())
                .SetKind(::ae::gfx_low::ImageViewKind::Image2d)
                .SetFormat(format)));
    }

    // Sampler の作成
    ::std::unique_ptr<::ae::gfx_low::Sampler> sampler;
    {
        sampler.reset(new ::ae::gfx_low::Sampler(
            ::ae::gfx_low::SamplerCreateInfo().SetDevice(&gfxKit.Device())));
    }

    // UniformBuffer の作成
    ::aesk::UniformBuffer uniformBuffer(
        &gfxKit.Device(),
        sizeof(fUniformDataType),
        gfxKit.SwapchainImageCount());

    // RenderPassSpecInfo の作成
    const ::ae::gfx_low::RenderTargetSpecInfo renderTargetSpecInfos[] = {
        gfxKit.Swapchain()->RenderTargetSpecInfo(),
    };
    const int renderTargetCount = AE_BASE_ARRAY_LENGTH(renderTargetSpecInfos);
    const auto depthStencilSpecInfo =
        ::ae::gfx_low::DepthStencilSpecInfo().SetImageFormat(
            gfxKit.DepthBufferFormat());
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
            .SetBindingIndex(0)
    };
    const ::ae::gfx_low::ShaderBindingInfo sampledImageBindingInfos[] = {
        ::ae::gfx_low::ShaderBindingInfo()
            .SetStages(::ae::gfx_low::ShaderBindingStageBitSet().Set(
                ::ae::gfx_low::ShaderBindingStage::Fragment,
                true))
            .SetBindingIndex(0)
    };
    const ::ae::gfx_low::ShaderBindingInfo samplerBindingInfos[] = {
        ::ae::gfx_low::ShaderBindingInfo()
            .SetStages(::ae::gfx_low::ShaderBindingStageBitSet().Set(
                ::ae::gfx_low::ShaderBindingStage::Fragment,
                true))
            .SetBindingIndex(0)
    };
    const auto graphicsDescriptorSetSpecInfo =
        ::ae::gfx_low::DescriptorSetSpecInfo()
            .SetBindingInfos(
                ::ae::gfx_low::DescriptorKind::UniformBuffer,
                AE_BASE_ARRAY_LENGTH(uniformBufferBindingInfos),
                uniformBufferBindingInfos)
            .SetBindingInfos(
                ::ae::gfx_low::DescriptorKind::SampledImage,
                AE_BASE_ARRAY_LENGTH(sampledImageBindingInfos),
                sampledImageBindingInfos)
            .SetBindingInfos(
                ::ae::gfx_low::DescriptorKind::Sampler,
                AE_BASE_ARRAY_LENGTH(samplerBindingInfos),
                samplerBindingInfos);
    const ::ae::gfx_low::ShaderBindingInfo storageImageBindingInfos[] = {
        ::ae::gfx_low::ShaderBindingInfo()
            .SetStages(::ae::gfx_low::ShaderBindingStageBitSet().Set(
                ::ae::gfx_low::ShaderBindingStage::Compute,
                true))
            .SetBindingIndex(0)
    };
    const auto computeDescriptorSetSpecInfo =
        ::ae::gfx_low::DescriptorSetSpecInfo().SetBindingInfos(
            ::ae::gfx_low::DescriptorKind::StorageImage,
            AE_BASE_ARRAY_LENGTH(storageImageBindingInfos),
            storageImageBindingInfos);

    // GraphicsPipeline 用 DescriptorSet の作成
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::DescriptorSet>
        graphicsDescriptorSets(gfxKit.SwapchainImageCount());
    for (int i = 0; i < gfxKit.SwapchainImageCount(); ++i) {
        graphicsDescriptorSets.Add(
            ::ae::gfx_low::DescriptorSetCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetSpecInfo(graphicsDescriptorSetSpecInfo));

        // UniformBuffer
        const ::ae::gfx_low::UniformBufferView* localUniformBufferViews[] = {
            &uniformBuffer.View(i)
        };
        const ::ae::gfx_low::UniformBufferDescriptorInfo
            uniformBufferDescs[] = {
                ::ae::gfx_low::UniformBufferDescriptorInfo()
                    .SetRegion(::ae::gfx_low::ShaderBindingRegion()
                                   .SetBindingIndex(0)
                                   .SetElemCount(AE_BASE_ARRAY_LENGTH(
                                       localUniformBufferViews)))
                    .SetViews(localUniformBufferViews),
            };

        // SampledImage
        const ::ae::gfx_low::SampledImageView* sampledImageViews[] = {
            textureView.get()
        };
        const ::ae::gfx_low::SampledImageDescriptorInfo sampledImageDescs[] = {
            ::ae::gfx_low::SampledImageDescriptorInfo()
                .SetRegion(
                    ::ae::gfx_low::ShaderBindingRegion()
                        .SetBindingIndex(0)
                        .SetElemCount(AE_BASE_ARRAY_LENGTH(sampledImageViews)))
                .SetViews(sampledImageViews),
        };

        // Sampler
        const ::ae::gfx_low::Sampler* samplers[] = { sampler.get() };
        const ::ae::gfx_low::SamplerDescriptorInfo samplerDescs[] = {
            ::ae::gfx_low::SamplerDescriptorInfo()
                .SetRegion(::ae::gfx_low::ShaderBindingRegion()
                               .SetBindingIndex(0)
                               .SetElemCount(AE_BASE_ARRAY_LENGTH(samplers)))
                .SetSamplers(samplers),
        };

        // 更新
        graphicsDescriptorSets[i].Update(
            ::ae::gfx_low::DescriptorSetUpdateInfo()
                .SetUniformBufferInfos(
                    AE_BASE_ARRAY_LENGTH(uniformBufferDescs),
                    uniformBufferDescs)
                .SetSampledImageInfos(
                    AE_BASE_ARRAY_LENGTH(sampledImageDescs),
                    sampledImageDescs)
                .SetSamplerInfos(
                    AE_BASE_ARRAY_LENGTH(samplerDescs),
                    samplerDescs));
    }

    // ComputePipeline 用 DescriptorSet の作成
    ::ae::gfx_low::DescriptorSet computeDescriptorSet(
        ::ae::gfx_low::DescriptorSetCreateInfo()
            .SetDevice(&gfxKit.Device())
            .SetSpecInfo(computeDescriptorSetSpecInfo));
    {
        // StorageImage
        const ::ae::gfx_low::StorageImageView* storageImageViews[] = {
            storageTextureView.get()
        };
        const ::ae::gfx_low::StorageImageDescriptorInfo storageImageDescs[] = {
            ::ae::gfx_low::StorageImageDescriptorInfo()
                .SetRegion(
                    ::ae::gfx_low::ShaderBindingRegion()
                        .SetBindingIndex(0)
                        .SetElemCount(AE_BASE_ARRAY_LENGTH(storageImageViews)))
                .SetViews(storageImageViews),
        };

        // 更新
        computeDescriptorSet.Update(
            ::ae::gfx_low::DescriptorSetUpdateInfo()
                .SetStorageImageInfos(
                    AE_BASE_ARRAY_LENGTH(storageImageDescs),
                    storageImageDescs));
    }

    // GraphicsPipeline 生成
    std::unique_ptr<::ae::gfx_low::RenderPipeline> graphicsPipeline;
    {
        const ::ae::gfx_low::RenderTargetBlendInfo blendInfos[] = {
            ::ae::gfx_low::RenderTargetBlendInfo(),
        };
        AE_BASE_ARRAY_LENGTH_CHECK(
            blendInfos,
            AE_BASE_ARRAY_LENGTH(renderTargetSpecInfos));

        graphicsPipeline.reset(new ::ae::gfx_low::RenderPipeline(
            ::ae::gfx_low::RenderPipelineCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetRenderPassSpecInfo(renderPassSpecInfo)
                .SetShaderInfo(
                    ::ae::gfx_low::RenderPipelineShaderStage::Vertex,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(&vertShader.Resource())
                        .SetEntryPointNamePtr("main"))
                .SetShaderInfo(
                    ::ae::gfx_low::RenderPipelineShaderStage::Fragment,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(&fragShader.Resource())
                        .SetEntryPointNamePtr("main"))
                .SetDescriptorSetSpecInfo(graphicsDescriptorSetSpecInfo)
                .SetVertexInputInfo(
                    ::ae::gfx_low::PipelineVertexInputInfo()
                        .SetBufferCount(1)
                        .SetBufferLayoutInfos(&vertexBufferLayoutInfo)
                        .SetAttributeCount(
                            AE_BASE_ARRAY_LENGTH(vertexAttrInfos))
                        .SetAttributeInfos(vertexAttrInfos))
                .SetPrimitiveTopologyKind(
                    ::ae::gfx_low::PrimitiveTopologyKind::TriangleList)
                .SetRasterizerInfo(
                    ::ae::gfx_low::PipelineRasterizerInfo()
                        .SetFrontFace(
                            ::ae::gfx_low::PolygonFrontFace::CounterClockwise)
                        .SetCullMode(::ae::gfx_low::RasterizeCullMode::Back))
                .SetDepthStencilInfo(
                    ::ae::gfx_low::PipelineDepthStencilInfo()
                        .SetDepthTestEnable(true)
                        .SetDepthWriteEnable(true)
                        .SetDepthCompareOp(::ae::gfx_low::CompareOp::LessEqual))
                .SetBlendInfo(::ae::gfx_low::PipelineBlendInfo()
                                  .SetRenderTargetBlendInfos(blendInfos))));
    }

    // ComputePipeline 生成
    ::ae::gfx_low::ComputePipeline computePipeline(
        ::ae::gfx_low::ComputePipelineCreateInfo()
            .SetDevice(&gfxKit.Device())
            .SetShaderInfo(::ae::gfx_low::PipelineShaderInfo()
                               .SetResource(&compShader.Resource())
                               .SetEntryPointNamePtr("main"))
            .SetDescriptorSetSpecInfo(computeDescriptorSetSpecInfo));

    // RenderPass 領域を事前確保
    ::ae::base::RuntimeArray<::std::unique_ptr<::ae::gfx_low::RenderPass>>
        renderPassArray;
    renderPassArray.Resize(gfxKit.SwapchainImageCount());

    // メインループ
    bool isFinishedSetupTexture = false;
    int frameCount = 0;
    while (app->ReceiveEvent() == ::ae::base::AppEvent::Update) {
        // ディスプレイが閉じてたら終了
        if (display.IsClosed()) {
            app->Quit();
            continue;
        }

        // 最小化中はループして待つ
        if (display.MainScreen().Extent().IsZero()) {
            continue;
        }

        // 前回実行したコマンドの終了保証
        gfxKit.WaitToResourceUsable();

        // スクリーンリサイズ処理
        gfxKit.ScreenResizeProcessIfNeeds();

        // Swapchain バッファ確保要求
        gfxKit.Swapchain()->AcquireNextImage();
        const auto bufferIndex = gfxKit.CurrentBufferIndex();

        // ユニフォームバッファ更新
        // （画面更新を確認するために毎フレーム更新）
        {
            auto proj = ::ae::base::Matrix44::Perspective(
                ::ae::base::Angle(::ae::base::Degree(25.0f)),
                float(display.MainScreen().Width()) /
                    display.MainScreen().Height(), // aspect
                0.1f, // near
                100.0f // far
            );
            auto view = ::ae::base::Matrix44::LookAt(
                ::ae::base::Vector3(0.0f, 3.0f, 5.0f), // eyePos
                ::ae::base::Vector3::Zero(), // targetPos
                ::ae::base::Vector3::UnitY() // upVec
            );
            auto model =
                ::ae::base::Quaternion(
                    ::ae::base::Vector3::UnitY(),
                    ::ae::base::Degree(3.0f * frameCount))
                    .ToRotateMatrix()
                    .ToMatrix44();
            auto vp = proj * view;
            auto mvp = vp * model;

            fUniformDataType data;
            memcpy(data.mvp, &mvp, sizeof(mvp));

            uniformBuffer.StoreToResourceMemory(bufferIndex, data);
        }

        // コマンドバッファ作成
        auto& cmd = gfxKit.CurrentCommandBuffer();
        cmd.BeginRecord();
        {
            // テクスチャのセットアップ
            if (!isFinishedSetupTexture) {
                // 書き込み可能状態に移行
                cmd.CmdImageResourceBarrier(
                    ::ae::gfx_low::ImageResourceBarrierInfo()
                        .SetResource(textureImage.get())
                        .SetOldState(::ae::gfx_low::ImageResourceState::Unknown)
                        .SetNewState(::ae::gfx_low::ImageResourceState::ShaderResource));

                // コンピュートシェーダーを実行してテクスチャを作成
                cmd.CmdBeginComputePass(::ae::gfx_low::ComputePassBeginInfo());
                cmd.CmdSetComputePipeline(computePipeline);
                cmd.CmdSetDescriptorSet(computeDescriptorSet);
                cmd.CmdDispatch(
                    ::ae::gfx_low::DispatchCallInfo()
                        .SetThreadsPerThreadGroup(::ae::base::Extent3i(
                            fThreadsPerThreadGroupX,
                            fThreadsPerThreadGroupY,
                            1))
                        .SetThreadGroups(::ae::base::Extent3i(
                            textureImageExtent.width / fThreadsPerThreadGroupX,
                            textureImageExtent.height / fThreadsPerThreadGroupY,
                            1)));
                cmd.CmdEndComputePass();

                // 読み込み専用状態に移行
                cmd.CmdImageResourceBarrier(
                    ::ae::gfx_low::ImageResourceBarrierInfo()
                        .SetResource(textureImage.get())
                        .SetOldState(
                            ::ae::gfx_low::ImageResourceState::ShaderResource)
                        .SetNewState(::ae::gfx_low::ImageResourceState::ShaderResourceReadOnly));
                isFinishedSetupTexture = true;
            }

            // レンダーパス準備
            // クリアカラー参考：https://www.colordic.org/colorscheme/7005
            auto& renderPassUniquePtr = renderPassArray[bufferIndex];
            {
                renderPassUniquePtr.reset();

                const ::ae::gfx_low::RenderTargetSetting
                    renderTargetSettings[] = {
                        ::ae::gfx_low::RenderTargetSetting()
                            .SetRenderTargetImageView(
                                &gfxKit.Swapchain()
                                     ->CurrentRenderTargetImageView())
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
                        .SetDepthStencilImageView(&gfxKit.DepthBufferView())
                        .SetInitialImageResourceState(
                            ::ae::gfx_low::ImageResourceState::Unknown)
                        .SetFinalImageResourceState(
                            ::ae::gfx_low::ImageResourceState::DepthStencil)
                        .SetDepthLoadOp(::ae::gfx_low::AttachmentLoadOp::Clear)
                        .SetDepthStoreOp(
                            ::ae::gfx_low::AttachmentStoreOp::Store)
                        .SetDepthClearValue(1.0f)
                        .SetStencilLoadOp(
                            ::ae::gfx_low::AttachmentLoadOp::Clear)
                        .SetStencilStoreOp(
                            ::ae::gfx_low::AttachmentStoreOp::Store)
                        .SetStencilClearValue(0);
                renderPassUniquePtr.reset(new ::ae::gfx_low::RenderPass(
                    ::ae::gfx_low::RenderPassCreateInfo()
                        .SetDevice(&gfxKit.Device())
                        .SetRenderPassSpecInfo(renderPassSpecInfo)
                        .SetRenderTargetSettings(renderTargetSettings)
                        .SetDepthStencilSettingPtr(&depthStencilSetting)
                        .SetRenderArea(::ae::base::Aabb2i(
                            ::ae::base::Vector2i::Zero(),
                            display.MainScreen().Extent()))));
            }

            // レンダーパス処理
            {
                // 開始
                cmd.CmdBeginRenderPass(
                    ::ae::gfx_low::RenderPassBeginInfo().SetRenderPass(
                        renderPassUniquePtr.get()));

                // Viewport
                {
                    const ::ae::gfx_low::ViewportSetting settings[] = {
                        ::ae::gfx_low::ViewportSetting().SetRect(
                            ::ae::base::Aabb2(
                                ::ae::base::Vector2::Zero(),
                                display.MainScreen().Extent().ToExtent2())),
                    };
                    AE_BASE_ARRAY_LENGTH_CHECK(settings, renderTargetCount);
                    cmd.CmdSetViewports(renderTargetCount, settings);
                }

                // Scissor
                {
                    const ::ae::gfx_low::ScissorSetting settings[] = {
                        ::ae::gfx_low::ScissorSetting().SetRect(
                            ::ae::base::Aabb2i(
                                ::ae::base::Vector2i::Zero(),
                                display.MainScreen().Extent())),
                    };
                    AE_BASE_ARRAY_LENGTH_CHECK(settings, renderTargetCount);
                    cmd.CmdSetScissors(renderTargetCount, settings);
                }

                // Pipeline & DescriptorSet
                cmd.CmdSetRenderPipeline(*graphicsPipeline);
                cmd.CmdSetDescriptorSet(graphicsDescriptorSets[bufferIndex]);

                // Draw
                cmd.CmdSetVertexBuffer(0, vertexBuffer.View());
                cmd.CmdDraw(
                    ::ae::gfx_low::DrawCallInfo().SetVertexCount(12 * 3));

                // 終了
                cmd.CmdEndRenderPass();
            }
        }
        cmd.EndRecord();

        // Swapchain バッファ確保同期
        gfxKit.Queue().PushSwapchainWait(&gfxKit.Swapchain().Ref());

        // コマンド実行
        gfxKit.Queue().PushCommandExecute(&cmd);

        // Swapchain 提出
        gfxKit.Queue().PushSwapchainPresent(&gfxKit.Swapchain().Ref());

        // GPU送信
        gfxKit.QueueSubmit();

        // フレームを進める
        ++frameCount;
    }

    // GPU 完了同期
    gfxKit.WaitAllDone();

    return 0;
}
// EOF
