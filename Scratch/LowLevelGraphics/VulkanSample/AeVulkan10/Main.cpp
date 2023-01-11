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
#include <ae/gfx_low/CommandBufferBeginRecordInfo.hpp>
#include <ae/gfx_low/CommandBufferCreateInfo.hpp>
#include <ae/gfx_low/CopyBufferInfo.hpp>
#include <ae/gfx_low/CopyBufferToImageInfo.hpp>
#include <ae/gfx_low/DepthStencilSetting.hpp>
#include <ae/gfx_low/DepthStencilSpecInfo.hpp>
#include <ae/gfx_low/DescriptorSet.hpp>
#include <ae/gfx_low/DescriptorSetCreateInfo.hpp>
#include <ae/gfx_low/DescriptorSetUpdateInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/DrawCallInfo.hpp>
#include <ae/gfx_low/DrawIndirectCallInfo.hpp>
#include <ae/gfx_low/DrawIndirectIndexedCommand.hpp>
#include <ae/gfx_low/DrawIndirectNormalCommand.hpp>
#include <ae/gfx_low/Fence.hpp>
#include <ae/gfx_low/FenceCreateInfo.hpp>
#include <ae/gfx_low/ImageResource.hpp>
#include <ae/gfx_low/ImageResourceBarrierInfo.hpp>
#include <ae/gfx_low/ImageResourceCreateInfo.hpp>
#include <ae/gfx_low/ImageSubresourceDataInfo.hpp>
#include <ae/gfx_low/ImageSubresourceLocation.hpp>
#include <ae/gfx_low/IndirectBufferView.hpp>
#include <ae/gfx_low/IndirectBufferViewCreateInfo.hpp>
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
#include <aesk/IndexBuffer.hpp>
#include <aesk/Shader.hpp>
#include <aesk/UniformBuffer.hpp>
#include <aesk/VertexBuffer.hpp>
#include <ext/GeometrySphere.hpp>
#include <memory>

//------------------------------------------------------------------------------
namespace {

struct fUniformDataType
{
    ::ae::base::Matrix44Pod projMtx;
    ::ae::base::Matrix44Pod viewMtx;
    ::ae::base::Matrix44Pod invViewMtx;
    ::ae::base::Matrix44Pod modelMtx;
    ::ae::base::Vector4Pod instanceTrans;
};

const uint32_t fCopyVertShaderCode[] = {
#include "ShaderCopy.vert.inc"
};

const uint32_t fCopyFragShaderCode[] = {
#include "ShaderCopy.frag.inc"
};

const uint32_t fShapeVertShaderCode[] = {
#include "ShaderShape.vert.inc"
};

const uint32_t fShapeaFragShaderCode[] = {
#include "ShaderShape.frag.inc"
};

} // namespace

//------------------------------------------------------------------------------
int aemain(::ae::base::Application* app)
{
    // コンソール出力
    AE_BASE_COUT_LINE_WITH_TIME("Adel runtime start.");

    // ディスプレイの作成
    ::ae::base::Display display = ::ae::base::Display(
        ::ae::base::DisplayContext()
            .SetWindowTitle("AeVulkan10 - Indirect Draw")
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
    ::aesk::Shader shapeVertShader(
        &gfxKit,
        fShapeVertShaderCode,
        sizeof(fShapeVertShaderCode));
    ::aesk::Shader shapeFragShader(
        &gfxKit,
        fShapeaFragShaderCode,
        sizeof(fShapeaFragShaderCode));

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
            .SetFormat(::ae::gfx_low::VertexFormat::Sfloat32x3)
            .SetOffset(geometryCube.OffsetNormal()),
    };
    ::aesk::VertexBuffer cubeVertexBuffer(
        &gfxKit.Device(),
        geometryCube.Data().Size(),
        cubeVertexBufferLayoutInfo);
    cubeVertexBuffer.StoreToResourceMemory(geometryCube.Data());

    // VertexBuffer の作成（球）
    ::GeometrySphere geometrySphere;
    const auto sphereVertexBufferLayoutInfo =
        ::ae::gfx_low::VertexBufferLayoutInfo().SetStride(
            geometrySphere.getInterleavedStride());
    const ::ae::gfx_low::VertexAttributeInfo sphereVrtexAttrInfos[] = {
        ::ae::gfx_low::VertexAttributeInfo()
            .SetFormat(::ae::gfx_low::VertexFormat::Sfloat32x3),
        ::ae::gfx_low::VertexAttributeInfo()
            .SetFormat(::ae::gfx_low::VertexFormat::Sfloat32x3)
            .SetOffset(geometrySphere.getInterleavedOffsetNormal()),
    };
    ::aesk::VertexBuffer sphereVertexBuffer(
        &gfxKit.Device(),
        geometrySphere.getInterleavedVertexSize(),
        sphereVertexBufferLayoutInfo);
    sphereVertexBuffer.StoreToResourceMemory(::ae::base::MemBlock(
        geometrySphere.getInterleavedVertices(),
        geometrySphere.getInterleavedVertexSize()));

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

    // IndexBuffer の作成
    ::aesk::IndexBuffer sphereIndexBuffer(
        &gfxKit.Device(),
        geometrySphere.getIndexSize(),
        ::ae::gfx_low::IndexFormat::Uint32);
    {
        // バッファ更新
        sphereIndexBuffer.StoreToResourceMemory(::ae::base::MemBlock(
            const_cast<uint32_t*>(geometrySphere.getIndices()),
            geometrySphere.getIndexSize()));
    }

    // Sampler の作成
    ::std::unique_ptr<::ae::gfx_low::Sampler> sampler;
    {
        sampler.reset(new ::ae::gfx_low::Sampler(
            ::ae::gfx_low::SamplerCreateInfo().SetDevice(&gfxKit.Device())));
    }

    // UniformBuffer の作成
    ::aesk::UniformBuffer cubeUniformBuffer(
        &gfxKit.Device(),
        sizeof(fUniformDataType),
        1, // dataCount: バッファリング不要なので１つでOK
        true // isDeviceLocal: CPU上からアクセスしないので true
    );
    ::aesk::UniformBuffer sphereUniformBuffer(
        &gfxKit.Device(),
        sizeof(fUniformDataType),
        1, // dataCount: バッファリング不要なので１つでOK
        true // isDeviceLocal: CPU上からアクセスしないので true
    );

    // IndirectBuffer の作成
    const int cubeInstanceCount = 3;
    const int sphereInstanceCount = 3;
    const auto cubeIndirectRegion =
        ::ae::gfx_low::ResourceMemoryRegion().SetSize(
            cubeInstanceCount *
            sizeof(::ae::gfx_low::DrawIndirectNormalCommand));
    const auto sphereIndirectRegion =
        ::ae::gfx_low::ResourceMemoryRegion().SetSize(
            sphereInstanceCount *
            sizeof(::ae::gfx_low::DrawIndirectIndexedCommand));
    ::ae::gfx_low::UniqueResourceMemory cubeIndirectMemory;
    ::ae::gfx_low::UniqueResourceMemory cubeCopySrcIndirectMemory;
    ::ae::gfx_low::UniqueResourceMemory sphereIndirectMemory;
    ::ae::gfx_low::UniqueResourceMemory sphereCopySrcIndirectMemory;
    ::std::unique_ptr<::ae::gfx_low::BufferResource> cubeIndirectBuffer;
    ::std::unique_ptr<::ae::gfx_low::BufferResource> cubeCopySrcIndirectBuffer;
    ::std::unique_ptr<::ae::gfx_low::BufferResource> sphereIndirectBuffer;
    ::std::unique_ptr<::ae::gfx_low::BufferResource> sphereCopySrcIndirectBuffer;
    ::std::unique_ptr<::ae::gfx_low::IndirectBufferView> cubeIndirectView;
    ::std::unique_ptr<::ae::gfx_low::IndirectBufferView> sphereIndirectView;
    {
        const auto cubeSpecInfo =
            ::ae::gfx_low::BufferResourceSpecInfo()
                .SetSize(cubeIndirectRegion.Size())
                .SetUsageBitSet(
                    ::ae::gfx_low::BufferResourceUsageBitSet()
                        .On(::ae::gfx_low::BufferResourceUsage::IndirectBuffer)
                        .On(::ae::gfx_low::BufferResourceUsage::CopyDst));
        const auto cubeCopySrcSpecInfo =
            ::ae::gfx_low::BufferResourceSpecInfo(cubeSpecInfo)
                .SetUsageBitSet(::ae::gfx_low::BufferResourceUsageBitSet().On(
                    ::ae::gfx_low::BufferResourceUsage::CopySrc));
        cubeIndirectMemory.Reset(
            &gfxKit.Device(),
            ::ae::gfx_low::ResourceMemoryAllocInfo()
                .SetKind(::ae::gfx_low::ResourceMemoryKind::DeviceLocal)
                .SetParams(
                    gfxKit.Device().CalcResourceMemoryRequirements(cubeSpecInfo)));
        cubeCopySrcIndirectMemory.Reset(
            &gfxKit.Device(),
            ::ae::gfx_low::ResourceMemoryAllocInfo()
                .SetKind(::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
                .SetParams(
                    gfxKit.Device().CalcResourceMemoryRequirements(cubeSpecInfo)));
        cubeIndirectBuffer.reset(new ::ae::gfx_low::BufferResource(
            ::ae::gfx_low::BufferResourceCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetSpecInfo(cubeSpecInfo)
                .SetDataAddress(*cubeIndirectMemory)));
        cubeCopySrcIndirectBuffer.reset(new ::ae::gfx_low::BufferResource(
            ::ae::gfx_low::BufferResourceCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetSpecInfo(cubeCopySrcSpecInfo)
                .SetDataAddress(*cubeCopySrcIndirectMemory)));
        cubeIndirectView.reset(new ::ae::gfx_low::IndirectBufferView(
            ::ae::gfx_low::IndirectBufferViewCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetResource(cubeIndirectBuffer.get())
                .SetRegion(cubeIndirectRegion)));
    }
    {
        const auto sphereSpecInfo =
            ::ae::gfx_low::BufferResourceSpecInfo()
                .SetSize(sphereIndirectRegion.Size())
                .SetUsageBitSet(
                    ::ae::gfx_low::BufferResourceUsageBitSet()
                        .On(::ae::gfx_low::BufferResourceUsage::IndirectBuffer)
                        .On(::ae::gfx_low::BufferResourceUsage::CopyDst));
        const auto sphereCopySrcSpecInfo =
            ::ae::gfx_low::BufferResourceSpecInfo(sphereSpecInfo)
                .SetUsageBitSet(::ae::gfx_low::BufferResourceUsageBitSet().On(
                    ::ae::gfx_low::BufferResourceUsage::CopySrc));
        sphereIndirectMemory.Reset(
            &gfxKit.Device(),
            ::ae::gfx_low::ResourceMemoryAllocInfo()
                .SetKind(::ae::gfx_low::ResourceMemoryKind::DeviceLocal)
                .SetParams(gfxKit.Device().CalcResourceMemoryRequirements(
                    sphereSpecInfo)));
        sphereCopySrcIndirectMemory.Reset(
            &gfxKit.Device(),
            ::ae::gfx_low::ResourceMemoryAllocInfo()
                .SetKind(::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
                .SetParams(gfxKit.Device().CalcResourceMemoryRequirements(
                    sphereSpecInfo)));
        sphereIndirectBuffer.reset(new ::ae::gfx_low::BufferResource(
            ::ae::gfx_low::BufferResourceCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetSpecInfo(sphereSpecInfo)
                .SetDataAddress(*sphereIndirectMemory)));
        sphereCopySrcIndirectBuffer.reset(new ::ae::gfx_low::BufferResource(
            ::ae::gfx_low::BufferResourceCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetSpecInfo(sphereCopySrcSpecInfo)
                .SetDataAddress(*sphereCopySrcIndirectMemory)));
        sphereIndirectView.reset(new ::ae::gfx_low::IndirectBufferView(
            ::ae::gfx_low::IndirectBufferViewCreateInfo()
                .SetDevice(&gfxKit.Device())
                .SetResource(sphereIndirectBuffer.get())
                .SetRegion(sphereIndirectRegion)));
    }
    auto initializeCubeCopySrcIndirectBuffer = [&gfxKit,
                                                   &geometryCube,
                                                   &cubeCopySrcIndirectMemory,
                                                   &cubeIndirectRegion](int mask) {
        auto* commands =
            reinterpret_cast<::ae::gfx_low::DrawIndirectNormalCommand*>(
                gfxKit.Device().MapResourceMemory(
                    *cubeCopySrcIndirectMemory,
                    cubeIndirectRegion));
        const auto baseCommand = ::ae::gfx_low::DrawIndirectNormalCommand()
                                     .SetVertexCount(geometryCube.VertexCount())
                                     .SetInstanceCount(1);
        commands[0] = baseCommand;
        commands[0].SetInstanceCount((mask & (1 << 0)) ? 1 : 0);
        commands[1] = baseCommand;
        commands[1].SetInstanceOffset(1);
        commands[1].SetInstanceCount((mask & (1 << 1)) ? 1 : 0);
        commands[2] = baseCommand;
        commands[2].SetInstanceOffset(2);
        commands[2].SetInstanceCount((mask & (1 << 2)) ? 1 : 0);
        gfxKit.Device().UnmapResourceMemory(*cubeCopySrcIndirectMemory);
    };
    auto initializeSphereCopySrcIndirectBuffer =
        [&gfxKit,
            &geometrySphere,
            &sphereCopySrcIndirectMemory,
            &sphereIndirectRegion](int mask) {
            auto* commands =
                reinterpret_cast<::ae::gfx_low::DrawIndirectIndexedCommand*>(
                    gfxKit.Device().MapResourceMemory(
                        *sphereCopySrcIndirectMemory,
                        sphereIndirectRegion));
            const auto baseCommand =
                ::ae::gfx_low::DrawIndirectIndexedCommand()
                    .SetVertexCount(geometrySphere.getIndexCount())
                    .SetInstanceCount(1);
            commands[0] = baseCommand;
            commands[0].SetInstanceCount((mask & (1 << 0)) ? 1 : 0);
            commands[1] = baseCommand;
            commands[1].SetInstanceOffset(1);
            commands[1].SetInstanceCount((mask & (1 << 1)) ? 1 : 0);
            commands[2] = baseCommand;
            commands[2].SetInstanceOffset(2);
            commands[2].SetInstanceCount((mask & (1 << 2)) ? 1 : 0);
            gfxKit.Device().UnmapResourceMemory(*sphereCopySrcIndirectMemory);
        };

    // コピー元となるバッファの作成
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::UniqueResourceMemory>
        cubeCopySrcMemories(gfxKit.SwapchainImageCount());
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::UniqueResourceMemory>
        sphereCopySrcMemories(gfxKit.SwapchainImageCount());
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::BufferResource>
        cubeCopySrcBuffers(gfxKit.SwapchainImageCount());
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::BufferResource>
        sphereCopySrcBuffers(gfxKit.SwapchainImageCount());
    {
        const auto specInfo =
            ::ae::gfx_low::BufferResourceSpecInfo()
                .SetSize(sizeof(fUniformDataType))
                .SetUsageBitSet(
                    ::ae::gfx_low::BufferResourceUsageBitSet()
                        .On(::ae::gfx_low::BufferResourceUsage::UniformBuffer)
                        .On(::ae::gfx_low::BufferResourceUsage::CopySrc));
        for (int i = 0; i < gfxKit.SwapchainImageCount(); ++i) {
            cubeCopySrcMemories.Add(
                &gfxKit.Device(),
                ::ae::gfx_low::ResourceMemoryAllocInfo()
                    .SetKind(::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
                    .SetParams(gfxKit.Device().CalcResourceMemoryRequirements(
                        specInfo)));
            sphereCopySrcMemories.Add(
                &gfxKit.Device(),
                ::ae::gfx_low::ResourceMemoryAllocInfo()
                    .SetKind(::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
                    .SetParams(gfxKit.Device().CalcResourceMemoryRequirements(
                        specInfo)));
            cubeCopySrcBuffers.Add(
                ::ae::gfx_low::BufferResourceCreateInfo()
                    .SetDevice(&gfxKit.Device())
                    .SetSpecInfo(specInfo)
                    .SetDataAddress(*cubeCopySrcMemories[i]));
            sphereCopySrcBuffers.Add(
                ::ae::gfx_low::BufferResourceCreateInfo()
                    .SetDevice(&gfxKit.Device())
                    .SetSpecInfo(specInfo)
                    .SetDataAddress(*sphereCopySrcMemories[i]));
        }
    }

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
                mainUniformBufferBindingInfos);
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
    ::ae::gfx_low::DescriptorSet cubeDescriptorSet(
        ::ae::gfx_low::DescriptorSetCreateInfo()
            .SetDevice(&gfxKit.Device())
            .SetSpecInfo(mainDescriptorSetSpecInfo));
    ::ae::gfx_low::DescriptorSet sphereDescriptorSet(
        ::ae::gfx_low::DescriptorSetCreateInfo()
            .SetDevice(&gfxKit.Device())
            .SetSpecInfo(mainDescriptorSetSpecInfo));
    ::ae::gfx_low::DescriptorSet copyDescriptorSet(
        ::ae::gfx_low::DescriptorSetCreateInfo()
            .SetDevice(&gfxKit.Device())
            .SetSpecInfo(copyDescriptorSetSpecInfo));
    {
        // UniformBuffer
        const ::ae::gfx_low::UniformBufferView* localUniformBufferViews[] = {
            &cubeUniformBuffer.View(0)
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

        // 更新
        cubeDescriptorSet.Update(
            ::ae::gfx_low::DescriptorSetUpdateInfo()
                .SetUniformBufferInfos(
                    AE_BASE_ARRAY_LENGTH(uniformBufferDescs),
                    uniformBufferDescs));
    }
    {
        // UniformBuffer
        const ::ae::gfx_low::UniformBufferView* localUniformBufferViews[] = {
            &sphereUniformBuffer.View(0)
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

        // 更新
        sphereDescriptorSet.Update(
            ::ae::gfx_low::DescriptorSetUpdateInfo().SetUniformBufferInfos(
                AE_BASE_ARRAY_LENGTH(uniformBufferDescs),
                uniformBufferDescs));
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
                        .SetResource(&shapeVertShader.Resource())
                        .SetEntryPointNamePtr("main"))
                .SetShaderInfo(
                    ::ae::gfx_low::RenderPipelineShaderStage::Fragment,
                    ::ae::gfx_low::PipelineShaderInfo()
                        .SetResource(&shapeFragShader.Resource())
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
    ::ae::gfx_low::CommandBuffer secondaryCommandBuffer(
        ::ae::gfx_low::CommandBufferCreateInfo()
            .SetDevice(&gfxKit.Device())
            .SetQueue(&gfxKit.Queue())
            .SetLevel(::ae::gfx_low::CommandBufferLevel::Secondary)
            .SetFeatures(::ae::gfx_low::CommandBufferFeatureBitSet().Set(
                ::ae::gfx_low::CommandBufferFeature::Render,
                true)));

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
                .SetKind(::ae::gfx_low::ResourceMemoryKind::DeviceLocal)
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
                    .SetResource(colorBufferImage.get())));
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
    int instanceMask = 0;
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
                ::ae::base::Angle(::ae::base::Degree(10.0f)),
                float(display.MainScreen().Width()) /
                    display.MainScreen().Height(), // aspect
                0.1f, // near
                100.0f // far
            );
            auto view = ::ae::base::Matrix44::LookAt(
                ::ae::base::Vector3(0.0f, 18.0f, 30.0f), // eyePos
                ::ae::base::Vector3::Zero(), // targetPos
                ::ae::base::Vector3::UnitY() // upVec
            );
            auto model =
                ::ae::base::Quaternion(
                    ::ae::base::Vector3::UnitY(),
                    ::ae::base::Degree(3.0f * frameCount))
                    .ToRotateMatrix()
                    .ToMatrix44();
            fUniformDataType baseData;
            baseData.projMtx = proj;
            baseData.viewMtx = view;
            baseData.invViewMtx = view.Invert();
            baseData.instanceTrans = ::ae::base::Vector4(4.0f, 0.0f, 0.0f, 0.0f);

            // キューブ
            {
                fUniformDataType data = baseData;
                data.modelMtx =
                    ::ae::base::Matrix44::Translate(
                        ::ae::base::Vector3(-4.0f, 2.0f, 0.0f)) *
                    model;

                {
                    const auto region =
                        ::ae::gfx_low::ResourceMemoryRegion().SetSize(
                            sizeof(fUniformDataType));
                    auto& targetCopySrcMemory =
                        cubeCopySrcMemories[bufferIndex];
                    void* mappedMemory = gfxKit.Device().MapResourceMemory(
                        *targetCopySrcMemory,
                        region);
                    std::memcpy(mappedMemory, &data, region.Size());
                    gfxKit.Device().UnmapResourceMemory(*targetCopySrcMemory);
                }
            }

            // 球
            {
                fUniformDataType data = baseData;
                data.modelMtx = ::ae::base::Matrix44::Translate(
                                    ::ae::base::Vector3(-4.0f, -2.0f, 0.0f)) *
                                model;

                {
                    const auto region =
                        ::ae::gfx_low::ResourceMemoryRegion().SetSize(
                            sizeof(fUniformDataType));
                    auto& targetCopySrcMemory =
                        sphereCopySrcMemories[bufferIndex];
                    void* mappedMemory = gfxKit.Device().MapResourceMemory(
                        *targetCopySrcMemory,
                        region);
                    std::memcpy(mappedMemory, &data, region.Size());
                    gfxKit.Device().UnmapResourceMemory(*targetCopySrcMemory);
                }
            }
        }

        // コマンドバッファ作成
        auto& cmd = gfxKit.CurrentCommandBuffer();
        cmd.BeginRecord();
        {
            // Viewport
            const ::ae::gfx_low::ViewportSetting mainViewportSettings[] = {
                ::ae::gfx_low::ViewportSetting().SetRect(::ae::base::Aabb2(
                    ::ae::base::Vector2::Zero(),
                    display.MainScreen().Extent().ToExtent2())),
            };
            AE_BASE_ARRAY_LENGTH_CHECK(mainViewportSettings, renderTargetCount);

            // Scissor
            const ::ae::gfx_low::ScissorSetting mainScissorSettings[] = {
                ::ae::gfx_low::ScissorSetting().SetRect(::ae::base::Aabb2i(
                    ::ae::base::Vector2i::Zero(),
                    display.MainScreen().Extent())),
            };
            AE_BASE_ARRAY_LENGTH_CHECK(mainScissorSettings, renderTargetCount);

            // インダイレクトバッファを一定周期で更新
            if ((frameCount % 40) == 0) {
                instanceMask = (instanceMask + 1) % 8;
                initializeCubeCopySrcIndirectBuffer(instanceMask);
                initializeSphereCopySrcIndirectBuffer(instanceMask);
                cmd.CmdCopyBuffer(
                    ::ae::gfx_low::CopyBufferInfo()
                        .SetSrcBufferResource(cubeCopySrcIndirectBuffer.get())
                        .SetDstBufferResource(cubeIndirectBuffer.get())
                        .SetSize(cubeIndirectRegion.Size()));
                cmd.CmdCopyBuffer(
                    ::ae::gfx_low::CopyBufferInfo()
                        .SetSrcBufferResource(sphereCopySrcIndirectBuffer.get())
                        .SetDstBufferResource(sphereIndirectBuffer.get())
                        .SetSize(sphereIndirectRegion.Size()));
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

                // コマンドを保存
                {
                    // 保存開始
                    auto& subCmd = secondaryCommandBuffer;
                    subCmd.BeginRecord(
                        ::ae::gfx_low::CommandBufferBeginRecordInfo()
                            .SetInheritRenderPassPtr(mainRenderPass.get())
                            .SetInheritViewportSettingsPtr(mainViewportSettings)
                            .SetInheritScissorSettingsPtr(mainScissorSettings));

                    // Pipeline
                    subCmd.CmdSetRenderPipeline(*mainPipeline);

                    // キューブ
                    subCmd.CmdSetDescriptorSet(cubeDescriptorSet);
                    subCmd.CmdSetVertexBuffer(0, cubeVertexBuffer.View());
                    subCmd.CmdDrawIndirect(
                        ::ae::gfx_low::DrawIndirectCallInfo()
                            .SetIndirectBufferView(cubeIndirectView.get())
                            .SetCommandCount(cubeInstanceCount));

                    // 球
                    subCmd.CmdSetDescriptorSet(sphereDescriptorSet);
                    subCmd.CmdSetVertexBuffer(0, sphereVertexBuffer.View());
                    subCmd.CmdSetIndexBuffer(sphereIndexBuffer.View());
                    subCmd.CmdDrawIndirect(
                        ::ae::gfx_low::DrawIndirectCallInfo()
                            .SetUseIndexBuffer(true)
                            .SetIndirectBufferView(sphereIndirectView.get())
                            .SetCommandCount(sphereInstanceCount));

                    // 保存終了
                    subCmd.EndRecord();
                }
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

            // ユニフォームバッファをバッファコピーで更新
            cmd.CmdCopyBuffer(
                ::ae::gfx_low::CopyBufferInfo()
                    .SetSrcBufferResource(&cubeCopySrcBuffers[bufferIndex])
                    .SetDstBufferResource(&cubeUniformBuffer.BufferResource(0))
                    .SetSize(sizeof(fUniformDataType)));
            cmd.CmdCopyBuffer(
                ::ae::gfx_low::CopyBufferInfo()
                    .SetSrcBufferResource(&sphereCopySrcBuffers[bufferIndex])
                    .SetDstBufferResource(&sphereUniformBuffer.BufferResource(0))
                    .SetSize(sizeof(fUniformDataType)));

            // メイン描画
            {
                // 開始
                cmd.CmdBeginRenderPass(
                    ::ae::gfx_low::RenderPassBeginInfo()
                        .SetRenderPass(mainRenderPass.get())
                        .SetUseSecondaryCommandBuffers(true));

                // Viewport
                cmd.CmdSetViewports(renderTargetCount, mainViewportSettings);

                // Scissor
                cmd.CmdSetScissors(renderTargetCount, mainScissorSettings);

                // コマンド実行
                cmd.CmdCall(secondaryCommandBuffer);

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
                cmd.CmdDrawIndirect(
                    ::ae::gfx_low::DrawIndirectCallInfo()
                        .SetIndirectBufferView(cubeIndirectView.get())
                        .SetCommandCount(cubeInstanceCount));

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
