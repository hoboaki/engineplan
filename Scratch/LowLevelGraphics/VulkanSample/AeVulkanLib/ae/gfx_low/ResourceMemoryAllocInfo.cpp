// 文字コード：UTF-8
#include <ae/gfx_low/ResourceMemoryAllocInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/ResourceMemoryRequirements.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
ResourceMemoryAllocInfo& ResourceMemoryAllocInfo::SetKind(
    const ResourceMemoryKind kind)
{
    AE_BASE_ASSERT_ENUM(kind, ResourceMemoryKind);
    AE_BASE_ASSERT(kind != ResourceMemoryKind::Invalid);
    kind_ = kind;
    return *this;
}

//------------------------------------------------------------------------------
ResourceMemoryAllocInfo& ResourceMemoryAllocInfo::SetParams(
    const ResourceMemoryRequirements& requirement)
{
    SetUsageBitSet(requirement.UsageBitSet());
    SetSize(requirement.Size());
    SetAlignment(requirement.Alignment());
    return *this;
}

} // namespace ae::gfx_low
// EOF
