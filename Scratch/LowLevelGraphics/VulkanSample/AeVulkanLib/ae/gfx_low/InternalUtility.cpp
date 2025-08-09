// 文字コード：UTF-8
#include <ae/gfx_low/InternalUtility.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/DepthStencilSetting.hpp>
#include <ae/gfx_low/DepthStencilSpecInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/ImageResource.hpp>
#include <ae/gfx_low/ImageSubresourceLocation.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/RenderPassSpecInfo.hpp>
#include <ae/gfx_low/RenderTargetSetting.hpp>
#include <ae/gfx_low/RenderTargetSpecInfo.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
::vk::ImageSubresourceRange InternalUtility::ToImageSubresourceRange(
    const ImageResource& resource,
    const ImageSubresourceLocation& location,
    const ::vk::ImageAspectFlags& aspectFlagsHint)
{
    const ::vk::ImageAspectFlags aspectFlags =
        aspectFlagsHint
            ? aspectFlagsHint
            : InternalEnumUtil::ToImageAspectFlags(resource.NativeFormat_());
    const uint32_t perLayerImageCount = resource.IsCubeMapImage_() ? 6 : 1;
    return ::vk::ImageSubresourceRange(
        aspectFlags,
        location.MipLevel(), // baseMipLevel
        1, // levelCount
        perLayerImageCount * location.ArrayIndex() +
            location.FaceIndex(), // baseArrayLayer
        1 // layerCount
    );
}

//------------------------------------------------------------------------------
void InternalUtility::CreateRenderPass(
    ::vk::RenderPass* target,
    Device* device,
    const RenderPassSpecInfo& specInfo,
    const RenderTargetSetting* renderTargetSettingsPtr,
    const DepthStencilSetting* depthStencilSettingPtr)
{
    AE_BASE_ASSERT_LESS_EQUALS(specInfo.RenderTargetCount(), Device::SupportedRenderTargetCountMax_);
    const bool hasDepthStencil = depthStencilSettingPtr != nullptr;
    const int attachmentsCount = specInfo.RenderTargetCount() + (hasDepthStencil ? 1 : 0);
    const int depthStencilIdx = hasDepthStencil ? attachmentsCount - 1 : -1;
    {
        // RenderPass 作成
        std::array<::vk::AttachmentDescription, Device::SupportedAttachmentCountMax_> attachments;
        std::array<::vk::AttachmentReference, Device::SupportedAttachmentCountMax_> attachmentRefs;
        if (0 < specInfo.RenderTargetCount()) {
            AE_BASE_ASSERT_POINTER(renderTargetSettingsPtr);
            for (int i = 0; i < specInfo.RenderTargetCount(); ++i) {
                const auto& spec = specInfo.RenderTargetSpecInfos()[i];
                const auto& setting = renderTargetSettingsPtr[i];
                auto& attachment = attachments[i];
                auto& attachmentRef = attachmentRefs[i];

                const auto format =
                    spec.NativeFormat_() != ::vk::Format::eUndefined
                        ? spec.NativeFormat_()
                        : InternalEnumUtil::ToFormat(spec.ImageFormat());

                attachment.setFormat(format)
                    .setSamples(::vk::SampleCountFlagBits::e1)
                    .setLoadOp(
                        InternalEnumUtil::ToAttachmentLoadOp(setting.LoadOp()))
                    .setStoreOp(
                        InternalEnumUtil::ToAttachmentStoreOp(setting.StoreOp()))
                    .setStencilLoadOp(vk::AttachmentLoadOp::eDontCare)
                    .setStencilStoreOp(vk::AttachmentStoreOp::eDontCare)
                    .setInitialLayout(
                        InternalEnumUtil::ToImageLayoutForColorAttachment(
                            setting.InitialImageResourceState()))
                    .setFinalLayout(
                        InternalEnumUtil::ToImageLayoutForColorAttachment(
                            setting.FinalImageResourceState()));
                attachmentRef.setAttachment(i).setLayout(
                    ::vk::ImageLayout::eColorAttachmentOptimal);
            }
        }
        if (depthStencilSettingPtr != nullptr) {
            const auto& spec = base::PtrToRef(specInfo.DepthStencilSpecInfoPtr());
            const auto& setting = base::PtrToRef(depthStencilSettingPtr);
            auto& attachment = attachments[depthStencilIdx];
            auto& attachmentRef = attachmentRefs[depthStencilIdx];
            attachment.setFormat(InternalEnumUtil::ToFormat(spec.ImageFormat()))
                .setSamples(::vk::SampleCountFlagBits::e1)
                .setLoadOp(
                    InternalEnumUtil::ToAttachmentLoadOp(setting.DepthLoadOp()))
                .setStoreOp(InternalEnumUtil::ToAttachmentStoreOp(
                    setting.DepthStoreOp()))
                .setStencilLoadOp(InternalEnumUtil::ToAttachmentLoadOp(
                    setting.StencilLoadOp()))
                .setStencilStoreOp(InternalEnumUtil::ToAttachmentStoreOp(
                    setting.StencilStoreOp()))
                .setInitialLayout(
                    InternalEnumUtil::ToImageLayoutForDepthStencilAttachment(
                        setting.InitialImageResourceState(),
                        spec.ImageFormat()))
                .setFinalLayout(
                    InternalEnumUtil::ToImageLayoutForDepthStencilAttachment(
                        setting.FinalImageResourceState(),
                        spec.ImageFormat()));
            attachmentRef.setAttachment(depthStencilIdx)
                .setLayout(::vk::ImageLayout::eDepthStencilAttachmentOptimal);
        }

        auto const subpass =
            vk::SubpassDescription()
                .setPipelineBindPoint(vk::PipelineBindPoint::eGraphics)
                .setInputAttachmentCount(0)
                .setPInputAttachments(nullptr)
                .setColorAttachmentCount(specInfo.RenderTargetCount())
                .setPColorAttachments(&attachmentRefs[0])
                .setPResolveAttachments(nullptr)
                .setPDepthStencilAttachment(
                    hasDepthStencil ? &attachmentRefs[depthStencilIdx]
                                    : nullptr)
                .setPreserveAttachmentCount(0)
                .setPPreserveAttachments(nullptr);

        std::array<::vk::SubpassDependency, 2> dependencies;
        if (hasDepthStencil) {
            const ::vk::PipelineStageFlags stages =
                ::vk::PipelineStageFlagBits::eEarlyFragmentTests |
                ::vk::PipelineStageFlagBits::eLateFragmentTests;
            dependencies[0] =
                ::vk::SubpassDependency()
                    .setSrcSubpass(VK_SUBPASS_EXTERNAL)
                    .setDstSubpass(0)
                    .setSrcStageMask(stages)
                    .setDstStageMask(stages)
                    .setSrcAccessMask(
                        vk::AccessFlagBits::eDepthStencilAttachmentWrite)
                    .setDstAccessMask(
                        vk::AccessFlagBits::eDepthStencilAttachmentRead |
                        vk::AccessFlagBits::eDepthStencilAttachmentWrite)
                    .setDependencyFlags(vk::DependencyFlags());
        }
        dependencies[hasDepthStencil ? 1 : 0] =
            ::vk::SubpassDependency()
                .setSrcSubpass(VK_SUBPASS_EXTERNAL)
                .setDstSubpass(0)
                .setSrcStageMask(
                    vk::PipelineStageFlagBits::eColorAttachmentOutput)
                .setDstStageMask(
                    vk::PipelineStageFlagBits::eColorAttachmentOutput)
                .setSrcAccessMask(vk::AccessFlagBits())
                .setDstAccessMask(
                    vk::AccessFlagBits::eColorAttachmentWrite |
                    vk::AccessFlagBits::eColorAttachmentRead)
                .setDependencyFlags(vk::DependencyFlags());

        auto const renderPassCreateInfo =
            vk::RenderPassCreateInfo()
                .setAttachmentCount(attachmentsCount)
                .setPAttachments(&attachments[0])
                .setSubpassCount(1)
                .setPSubpasses(&subpass)
                .setDependencyCount(hasDepthStencil ? 2 : 1)
                .setPDependencies(&dependencies[0]);
        {
            const auto result = base::PtrToRef(device).NativeObject_().createRenderPass(
                &renderPassCreateInfo,
                nullptr,
                &base::PtrToRef(target));
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
        }
    }
}

} // namespace ae::gfx_low
// EOF
