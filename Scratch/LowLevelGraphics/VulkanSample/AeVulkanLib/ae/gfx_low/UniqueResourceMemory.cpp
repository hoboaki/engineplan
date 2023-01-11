// 文字コード：UTF-8
#include <ae/gfx_low/UniqueResourceMemory.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/Device.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
void UniqueResourceMemory::Reset()
{
    if (memory_.IsValid()) {
        device_->FreeResourceMemory(memory_);
    }
    device_.Reset();
    memory_ = ResourceMemory();
}

//------------------------------------------------------------------------------
void UniqueResourceMemory::Reset(
    Device* device,
    const ResourceMemoryAllocInfo& allocInfo)
{
    Reset();
    device_.Reset(&base::PtrToRef(device));
    memory_ = device_->AllocResourceMemory(allocInfo);
}

//------------------------------------------------------------------------------
void UniqueResourceMemory::Reset(Device* device, const ResourceMemory& memory)
{
    Reset();
    device_.Reset(&base::PtrToRef(device));
    memory_ = memory;
}

//------------------------------------------------------------------------------
UniqueResourceMemory::~UniqueResourceMemory()
{
    Reset();
}

} // namespace ae::gfx_low
// EOF
