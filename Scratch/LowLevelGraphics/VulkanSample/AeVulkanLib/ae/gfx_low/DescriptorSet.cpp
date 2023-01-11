// 文字コード：UTF-8
#include <ae/gfx_low/DescriptorSet.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/BufferResource.hpp>
#include <ae/gfx_low/DescriptorSetCreateInfo.hpp>
#include <ae/gfx_low/DescriptorSetUpdateInfo.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/SampledImageDescriptorInfo.hpp>
#include <ae/gfx_low/SampledImageView.hpp>
#include <ae/gfx_low/Sampler.hpp>
#include <ae/gfx_low/SamplerDescriptorInfo.hpp>
#include <ae/gfx_low/StorageBufferDescriptorInfo.hpp>
#include <ae/gfx_low/StorageBufferView.hpp>
#include <ae/gfx_low/StorageImageDescriptorInfo.hpp>
#include <ae/gfx_low/StorageImageView.hpp>
#include <ae/gfx_low/UniformBufferDescriptorInfo.hpp>
#include <ae/gfx_low/UniformBufferView.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
DescriptorSet::DescriptorSet(const DescriptorSetCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, descriptorSetLayouts_(&device_, createInfo.SpecInfo())
, descriptorPool_()
, nativeObjects_()
{
    // デスクリプタが不要なら何もしない
    if (descriptorSetLayouts_.DescriptorSetLayoutCount() == 0) {
        return;
    }

    const auto specInfo = createInfo.SpecInfo();

    // DescriptorPool
    {
        constexpr int sizesCountMax = 5;
        int sizeCount = 0;
        std::array<::vk::DescriptorPoolSize, sizesCountMax> sizes_;
        if (0 < specInfo.BindingInfoCount(DescriptorKind::UniformBuffer)) {
            sizes_[sizeCount] =
                ::vk::DescriptorPoolSize()
                    .setType(::vk::DescriptorType::eUniformBuffer)
                    .setDescriptorCount(specInfo.TotalBindingCount(
                        DescriptorKind::UniformBuffer));
            ++sizeCount;
        }
        if (0 < specInfo.BindingInfoCount(DescriptorKind::StorageBuffer)) {
            sizes_[sizeCount] =
                ::vk::DescriptorPoolSize()
                    .setType(::vk::DescriptorType::eStorageBuffer)
                    .setDescriptorCount(specInfo.TotalBindingCount(
                        DescriptorKind::StorageBuffer));
            ++sizeCount;
        }
        if (0 < specInfo.BindingInfoCount(DescriptorKind::SampledImage)) {
            sizes_[sizeCount] =
                ::vk::DescriptorPoolSize()
                    .setType(::vk::DescriptorType::eSampledImage)
                    .setDescriptorCount(specInfo.TotalBindingCount(
                        DescriptorKind::SampledImage));
            ++sizeCount;
        }
        if (0 < specInfo.BindingInfoCount(DescriptorKind::StorageImage)) {
            sizes_[sizeCount] =
                ::vk::DescriptorPoolSize()
                    .setType(::vk::DescriptorType::eStorageImage)
                    .setDescriptorCount(specInfo.TotalBindingCount(
                        DescriptorKind::StorageImage));
            ++sizeCount;
        }
        if (0 < specInfo.BindingInfoCount(DescriptorKind::Sampler)) {
            sizes_[sizeCount] =
                ::vk::DescriptorPoolSize()
                    .setType(::vk::DescriptorType::eSampler)
                    .setDescriptorCount(
                        specInfo.TotalBindingCount(DescriptorKind::Sampler));
            ++sizeCount;
        }
        AE_BASE_ASSERT_LESS(0, sizeCount);

        const auto nativeCreateInfo =
            ::vk::DescriptorPoolCreateInfo()
                .setMaxSets(descriptorSetLayouts_.DescriptorSetLayoutCount())
                .setPoolSizeCount(sizeCount)
                .setPPoolSizes(&sizes_[0]);
        const auto result = device_.NativeObject_().createDescriptorPool(
            &nativeCreateInfo,
            nullptr,
            &descriptorPool_);
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }

    // DescriptorSet
    {
        const auto allocInfo =
            ::vk::DescriptorSetAllocateInfo()
                .setDescriptorPool(descriptorPool_)
                .setDescriptorSetCount(
                    descriptorSetLayouts_.DescriptorSetLayoutCount())
                .setPSetLayouts(descriptorSetLayouts_.DescriptorSetLayouts());
        const auto result = device_.NativeObject_().allocateDescriptorSets(
            &allocInfo,
            &nativeObjects_[0]);
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }
}

//------------------------------------------------------------------------------
DescriptorSet::~DescriptorSet()
{
    // デスクリプタが不要なら何もしない
    if (descriptorSetLayouts_.DescriptorSetLayoutCount() == 0) {
        return;
    }

    // DescriptorSet の free は DescriptorPool の破棄時に一括でされるため不要
    device_.NativeObject_().destroyDescriptorPool(descriptorPool_, nullptr);
    descriptorPool_ = ::vk::DescriptorPool();
}

//------------------------------------------------------------------------------
void DescriptorSet::Update(const DescriptorSetUpdateInfo& info)
{
    // 1回の Update でこの数だけの DescriptorInfo を扱える。
    // また、スタック上に確保することで new/delete オーバーヘッドをなくす。
    constexpr int writesCountMax = 64;
    int writeCount = 0;
    int bufferCount = 0;
    int imageCount = 0;
    std::array<::vk::WriteDescriptorSet, writesCountMax> writes;
    std::array<::vk::DescriptorBufferInfo, writesCountMax> buffers;
    std::array<::vk::DescriptorImageInfo, writesCountMax> images;

    // メモ：
    // バインド番号の仕様については
    // DescriptorSetSpecInfo のクラスコメントを参照してください

    // UniformBuffer
    for (int infoIdx = 0; infoIdx < info.UniformBufferInfoCount(); ++infoIdx) {
        const auto& descInfo =
            base::PtrToRef(&info.UniformBufferInfos()[infoIdx]);
        const auto descSetIdx = descriptorSetLayouts_.DescriptorSetLayoutIndex(
            DescriptorKind::UniformBuffer);
        AE_BASE_ASSERT_LESS_EQUALS(0, descSetIdx);
        writes[writeCount] =
            ::vk::WriteDescriptorSet()
                .setDstSet(nativeObjects_[descSetIdx])
                .setDstBinding(descInfo.Region().BindingIndex())
                .setDstArrayElement(descInfo.Region().ElemOffset())
                .setDescriptorCount(descInfo.Region().ElemCount())
                .setDescriptorType(::vk::DescriptorType::eUniformBuffer)
                .setPBufferInfo(&buffers[bufferCount]);
        ++writeCount;

        for (int viewIdx = 0; viewIdx < descInfo.Region().ElemCount();
             ++viewIdx) {
            const auto& view =
                base::PtrToRef(base::PtrToRef(&descInfo.Views()[viewIdx]));
            buffers[bufferCount] =
                ::vk::DescriptorBufferInfo()
                    .setBuffer(view.BufferResource_().NativeObject_())
                    .setOffset(view.Region_().Offset())
                    .setRange(view.Region_().Size());
            ++bufferCount;
        }
    }

    // StorageBuffer
    for (int infoIdx = 0; infoIdx < info.StorageBufferInfoCount(); ++infoIdx) {
        const auto& descInfo =
            base::PtrToRef(&info.StorageBufferInfos()[infoIdx]);
        const auto descSetIdx = descriptorSetLayouts_.DescriptorSetLayoutIndex(
            DescriptorKind::StorageBuffer);
        AE_BASE_ASSERT_LESS_EQUALS(0, descSetIdx);
        writes[writeCount] =
            ::vk::WriteDescriptorSet()
                .setDstSet(nativeObjects_[descSetIdx])
                .setDstBinding(
                    descriptorSetLayouts_.StorageBufferBindingImageOffset() +
                    descInfo.Region().BindingIndex())
                .setDstArrayElement(descInfo.Region().ElemOffset())
                .setDescriptorCount(descInfo.Region().ElemCount())
                .setDescriptorType(::vk::DescriptorType::eStorageBuffer)
                .setPBufferInfo(&buffers[bufferCount]);
        ++writeCount;

        for (int viewIdx = 0; viewIdx < descInfo.Region().ElemCount();
             ++viewIdx) {
            const auto& view =
                base::PtrToRef(base::PtrToRef(&descInfo.Views()[viewIdx]));
            buffers[bufferCount] =
                ::vk::DescriptorBufferInfo()
                    .setBuffer(view.BufferResource_().NativeObject_())
                    .setOffset(view.Region_().Offset())
                    .setRange(view.Region_().Size());
            ++bufferCount;
        }
    }

    // SampledImage
    for (int infoIdx = 0; infoIdx < info.SampledImageInfoCount(); ++infoIdx) {
        const auto& descInfo =
            base::PtrToRef(&info.SampledImageInfos()[infoIdx]);
        const auto descSetIdx = descriptorSetLayouts_.DescriptorSetLayoutIndex(
            DescriptorKind::SampledImage);
        AE_BASE_ASSERT_LESS_EQUALS(0, descSetIdx);
        writes[writeCount] =
            ::vk::WriteDescriptorSet()
                .setDstSet(nativeObjects_[descSetIdx])
                .setDstBinding(descInfo.Region().BindingIndex())
                .setDstArrayElement(descInfo.Region().ElemOffset())
                .setDescriptorCount(descInfo.Region().ElemCount())
                .setDescriptorType(::vk::DescriptorType::eSampledImage)
                .setPImageInfo(&images[imageCount]);
        ++writeCount;

        for (int viewIdx = 0; viewIdx < descInfo.Region().ElemCount();
             ++viewIdx) {
            const auto& view =
                base::PtrToRef(base::PtrToRef(&descInfo.Views()[viewIdx]));
            images[imageCount] =
                ::vk::DescriptorImageInfo()
                    .setImageView(view.NativeObject_())
                    .setImageLayout(::vk::ImageLayout::eShaderReadOnlyOptimal);
            ++imageCount;
        }
    }

    // StorageImage
    for (int infoIdx = 0; infoIdx < info.StorageImageInfoCount(); ++infoIdx) {
        const auto& descInfo =
            base::PtrToRef(&info.StorageImageInfos()[infoIdx]);
        const auto descSetIdx = descriptorSetLayouts_.DescriptorSetLayoutIndex(
            DescriptorKind::StorageImage);
        AE_BASE_ASSERT_LESS_EQUALS(0, descSetIdx);
        writes[writeCount] =
            ::vk::WriteDescriptorSet()
                .setDstSet(nativeObjects_[descSetIdx])
                .setDstBinding(
                    descriptorSetLayouts_.StorageImageBindingImageOffset() +
                    descInfo.Region().BindingIndex())
                .setDstArrayElement(descInfo.Region().ElemOffset())
                .setDescriptorCount(descInfo.Region().ElemCount())
                .setDescriptorType(::vk::DescriptorType::eStorageImage)
                .setPImageInfo(&images[imageCount]);
        ++writeCount;

        for (int viewIdx = 0; viewIdx < descInfo.Region().ElemCount();
             ++viewIdx) {
            const auto& view =
                base::PtrToRef(base::PtrToRef(&descInfo.Views()[viewIdx]));
            images[imageCount] =
                ::vk::DescriptorImageInfo()
                    .setImageView(view.NativeObject_())
                    .setImageLayout(::vk::ImageLayout::eGeneral);
            ++imageCount;
        }
    }

    // Sampler
    for (int infoIdx = 0; infoIdx < info.SamplerInfoCount(); ++infoIdx) {
        const auto& descInfo = base::PtrToRef(&info.SamplerInfos()[infoIdx]);
        const auto descSetIdx = descriptorSetLayouts_.DescriptorSetLayoutIndex(
            DescriptorKind::Sampler);
        AE_BASE_ASSERT_LESS_EQUALS(0, descSetIdx);
        writes[writeCount] =
            ::vk::WriteDescriptorSet()
                .setDstSet(nativeObjects_[descSetIdx])
                .setDstBinding(descInfo.Region().BindingIndex())
                .setDstArrayElement(descInfo.Region().ElemOffset())
                .setDescriptorCount(descInfo.Region().ElemCount())
                .setDescriptorType(::vk::DescriptorType::eSampler)
                .setPImageInfo(&images[imageCount]);
        ++writeCount;

        for (int samplerIdx = 0; samplerIdx < descInfo.Region().ElemCount();
             ++samplerIdx) {
            const auto& sampler = base::PtrToRef(
                base::PtrToRef(&descInfo.Samplers()[samplerIdx]));
            images[imageCount] =
                ::vk::DescriptorImageInfo()
                    .setSampler(sampler.NativeObject_())
                    .setImageLayout(::vk::ImageLayout::eUndefined);
            ++imageCount;
        }
    }

    AE_BASE_ASSERT_LESS_EQUALS(writeCount, writesCountMax);
    AE_BASE_ASSERT_LESS_EQUALS(bufferCount, int(buffers.size()));
    AE_BASE_ASSERT_LESS_EQUALS(imageCount, int(images.size()));
    device_.NativeObject_()
        .updateDescriptorSets(writeCount, &writes[0], 0, nullptr);
}

} // namespace ae::gfx_low
// EOF
