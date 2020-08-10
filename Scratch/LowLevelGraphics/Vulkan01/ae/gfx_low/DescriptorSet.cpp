// 文字コード：UTF-8
#include <ae/gfx_low/DescriptorSet.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/DescriptorSetCreateInfo.hpp>
#include <ae/gfx_low/Device.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
DescriptorSet::DescriptorSet(const DescriptorSetCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, descriptorSetLayouts_(&device_, createInfo.SpecInfo())
, descriptorPool_()
, nativeObjects_() {
    // デスクリプタが不要なら何もしない
    if (descriptorSetLayouts_.DescriptorSetLayoutsCount() == 0) {
        return;
    }

    const auto specInfo = createInfo.SpecInfo();

    // DescriptorPool
    {
        constexpr int sizesCountMax = 5;
        int sizesCount = 0;
        std::array<::vk::DescriptorPoolSize, sizesCountMax> sizes_;
        if (0 < specInfo.BindingInfosCount(DescriptorKind::UniformBuffer)) {
            sizes_[sizesCount] =
                ::vk::DescriptorPoolSize()
                    .setType(::vk::DescriptorType::eUniformBuffer)
                    .setDescriptorCount(specInfo.TotalBindingCount(
                        DescriptorKind::UniformBuffer));
            ++sizesCount;
        }
        if (0 < specInfo.BindingInfosCount(DescriptorKind::StorageBuffer)) {
            sizes_[sizesCount] =
                ::vk::DescriptorPoolSize()
                    .setType(::vk::DescriptorType::eStorageBuffer)
                    .setDescriptorCount(specInfo.TotalBindingCount(
                        DescriptorKind::StorageBuffer));
            ++sizesCount;
        }
        if (0 < specInfo.BindingInfosCount(DescriptorKind::SampledImage)) {
            sizes_[sizesCount] =
                ::vk::DescriptorPoolSize()
                    .setType(::vk::DescriptorType::eSampledImage)
                    .setDescriptorCount(specInfo.TotalBindingCount(
                        DescriptorKind::SampledImage));
            ++sizesCount;
        }
        if (0 < specInfo.BindingInfosCount(DescriptorKind::StorageImage)) {
            sizes_[sizesCount] =
                ::vk::DescriptorPoolSize()
                    .setType(::vk::DescriptorType::eStorageImage)
                    .setDescriptorCount(specInfo.TotalBindingCount(
                        DescriptorKind::StorageImage));
            ++sizesCount;
        }
        if (0 < specInfo.BindingInfosCount(DescriptorKind::Sampler)) {
            sizes_[sizesCount] =
                ::vk::DescriptorPoolSize()
                    .setType(::vk::DescriptorType::eSampler)
                    .setDescriptorCount(
                        specInfo.TotalBindingCount(DescriptorKind::Sampler));
            ++sizesCount;
        }
        AE_BASE_ASSERT_LESS(0, sizesCount);

        const auto nativeCreateInfo =
            ::vk::DescriptorPoolCreateInfo()
                .setMaxSets(descriptorSetLayouts_.DescriptorSetLayoutsCount())
                .setPoolSizeCount(sizesCount)
                .setPPoolSizes(&sizes_[0]);
        const auto result = device_.NativeObject_().createDescriptorPool(
            &nativeCreateInfo, nullptr, &descriptorPool_);
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }

    // DescriptorSet
    {
        const auto allocInfo =
            ::vk::DescriptorSetAllocateInfo()
                .setDescriptorPool(descriptorPool_)
                .setDescriptorSetCount(
                    descriptorSetLayouts_.DescriptorSetLayoutsCount())
                .setPSetLayouts(descriptorSetLayouts_.DescriptorSetLayouts());
        const auto result = device_.NativeObject_().allocateDescriptorSets(
            &allocInfo, &nativeObjects_[0]);
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }
}

//------------------------------------------------------------------------------
DescriptorSet::~DescriptorSet() {
    // デスクリプタが不要なら何もしない
    if (descriptorSetLayouts_.DescriptorSetLayoutsCount() == 0) {
        return;
    }

    {
        const auto result = device_.NativeObject_().freeDescriptorSets(
            descriptorPool_, descriptorSetLayouts_.DescriptorSetLayoutsCount(),
            &nativeObjects_[0]);
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }
    device_.NativeObject_().destroyDescriptorPool(descriptorPool_, nullptr);
    descriptorPool_ = ::vk::DescriptorPool();
}

} // namespace gfx_low
} // namespace ae
// EOF
