// 文字コード：UTF-8
#include <ae/gfx_low/Queue.hpp>

// includes
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/System.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
Queue::Queue(gfx_low::Device* device, const ::vk::Queue& queue, QueueKind kind,
    int operationCountMax, const ::vk::CommandPool& commandPool)
: device_(base::PtrToRef(device))
, queue_(queue)
, kind_(kind)
, operations_(operationCountMax, device_.System().InternalObjectAllocator())
, commandPool_(commandPool) {}

//------------------------------------------------------------------------------
Queue::~Queue() {}

}  // namespace gfx_low
}  // namespace ae
// EOF
