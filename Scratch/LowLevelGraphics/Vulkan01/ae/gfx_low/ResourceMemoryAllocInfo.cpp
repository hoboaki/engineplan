// 文字コード：UTF-8
#include <ae/gfx_low/ResourceMemoryAllocInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
ResourceMemoryAllocInfo& ResourceMemoryAllocInfo::SetKind(
    const ResourceMemoryKind kind) {
    AE_BASE_ASSERT_ENUM(kind, ResourceMemoryKind);
    AE_BASE_ASSERT(kind != ResourceMemoryKind::Invalid);
    kind_ = kind;
    return *this;
}

} // namespace gfx_low
} // namespace ae
// EOF
