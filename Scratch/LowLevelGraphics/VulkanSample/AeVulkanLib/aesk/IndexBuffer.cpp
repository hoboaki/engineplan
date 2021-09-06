// 文字コード：UTF-8
#include <aesk/IndexBuffer.hpp>

// includes
#include <ae/gfx_low/BufferResourceCreateInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/ResourceMemoryAllocInfo.hpp>
#include <ae/gfx_low/ResourceMemoryRequirements.hpp>
#include <ae/gfx_low/IndexBufferViewCreateinfo.hpp>

//------------------------------------------------------------------------------
namespace aesk {

//------------------------------------------------------------------------------
IndexBuffer::IndexBuffer(
    ::ae::gfx_low::Device* device,
    const size_t bufferSize,
    const ::ae::gfx_low::IndexFormat format)
: device_(::ae::base::PtrToRef(device))
, bufferSize_(bufferSize) {
    const auto specInfo =
        ::ae::gfx_low::BufferResourceSpecInfo()
            .SetSize(bufferSize)
            .SetUsageBitSet(::ae::gfx_low::BufferResourceUsageBitSet().Set(
                ::ae::gfx_low::BufferResourceUsage::IndexBuffer,
                true));
    const auto region =
        ::ae::gfx_low::ResourceMemoryRegion().SetSize(bufferSize);
    memory_.Reset(
        &device_,
        ::ae::gfx_low::ResourceMemoryAllocInfo()
            .SetKind(::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
            .SetParams(device_.CalcResourceMemoryRequirements(specInfo)));
    bufferResource_.reset(new ::ae::gfx_low::BufferResource(
        ::ae::gfx_low::BufferResourceCreateInfo()
            .SetDevice(&device_)
            .SetSpecInfo(specInfo)
            .SetDataAddress(*memory_)));
    view_.reset(new ::ae::gfx_low::IndexBufferView(
        ::ae::gfx_low::IndexBufferViewCreateInfo()
            .SetDevice(&device_)
            .SetResource(bufferResource_.get())
            .SetRegion(region)
            .SetFormat(format)));
}

//------------------------------------------------------------------------------
IndexBuffer::~IndexBuffer() {
}

//------------------------------------------------------------------------------
void IndexBuffer::StoreToResourceMemory(
    const ::ae::base::MemBlock& block) const {
    AE_BASE_ASSERT_LESS_EQUALS(block.Size(), bufferSize_);

    const auto region =
        ::ae::gfx_low::ResourceMemoryRegion().SetSize(block.Size());
    void* mappedMemory = device_.MapResourceMemory(*memory_, region);
    std::memcpy(mappedMemory, block.Head(), block.Size());
    device_.UnmapResourceMemory(*memory_);
}

} // namespace aesk
// EOF
