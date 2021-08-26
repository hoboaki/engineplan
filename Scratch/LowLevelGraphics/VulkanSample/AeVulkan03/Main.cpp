// 文字コード：UTF-8
#include <ae/base/EntryPoint.hpp>

// includes
#include <ae/base/AppEvent.hpp>
#include <ae/base/Application.hpp>
#include <ae/base/ArrayLength.hpp>
#include <ae/base/Console.hpp>
#include <ae/base/Extent2.hpp>
#include <ae/base/Extent2i.hpp>
#include <ae/base/Quaternion.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/SdkHeader.hpp>
#include <ae/gfx_low/BufferResource.hpp>
#include <ae/gfx_low/BufferResourceCreateInfo.hpp>
#include <ae/gfx_low/CommandBuffer.hpp>
#include <ae/gfx_low/CommandBufferCreateInfo.hpp>
#include <ae/gfx_low/DescriptorSet.hpp>
#include <ae/gfx_low/DescriptorSetCreateInfo.hpp>
#include <ae/gfx_low/DescriptorSetUpdateInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/DeviceCreateInfo.hpp>
#include <ae/gfx_low/DrawCallInfo.hpp>
#include <ae/gfx_low/Fence.hpp>
#include <ae/gfx_low/FenceCreateInfo.hpp>
#include <ae/gfx_low/Queue.hpp>
#include <ae/gfx_low/QueueCreateInfo.hpp>
#include <ae/gfx_low/ResourceMemory.hpp>
#include <ae/gfx_low/ResourceMemoryAllocInfo.hpp>
#include <ae/gfx_low/ResourceMemoryRequirements.hpp>
#include <ae/gfx_low/ShaderBindingInfo.hpp>
#include <ae/gfx_low/ShaderModuleResource.hpp>
#include <ae/gfx_low/ShaderModuleResourceCreateInfo.hpp>
#include <ae/gfx_low/System.hpp>
#include <ae/gfx_low/SystemCreateInfo.hpp>
#include <ae/gfx_low/StorageBufferDescriptorInfo.hpp>
#include <ae/gfx_low/StorageBufferView.hpp>
#include <ae/gfx_low/StorageBufferViewCreateinfo.hpp>
#include <ae/gfx_low/UniqueResourceMemory.hpp>
#include <memory>

//------------------------------------------------------------------------------
namespace {

struct fStorageDataType {
    uint32_t elems[16*16*4*4];
};

const uint32_t fCompShaderCode[] = {
#include "Shader.comp.inc"
};

// clang-format on

} // namespace

//------------------------------------------------------------------------------
int aemain(::ae::base::Application* app) {
    // コンソール出力
    AE_BASE_COUT_LINE_WITH_TIME("Adel runtime start.");


    // グラフィックスシステムインスタンス作成
    ::std::unique_ptr<::ae::gfx_low::System> system(new ::ae::gfx_low::System(
        ::ae::gfx_low::SystemCreateInfo().SetDebugLevel(
            ::ae::gfx_low::SystemDebugLevel::Normal)));

    // Device & Queue 作成
    ::std::unique_ptr<::ae::gfx_low::Device> device;
    {
        // デバッグダンプ
        system->DumpAllPhysicalDeviceInfo();

        // Queue の作成情報を用意
        const int queueCount = 1;
        ::ae::gfx_low::QueueCreateInfo queueCreateInfos[queueCount];
        queueCreateInfos[0] =
            ::ae::gfx_low::QueueCreateInfo()
                .SetKind(::ae::gfx_low::QueueKind::Normal)
                .SetPriority(::ae::gfx_low::QueuePriority::Normal)
                .SetOperationCountMax(32);

        // Device の作成
        device.reset(new ::ae::gfx_low::Device(
            ::ae::gfx_low::DeviceCreateInfo()
                .SetSystem(system.get())
                .SetQueueCreateInfos(queueCount, queueCreateInfos)));

        // 更にデバッグダンプ
        AE_BASE_COUTFMT_LINE("IsDeviceLocalMemoryShared: %d",
            device->IsDeviceLocalMemoryShared() ? 1 : 0);
    }
    auto& queue = device->Queue(0);


    // CommandBuffer の作成
    ::ae::gfx_low::CommandBuffer commandBuffer(
        ::ae::gfx_low::CommandBufferCreateInfo()
        .SetDevice(device.get())
        .SetQueue(&queue));
    

    // Fence の作成
    ::ae::gfx_low::Fence fence(::ae::gfx_low::FenceCreateInfo().SetDevice(device.get()));

    // Shader の作成
    ::ae::gfx_low::UniqueResourceMemory compShaderMemory;
    std::unique_ptr<::ae::gfx_low::ShaderModuleResource> compShader;
    {
        const auto size = sizeof(fCompShaderCode);
        const auto specInfo =
            ::ae::gfx_low::ShaderModuleResourceSpecInfo().SetSize(size);
        compShaderMemory.Reset(device.get(),
            ::ae::gfx_low::ResourceMemoryAllocInfo()
                .SetKind(::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
                .SetParams(device->CalcResourceMemoryRequirements(specInfo)));
        std::memcpy(device->MapResourceMemory(*compShaderMemory,
                        ::ae::gfx_low::ResourceMemoryRegion().SetSize(size)),
            fCompShaderCode, size);
        device->UnmapResourceMemory(*compShaderMemory);
        compShader.reset(new ::ae::gfx_low::ShaderModuleResource(
            ::ae::gfx_low::ShaderModuleResourceCreateInfo()
                .SetDevice(device.get())
                .SetSpecInfo(specInfo)
                .SetDataAddress(*compShaderMemory)));
    }

    // StorageBuffer の作成
    ::ae::gfx_low::UniqueResourceMemory storageBufferMemory;
    std::unique_ptr<::ae::gfx_low::BufferResource> storageBufferResource;
    std::unique_ptr<::ae::gfx_low::StorageBufferView> storageBufferView;
    {
        const auto specInfo =
            ::ae::gfx_low::BufferResourceSpecInfo()
                .SetSize(sizeof(fStorageDataType))
                .SetUsageBitSet(::ae::gfx_low::BufferResourceUsageBitSet().Set(
                    ::ae::gfx_low::BufferResourceUsage::StorageBuffer, true));
        const auto region = ::ae::gfx_low::ResourceMemoryRegion().SetSize(
            sizeof(fStorageDataType));
        storageBufferMemory.Reset(device.get(),
            ::ae::gfx_low::ResourceMemoryAllocInfo()
                .SetKind(::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
                .SetParams(device->CalcResourceMemoryRequirements(specInfo)));
        storageBufferResource.reset(new ::ae::gfx_low::BufferResource(
            ::ae::gfx_low::BufferResourceCreateInfo()
                .SetDevice(device.get())
                .SetSpecInfo(specInfo)
                .SetDataAddress(*storageBufferMemory)));
        storageBufferView.reset(new ::ae::gfx_low::StorageBufferView(
            ::ae::gfx_low::StorageBufferViewCreateInfo()
                .SetDevice(device.get())
                .SetResource(storageBufferResource.get())
                .SetRegion(region)));
    }

    // DescriptorSetSpecInfo の作成
    const ::ae::gfx_low::ShaderBindingInfo storageBufferBindingInfos[] = {
        ::ae::gfx_low::ShaderBindingInfo()
            .SetStages(
                ::ae::gfx_low::ShaderBindingStageBitSet()
                    .Set(::ae::gfx_low::ShaderBindingStage::Compute, true))
            .SetBindingIndex(0)};
    const auto descriptorSetSpecInfo =
        ::ae::gfx_low::DescriptorSetSpecInfo()
            .SetBindingInfos(::ae::gfx_low::DescriptorKind::StorageBuffer,
                AE_BASE_ARRAY_LENGTH(storageBufferBindingInfos),
                storageBufferBindingInfos);

    // DescriptorSet の作成
    ::ae::gfx_low::DescriptorSet descriptorSet(
        ::ae::gfx_low::DescriptorSetCreateInfo()
            .SetDevice(device.get())
            .SetSpecInfo(descriptorSetSpecInfo));
    {
        // StorageBuffer
        const ::ae::gfx_low::StorageBufferView* localStorageBufferViews[] = {
            storageBufferView.get()};
        const ::ae::gfx_low::StorageBufferDescriptorInfo storageBufferDescs[] =
            {
                ::ae::gfx_low::StorageBufferDescriptorInfo()
                    .SetRegion(::ae::gfx_low::ShaderBindingRegion()
                                   .SetBindingIndex(0)
                                   .SetElemCount(AE_BASE_ARRAY_LENGTH(
                                       localStorageBufferViews)))
                    .SetViews(localStorageBufferViews),
            };

        // 更新
        descriptorSet.Update(
            ::ae::gfx_low::DescriptorSetUpdateInfo().SetStorageBufferInfos(
                AE_BASE_ARRAY_LENGTH(storageBufferDescs), storageBufferDescs));
    }

    // コマンドの実行＆完了待ち
    {
        // コマンドバッファ作成
        auto& cmd = commandBuffer;
        cmd.BeginRecord();
        {
        }
        cmd.EndRecord();


        // コマンド実行
        queue.PushCommandExecute(&cmd);


        // GPU送信
        queue.Submit(&fence);

        // 完了待ち
        fence.Wait();
    }
    
    // 処理結果を出力
    // ...

    return 0;
}
// EOF
