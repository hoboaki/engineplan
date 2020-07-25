// 文字コード：UTF-8
#include <ae/gfx_low/Event.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/EventCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
Event::Event(const EventCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, semaphore_() {
    const auto semaphoreCreateInfo = ::vk::SemaphoreCreateInfo();
    const auto result = device_.InternalInstance().createSemaphore(
        &semaphoreCreateInfo, nullptr, &semaphore_);
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
}

//------------------------------------------------------------------------------
Event::~Event() {
    device_.InternalInstance().destroySemaphore(semaphore_, nullptr);
}

}  // namespace gfx_low
}  // namespace ae
// EOF
