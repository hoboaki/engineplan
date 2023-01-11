// 文字コード：UTF-8
#include <ae/gfx_low/Event.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/EventCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
Event::Event(const EventCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, nativeObject_()
{
    const auto semaphoreCreateInfo = ::vk::SemaphoreCreateInfo();
    const auto result = device_.NativeObject_().createSemaphore(
        &semaphoreCreateInfo,
        nullptr,
        &nativeObject_);
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
}

//------------------------------------------------------------------------------
Event::~Event()
{
    device_.NativeObject_().destroySemaphore(nativeObject_, nullptr);
}

} // namespace ae::gfx_low
// EOF
