// 文字コード：UTF-8
#include <ae/gfx_low/DescriptorSet.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/DescriptorSetCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
DescriptorSet::DescriptorSet(const DescriptorSetCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, descriptorSetLayouts_(&device_, createInfo.SpecInfo())
, descriptorPool_()
, nativeObjects_() {
    //const auto specInfo = createInfo.SpecInfo();

    //// DescriptorPool 作成
    //{ 
    //    constexpr int sizesCountMax = 5;
    //    int sizesCount = 0;
    //    std::array<::vk::DescriptorPoolSize, sizesCountMax> sizes_;
    //    if (0 < specInfo.UniformBufferInfosCount()) {
    //        sizes_[sizesCount] =
    //            ::vk::DescriptorPoolSize()
    //                .setType(::vk::DescriptorType::eUniformBuffer)
    //                .setDescriptorCount(specInfo.UniformBufferInfosCount());
    //        ++sizesCount;
    //    }
    //}
}

//------------------------------------------------------------------------------
DescriptorSet::~DescriptorSet() {
}

} // namespace gfx_low
} // namespace ae
// EOF
