// 文字コード：UTF-8
#include <aesk/UniformBuffer.hpp>

// includes
#include <ae/gfx_low/BufferResourceCreateInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/ResourceMemoryAllocInfo.hpp>
#include <ae/gfx_low/ResourceMemoryRequirements.hpp>
#include <ae/gfx_low/UniformBufferViewCreateinfo.hpp>

//------------------------------------------------------------------------------
namespace aesk {

//------------------------------------------------------------------------------
UniformBuffer::UniformBuffer(
    ::ae::gfx_low::Device* device,
    const size_t sizePerData,
    const int dataCount,
    const bool isDeviceLocal)
: device_(::ae::base::PtrToRef(device))
, sizePerData_(sizePerData)
, dataCount_(dataCount)
, memories_(dataCount)
, bufferResources_(dataCount)
, views_(dataCount) {
    const auto specInfo =
        ::ae::gfx_low::BufferResourceSpecInfo()
            .SetSize(sizePerData_)
            .SetUsageBitSet(
                ::ae::gfx_low::BufferResourceUsageBitSet()
                    .On(::ae::gfx_low::BufferResourceUsage::UniformBuffer)
                    .Set(
                        ::ae::gfx_low::BufferResourceUsage::CopyDst,
                        isDeviceLocal));
    const auto region =
        ::ae::gfx_low::ResourceMemoryRegion().SetSize(sizePerData_);
    for (int i = 0; i < dataCount_; ++i) {
        memories_.Add(
            device,
            ::ae::gfx_low::ResourceMemoryAllocInfo()
                .SetKind(
                    isDeviceLocal
                        ? ::ae::gfx_low::ResourceMemoryKind::DeviceLocal
                        : ::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
                .SetParams(device_.CalcResourceMemoryRequirements(specInfo)));
        bufferResources_.Add(::ae::gfx_low::BufferResourceCreateInfo()
                                 .SetDevice(device)
                                 .SetSpecInfo(specInfo)
                                 .SetDataAddress(*memories_[i]));
        views_.Add(::ae::gfx_low::UniformBufferViewCreateInfo()
                       .SetDevice(device)
                       .SetResource(&bufferResources_[i])
                       .SetRegion(region));
    }
}

//------------------------------------------------------------------------------
UniformBuffer::~UniformBuffer() {
}

//------------------------------------------------------------------------------
void UniformBuffer::StoreToResourceMemory(
    const int index,
    const ::ae::base::MemBlock& block) const {
    AE_BASE_ASSERT_EQUALS(sizePerData_, block.Size());
    AE_BASE_ASSERT_MIN_TERM(index, 0, dataCount_);

    const auto region =
        ::ae::gfx_low::ResourceMemoryRegion().SetSize(sizePerData_);
    void* mappedMemory = device_.MapResourceMemory(*memories_[index], region);
    std::memcpy(mappedMemory, block.Head(), block.Size());
    device_.UnmapResourceMemory(*memories_[index]);
}

} // namespace aesk
// EOF
