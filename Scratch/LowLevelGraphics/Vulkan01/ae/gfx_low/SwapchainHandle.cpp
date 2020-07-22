// 文字コード：UTF-8
#include <ae/gfx_low/SwapchainHandle.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/Swapchain.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
SwapchainHandle::SwapchainHandle(Swapchain* entity)
: entity_(&base::PtrToRef(entity))
, entityMaster_(&entity_->swapchainMaster())
, entityUniqueId_(entity_->InternalUniqueId()) {}

//------------------------------------------------------------------------------
bool SwapchainHandle::IsValid() const {
    return entity_.isValid() &&
           &entity_->swapchainMaster() == entityMaster_.get() &&
           entity_->InternalUniqueId() == entityUniqueId_;
}

//------------------------------------------------------------------------------
Swapchain& SwapchainHandle::operator->() const
{
    AE_BASE_ASSERT(IsValid());
    return entity_.ref();
}

}  // namespace gfx_low
}  // namespace ae
// EOF
