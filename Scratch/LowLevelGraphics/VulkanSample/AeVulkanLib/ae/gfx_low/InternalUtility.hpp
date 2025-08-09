// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class DepthStencilSetting;
class Device;
class ImageResource;
class ImageSubresourceLocation;
class RenderPassSpecInfo;
class RenderTargetSetting;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// 内部実装用便利機能群。
struct InternalUtility
{
    /// @param aspectFlagsHint ImageAspectFlags が事前に分かっている場合は指定。（処理負荷削減目的の引数）
    static ::vk::ImageSubresourceRange ToImageSubresourceRange(
        const ImageResource& resource,
        const ImageSubresourceLocation& location,
        const ::vk::ImageAspectFlags& aspectFlagsHint = {});

    // RenderPassSpecInfo を元に RenderPass オブジェクトを作成する。
    static void CreateRenderPass(
        ::vk::RenderPass* target,
        Device* device,
        const RenderPassSpecInfo& specInfo,
        const RenderTargetSetting* renderTargetSettingsPtr,
        const DepthStencilSetting* depthStencilSettingPtr);
};

} // namespace ae::gfx_low
// EOF
