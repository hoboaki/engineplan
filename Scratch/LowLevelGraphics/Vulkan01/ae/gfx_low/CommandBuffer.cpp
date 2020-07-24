// 文字コード：UTF-8
#include <ae/gfx_low/CommandBuffer.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/CommandBufferCreateInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/Queue.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
CommandBuffer::CommandBuffer(const CommandBufferCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, queuePtr_(createInfo.Queue())
, level_(createInfo.Level())
, features_(createInfo.Features())
, commandBuffer_() {
    // 今は Primary のみサポート
    AE_BASE_ASSERT(level_ == CommandBufferLevel::Primary);

    const auto allocateInfo =
        ::vk::CommandBufferAllocateInfo()
            .setCommandPool(queuePtr_->InternalCommandPool())
            .setLevel(::vk::CommandBufferLevel::ePrimary)
            .setCommandBufferCount(1);

    auto result = device_.InternalInstance().allocateCommandBuffers(
        &allocateInfo, &commandBuffer_);
    AE_BASE_ASSERT(result == vk::Result::eSuccess);
}

//------------------------------------------------------------------------------
CommandBuffer::~CommandBuffer() {
    device_.InternalInstance().freeCommandBuffers(
        queuePtr_->InternalCommandPool(), commandBuffer_);
}

}  // namespace gfx_low
}  // namespace ae
// EOF
