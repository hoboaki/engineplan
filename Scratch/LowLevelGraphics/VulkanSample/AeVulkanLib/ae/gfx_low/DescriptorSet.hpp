// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/InternalDescriptorSetLayouts.hpp>
#include <ae/gfx_low/SdkHeader.hpp>
#include <array>

namespace ae::gfx_low {
class DescriptorSetCreateInfo;
class DescriptorSetUpdateInfo;
class Device;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// デスクリプタセットを扱うクラス。
class DescriptorSet {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    DescriptorSet(const DescriptorSetCreateInfo& createInfo);
    ~DescriptorSet();
    //@}

    /// @name プロパティ
    //@{
    /// 所属する Device。
    gfx_low::Device& Device() const { return device_; }
    //@}

    /// @name 操作
    //@{
    /// デスクリプタセットの内容を更新する。
    /// @details
    /// 更新は本オブジェクトを GPU が参照していないときに行ってください。
    void Update(const DescriptorSetUpdateInfo& info);
    //@}

    /// @name 内部処理用機能
    //@{
    ::vk::DescriptorSet* NativeObjects_() { return &nativeObjects_[0]; }
    const ::vk::DescriptorSet* NativeObjects_() const
    {
        return &nativeObjects_[0];
    }

    const InternalDescriptorSetLayouts& Layouts_() const
    {
        return descriptorSetLayouts_;
    }
    //@}

private:
    gfx_low::Device& device_;
    InternalDescriptorSetLayouts descriptorSetLayouts_;
    ::vk::DescriptorPool descriptorPool_;
    std::array<
        ::vk::DescriptorSet,
        InternalDescriptorSetLayouts::DescriptorSetLayoutsCountMax>
        nativeObjects_;
};

} // namespace ae::gfx_low
// EOF
