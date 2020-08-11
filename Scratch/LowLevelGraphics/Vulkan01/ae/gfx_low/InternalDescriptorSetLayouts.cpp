// 文字コード：UTF-8
#include <ae/gfx_low/InternalDescriptorSetLayouts.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/DescriptorSetSpecInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/ShaderBindingInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
InternalDescriptorSetLayouts::InternalDescriptorSetLayouts(
    Device* device, const DescriptorSetSpecInfo& info)
: device_(base::PtrToRef(device)) {
    // 各 DescriptorSetLayou 内でこの数まで binding を記述できる。
    // また、スタック上に確保することで new/delete オーバーヘッドをなくす。
    constexpr int bindingsCountMax = 64;
    int bindingsCount = 0;
    std::array<::vk::DescriptorSetLayoutBinding, bindingsCountMax> bindings;

    // 汎用的な確保関数
    auto addBinding = [bindingsCountMax](int& bindingsCount,
                          ::vk::DescriptorSetLayoutBinding* bindingsPtr,
                          const int bindingInfosIdx,
                          const ShaderBindingInfo* bindingInfosPtr,
                          const ::vk::DescriptorType descriptorType) {
        AE_BASE_ASSERT_LESS(bindingsCount, bindingsCountMax);
        const auto& info = base::PtrToRef(&bindingInfosPtr[bindingInfosIdx]);
        bindingsPtr[bindingsCount] =
            ::vk::DescriptorSetLayoutBinding()
                .setBinding(info.BindingIndex())
                .setDescriptorType(descriptorType)
                .setDescriptorCount(info.ElemCount())
                .setStageFlags(
                    InternalEnumUtil::ToShaderStageFlags(info.Stages()))
                .setPImmutableSamplers(nullptr);
        ++bindingsCount;
    };
    auto addSetLayout =
        [](gfx_low::Device& device, int& layoutsCount,
            ::vk::DescriptorSetLayout* layoutsPtr, int& bindingsCount,
            const ::vk::DescriptorSetLayoutBinding* bindingsPtr) {
            AE_BASE_ASSERT_LESS(layoutsCount, DescriptorSetLayoutsCountMax);

            const auto info = ::vk::DescriptorSetLayoutCreateInfo()
                                  .setBindingCount(bindingsCount)
                                  .setPBindings(bindingsPtr);
            const auto result =
                device.NativeObject_().createDescriptorSetLayout(
                    &info, nullptr, &layoutsPtr[layoutsCount]);
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
            ++layoutsCount;
            bindingsCount = 0;
        };

    // Buffer
    if (0 < info.BindingInfosCount(DescriptorKind::UniformBuffer) ||
        0 < info.BindingInfosCount(DescriptorKind::StorageBuffer)) {
        // UniformBuffer
        for (int i = 0; i < info.BindingInfosCount(DescriptorKind::UniformBuffer); ++i) {
            addBinding(bindingsCount, &bindings[0], i,
                info.BindingInfos(DescriptorKind::UniformBuffer),
                ::vk::DescriptorType::eUniformBuffer);
        }

        // StorageBuffer
        for (int i = 0;
             i < info.BindingInfosCount(DescriptorKind::StorageBuffer); ++i) {
            addBinding(bindingsCount, &bindings[0], i,
                info.BindingInfos(DescriptorKind::StorageBuffer),
                ::vk::DescriptorType::eStorageBuffer);
        }

        // 作成
        addSetLayout(device_, descriptorSetLayoutsCount_,
            &descriptorSetLayouts_[0], bindingsCount, &bindings[0]);
    }

    // Image
    if (0 < info.BindingInfosCount(DescriptorKind::SampledImage) ||
        0 < info.BindingInfosCount(DescriptorKind::StorageImage)) {
        // SampledImage
        for (int i = 0;
             i < info.BindingInfosCount(DescriptorKind::SampledImage); ++i) {
            addBinding(bindingsCount, &bindings[0], i,
                info.BindingInfos(DescriptorKind::SampledImage),
                ::vk::DescriptorType::eSampledImage);
        }

        // StorageImage
        for (int i = 0;
             i < info.BindingInfosCount(DescriptorKind::StorageImage); ++i) {
            addBinding(bindingsCount, &bindings[0], i,
                info.BindingInfos(DescriptorKind::StorageImage),
                ::vk::DescriptorType::eStorageImage);
        }

        // 作成
        addSetLayout(device_, descriptorSetLayoutsCount_,
            &descriptorSetLayouts_[0], bindingsCount, &bindings[0]);
    }

    // Sampler
    if (0 < info.BindingInfosCount(DescriptorKind::Sampler)) {
        for (int i = 0;
             i < info.BindingInfosCount(DescriptorKind::Sampler); ++i) {
            addBinding(bindingsCount, &bindings[0], i,
                info.BindingInfos(DescriptorKind::Sampler),
                ::vk::DescriptorType::eSampler);
        }

        // 作成
        addSetLayout(device_, descriptorSetLayoutsCount_,
            &descriptorSetLayouts_[0], bindingsCount, &bindings[0]);
    }
}

//------------------------------------------------------------------------------
InternalDescriptorSetLayouts::~InternalDescriptorSetLayouts() {
    for (int i = descriptorSetLayoutsCount_ - 1; 0 <= i; --i) {
        device_.NativeObject_().destroyDescriptorSetLayout(
            descriptorSetLayouts_[i], nullptr);
        descriptorSetLayouts_[i] = ::vk::DescriptorSetLayout();
    }
}

} // namespace gfx_low
} // namespace ae
// EOF
