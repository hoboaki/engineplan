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
#include <aesk/GfxBasicKit.hpp>
#include <aesk/IndexBuffer.hpp>
#include <aesk/Shader.hpp>
#include <aesk/UniformBuffer.hpp>
#include <aesk/VertexBuffer.hpp>
#include <ext/GeometrySphere.hpp>
#include <memory>

//------------------------------------------------------------------------------
namespace {

struct fSceneUniformDataType
{
    ::ae::base::Matrix44Pod projMtx;
    ::ae::base::Matrix44Pod viewMtx;
    ::ae::base::Matrix44Pod invViewMtx;
};

struct fModelUniformDataType
{
    ::ae::base::Matrix44Pod modelMtx;
};

const uint32_t fShapeVertShaderCode[] = {
#include "ShaderShape.vert.inc"
};

const uint32_t fShapeFragShaderCode[] = {
#include "ShaderShape.frag.inc"
};

const uint32_t fSkySphereVertShaderCode[] = {
#include "ShaderSkySphere.vert.inc"
};

const uint32_t fSkySphereFragShaderCode[] = {
#include "ShaderSkySphere.frag.inc"
};

#include <../Resource/cubemap_yokohama256/NegX.hpp>
#include <../Resource/cubemap_yokohama256/NegY.hpp>
#include <../Resource/cubemap_yokohama256/NegZ.hpp>
#include <../Resource/cubemap_yokohama256/PosX.hpp>
#include <../Resource/cubemap_yokohama256/PosY.hpp>
#include <../Resource/cubemap_yokohama256/PosZ.hpp>
namespace cubemap = ::cubemap_yokohama256;
const uint8_t* const fCubemapPixelFaces[] = {
    cubemap::PosX_Pixels,
    cubemap::NegX_Pixels,
    cubemap::PosY_Pixels,
    cubemap::NegY_Pixels,
    cubemap::PosZ_Pixels,
    cubemap::NegZ_Pixels,
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
                                .SetWindowTitle("AeVulkan06 - Cube Map")
                                .SetIsResizableWindow(true));

    // ディスプレイの表示
    display.Show();

    // 基本キット
    ::aesk::GfxBasicKit gfxKit(&display);

    // Shader の作成
    ::aesk::Shader shapelVertShader(
        &gfxKit,
        fShapeVertShaderCode,
        sizeof(fShapeVertShaderCode));
    ::aesk::Shader shapeFragShader(
        &gfxKit,
        fShapeFragShaderCode,
        sizeof(fShapeFragShaderCode));
    ::aesk::Shader skySphereVertShader(
        &gfxKit,
        fSkySphereVertShaderCode,
        sizeof(fSkySphereVertShaderCode));
    ::aesk::Shader skySphereFragShader(
        &gfxKit,
        fSkySphereFragShaderCode,
        sizeof(fSkySphereFragShaderCode));

    // Sphere の用意
    GeometrySphere geometrySphere;

    // VertexBuffer の作成
    const auto vertexBufferLayoutInfo =
        ::ae::gfx_low::VertexBufferLayoutInfo().SetStride(
            geometrySphere.getInterleavedStride());
    const ::ae::gfx_low::VertexAttributeInfo vertexAttrInfos[] = {
        ::ae::gfx_low::VertexAttributeInfo().SetFormat(
            ::ae::gfx_low::VertexFormat::Sfloat32x3),
        ::ae::gfx_low::VertexAttributeInfo()
            .SetFormat(::ae::gfx_low::VertexFormat::Sfloat32x3)
            .SetOffset(geometrySphere.getInterleavedOffsetNormal()),
        ::ae::gfx_low::VertexAttributeInfo()
            .SetFormat(::ae::gfx_low::VertexFormat::Sfloat32x2)
            .SetOffset(geometrySphere.getInterleavedOffsetTexCoord()),
    };
    ::aesk::VertexBuffer vertexBuffer(
        &gfxKit.Device(),
        geometrySphere.getInterleavedVertexSize(),
        vertexBufferLayoutInfo);
    {
        // バッファ更新
        vertexBuffer.StoreToResourceMemory(::ae::base::MemBlock(
            const_cast<float*>(geometrySphere.getInterleavedVertices()),
            geometrySphere.getInterleavedVertexSize()));
    }

    // IndexBuffer の作成
    ::aesk::IndexBuffer indexBuffer(
        &gfxKit.Device(),
        geometrySphere.getIndexSize(),
        ::ae::gfx_low::IndexFormat::Uint32);
    {
        // バッファ更新
        indexBuffer.StoreToResourceMemory(::ae::base::MemBlock(
            const_cast<uint32_t*>(geometrySphere.getIndices()),
            geometrySphere.getIndexSize()));
    }

    // ポリゴンに貼り付けるキューブテクスチャの作成
    // 画像の内容はコピー処理で転送される
    constexpr int cubeFaceCount = 6;
    ::ae::gfx_low::UniqueResourceMemory textureMemory;
    ::std::unique_ptr<::ae::gfx_low::ImageResource> textureImage;
    ::std::unique_ptr<::ae::gfx_low::SampledImageView> textureView;
    const auto textureImageExtent =
        ::ae::base::Extent2i(cubemap::NegX_Width, cubemap::NegX_Height);
    const auto textureImageFormat = ::ae::gfx_low::ImageFormat::R8G8B8A8Unorm;
    {
        const auto baseSpecInfo =
            ::ae::gfx_low::ImageResourceSpecInfo()
                .SetKind(::ae::gfx_low::ImageResourceKind::ImageCube)
                .SetFormat(textureImageFormat)
                .SetExtent(textureImageExtent);
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
                        .Set(::ae::gfx_low::ImageResourceUsage::CopyDst, true));
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
                .SetKind(::ae::gfx_low::ImageViewKind::ImageCube)
                .SetFormat(textureImageFormat)));
    }

    // 転送元用テクスチャメモリの用意
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::UniqueResourceMemory>
        faceImageSrcMemories(cubeFaceCount);
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::BufferResource>
        faceImageSrcBuffers(cubeFaceCount);
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::CopyBufferToImageInfo>
        copyBufferToImageInfos(cubeFaceCount);
    {
        const auto specInfo =
            ::ae::gfx_low::ImageResourceSpecInfo()
                .SetKind(::ae::gfx_low::ImageResourceKind::Image2d)
                .SetFormat(textureImageFormat)
                .SetExtent(textureImageExtent)
                .SetTiling(::ae::gfx_low::ImageResourceTiling::Linear)
                .SetUsageBitSet(::ae::gfx_low::ImageResourceUsageBitSet().Set(
                    ::ae::gfx_low::ImageResourceUsage::CopySrc,
                    true));
        const auto dataInfo = gfxKit.Device().CalcImageSubresourceDataInfo(
            specInfo,
            ::ae::gfx_low::ImageSubresourceLocation());
        for (int faceIdx = 0; faceIdx < cubeFaceCount; ++faceIdx) {
            faceImageSrcMemories.Add(
                &gfxKit.Device(),
                ::ae::gfx_low::ResourceMemoryAllocInfo()
                    .SetKind(::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
                    .SetParams(gfxKit.Device().CalcResourceMemoryRequirements(
                        specInfo)));
            faceImageSrcBuffers.Add(
                ::ae::gfx_low::BufferResourceCreateInfo()
                    .SetDevice(&gfxKit.Device())
                    .SetSpecInfo(
                        ::ae::gfx_low::BufferResourceSpecInfo()
                            .SetSize(
                                dataInfo.RowPitch() * textureImageExtent.height)
                            .SetUsageBitSet(
                                ::ae::gfx_low::BufferResourceUsageBitSet().Set(
                                    ::ae::gfx_low::BufferResourceUsage::CopySrc,
                                    true)))
                    .SetDataAddress(faceImageSrcMemories[faceIdx]->Address()));
            copyBufferToImageInfos.Add(
                ::ae::gfx_low::CopyBufferToImageInfo()
                    .SetSrcBufferResource(&faceImageSrcBuffers[faceIdx])
                    .SetSrcBufferRowPitch(dataInfo.RowPitch())
                    .SetSrcBufferDepthPitch(dataInfo.DepthPitch())
                    .SetSrcImageFormat(textureImageFormat)
                    .SetSrcImageExtent(textureImageExtent)
                    .SetDstImageResource(textureImage.get())
                    .SetDstSubresourceLocation(
                        ::ae::gfx_low::ImageSubresourceLocation().SetFaceIndex(
                            faceIdx))
                    .SetDstImageResourceState(
                        ::ae::gfx_low::ImageResourceState::CopyDst));

            // ピクセルデータをバッファに格納
            uint8_t* dst = gfxKit.Device().MapResourceMemory(
                *faceImageSrcMemories[faceIdx],
                ::ae::gfx_low::ResourceMemoryRegion()
                    .SetOffset(dataInfo.Offset())
                    .SetSize(dataInfo.RowPitch() * textureImageExtent.height));
            const auto* pixels = fCubemapPixelFaces[faceIdx];
            for (int y = 0; y < textureImageExtent.height; ++y) {
                for (int x = 0; x < textureImageExtent.width; ++x) {
                    const size_t baseOffset =
                        size_t(y) * dataInfo.RowPitch() + size_t(x) * 4;
                    const int pixelsOffset =
                        (y * textureImageExtent.width + x) * 3;
                    dst[baseOffset + 0] = pixels[pixelsOffset + 0];
                    dst[baseOffset + 1] = pixels[pixelsOffset + 1];
                    dst[baseOffset + 2] = pixels[pixelsOffset + 2];
                    dst[baseOffset + 3] = 0xFF;
                }
            }
            gfxKit.Device().UnmapResourceMemory(*faceImageSrcMemories[faceIdx]);
        }
    }

    // Sampler の作成
    ::std::unique_ptr<::ae::gfx_low::Sampler> sampler;
    {
        sampler.reset(new ::ae::gfx_low::Sampler(
            ::ae::gfx_low::SamplerCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetMinFilter(::ae::gfx_low::SamplerMinMagFilter::Linear)
                .SetMagFilter(::ae::gfx_low::SamplerMinMagFilter::Linear)));
    }

    // UniformBuffer の作成
    ::aesk::UniformBuffer sceneUniformBuffer(
        &gfxKit.Device(),
        sizeof(fSceneUniformDataType),
        gfxKit.SwapchainImageCount());
    ::aesk::UniformBuffer shapeModelUniformBuffer(
        &gfxKit.Device(),
        sizeof(fModelUniformDataType),
        gfxKit.SwapchainImageCount());
    ::aesk::UniformBuffer skyBoxModelUniformBuffer(
        &gfxKit.Device(),
        sizeof(fModelUniformDataType),
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

    // GraphicsPipeline 用 DescriptorSetSpecInfo の作成
    const ::ae::gfx_low::ShaderBindingInfo
        graphicsUniformBufferBindingInfos[] = {
            ::ae::gfx_low::ShaderBindingInfo()
                .SetStages(
                    ::ae::gfx_low::ShaderBindingStageBitSet()
                        .Set(::ae::gfx_low::ShaderBindingStage::Vertex, true)
                        .Set(::ae::gfx_low::ShaderBindingStage::Fragment, true))
                .SetBindingIndex(0),
            ::ae::gfx_low::ShaderBindingInfo()
                .SetStages(
                    ::ae::gfx_low::ShaderBindingStageBitSet()
                        .Set(::ae::gfx_low::ShaderBindingStage::Vertex, true)
                        .Set(::ae::gfx_low::ShaderBindingStage::Fragment, true))
                .SetBindingIndex(1)
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
                AE_BASE_ARRAY_LENGTH(graphicsUniformBufferBindingInfos),
                graphicsUniformBufferBindingInfos)
            .SetBindingInfos(
                ::ae::gfx_low::DescriptorKind::SampledImage,
                AE_BASE_ARRAY_LENGTH(sampledImageBindingInfos),
                sampledImageBindingInfos)
            .SetBindingInfos(
                ::ae::gfx_low::DescriptorKind::Sampler,
                AE_BASE_ARRAY_LENGTH(samplerBindingInfos),
                samplerBindingInfos);

    // GraphicsPipeline 用 DescriptorSet の作成
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::DescriptorSet>
        shapeDescriptorSets(gfxKit.SwapchainImageCount());
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::DescriptorSet>
        skySphereDescriptorSets(gfxKit.SwapchainImageCount());
    for (int i = 0; i < gfxKit.SwapchainImageCount(); ++i) {
        shapeDescriptorSets.Add(
            ::ae::gfx_low::DescriptorSetCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetSpecInfo(graphicsDescriptorSetSpecInfo));
        skySphereDescriptorSets.Add(
            ::ae::gfx_low::DescriptorSetCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetSpecInfo(graphicsDescriptorSetSpecInfo));
    }
    {
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
        for (int i = 0; i < gfxKit.SwapchainImageCount(); ++i) {
            {
                // UniformBuffer
                const ::ae::gfx_low::UniformBufferView* views[] = {
                    &sceneUniformBuffer.View(i),
                    &shapeModelUniformBuffer.View(i)
                };
                const ::ae::gfx_low::UniformBufferDescriptorInfo
                    uniformBufferDescs[] = {
                        ::ae::gfx_low::UniformBufferDescriptorInfo()
                            .SetRegion(
                                ::ae::gfx_low::ShaderBindingRegion()
                                    .SetBindingIndex(0)
                                    .SetElemCount(AE_BASE_ARRAY_LENGTH(views)))
                            .SetViews(views),
                    };
                shapeDescriptorSets[i].Update(
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
            {
                // UniformBuffer
                const ::ae::gfx_low::UniformBufferView* views[] = {
                    &sceneUniformBuffer.View(i),
                    &skyBoxModelUniformBuffer.View(i)
                };
                const ::ae::gfx_low::UniformBufferDescriptorInfo
                    uniformBufferDescs[] = {
                        ::ae::gfx_low::UniformBufferDescriptorInfo()
                            .SetRegion(
                                ::ae::gfx_low::ShaderBindingRegion()
                                    .SetBindingIndex(0)
                                    .SetElemCount(AE_BASE_ARRAY_LENGTH(views)))
                            .SetViews(views),
                    };
                skySphereDescriptorSets[i].Update(
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
    }

    // GraphicsPipeline 生成
    std::unique_ptr<::ae::gfx_low::RenderPipeline> shapeGraphicsPipeline;
    {
        const ::ae::gfx_low::RenderTargetBlendInfo blendInfos[] = {
            ::ae::gfx_low::RenderTargetBlendInfo(),
        };
        AE_BASE_ARRAY_LENGTH_CHECK(
            blendInfos,
            AE_BASE_ARRAY_LENGTH(renderTargetSpecInfos));

        shapeGraphicsPipeline.reset(new ::ae::gfx_low::RenderPipeline(
            ::ae::gfx_low::RenderPipelineCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetRenderPassSpecInfo(renderPassSpecInfo)
                .SetShaderInfo(
                    ::ae::gfx_low::RenderPipelineShaderStage::Vertex,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(&shapelVertShader.Resource())
                        .SetEntryPointNamePtr("main"))
                .SetShaderInfo(
                    ::ae::gfx_low::RenderPipelineShaderStage::Fragment,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(&shapeFragShader.Resource())
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
    std::unique_ptr<::ae::gfx_low::RenderPipeline> skySphereGraphicsPipeline;
    {
        const ::ae::gfx_low::RenderTargetBlendInfo blendInfos[] = {
            ::ae::gfx_low::RenderTargetBlendInfo(),
        };
        AE_BASE_ARRAY_LENGTH_CHECK(
            blendInfos,
            AE_BASE_ARRAY_LENGTH(renderTargetSpecInfos));

        skySphereGraphicsPipeline.reset(new ::ae::gfx_low::RenderPipeline(
            ::ae::gfx_low::RenderPipelineCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetRenderPassSpecInfo(renderPassSpecInfo)
                .SetShaderInfo(
                    ::ae::gfx_low::RenderPipelineShaderStage::Vertex,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(&skySphereVertShader.Resource())
                        .SetEntryPointNamePtr("main"))
                .SetShaderInfo(
                    ::ae::gfx_low::RenderPipelineShaderStage::Fragment,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(&skySphereFragShader.Resource())
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
                            ::ae::gfx_low::PolygonFrontFace::
                                Clockwise) // 裏面を表として扱うので時計周りを表面に
                        .SetCullMode(::ae::gfx_low::RasterizeCullMode::Back))
                .SetDepthStencilInfo(
                    ::ae::gfx_low::PipelineDepthStencilInfo()
                        .SetDepthTestEnable(true)
                        .SetDepthWriteEnable(true)
                        .SetDepthCompareOp(::ae::gfx_low::CompareOp::LessEqual))
                .SetBlendInfo(::ae::gfx_low::PipelineBlendInfo()
                                  .SetRenderTargetBlendInfos(blendInfos))));
    }

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
            // シーンユニフォーム更新
            {
                fSceneUniformDataType data = {};
                data.projMtx = ::ae::base::Matrix44::Perspective(
                    ::ae::base::Angle(::ae::base::Degree(25.0f)),
                    float(display.MainScreen().Width()) /
                        display.MainScreen().Height(), // aspect
                    0.1f, // near
                    1000.0f // far
                );
                auto eyePos = ::ae::base::Quaternion(
                                  ::ae::base::Vector3::UnitY(),
                                  ::ae::base::Degree(0.6f * frameCount))
                                  .ToRotateMatrix() *
                              ::ae::base::Vector3(0.0f, 0.0f, 5.0f);
                data.viewMtx = ::ae::base::Matrix44::LookAt(
                    eyePos,
                    ::ae::base::Vector3::Zero(), // targetPos
                    ::ae::base::Vector3::UnitY() // upVec
                );
                data.invViewMtx = data.viewMtx.Invert();
                sceneUniformBuffer.StoreToResourceMemory(bufferIndex, data);
            }

            // シェイプモデルユニフォーム
            {
                fModelUniformDataType data = {};
                data.modelMtx = ::ae::base::Matrix44::Identity();
                shapeModelUniformBuffer.StoreToResourceMemory(
                    bufferIndex,
                    data);
            }

            // 天球モデルユニフォーム
            {
                fModelUniformDataType data = {};
                data.modelMtx =
                    ::ae::base::Matrix34::Scale(::ae::base::Vector3::One() * 100.0f)
                        .ToMatrix44();
                skyBoxModelUniformBuffer.StoreToResourceMemory(
                    bufferIndex,
                    data);
            }
        }

        // コマンドバッファ作成
        auto& cmd = gfxKit.CurrentCommandBuffer();
        cmd.BeginRecord();
        {
            // テクスチャのセットアップ
            if (!isFinishedSetupTexture) {
                // コピー先状態に移行
                cmd.CmdImageResourceBarrier(
                    ::ae::gfx_low::ImageResourceBarrierInfo()
                        .SetResource(textureImage.get())
                        .SetOldState(::ae::gfx_low::ImageResourceState::Unknown)
                        .SetNewState(
                            ::ae::gfx_low::ImageResourceState::CopyDst));

                // 各面をコピー
                for (int faceIdx = 0; faceIdx < cubeFaceCount; ++faceIdx) {
                    cmd.CmdCopyBufferToImage(copyBufferToImageInfos[faceIdx]);
                }

                // 読み込み専用状態に移行
                cmd.CmdImageResourceBarrier(
                    ::ae::gfx_low::ImageResourceBarrierInfo()
                        .SetResource(textureImage.get())
                        .SetOldState(::ae::gfx_low::ImageResourceState::CopyDst)
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

                // Draw-Shape
                {
                    // Pipeline & DescriptorSet
                    cmd.CmdSetRenderPipeline(*shapeGraphicsPipeline);
                    cmd.CmdSetDescriptorSet(shapeDescriptorSets[bufferIndex]);

                    // Draw
                    cmd.CmdSetVertexBuffer(0, vertexBuffer.View());
                    cmd.CmdSetIndexBuffer(indexBuffer.View());
                    cmd.CmdDraw(
                        ::ae::gfx_low::DrawCallInfo()
                            .SetUseIndexBuffer(true)
                            .SetVertexCount(geometrySphere.getIndexCount()));
                }

                // Draw-SkySphere
                {
                    // Pipeline & DescriptorSet
                    cmd.CmdSetRenderPipeline(*skySphereGraphicsPipeline);
                    cmd.CmdSetDescriptorSet(
                        skySphereDescriptorSets[bufferIndex]);

                    // Draw
                    cmd.CmdSetVertexBuffer(0, vertexBuffer.View());
                    cmd.CmdSetIndexBuffer(indexBuffer.View());
                    cmd.CmdDraw(
                        ::ae::gfx_low::DrawCallInfo()
                            .SetUseIndexBuffer(true)
                            .SetVertexCount(geometrySphere.getIndexCount()));
                }

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
