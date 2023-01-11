// 文字コード：UTF-8
#include <ae/gfx_low/SwapchainHandle.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/Swapchain.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
SwapchainHandle::SwapchainHandle(Swapchain* entity)
: entity_(&base::PtrToRef(entity))
, entityMaster_(&entity_->SwapchainMaster())
, entityUniqueId_(entity_->UniqueId_())
{
}

//------------------------------------------------------------------------------
bool SwapchainHandle::IsValid() const
{
    return entity_.IsValid() &&
           &entity_->SwapchainMaster() == entityMaster_.Get() &&
           entity_->UniqueId_() == entityUniqueId_;
}

//------------------------------------------------------------------------------
Swapchain& SwapchainHandle::Ref() const
{
    AE_BASE_ASSERT(IsValid());
    return entity_.Ref();
}

} // namespace ae::gfx_low
// EOF
