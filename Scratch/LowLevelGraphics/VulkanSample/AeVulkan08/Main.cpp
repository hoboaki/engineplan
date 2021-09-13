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
#include <aesk/GeometryCube.hpp>
#include <aesk/GeometrySquare.hpp>
#include <aesk/GfxBasicKit.hpp>
#include <aesk/Shader.hpp>
#include <aesk/UniformBuffer.hpp>
#include <aesk/VertexBuffer.hpp>
#include <memory>

//------------------------------------------------------------------------------
namespace {

struct fUniformDataType {
    float mvp[4][4];
};

const uint32_t fCopyVertShaderCode[] = {
#include "ShaderCopy.vert.inc"
};

const uint32_t fCopyFragShaderCode[] = {
#include "ShaderCopy.frag.inc"
};

const uint32_t fCubeVertShaderCode[] = {
#include "ShaderCube.vert.inc"
};

const uint32_t fCubeFragShaderCode[] = {
#include "ShaderCube.frag.inc"
};
// clang-format on

} // namespace

//------------------------------------------------------------------------------
int aemain(::ae::base::Application* app) {
    // コンソール出力
    AE_BASE_COUT_LINE_WITH_TIME("Adel runtime start.");

    // ディスプレイの作成
    ::ae::base::Display display = ::ae::base::Display(
        ::ae::base::DisplayContext()
            .SetWindowTitle("AeVulkan08 - Secondary Command Buffer")
            .SetIsResizableWindow(true));

    // ディスプレイの表示
    display.Show();

    // 基本キット
    ::aesk::GfxBasicKit gfxKit(&display);

    // Shader の作成
    ::aesk::Shader copyVertShader(
        &gfxKit,
        fCopyVertShaderCode,
        sizeof(fCopyVertShaderCode));
    ::aesk::Shader copyFragShader(
        &gfxKit,
        fCopyFragShaderCode,
        sizeof(fCopyFragShaderCode));
    ::aesk::Shader cubeVertShader(
        &gfxKit,
        fCubeVertShaderCode,
        sizeof(fCubeVertShaderCode));
    ::aesk::Shader cubeFragShader(
        &gfxKit,
        fCubeFragShaderCode,
        sizeof(fCubeFragShaderCode));

    // VertexBuffer の作成（キューブ）
    ::aesk::GeometryCube geometryCube;
    const auto cubeVertexBufferLayoutInfo =
        ::ae::gfx_low::VertexBufferLayoutInfo().SetStride(
            geometryCube.Stride());
    const ::ae::gfx_low::VertexAttributeInfo cubeVrtexAttrInfos[] = {
        ::ae::gfx_low::VertexAttributeInfo()
            .SetFormat(::ae::gfx_low::VertexFormat::Sfloat32x3)
            .SetOffset(geometryCube.OffsetPosition()),
        ::ae::gfx_low::VertexAttributeInfo()
            .SetFormat(::ae::gfx_low::VertexFormat::Sfloat32x2)
            .SetOffset(geometryCube.OffsetUv0()),
    };
    ::aesk::VertexBuffer cubeVertexBuffer(
        &gfxKit.Device(),
        geometryCube.Data().Size(),
        cubeVertexBufferLayoutInfo);
    cubeVertexBuffer.StoreToResourceMemory(geometryCube.Data());

    
    // VertexBuffer の作成（正方形）
    ::aesk::GeometrySquare geometrySquare;
    const auto squareVertexBufferLayoutInfo =
        ::ae::gfx_low::VertexBufferLayoutInfo().SetStride(
            geometrySquare.Stride());
    const ::ae::gfx_low::VertexAttributeInfo squareVrtexAttrInfos[] = {
        ::ae::gfx_low::VertexAttributeInfo()
            .SetFormat(::ae::gfx_low::VertexFormat::Sfloat32x3)
            .SetOffset(geometrySquare.OffsetPosition()),
        ::ae::gfx_low::VertexAttributeInfo()
            .SetFormat(::ae::gfx_low::VertexFormat::Sfloat32x2)
            .SetOffset(geometryCube.OffsetUv0()),
    };
    ::aesk::VertexBuffer squareVertexBuffer(
        &gfxKit.Device(),
        geometrySquare.Data().Size(),
        squareVertexBufferLayoutInfo);
    squareVertexBuffer.StoreToResourceMemory(geometrySquare.Data());

    // キューブに貼り付けるテクスチャの作成
    ::ae::gfx_low::UniqueResourceMemory textureMemory;
    ::ae::gfx_low::UniqueResourceMemory copySrcTextureMemory;
    ::std::unique_ptr<::ae::gfx_low::ImageResource> textureImage;
    ::std::unique_ptr<::ae::gfx_low::BufferResource> copySrcTextureBuffer;
    ::std::unique_ptr<::ae::gfx_low::SampledImageView> textureView;
    ::ae::gfx_low::CopyBufferToImageInfo copyBufferToImageInfo;
    {
        const auto extent = ::ae::base::Extent2i(256, 256);
        const auto format = ::ae::gfx_low::ImageFormat::R8G8B8A8UnormSrgb;
        const auto baseSpecInfo =
            ::ae::gfx_low::ImageResourceSpecInfo()
                .SetKind(::ae::gfx_low::ImageResourceKind::Image2d)
                .SetFormat(format)
                .SetExtent(extent);
        ::ae::gfx_low::ImageSubresourceDataInfo dataInfo;

        if (gfxKit.Device().IsDeviceLocalMemoryShared()) {
            // デバイスメモリが共有メモリの場合
            // コピーは不要のため共有メモリ上にテクスチャメモリを配置し
            // GPU からもそのデータを参照するようにする
            const auto specInfo =
                ::ae::gfx_low::ImageResourceSpecInfo(baseSpecInfo)
                    .SetTiling(::ae::gfx_low::ImageResourceTiling::Linear)
                    .SetUsageBitSet(
                        ::ae::gfx_low::ImageResourceUsageBitSet().Set(
                            ::ae::gfx_low::ImageResourceUsage::SampledImage,
                            true));
            textureMemory.Reset(
                &gfxKit.Device(),
                ::ae::gfx_low::ResourceMemoryAllocInfo()
                    .SetKind(::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
                    .SetParams(gfxKit.Device().CalcResourceMemoryRequirements(
                        specInfo)));
            textureImage.reset(new ::ae::gfx_low::ImageResource(
                ::ae::gfx_low::ImageResourceCreateInfo()
                    .SetDevice(&gfxKit.Device())
                    .SetSpecInfo(specInfo)
                    .SetDataAddress(textureMemory->Address())));
            dataInfo = gfxKit.Device().CalcImageSubresourceDataInfo(
                specInfo,
                ::ae::gfx_low::ImageSubresourceLocation());
        } else {
            // デバイスメモリが専用メモリの場合
            // 共有メモリから専用メモリへのコピーが必要のため
            // ２つずつオブジェクトを作る
            {
                const auto specInfo =
                    ::ae::gfx_low::ImageResourceSpecInfo(baseSpecInfo)
                        .SetTiling(::ae::gfx_low::ImageResourceTiling::Optimal)
                        .SetUsageBitSet(
                            ::ae::gfx_low::ImageResourceUsageBitSet()
                                .Set(
                                    ::ae::gfx_low::ImageResourceUsage::
                                        SampledImage,
                                    true)
                                .Set(
                                    ::ae::gfx_low::ImageResourceUsage::CopyDst,
                                    true));
                textureMemory.Reset(
                    &gfxKit.Device(),
                    ::ae::gfx_low::ResourceMemoryAllocInfo()
                        .SetKind(::ae::gfx_low::ResourceMemoryKind::DeviceLocal)
                        .SetParams(
                            gfxKit.Device().CalcResourceMemoryRequirements(
                                specInfo)));
                textureImage.reset(new ::ae::gfx_low::ImageResource(
                    ::ae::gfx_low::ImageResourceCreateInfo()
                        .SetDevice(&gfxKit.Device())
                        .SetSpecInfo(specInfo)
                        .SetDataAddress(textureMemory->Address())));
            }
            {
                const auto specInfo =
                    ::ae::gfx_low::ImageResourceSpecInfo(baseSpecInfo)
                        .SetTiling(::ae::gfx_low::ImageResourceTiling::Linear)
                        .SetUsageBitSet(
                            ::ae::gfx_low::ImageResourceUsageBitSet().Set(
                                ::ae::gfx_low::ImageResourceUsage::CopySrc,
                                true));
                dataInfo = gfxKit.Device().CalcImageSubresourceDataInfo(
                    specInfo,
                    ::ae::gfx_low::ImageSubresourceLocation());
                copySrcTextureMemory.Reset(
                    &gfxKit.Device(),
                    ::ae::gfx_low::ResourceMemoryAllocInfo()
                        .SetKind(
                            ::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
                        .SetParams(
                            gfxKit.Device().CalcResourceMemoryRequirements(
                                specInfo)));
                copySrcTextureBuffer.reset(new ::ae::gfx_low::BufferResource(
                    ::ae::gfx_low::BufferResourceCreateInfo()
                        .SetDevice(&gfxKit.Device())
                        .SetSpecInfo(
                            ::ae::gfx_low::BufferResourceSpecInfo()
                                .SetSize(dataInfo.RowPitch() * extent.height)
                                .SetUsageBitSet(
                                    ::ae::gfx_low::BufferResourceUsageBitSet()
                                        .Set(
                                            ::ae::gfx_low::BufferResourceUsage::
                                                CopySrc,
                                            true)))
                        .SetDataAddress(copySrcTextureMemory->Address())));
            }

            // コピー用情報を先行して作成しておく
            copyBufferToImageInfo =
                ::ae::gfx_low::CopyBufferToImageInfo()
                    .SetSrcBufferResource(copySrcTextureBuffer.get())
                    .SetSrcBufferRowPitch(dataInfo.RowPitch())
                    .SetSrcBufferDepthPitch(dataInfo.DepthPitch())
                    .SetSrcImageFormat(format)
                    .SetSrcImageExtent(extent)
                    .SetDstImageResource(textureImage.get())
                    .SetDstImageResourceState(
                        ::ae::gfx_low::ImageResourceState::CopyDst);
        }

        // サンプラー用イメージビューの作成
        textureView.reset(new ::ae::gfx_low::SampledImageView(
            ::ae::gfx_low::SampledImageViewCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetResource(textureImage.get())
                .SetKind(::ae::gfx_low::ImageViewKind::Image2d)
                .SetFormat(format)));

        // テクスチャイメージをプログラムコードで作成
        {
            auto& targetMemory = gfxKit.Device().IsDeviceLocalMemoryShared()
                                     ? textureMemory
                                     : copySrcTextureMemory;
            uint8_t* dst = gfxKit.Device().MapResourceMemory(
                *targetMemory,
                ::ae::gfx_low::ResourceMemoryRegion()
                    .SetOffset(dataInfo.Offset())
                    .SetSize(dataInfo.RowPitch() * extent.height));
            const ::ae::base::Color4bPod rgbColors[] = {
                ::ae::base::Color4b(0xFF, 0xFF, 0xFF, 0xFF),
                ::ae::base::Color4b(0xFF, 0xFF, 0, 0xFF),
                ::ae::base::Color4b(0, 0xFF, 0xFF, 0xFF),
                ::ae::base::Color4b(0, 0xFF, 0, 0xFF),
                ::ae::base::Color4b(0xFF, 0, 0xFF, 0xFF),
                ::ae::base::Color4b(0xFF, 0, 0, 0xFF),
                ::ae::base::Color4b(0, 0, 0xFF, 0xFF),
            };
            for (int y = 0; y < extent.height; ++y) {
                for (int x = 0; x < extent.width; ++x) {
                    const int colorIndex =
                        x / (extent.width / AE_BASE_ARRAY_LENGTH(rgbColors));
                    const auto& color = rgbColors[colorIndex];
                    const size_t baseOffset =
                        size_t(y) * dataInfo.RowPitch() + size_t(x) * 4;
                    dst[baseOffset + 0] = color.r;
                    dst[baseOffset + 1] = color.g;
                    dst[baseOffset + 2] = color.b;
                    dst[baseOffset + 3] = color.a;
                }
            }
            gfxKit.Device().UnmapResourceMemory(*targetMemory);
        }
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
    const auto colorBufferFormat =
        ::ae::gfx_low::ImageFormat::R8G8B8A8UnormSrgb;
    const int renderTargetCount = 1;
    const ::ae::gfx_low::RenderTargetSpecInfo mainRenderTargetSpecInfos[] = {
        ::ae::gfx_low::RenderTargetSpecInfo().SetImageFormat(colorBufferFormat),
    };
    AE_BASE_ASSERT_EQUALS(renderTargetCount, AE_BASE_ARRAY_LENGTH(mainRenderTargetSpecInfos));
    const ::ae::gfx_low::RenderTargetSpecInfo copyRenderTargetSpecInfos[] = {
        gfxKit.Swapchain()->RenderTargetSpecInfo(),
    };
    AE_BASE_ASSERT_EQUALS(
        renderTargetCount,
        AE_BASE_ARRAY_LENGTH(copyRenderTargetSpecInfos));
    const auto depthStencilSpecInfo =
        ::ae::gfx_low::DepthStencilSpecInfo().SetImageFormat(
            gfxKit.DepthBufferFormat());
    const auto mainRenderPassSpecInfo =
        ::ae::gfx_low::RenderPassSpecInfo()
            .SetRenderTargetCount(renderTargetCount)
            .SetRenderTargetSpecInfos(mainRenderTargetSpecInfos)
            .SetDepthStencilSpecInfoPtr(&depthStencilSpecInfo);
    const auto copyRenderPassSpecInfo =
        ::ae::gfx_low::RenderPassSpecInfo()
            .SetRenderTargetCount(renderTargetCount)
            .SetRenderTargetSpecInfos(copyRenderTargetSpecInfos);

    // DescriptorSetSpecInfo の作成
    const ::ae::gfx_low::ShaderBindingInfo mainUniformBufferBindingInfos[] = {
        ::ae::gfx_low::ShaderBindingInfo()
            .SetStages(
                ::ae::gfx_low::ShaderBindingStageBitSet()
                    .Set(::ae::gfx_low::ShaderBindingStage::Vertex, true)
                    .Set(::ae::gfx_low::ShaderBindingStage::Fragment, true))
            .SetBindingIndex(0)
    };
    const ::ae::gfx_low::ShaderBindingInfo mainSampledImageBindingInfos[] = {
        ::ae::gfx_low::ShaderBindingInfo()
            .SetStages(::ae::gfx_low::ShaderBindingStageBitSet().Set(
                ::ae::gfx_low::ShaderBindingStage::Fragment,
                true))
            .SetBindingIndex(0)
    };
    const ::ae::gfx_low::ShaderBindingInfo mainSamplerBindingInfos[] = {
        ::ae::gfx_low::ShaderBindingInfo()
            .SetStages(::ae::gfx_low::ShaderBindingStageBitSet().Set(
                ::ae::gfx_low::ShaderBindingStage::Fragment,
                true))
            .SetBindingIndex(0)
    };
    const ::ae::gfx_low::ShaderBindingInfo copySampledImageBindingInfos[] = {
        ::ae::gfx_low::ShaderBindingInfo()
            .SetStages(::ae::gfx_low::ShaderBindingStageBitSet().Set(
                ::ae::gfx_low::ShaderBindingStage::Fragment,
                true))
            .SetBindingIndex(0)
    };
    const ::ae::gfx_low::ShaderBindingInfo copySamplerBindingInfos[] = {
        ::ae::gfx_low::ShaderBindingInfo()
            .SetStages(::ae::gfx_low::ShaderBindingStageBitSet().Set(
                ::ae::gfx_low::ShaderBindingStage::Fragment,
                true))
            .SetBindingIndex(0)
    };
    const auto mainDescriptorSetSpecInfo =
        ::ae::gfx_low::DescriptorSetSpecInfo()
            .SetBindingInfos(
                ::ae::gfx_low::DescriptorKind::UniformBuffer,
                AE_BASE_ARRAY_LENGTH(mainUniformBufferBindingInfos),
                mainUniformBufferBindingInfos)
            .SetBindingInfos(
                ::ae::gfx_low::DescriptorKind::SampledImage,
                AE_BASE_ARRAY_LENGTH(mainSampledImageBindingInfos),
                mainSampledImageBindingInfos)
            .SetBindingInfos(
                ::ae::gfx_low::DescriptorKind::Sampler,
                AE_BASE_ARRAY_LENGTH(mainSamplerBindingInfos),
                mainSamplerBindingInfos);
    const auto copyDescriptorSetSpecInfo =
        ::ae::gfx_low::DescriptorSetSpecInfo()
            .SetBindingInfos(
                ::ae::gfx_low::DescriptorKind::SampledImage,
                AE_BASE_ARRAY_LENGTH(copySampledImageBindingInfos),
                copySampledImageBindingInfos)
            .SetBindingInfos(
                ::ae::gfx_low::DescriptorKind::Sampler,
                AE_BASE_ARRAY_LENGTH(copySamplerBindingInfos),
                copySamplerBindingInfos);

    // DescriptorSet の作成
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::DescriptorSet> mainDescriptorSets(
        gfxKit.SwapchainImageCount());
    ::ae::gfx_low::DescriptorSet copyDescriptorSet(
        ::ae::gfx_low::DescriptorSetCreateInfo()
            .SetDevice(&gfxKit.Device())
            .SetSpecInfo(copyDescriptorSetSpecInfo));
    for (int i = 0; i < gfxKit.SwapchainImageCount(); ++i) {
        mainDescriptorSets.Add(::ae::gfx_low::DescriptorSetCreateInfo()
                               .SetDevice(&gfxKit.Device())
                                   .SetSpecInfo(mainDescriptorSetSpecInfo));

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
        mainDescriptorSets[i].Update(
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

    // GraphicsPipeline 生成
    std::unique_ptr<::ae::gfx_low::RenderPipeline> mainPipeline;
    std::unique_ptr<::ae::gfx_low::RenderPipeline> copyPipeline;
    {
        const ::ae::gfx_low::RenderTargetBlendInfo blendInfos[] = {
            ::ae::gfx_low::RenderTargetBlendInfo(),
        };
        AE_BASE_ARRAY_LENGTH_CHECK(
            blendInfos,
            AE_BASE_ARRAY_LENGTH(mainRenderTargetSpecInfos));

        mainPipeline.reset(new ::ae::gfx_low::RenderPipeline(
            ::ae::gfx_low::RenderPipelineCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetRenderPassSpecInfo(mainRenderPassSpecInfo)
                .SetShaderInfo(
                    ::ae::gfx_low::RenderPipelineShaderStage::Vertex,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(&cubeVertShader.Resource())
                        .SetEntryPointNamePtr("main"))
                .SetShaderInfo(
                    ::ae::gfx_low::RenderPipelineShaderStage::Fragment,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(&cubeFragShader.Resource())
                        .SetEntryPointNamePtr("main"))
                .SetDescriptorSetSpecInfo(mainDescriptorSetSpecInfo)
                .SetVertexInputInfo(
                    ::ae::gfx_low::PipelineVertexInputInfo()
                        .SetBufferCount(1)
                        .SetBufferLayoutInfos(&cubeVertexBufferLayoutInfo)
                        .SetAttributeCount(
                            AE_BASE_ARRAY_LENGTH(cubeVrtexAttrInfos))
                        .SetAttributeInfos(cubeVrtexAttrInfos))
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

        copyPipeline.reset(new ::ae::gfx_low::RenderPipeline(
            ::ae::gfx_low::RenderPipelineCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetRenderPassSpecInfo(copyRenderPassSpecInfo)
                .SetShaderInfo(
                    ::ae::gfx_low::RenderPipelineShaderStage::Vertex,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(&copyVertShader.Resource())
                        .SetEntryPointNamePtr("main"))
                .SetShaderInfo(
                    ::ae::gfx_low::RenderPipelineShaderStage::Fragment,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(&copyFragShader.Resource())
                        .SetEntryPointNamePtr("main"))
                .SetDescriptorSetSpecInfo(copyDescriptorSetSpecInfo)
                .SetVertexInputInfo(
                    ::ae::gfx_low::PipelineVertexInputInfo()
                        .SetBufferCount(1)
                        .SetBufferLayoutInfos(&squareVertexBufferLayoutInfo)
                        .SetAttributeCount(
                            AE_BASE_ARRAY_LENGTH(squareVrtexAttrInfos))
                        .SetAttributeInfos(squareVrtexAttrInfos))
                .SetPrimitiveTopologyKind(
                    ::ae::gfx_low::PrimitiveTopologyKind::TriangleList)
                .SetRasterizerInfo(
                    ::ae::gfx_low::PipelineRasterizerInfo()
                        .SetFrontFace(
                            ::ae::gfx_low::PolygonFrontFace::CounterClockwise)
                        .SetCullMode(::ae::gfx_low::RasterizeCullMode::Back))
                .SetBlendInfo(::ae::gfx_low::PipelineBlendInfo()
                                  .SetRenderTargetBlendInfos(blendInfos))));
    }

    // セカンダリコマンドバッファ作成
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::CommandBuffer>
        secondaryCommandBuffers(renderTargetCount);
    for (int i = 0; i < renderTargetCount; ++i) {
        secondaryCommandBuffers.Add(
            ::ae::gfx_low::CommandBufferCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetQueue(&gfxKit.Queue())
                .SetLevel(::ae::gfx_low::CommandBufferLevel::Secondary)
                .SetFeatures(::ae::gfx_low::CommandBufferFeatureBitSet().Set(
                    ::ae::gfx_low::CommandBufferFeature::Render,
                    true)));
    }

    // レンダーターゲット用カラーバッファの作成
    // 直接 Swapchain に書き込まなくすることで
    // セカンダリコマンドバッファの再レコードを最低限にする
    ::ae::gfx_low::UniqueResourceMemory colorBufferMemory;
    ::std::unique_ptr<::ae::gfx_low::ImageResource> colorBufferImage;
    ::std::unique_ptr<::ae::gfx_low::RenderTargetImageView> colorBufferRenderTargetView;
    ::std::unique_ptr<::ae::gfx_low::SampledImageView> colorBufferTextureView;
    auto setupColorBuffer = [&gfxKit,
                             &display,
                             &colorBufferMemory,
                             &colorBufferImage,
                             &colorBufferRenderTargetView,
                             &colorBufferTextureView,
                             &colorBufferFormat]() {
        const auto extent = display.MainScreen().Extent();
        const auto specInfo =
            ::ae::gfx_low::ImageResourceSpecInfo()
                .SetKind(::ae::gfx_low::ImageResourceKind::Image2d)
                .SetFormat(colorBufferFormat)
                .SetExtent(extent)
                .SetTiling(::ae::gfx_low::ImageResourceTiling::Optimal)
                .SetUsageBitSet(
                    ::ae::gfx_low::ImageResourceUsageBitSet()
                        .On(::ae::gfx_low::ImageResourceUsage::
                                RenderTargetImage)
                        .On(::ae::gfx_low::ImageResourceUsage::SampledImage));
        colorBufferMemory.Reset(
            &gfxKit.Device(),
            ::ae::gfx_low::ResourceMemoryAllocInfo()
                .SetKind(::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
                .SetParams(
                    gfxKit.Device().CalcResourceMemoryRequirements(specInfo)));
        colorBufferImage.reset(new ::ae::gfx_low::ImageResource(
            ::ae::gfx_low::ImageResourceCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetSpecInfo(specInfo)
                .SetDataAddress(colorBufferMemory->Address())));
        colorBufferRenderTargetView.reset(
            new ::ae::gfx_low::RenderTargetImageView(
                ::ae::gfx_low::RenderTargetImageViewCreateInfo()
                    .SetDevice(&gfxKit.Device())
                    .SetResource(colorBufferImage.get())
                    ));
        colorBufferTextureView.reset(new ::ae::gfx_low::SampledImageView(
            ::ae::gfx_low::SampledImageViewCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetResource(colorBufferImage.get())
                .SetKind(::ae::gfx_low::ImageViewKind::Image2d)
                .SetFormat(colorBufferFormat)));
    };
    auto cleanupColorBuffer = [&colorBufferMemory,
                               &colorBufferImage,
                               &colorBufferRenderTargetView,
                               &colorBufferTextureView]() {
        colorBufferTextureView.reset();
        colorBufferRenderTargetView.reset();
        colorBufferImage.reset();
        colorBufferMemory.Reset();
    };
    setupColorBuffer(); // 初回セットアップ

    // RenderPass 領域を事前確保
    ::std::unique_ptr<::ae::gfx_low::RenderPass> mainRenderPass;
    ::ae::base::RuntimeArray<::std::unique_ptr<::ae::gfx_low::RenderPass>>
        copyRenderPassArray;
    copyRenderPassArray.Resize(gfxKit.SwapchainImageCount());

    // メインループ
    bool isFinishedSetupTexture = false;
    bool isFinishedSetupColorBufferState = false;
    int frameCount = 0;
    while (app->ReceiveEvent() == ::ae::base::AppEvent::Update) {
        // ディスプレイが閉じてたら終了
        if (display.IsClosed()) {
            app->Quit();
            continue;
        }

        // 前回実行したコマンドの終了保証
        gfxKit.WaitToResourceUsable();

        // スクリーンリサイズ処理
        if (gfxKit.ScreenResizeProcessIfNeeds()) {
            cleanupColorBuffer();
            setupColorBuffer();
            isFinishedSetupColorBufferState = false;
        }

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
            auto model = ::ae::base::Quaternion(
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

        
        // 初回ならコマンドを保存
        //if (frameCount < secondaryCommandBuffers.Count()) {
        //    // 保存開始
        //    auto& subCmd = secondaryCommandBuffers[bufferIndex];
        //    subCmd.BeginRecord();

        //    // Pipeline & DescriptorSet
        //    subCmd.CmdSetRenderPipeline(*mainPipeline);
        //    subCmd.CmdSetDescriptorSet(mainDescriptorSets[bufferIndex]);

        //    // Draw
        //    subCmd.CmdSetVertexBuffer(0, cubeVertexBuffer.View());
        //    subCmd.CmdDraw(
        //        ::ae::gfx_low::DrawCallInfo().SetVertexCount(12 * 3));

        //    // 保存終了
        //    subCmd.EndRecord();
        //}

        // コマンドバッファ作成
        auto& cmd = gfxKit.CurrentCommandBuffer();
        cmd.BeginRecord();
        {
            // テクスチャのセットアップ
            if (!isFinishedSetupTexture) {
                isFinishedSetupTexture = true;

                if (copySrcTextureBuffer.get() == nullptr) {
                    // デバイスメモリが共有メモリの場合はメモリバリアのみ設定して終了
                    cmd.CmdImageResourceBarrier(
                        ::ae::gfx_low::ImageResourceBarrierInfo()
                            .SetResource(textureImage.get())
                            .SetOldState(
                                ::ae::gfx_low::ImageResourceState::Unknown)
                            .SetNewState(::ae::gfx_low::ImageResourceState::
                                             ShaderResourceReadOnly));
                } else {
                    // デバイスメモリが専用メモリの場合はアップロードとメモリバリアを設定
                    cmd.CmdImageResourceBarrier(
                        ::ae::gfx_low::ImageResourceBarrierInfo()
                            .SetResource(textureImage.get())
                            .SetOldState(
                                ::ae::gfx_low::ImageResourceState::Unknown)
                            .SetNewState(
                                ::ae::gfx_low::ImageResourceState::CopyDst));
                    cmd.CmdCopyBufferToImage(copyBufferToImageInfo);
                    cmd.CmdImageResourceBarrier(
                        ::ae::gfx_low::ImageResourceBarrierInfo()
                            .SetResource(textureImage.get())
                            .SetOldState(
                                ::ae::gfx_low::ImageResourceState::CopyDst)
                            .SetNewState(::ae::gfx_low::ImageResourceState::
                                             ShaderResourceReadOnly));
                }
            }

            // カラーバッファの状態セットアップ
            if (!isFinishedSetupColorBufferState) {
                isFinishedSetupColorBufferState = true;

                // デスクリプタセット更新
                {
                    // SampledImage
                    const ::ae::gfx_low::SampledImageView*
                        sampledImageViews[] = { colorBufferTextureView.get() };
                    const ::ae::gfx_low::SampledImageDescriptorInfo
                        sampledImageDescs[] = {
                            ::ae::gfx_low::SampledImageDescriptorInfo()
                                .SetRegion(
                                    ::ae::gfx_low::ShaderBindingRegion()
                                        .SetBindingIndex(0)
                                        .SetElemCount(AE_BASE_ARRAY_LENGTH(
                                            sampledImageViews)))
                                .SetViews(sampledImageViews),
                        };

                    // Sampler
                    const ::ae::gfx_low::Sampler* samplers[] = {
                        sampler.get()
                    };
                    const ::ae::gfx_low::SamplerDescriptorInfo
                        samplerDescs[] = {
                            ::ae::gfx_low::SamplerDescriptorInfo()
                                .SetRegion(
                                    ::ae::gfx_low::ShaderBindingRegion()
                                        .SetBindingIndex(0)
                                        .SetElemCount(
                                            AE_BASE_ARRAY_LENGTH(samplers)))
                                .SetSamplers(samplers),
                        };

                    // 更新
                    copyDescriptorSet.Update(
                        ::ae::gfx_low::DescriptorSetUpdateInfo()
                            .SetSampledImageInfos(
                                AE_BASE_ARRAY_LENGTH(sampledImageDescs),
                                sampledImageDescs)
                            .SetSamplerInfos(
                                AE_BASE_ARRAY_LENGTH(samplerDescs),
                                samplerDescs));
                }

                // レンダーパス再生成
                mainRenderPass.reset();
                {
                    const ::ae::gfx_low::RenderTargetSetting
                        renderTargetSettings[] = {
                            ::ae::gfx_low::RenderTargetSetting()
                                .SetRenderTargetImageView(
                                    colorBufferRenderTargetView.get())
                                .SetLoadOp(
                                    ::ae::gfx_low::AttachmentLoadOp::Clear)
                                .SetStoreOp(
                                    ::ae::gfx_low::AttachmentStoreOp::Store)
                                .SetInitialImageResourceState(
                                    ::ae::gfx_low::ImageResourceState::Unknown)
                                .SetFinalImageResourceState(
                                    ::ae::gfx_low::ImageResourceState::
                                        ShaderResourceReadOnly)
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
                            .SetDepthLoadOp(
                                ::ae::gfx_low::AttachmentLoadOp::Clear)
                            .SetDepthStoreOp(
                                ::ae::gfx_low::AttachmentStoreOp::Store)
                            .SetDepthClearValue(1.0f)
                            .SetStencilLoadOp(
                                ::ae::gfx_low::AttachmentLoadOp::Clear)
                            .SetStencilStoreOp(
                                ::ae::gfx_low::AttachmentStoreOp::Store)
                            .SetStencilClearValue(0);
                    mainRenderPass.reset(new ::ae::gfx_low::RenderPass(
                        ::ae::gfx_low::RenderPassCreateInfo(
                            ::ae::gfx_low::RenderPassCreateInfo()
                                .SetDevice(&gfxKit.Device())
                                .SetRenderPassSpecInfo(mainRenderPassSpecInfo)
                                .SetRenderTargetSettings(renderTargetSettings)
                                .SetDepthStencilSettingPtr(&depthStencilSetting)
                                .SetRenderArea(::ae::base::Aabb2i(
                                    ::ae::base::Vector2i::Zero(),
                                    display.MainScreen().Extent())))));

                }

                // ２ループ目以降と状況一致させるために初期状態を変更
                //cmd.CmdImageResourceBarrier(
                //    ::ae::gfx_low::ImageResourceBarrierInfo()
                //        .SetResource(colorBufferImage.get())
                //        .SetOldState(::ae::gfx_low::ImageResourceState::Unknown)
                //        .SetNewState(::ae::gfx_low::ImageResourceState::
                //                         ShaderResourceReadOnly));
            }

            
            // コピー用レンダーパス準備
            auto& copyRenderPassUniquePtr = copyRenderPassArray[bufferIndex];
            {
                copyRenderPassUniquePtr.reset();

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
                copyRenderPassUniquePtr.reset(new ::ae::gfx_low::RenderPass(
                    ::ae::gfx_low::RenderPassCreateInfo()
                        .SetDevice(&gfxKit.Device())
                        .SetRenderPassSpecInfo(copyRenderPassSpecInfo)
                        .SetRenderTargetSettings(renderTargetSettings)
                        .SetRenderArea(::ae::base::Aabb2i(
                            ::ae::base::Vector2i::Zero(),
                            display.MainScreen().Extent()))));
            }


            // メイン描画
            {
                // 開始
                cmd.CmdBeginRenderPass(
                    ::ae::gfx_low::RenderPassBeginInfo().SetRenderPass(
                        mainRenderPass.get()));

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
                cmd.CmdSetRenderPipeline(*mainPipeline);
                cmd.CmdSetDescriptorSet(mainDescriptorSets[bufferIndex]);

                // Draw
                cmd.CmdSetVertexBuffer(0, cubeVertexBuffer.View());
                cmd.CmdDraw(
                    ::ae::gfx_low::DrawCallInfo().SetVertexCount(geometryCube.VertexCount()));

                // 描画パス終了
                cmd.CmdEndRenderPass();
            }

            // Swapchain にコピー描画
            {
                // 開始
                cmd.CmdBeginRenderPass(
                    ::ae::gfx_low::RenderPassBeginInfo().SetRenderPass(
                        copyRenderPassUniquePtr.get()));

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
                cmd.CmdSetRenderPipeline(*copyPipeline);
                cmd.CmdSetDescriptorSet(copyDescriptorSet);

                // Draw
                cmd.CmdSetVertexBuffer(0, squareVertexBuffer.View());
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