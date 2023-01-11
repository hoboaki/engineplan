// 文字コード：UTF-8
#include <ae/gfx_low/BufferResourceCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
::vk::BufferCreateInfo BufferResourceCreateInfo::NativeCreateInfo_() const
{
    return ::vk::BufferCreateInfo()
        .setSize(specInfo_.Size())
        .setUsage(InternalEnumUtil::ToBufferUsageFlags(specInfo_.UsageBitSet()))
        .setSharingMode(vk::SharingMode::eExclusive)
        .setQueueFamilyIndexCount(0)
        .setPQueueFamilyIndices(nullptr);
}

} // namespace ae::gfx_low
// EOF
