// 文字コード：UTF-8
#include <ae/gfx_low/CommandBuffer.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/CommandBufferCreateInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/EventCreateInfo.hpp>
#include <ae/gfx_low/Queue.hpp>
#include <ae/gfx_low/RenderPassBeginInfo.hpp>
#include <ae/gfx_low/RenderPassSpecInfo.hpp>
#include <ae/gfx_low/RenderTargetSetting.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
CommandBuffer::CommandBuffer(const CommandBufferCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, queuePtr_(createInfo.Queue())
, level_(createInfo.Level())
, features_(createInfo.Features())
, commandBuffer_()
, completeEvent_(EventCreateInfo().SetDevice(&device_)) {
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

//------------------------------------------------------------------------------
void CommandBuffer::BeginRecord() {
    Reset();
    AE_BASE_ASSERT(state_ == CommandBufferState::Initial);
    const auto beginInfo =
        ::vk::CommandBufferBeginInfo().setPInheritanceInfo(nullptr);
    const auto result = commandBuffer_.begin(&beginInfo);
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    state_ = CommandBufferState::Recording;
}

//------------------------------------------------------------------------------
void CommandBuffer::EndRecord() {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    const ::vk::Result result = commandBuffer_.end();
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    state_ = CommandBufferState::Recorded;
}

//------------------------------------------------------------------------------
void CommandBuffer::Reset() {
    switch (state_) {
    case CommandBufferState::Initial:
        // 何もする必要がない
        break;

    case CommandBufferState::Recorded: {
        const auto result =
            commandBuffer_.reset(::vk::CommandBufferResetFlags(0));
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
        state_ = CommandBufferState::Initial;
        break;
    }
    default:
        AE_BASE_ASSERT_NOT_REACHED_MSGFMT(
            "[CommandBuffer::Reset] Invalid state(%d).", state_);
        break;
    }
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdBeginRenderPass(const RenderPassBeginInfo& info) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.isAllOff());

    activePass_.set(int(CommandBufferFeature::Render), true);

    std::array<::vk::ClearValue, 8> clearValues;
    for (int i = 0; i < info.RenderPassSpecInfo().RenderTargetCount(); ++i) {
        const auto color = info.RenderTargetSettings()[i].ClearColor();
        ::vk::ClearColorValue val;
        val.float32 =
            std::array<float, 4>({color.r, color.g, color.b, color.a});
        clearValues[i].setColor(val);
    }

    auto const passInfo =
        ::vk::RenderPassBeginInfo()
            .setRenderPass(device_.InternalAcquireRenderPass(info))
            .setFramebuffer(device_.InternalAcquireFramebuffer(info))
            .setRenderArea(
                ::vk::Rect2D(::vk::Offset2D(info.RenderArea().begin().x,
                                 info.RenderArea().begin().y),
                    ::vk::Extent2D(uint32_t(info.RenderArea().width()),
                        uint32_t(info.RenderArea().height()))))
            .setClearValueCount(1)
            .setPClearValues(&clearValues[0]);

    commandBuffer_.beginRenderPass(passInfo, vk::SubpassContents::eInline);
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdEndRenderPass() {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.get(int(CommandBufferFeature::Render)));

    commandBuffer_.endRenderPass();
    activePass_.set(int(CommandBufferFeature::Render), false);
}

}  // namespace gfx_low
}  // namespace ae
// EOF
