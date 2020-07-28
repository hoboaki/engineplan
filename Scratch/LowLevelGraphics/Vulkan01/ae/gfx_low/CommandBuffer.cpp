// 文字コード：UTF-8
#include <ae/gfx_low/CommandBuffer.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/CommandBufferCreateInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/EnumUtil.hpp>
#include <ae/gfx_low/EventCreateInfo.hpp>
#include <ae/gfx_low/Queue.hpp>
#include <ae/gfx_low/RenderPassBeginInfo.hpp>
#include <ae/gfx_low/RenderPassSpecInfo.hpp>
#include <ae/gfx_low/RenderTargetImageView.hpp>
#include <ae/gfx_low/RenderTargetSetting.hpp>
#include <ae/gfx_low/System.hpp>

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
, completeEvent_(EventCreateInfo().SetDevice(&device_))
, renderPassProperties_(createInfo.RenderPassCountMax(),
      device_.System().InternalObjectAllocator()) {
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
    Reset();
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
        return;

    case CommandBufferState::Recorded: {
        // リセット処理が必要なので続行
        break;
    }
    default:
        AE_BASE_ASSERT_NOT_REACHED_MSGFMT(
            "[CommandBuffer::Reset] Invalid state(%d).", state_);
        return;
    }

    // コマンドバッファをリセット
    const auto result = commandBuffer_.reset(::vk::CommandBufferResetFlags(0));
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    state_ = CommandBufferState::Initial;

    // コマンドバッファで作った情報をリセット
    for (int i = renderPassProperties_.count() - 1; 0 <= i; --i) {
        auto& prop = renderPassProperties_[i];
        device_.InternalInstance().destroyFramebuffer(
            prop.framebuffer, nullptr);
        device_.InternalInstance().destroyRenderPass(prop.renderPass, nullptr);
    }
    renderPassProperties_.clear();
}

//------------------------------------------------------------------------------
void CommandBuffer::CmdBeginRenderPass(const RenderPassBeginInfo& info) {
    AE_BASE_ASSERT(state_ == CommandBufferState::Recording);
    AE_BASE_ASSERT(activePass_.isAllOff());

    activePass_.set(int(CommandBufferFeature::Render), true);

    RenderPassProperty prop;
    {
        // RenderPass 作成
        std::array<::vk::AttachmentDescription,
            Device::InternalSupportedAttachmentCountMax>
            attachments;
        for (int i = 0; i < info.RenderPassSpecInfo().RenderTargetCount();
             ++i) {
            const auto& renderTargetSpec =
                info.RenderPassSpecInfo().RenderTargetSpecInfos()[i];
            const auto& renderTargetSetting = info.RenderTargetSettings()[i];
            auto& attachment = attachments[i];

            // @todo 普通の Format での指定
            AE_BASE_ASSERT(renderTargetSpec.InternalNativeFormat() !=
                           ::vk::Format::eUndefined);
            attachment.setFormat(renderTargetSpec.InternalNativeFormat());

            // その他の設定
            attachment.setSamples(::vk::SampleCountFlagBits::e1)
                .setLoadOp(EnumUtil::ToNative(renderTargetSetting.LoadOp()))
                .setStoreOp(EnumUtil::ToNative(renderTargetSetting.StoreOp()))
                .setStencilLoadOp(vk::AttachmentLoadOp::eDontCare)
                .setStencilStoreOp(vk::AttachmentStoreOp::eDontCare)
                .setInitialLayout(EnumUtil::ToImageLayoutForColorAttachment(
                    renderTargetSetting.InitialImageResourceState()))
                .setFinalLayout(EnumUtil::ToImageLayoutForColorAttachment(
                    renderTargetSetting.FinalImageResourceState()));
        }

        auto const colorReference =
            vk::AttachmentReference().setAttachment(0).setLayout(
                vk::ImageLayout::eColorAttachmentOptimal);

        auto const subpass =
            vk::SubpassDescription()
                .setPipelineBindPoint(vk::PipelineBindPoint::eGraphics)
                .setInputAttachmentCount(0)
                .setPInputAttachments(nullptr)
                .setColorAttachmentCount(1)
                .setPColorAttachments(&colorReference)
                .setPResolveAttachments(nullptr)
                .setPDepthStencilAttachment(nullptr)
                .setPreserveAttachmentCount(0)
                .setPPreserveAttachments(nullptr);

        vk::PipelineStageFlags stages =
            vk::PipelineStageFlagBits::eEarlyFragmentTests |
            vk::PipelineStageFlagBits::eLateFragmentTests;
        vk::SubpassDependency const dependencies[1] = {
            vk::SubpassDependency()  // Image layout transition
                .setSrcSubpass(VK_SUBPASS_EXTERNAL)
                .setDstSubpass(0)
                .setSrcStageMask(
                    vk::PipelineStageFlagBits::eColorAttachmentOutput)
                .setDstStageMask(
                    vk::PipelineStageFlagBits::eColorAttachmentOutput)
                .setSrcAccessMask(vk::AccessFlagBits())
                .setDstAccessMask(vk::AccessFlagBits::eColorAttachmentWrite |
                                  vk::AccessFlagBits::eColorAttachmentRead)
                .setDependencyFlags(vk::DependencyFlags()),
        };

        auto const renderPassCreateInfo = vk::RenderPassCreateInfo()
                                              .setAttachmentCount(1)
                                              .setPAttachments(&attachments[0])
                                              .setSubpassCount(1)
                                              .setPSubpasses(&subpass)
                                              .setDependencyCount(1)
                                              .setPDependencies(dependencies);
        {
            const auto result = device_.InternalInstance().createRenderPass(
                &renderPassCreateInfo, nullptr, &prop.renderPass);
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
        }
    }
    {
        // Framebuffer 生成
        std::array<::vk::ImageView, Device::InternalSupportedAttachmentCountMax>
            imageViews;
        for (int i = 0; i < info.RenderPassSpecInfo().RenderTargetCount();
             ++i) {
            imageViews[i] = info.RenderTargetSettings()[i]
                                .RenderTargetImageView()
                                ->InternalInstance();
        }

        auto const createInfo =
            vk::FramebufferCreateInfo()
                .setRenderPass(prop.renderPass)
                .setAttachmentCount(1)
                .setPAttachments(&imageViews[0])
                .setWidth(uint32_t(info.RenderArea().width()))
                .setHeight(uint32_t(info.RenderArea().height()))
                .setLayers(1);
        ::vk::Framebuffer framebuffer;
        {
            const auto result = device_.InternalInstance().createFramebuffer(
                &createInfo, nullptr, &framebuffer);
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
        }
    }
    renderPassProperties_.add(prop);

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
            .setRenderPass(prop.renderPass)
            .setFramebuffer(prop.framebuffer)
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
