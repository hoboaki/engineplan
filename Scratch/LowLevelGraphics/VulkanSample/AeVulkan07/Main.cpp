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
#include <ae/gfx_low/CopyBufferToImageInfo.hpp>
#include <ae/gfx_low/DepthStencilSetting.hpp>
#include <ae/gfx_low/DepthStencilSpecInfo.hpp>
#include <ae/gfx_low/DescriptorSet.hpp>
#include <ae/gfx_low/DescriptorSetCreateInfo.hpp>
#include <ae/gfx_low/DescriptorSetUpdateInfo.hpp>
#include <ae/gfx_low/Device.hpp>
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
#include <ae/gfx_low/RenderTargetImageView.hpp>
#include <ae/gfx_low/RenderTargetImageViewCreateInfo.hpp>
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
#include <ae/gfx_low/Swapchain.hpp>
#include <ae/gfx_low/SwapchainHandle.hpp>
#include <ae/gfx_low/System.hpp>
#include <ae/gfx_low/SystemCreateInfo.hpp>
#include <ae/gfx_low/UniformBufferDescriptorInfo.hpp>
#include <ae/gfx_low/UniqueResourceMemory.hpp>
#include <ae/gfx_low/VertexAttributeInfo.hpp>
#include <ae/gfx_low/ViewportSetting.hpp>
#include <aesk/GeometrySquare.hpp>
#include <aesk/GfxBasicKit.hpp>
#include <aesk/Shader.hpp>
#include <aesk/UniformBuffer.hpp>
#include <aesk/VertexBuffer.hpp>
#include <memory>

//------------------------------------------------------------------------------
namespace {

struct fMultiUniformDataType
{
    ::ae::base::Matrix44Pod mvp;
    ::ae::base::Vector4fPod uvTrans;
};

struct fMixUniformDataType
{
    ::ae::base::Matrix44Pod mvp;
};

// clang-format off

const uint32_t fMultiVertShaderCode[] = {
#include "ShaderMulti.vert.inc"
};

const uint32_t fMultiFragShaderCode[] = {
#include "ShaderMulti.frag.inc"
};

const uint32_t fMixVertShaderCode[] = {
#include "ShaderMix.vert.inc"
};

const uint32_t fMixFragShaderCode[] = {
#include "ShaderMix.frag.inc"
};

// clang-format on

} // namespace

//------------------------------------------------------------------------------
int aemain(::ae::base::Application* app)
{
    // コンソール出力
    AE_BASE_COUT_LINE_WITH_TIME("Adel runtime start.");

    // ディスプレイの作成
    ::ae::base::Display display = ::ae::base::Display(
        ::ae::base::DisplayContext()
            .SetWindowTitle("AeVulkan07 - Multi Render Target")
            .SetIsResizableWindow(true));

    // ディスプレイの表示
    display.Show();

    // 基本キット
    ::aesk::GfxBasicKit gfxKit(&display);

    // Shader の作成
    ::aesk::Shader multiVertShader(
        &gfxKit,
        fMultiVertShaderCode,
        sizeof(fMultiVertShaderCode));
    ::aesk::Shader multiFragShader(
        &gfxKit,
        fMultiFragShaderCode,
        sizeof(fMultiFragShaderCode));
    ::aesk::Shader mixVertShader(
        &gfxKit,
        fMixVertShaderCode,
        sizeof(fMixVertShaderCode));
    ::aesk::Shader mixFragShader(
        &gfxKit,
        fMixFragShaderCode,
        sizeof(fMixFragShaderCode));

    // VertexBuffer の作成
    ::aesk::GeometrySquare geometrySquare;
    const auto vertexBufferLayoutInfo =
        ::ae::gfx_low::VertexBufferLayoutInfo().SetStride(
            geometrySquare.Stride());
    const ::ae::gfx_low::VertexAttributeInfo vertexAttrInfos[] = {
        ::ae::gfx_low::VertexAttributeInfo()
            .SetFormat(::ae::gfx_low::VertexFormat::Sfloat32x3)
            .SetOffset(geometrySquare.OffsetPosition()),
        ::ae::gfx_low::VertexAttributeInfo()
            .SetFormat(::ae::gfx_low::VertexFormat::Sfloat32x2)
            .SetOffset(geometrySquare.OffsetUv0()),
    };
    ::aesk::VertexBuffer vertexBuffer(
        &gfxKit.Device(),
        geometrySquare.Data().Size(),
        vertexBufferLayoutInfo);
    vertexBuffer.StoreToResourceMemory(geometrySquare.Data());

    // マルチレンダーターゲット用テクスチャの作成
    constexpr int multiRenderTargetCount = 2;
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::UniqueResourceMemory>
        textureMemories(multiRenderTargetCount);
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::ImageResource> textureImages(
        multiRenderTargetCount);
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::SampledImageView> textureViews(
        multiRenderTargetCount);
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::RenderTargetImageView>
        renderTargetImageViews(multiRenderTargetCount);
    const auto textureFormat = ::ae::gfx_low::ImageFormat::R8G8B8A8UnormSrgb;
    const auto textureExtent = ::ae::base::Extent2i(256, 256);
    {
        const auto baseSpecInfo =
            ::ae::gfx_low::ImageResourceSpecInfo()
                .SetKind(::ae::gfx_low::ImageResourceKind::Image2d)
                .SetFormat(textureFormat)
                .SetExtent(textureExtent);
        ::ae::gfx_low::ImageSubresourceDataInfo dataInfo;

        // メモ：
        // イメージは別メモリからコピーされるため
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
                            ::ae::gfx_low::ImageResourceUsage::
                                RenderTargetImage,
                            true));

        for (int i = 0; i < multiRenderTargetCount; ++i) {
            textureMemories.Add(
                &gfxKit.Device(),
                ::ae::gfx_low::ResourceMemoryAllocInfo()
                    .SetKind(::ae::gfx_low::ResourceMemoryKind::DeviceLocal)
                    .SetParams(gfxKit.Device().CalcResourceMemoryRequirements(
                        specInfo)));
            textureImages.Add(
                ::ae::gfx_low::ImageResourceCreateInfo()
                    .SetDevice(&gfxKit.Device())
                    .SetSpecInfo(specInfo)
                    .SetDataAddress(textureMemories[i]->Address()));
            textureViews.Add(::ae::gfx_low::SampledImageViewCreateInfo()
                                 .SetDevice(&gfxKit.Device())
                                 .SetResource(&textureImages[i])
                                 .SetKind(::ae::gfx_low::ImageViewKind::Image2d)
                                 .SetFormat(textureFormat));
            renderTargetImageViews.Add(
                ::ae::gfx_low::RenderTargetImageViewCreateInfo()
                    .SetDevice(&gfxKit.Device())
                    .SetResource(&textureImages[i]));
        }
    }

    // Sampler の作成
    ::std::unique_ptr<::ae::gfx_low::Sampler> sampler;
    {
        sampler.reset(new ::ae::gfx_low::Sampler(
            ::ae::gfx_low::SamplerCreateInfo().SetDevice(&gfxKit.Device())));
    }

    // UniformBuffer の作成
    ::aesk::UniformBuffer multiUniformBuffer(
        &gfxKit.Device(),
        sizeof(fMultiUniformDataType),
        gfxKit.SwapchainImageCount());
    ::aesk::UniformBuffer mixUniformBuffer(
        &gfxKit.Device(),
        sizeof(fMixUniformDataType),
        gfxKit.SwapchainImageCount());

    // RenderPassSpecInfo の作成
    const ::ae::gfx_low::RenderTargetSpecInfo multiRenderTargetSpecInfos[] = {
        ::ae::gfx_low::RenderTargetSpecInfo().SetImageFormat(textureFormat),
        ::ae::gfx_low::RenderTargetSpecInfo().SetImageFormat(textureFormat),
    };
    const auto multiRenderPassSpecInfo =
        ::ae::gfx_low::RenderPassSpecInfo()
            .SetRenderTargetCount(multiRenderTargetCount)
            .SetRenderTargetSpecInfos(multiRenderTargetSpecInfos);

    const ::ae::gfx_low::RenderTargetSpecInfo mixRenderTargetSpecInfos[] = {
        gfxKit.Swapchain()->RenderTargetSpecInfo(),
    };
    const int mixRenderTargetCount =
        AE_BASE_ARRAY_LENGTH(mixRenderTargetSpecInfos);
    const auto depthStencilSpecInfo =
        ::ae::gfx_low::DepthStencilSpecInfo().SetImageFormat(
            gfxKit.DepthBufferFormat());
    const auto mixRenderPassSpecInfo =
        ::ae::gfx_low::RenderPassSpecInfo()
            .SetRenderTargetCount(mixRenderTargetCount)
            .SetRenderTargetSpecInfos(mixRenderTargetSpecInfos)
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
            .SetBindingIndex(0),
        ::ae::gfx_low::ShaderBindingInfo()
            .SetStages(::ae::gfx_low::ShaderBindingStageBitSet().Set(
                ::ae::gfx_low::ShaderBindingStage::Fragment,
                true))
            .SetBindingIndex(1)
    };
    const ::ae::gfx_low::ShaderBindingInfo samplerBindingInfos[] = {
        ::ae::gfx_low::ShaderBindingInfo()
            .SetStages(::ae::gfx_low::ShaderBindingStageBitSet().Set(
                ::ae::gfx_low::ShaderBindingStage::Fragment,
                true))
            .SetBindingIndex(0)
    };
    const auto multiDescriptorSetSpecInfo =
        ::ae::gfx_low::DescriptorSetSpecInfo().SetBindingInfos(
            ::ae::gfx_low::DescriptorKind::UniformBuffer,
            AE_BASE_ARRAY_LENGTH(uniformBufferBindingInfos),
            uniformBufferBindingInfos);
    const auto mixDescriptorSetSpecInfo =
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

    // DescriptorSet の作成
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::DescriptorSet>
        multiDescriptorSets(gfxKit.SwapchainImageCount());
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::DescriptorSet>
        mixDescriptorSets(gfxKit.SwapchainImageCount());
    for (int i = 0; i < gfxKit.SwapchainImageCount(); ++i) {
        multiDescriptorSets.Add(::ae::gfx_low::DescriptorSetCreateInfo()
                                    .SetDevice(&gfxKit.Device())
                                    .SetSpecInfo(multiDescriptorSetSpecInfo));
        mixDescriptorSets.Add(::ae::gfx_low::DescriptorSetCreateInfo()
                                  .SetDevice(&gfxKit.Device())
                                  .SetSpecInfo(mixDescriptorSetSpecInfo));

        // multi
        {
            // UniformBuffer
            const ::ae::gfx_low::UniformBufferView*
                localUniformBufferViews[] = { &multiUniformBuffer.View(i) };
            const ::ae::gfx_low::UniformBufferDescriptorInfo
                uniformBufferDescs[] = {
                    ::ae::gfx_low::UniformBufferDescriptorInfo()
                        .SetRegion(::ae::gfx_low::ShaderBindingRegion()
                                       .SetBindingIndex(0)
                                       .SetElemCount(AE_BASE_ARRAY_LENGTH(
                                           localUniformBufferViews)))
                        .SetViews(localUniformBufferViews),
                };

            // 更新
            multiDescriptorSets[i].Update(
                ::ae::gfx_low::DescriptorSetUpdateInfo().SetUniformBufferInfos(
                    AE_BASE_ARRAY_LENGTH(uniformBufferDescs),
                    uniformBufferDescs));
        }

        // mix
        {
            // UniformBuffer
            const ::ae::gfx_low::UniformBufferView*
                localUniformBufferViews[] = { &mixUniformBuffer.View(i) };
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
                &textureViews[0],
                &textureViews[1],
            };
            const ::ae::gfx_low::SampledImageDescriptorInfo
                sampledImageDescs[] = {
                    ::ae::gfx_low::SampledImageDescriptorInfo()
                        .SetRegion(::ae::gfx_low::ShaderBindingRegion()
                                       .SetBindingIndex(0)
                                       .SetElemCount(AE_BASE_ARRAY_LENGTH(
                                           sampledImageViews)))
                        .SetViews(sampledImageViews),
                };

            // Sampler
            const ::ae::gfx_low::Sampler* samplers[] = { sampler.get() };
            const ::ae::gfx_low::SamplerDescriptorInfo samplerDescs[] = {
                ::ae::gfx_low::SamplerDescriptorInfo()
                    .SetRegion(
                        ::ae::gfx_low::ShaderBindingRegion()
                            .SetBindingIndex(0)
                            .SetElemCount(AE_BASE_ARRAY_LENGTH(samplers)))
                    .SetSamplers(samplers),
            };

            // 更新
            mixDescriptorSets[i].Update(
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
    }

    // GraphicsPipeline 生成
    std::unique_ptr<::ae::gfx_low::RenderPipeline> multiPipeline;
    std::unique_ptr<::ae::gfx_low::RenderPipeline> mixPipeline;
    {
        const ::ae::gfx_low::RenderTargetBlendInfo blendInfos[] = {
            ::ae::gfx_low::RenderTargetBlendInfo(),
            ::ae::gfx_low::RenderTargetBlendInfo(),
        };
        AE_BASE_ARRAY_LENGTH_CHECK(
            blendInfos,
            AE_BASE_ARRAY_LENGTH(multiRenderTargetSpecInfos));

        multiPipeline.reset(new ::ae::gfx_low::RenderPipeline(
            ::ae::gfx_low::RenderPipelineCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetRenderPassSpecInfo(multiRenderPassSpecInfo)
                .SetShaderInfo(
                    ::ae::gfx_low::RenderPipelineShaderStage::Vertex,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(&multiVertShader.Resource())
                        .SetEntryPointNamePtr("main"))
                .SetShaderInfo(
                    ::ae::gfx_low::RenderPipelineShaderStage::Fragment,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(&multiFragShader.Resource())
                        .SetEntryPointNamePtr("main"))
                .SetDescriptorSetSpecInfo(multiDescriptorSetSpecInfo)
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
                .SetDepthStencilInfo(::ae::gfx_low::PipelineDepthStencilInfo())
                .SetBlendInfo(::ae::gfx_low::PipelineBlendInfo()
                                  .SetRenderTargetBlendInfos(blendInfos))));
    }
    {
        const ::ae::gfx_low::RenderTargetBlendInfo blendInfos[] = {
            ::ae::gfx_low::RenderTargetBlendInfo(),
        };
        AE_BASE_ARRAY_LENGTH_CHECK(
            blendInfos,
            AE_BASE_ARRAY_LENGTH(mixRenderTargetSpecInfos));

        mixPipeline.reset(new ::ae::gfx_low::RenderPipeline(
            ::ae::gfx_low::RenderPipelineCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetRenderPassSpecInfo(mixRenderPassSpecInfo)
                .SetShaderInfo(
                    ::ae::gfx_low::RenderPipelineShaderStage::Vertex,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(&mixVertShader.Resource())
                        .SetEntryPointNamePtr("main"))
                .SetShaderInfo(
                    ::ae::gfx_low::RenderPipelineShaderStage::Fragment,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(&mixFragShader.Resource())
                        .SetEntryPointNamePtr("main"))
                .SetDescriptorSetSpecInfo(mixDescriptorSetSpecInfo)
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
                .SetDepthStencilInfo(::ae::gfx_low::PipelineDepthStencilInfo())
                .SetBlendInfo(::ae::gfx_low::PipelineBlendInfo()
                                  .SetRenderTargetBlendInfos(blendInfos))));
    }

    // RenderPass 作成＆領域を事前確保
    ::std::unique_ptr<::ae::gfx_low::RenderPass> multiRenderPass;
    {
        const auto renderTargetSetting =
            ::ae::gfx_low::RenderTargetSetting()
                .SetLoadOp(::ae::gfx_low::AttachmentLoadOp::Clear)
                .SetStoreOp(::ae::gfx_low::AttachmentStoreOp::Store)
                .SetInitialImageResourceState(
                    ::ae::gfx_low::ImageResourceState::RenderTarget)
                .SetFinalImageResourceState(
                    ::ae::gfx_low::ImageResourceState::ShaderResourceReadOnly)
                .SetClearColor(
                    ::ae::base::Color4b(0x80, 0x80, 0x80, 0xff).ToRGBAf());
        const ::ae::gfx_low::RenderTargetSetting renderTargetSettings[] = {
            ::ae::gfx_low::RenderTargetSetting(renderTargetSetting)
                .SetRenderTargetImageView(&renderTargetImageViews[0]),
            ::ae::gfx_low::RenderTargetSetting(renderTargetSetting)
                .SetRenderTargetImageView(&renderTargetImageViews[1]),
        };
        multiRenderPass.reset(new ::ae::gfx_low::RenderPass(
            ::ae::gfx_low::RenderPassCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetRenderPassSpecInfo(multiRenderPassSpecInfo)
                .SetRenderTargetSettings(renderTargetSettings)
                .SetRenderArea(::ae::base::Aabb2i(
                    ::ae::base::Vector2i::Zero(),
                    textureExtent))));
    }
    ::ae::base::RuntimeArray<::std::unique_ptr<::ae::gfx_low::RenderPass>>
        mixRenderPassArray;
    mixRenderPassArray.Resize(gfxKit.SwapchainImageCount());

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
        {
            // multi
            {
                auto proj = ::ae::base::Matrix44::Ortho(
                    -1.0f, // left
                    1.0f, // top
                    1.0f, // right
                    -1.0f, // bottom
                    0.1f, // near
                    100.0f // far
                );
                auto view = ::ae::base::Matrix44::LookAt(
                    ::ae::base::Vector3(0.0f, 0.0f, 5.0f), // eyePos
                    ::ae::base::Vector3::Zero(), // targetPos
                    ::ae::base::Vector3::UnitY() // upVec
                );
                auto model = ::ae::base::Matrix44::Identity();
                auto vp = proj * view;
                auto mvp = vp * model;

                fMultiUniformDataType data = {};
                data.mvp = mvp;
                data.uvTrans = ::ae::base::Vector4(1.0f, 1.0f, 0.0f, 0.0f) *
                               float(frameCount) * 0.01f;
                multiUniformBuffer.StoreToResourceMemory(bufferIndex, data);
            }

            // mix
            {
                auto proj = ::ae::base::Matrix44::Perspective(
                    ::ae::base::Angle(::ae::base::Degree(25.0f)),
                    float(display.MainScreen().Width()) /
                        display.MainScreen().Height(), // aspect
                    0.1f, // near
                    1000.0f // far
                );
                auto view = ::ae::base::Matrix44::LookAt(
                    ::ae::base::Vector3(0.0f, 0.0f, 5.0f), // eyePos
                    ::ae::base::Vector3::Zero(), // targetPos
                    ::ae::base::Vector3::UnitY() // upVec
                );
                auto model = ::ae::base::Matrix44::Identity();
                auto vp = proj * view;
                auto mvp = vp * model;

                fMixUniformDataType data = {};
                data.mvp = mvp;
                mixUniformBuffer.StoreToResourceMemory(bufferIndex, data);
            }
        }

        // コマンドバッファ作成
        auto& cmd = gfxKit.CurrentCommandBuffer();
        cmd.BeginRecord();
        {
            // テクスチャのセットアップ
            if (!isFinishedSetupTexture) {
                // 初期状態をサンプリング用モードにしておくことで
                // 以降のコードを２ループ目以降と同じ処理にできるようにする
                for (int i = 0; i < multiRenderTargetCount; ++i) {
                    cmd.CmdImageResourceBarrier(
                        ::ae::gfx_low::ImageResourceBarrierInfo()
                            .SetResource(&textureImages[i])
                            .SetOldState(
                                ::ae::gfx_low::ImageResourceState::Unknown)
                            .SetNewState(::ae::gfx_low::ImageResourceState::ShaderResourceReadOnly));
                }
                isFinishedSetupTexture = true;
            }

            // レンダーターゲット用にテクスチャセットアップ
            for (int i = 0; i < multiRenderTargetCount; ++i) {
                cmd.CmdImageResourceBarrier(
                    ::ae::gfx_low::ImageResourceBarrierInfo()
                        .SetResource(&textureImages[i])
                        .SetOldState(::ae::gfx_low::ImageResourceState::ShaderResourceReadOnly)
                        .SetNewState(
                            ::ae::gfx_low::ImageResourceState::RenderTarget));
            }

            // mix用レンダーパス準備
            // クリアカラー参考：https://www.colordic.org/colorscheme/7005
            auto& mixRenderPassUniquePtr = mixRenderPassArray[bufferIndex];
            {
                mixRenderPassUniquePtr.reset();

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
                mixRenderPassUniquePtr.reset(new ::ae::gfx_low::RenderPass(
                    ::ae::gfx_low::RenderPassCreateInfo()
                        .SetDevice(&gfxKit.Device())
                        .SetRenderPassSpecInfo(mixRenderPassSpecInfo)
                        .SetRenderTargetSettings(renderTargetSettings)
                        .SetDepthStencilSettingPtr(&depthStencilSetting)
                        .SetRenderArea(::ae::base::Aabb2i(
                            ::ae::base::Vector2i::Zero(),
                            display.MainScreen().Extent()))));
            }

            // マルチレンダーターゲットで描画
            {
                // 開始
                cmd.CmdBeginRenderPass(
                    ::ae::gfx_low::RenderPassBeginInfo().SetRenderPass(
                        multiRenderPass.get()));

                // Viewport
                {
                    const ::ae::gfx_low::ViewportSetting settings[] = {
                        ::ae::gfx_low::ViewportSetting().SetRect(
                            ::ae::base::Aabb2(
                                ::ae::base::Vector2::Zero(),
                                textureExtent.ToExtent2())),
                        ::ae::gfx_low::ViewportSetting().SetRect(
                            ::ae::base::Aabb2(
                                ::ae::base::Vector2::Zero(),
                                textureExtent.ToExtent2())),
                    };
                    AE_BASE_ARRAY_LENGTH_CHECK(
                        settings,
                        multiRenderTargetCount);
                    cmd.CmdSetViewports(multiRenderTargetCount, settings);
                }

                // Scissor
                {
                    const ::ae::gfx_low::ScissorSetting settings[] = {
                        ::ae::gfx_low::ScissorSetting().SetRect(
                            ::ae::base::Aabb2i(
                                ::ae::base::Vector2i::Zero(),
                                textureExtent)),
                        ::ae::gfx_low::ScissorSetting().SetRect(
                            ::ae::base::Aabb2i(
                                ::ae::base::Vector2i::Zero(),
                                textureExtent)),
                    };
                    AE_BASE_ARRAY_LENGTH_CHECK(
                        settings,
                        multiRenderTargetCount);
                    cmd.CmdSetScissors(multiRenderTargetCount, settings);
                }

                // Pipeline & DescriptorSet
                cmd.CmdSetRenderPipeline(*multiPipeline);
                cmd.CmdSetDescriptorSet(multiDescriptorSets[bufferIndex]);

                // Draw
                cmd.CmdSetVertexBuffer(0, vertexBuffer.View());
                cmd.CmdDraw(::ae::gfx_low::DrawCallInfo().SetVertexCount(
                    geometrySquare.VertexCount()));

                // 終了
                cmd.CmdEndRenderPass();
            }

            // 最終レンダーターゲットに描画
            {
                // 開始
                cmd.CmdBeginRenderPass(
                    ::ae::gfx_low::RenderPassBeginInfo().SetRenderPass(
                        mixRenderPassUniquePtr.get()));

                // Viewport
                {
                    const ::ae::gfx_low::ViewportSetting settings[] = {
                        ::ae::gfx_low::ViewportSetting().SetRect(
                            ::ae::base::Aabb2(
                                ::ae::base::Vector2::Zero(),
                                display.MainScreen().Extent().ToExtent2())),
                    };
                    AE_BASE_ARRAY_LENGTH_CHECK(settings, mixRenderTargetCount);
                    cmd.CmdSetViewports(mixRenderTargetCount, settings);
                }

                // Scissor
                {
                    const ::ae::gfx_low::ScissorSetting settings[] = {
                        ::ae::gfx_low::ScissorSetting().SetRect(
                            ::ae::base::Aabb2i(
                                ::ae::base::Vector2i::Zero(),
                                display.MainScreen().Extent())),
                    };
                    AE_BASE_ARRAY_LENGTH_CHECK(settings, mixRenderTargetCount);
                    cmd.CmdSetScissors(mixRenderTargetCount, settings);
                }

                // Pipeline & DescriptorSet
                cmd.CmdSetRenderPipeline(*mixPipeline);
                cmd.CmdSetDescriptorSet(mixDescriptorSets[bufferIndex]);

                // Draw
                cmd.CmdSetVertexBuffer(0, vertexBuffer.View());
                cmd.CmdDraw(::ae::gfx_low::DrawCallInfo().SetVertexCount(
                    geometrySquare.VertexCount()));

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
