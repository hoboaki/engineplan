// 文字コード：UTF-8
#include <ae/gfx_low/InternalDescriptorSetLayouts.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/DescriptorSetSpecInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/ShaderBindingInfo.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
InternalDescriptorSetLayouts::InternalDescriptorSetLayouts(
    Device* device,
    const DescriptorSetSpecInfo& info)
: device_(base::PtrToRef(device))
{
    // 初期化
    descriptorSetLayoutIndexes_.Fill(-1);

    // 各 DescriptorSetLayou 内でこの数まで binding を記述できる。
    // また、スタック上に確保することで new/delete オーバーヘッドをなくす。
    constexpr int bindingsCountMax = 64;
    int bindingsCount = 0;
    std::array<::vk::DescriptorSetLayoutBinding, bindingsCountMax> bindings;

    // 汎用的な確保関数
    auto addBinding =
        [bindingsCountMax](
            int& bindingsCount,
            ::vk::DescriptorSetLayoutBinding* bindingsPtr,
            const int bindingInfosIdx,
            const int bindingIndexOffset,
            const ShaderBindingInfo* bindingInfosPtr,
            const ::vk::DescriptorType descriptorType) {
            AE_BASE_ASSERT_LESS(bindingsCount, bindingsCountMax);
            const auto& info = base::PtrToRef(&bindingInfosPtr[bindingInfosIdx]);
            bindingsPtr[bindingsCount] =
                ::vk::DescriptorSetLayoutBinding()
                    .setBinding(bindingIndexOffset + info.BindingIndex())
                    .setDescriptorType(descriptorType)
                    .setDescriptorCount(info.ElemCount())
                    .setStageFlags(
                        InternalEnumUtil::ToShaderStageFlags(info.Stages()))
                    .setPImmutableSamplers(nullptr);
            ++bindingsCount;
        };
    auto addSetLayout =
        [](
            gfx_low::Device& device,
            int& layoutsCount,
            ::vk::DescriptorSetLayout* layoutsPtr,
            int& bindingsCount,
            const ::vk::DescriptorSetLayoutBinding* bindingsPtr) {
            AE_BASE_ASSERT_LESS(layoutsCount, DescriptorSetLayoutsCountMax);

            const auto info = ::vk::DescriptorSetLayoutCreateInfo()
                                  .setBindingCount(bindingsCount)
                                  .setPBindings(bindingsPtr);
            const auto result =
                device.NativeObject_().createDescriptorSetLayout(
                    &info,
                    nullptr,
                    &layoutsPtr[layoutsCount]);
            AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
            ++layoutsCount;
            bindingsCount = 0;
        };

    // Buffer
    if (0 < info.BindingInfoCount(DescriptorKind::UniformBuffer) ||
        0 < info.BindingInfoCount(DescriptorKind::StorageBuffer)) {
        // UniformBuffer
        if (0 < info.BindingInfoCount(DescriptorKind::UniformBuffer)) {
            descriptorSetLayoutIndexes_[DescriptorKind::UniformBuffer] =
                descriptorSetLayoutCount_;
            for (int i = 0;
                 i < info.BindingInfoCount(DescriptorKind::UniformBuffer);
                 ++i) {
                addBinding(
                    bindingsCount,
                    &bindings[0],
                    i,
                    0, // bindingIndexOffset
                    info.BindingInfos(DescriptorKind::UniformBuffer),
                    ::vk::DescriptorType::eUniformBuffer);
            }
            storageBufferBindingIndexOffset_ =
                info.MaxBindingIndex(DescriptorKind::UniformBuffer) + 1;
        }

        // StorageBuffer
        if (0 < info.BindingInfoCount(DescriptorKind::StorageBuffer)) {
            descriptorSetLayoutIndexes_[DescriptorKind::StorageBuffer] =
                descriptorSetLayoutCount_;
            for (int i = 0;
                 i < info.BindingInfoCount(DescriptorKind::StorageBuffer);
                 ++i) {
                addBinding(
                    bindingsCount,
                    &bindings[0],
                    i,
                    storageBufferBindingIndexOffset_,
                    info.BindingInfos(DescriptorKind::StorageBuffer),
                    ::vk::DescriptorType::eStorageBuffer);
            }
        }

        // 作成
        addSetLayout(
            device_,
            descriptorSetLayoutCount_,
            &descriptorSetLayouts_[0],
            bindingsCount,
            &bindings[0]);
    }

    // Image
    if (0 < info.BindingInfoCount(DescriptorKind::SampledImage) ||
        0 < info.BindingInfoCount(DescriptorKind::StorageImage)) {
        // SampledImage
        if (0 < info.BindingInfoCount(DescriptorKind::SampledImage)) {
            descriptorSetLayoutIndexes_[DescriptorKind::SampledImage] =
                descriptorSetLayoutCount_;
            for (int i = 0;
                 i < info.BindingInfoCount(DescriptorKind::SampledImage);
                 ++i) {
                addBinding(
                    bindingsCount,
                    &bindings[0],
                    i,
                    0, // bindingIndexOffset
                    info.BindingInfos(DescriptorKind::SampledImage),
                    ::vk::DescriptorType::eSampledImage);
            }
            storageImageBindingIndexOffset_ =
                info.MaxBindingIndex(DescriptorKind::SampledImage) + 1;
        }

        // StorageImage
        if (0 < info.BindingInfoCount(DescriptorKind::StorageImage)) {
            descriptorSetLayoutIndexes_[DescriptorKind::StorageImage] =
                descriptorSetLayoutCount_;
            for (int i = 0;
                 i < info.BindingInfoCount(DescriptorKind::StorageImage);
                 ++i) {
                addBinding(
                    bindingsCount,
                    &bindings[0],
                    i,
                    storageImageBindingIndexOffset_,
                    info.BindingInfos(DescriptorKind::StorageImage),
                    ::vk::DescriptorType::eStorageImage);
            }
        }

        // 作成
        addSetLayout(
            device_,
            descriptorSetLayoutCount_,
            &descriptorSetLayouts_[0],
            bindingsCount,
            &bindings[0]);
    }

    // Sampler
    if (0 < info.BindingInfoCount(DescriptorKind::Sampler)) {
        descriptorSetLayoutIndexes_[DescriptorKind::Sampler] =
            descriptorSetLayoutCount_;
        for (int i = 0; i < info.BindingInfoCount(DescriptorKind::Sampler);
             ++i) {
            addBinding(
                bindingsCount,
                &bindings[0],
                i,
                0, // bindingIndexOffset
                info.BindingInfos(DescriptorKind::Sampler),
                ::vk::DescriptorType::eSampler);
        }

        // 作成
        addSetLayout(
            device_,
            descriptorSetLayoutCount_,
            &descriptorSetLayouts_[0],
            bindingsCount,
            &bindings[0]);
    }
}

//------------------------------------------------------------------------------
InternalDescriptorSetLayouts::~InternalDescriptorSetLayouts()
{
    for (int i = descriptorSetLayoutCount_ - 1; 0 <= i; --i) {
        device_.NativeObject_().destroyDescriptorSetLayout(
            descriptorSetLayouts_[i],
            nullptr);
        descriptorSetLayouts_[i] = ::vk::DescriptorSetLayout();
    }
}

//------------------------------------------------------------------------------
int InternalDescriptorSetLayouts::DescriptorSetLayoutIndex(
    const DescriptorKind kind) const
{
    AE_BASE_ASSERT(kind != DescriptorKind::Invalid);
    return descriptorSetLayoutIndexes_[kind];
}

} // namespace ae::gfx_low
// EOF
