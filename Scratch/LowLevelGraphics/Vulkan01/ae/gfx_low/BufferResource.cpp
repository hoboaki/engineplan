// 文字コード：UTF-8
#include <ae/gfx_low/BufferResource.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/BufferResourceCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
BufferResource::BufferResource(const BufferResourceCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, buffer_()
, isCreatedByBufferPtr_(false) {
    // ImagePtr からの作成
    if (createInfo.BufferPtr_() != nullptr) {
        AE_BASE_ASSERT(createInfo.BufferPtr_() != nullptr);
        buffer_ = base::PtrToRef(createInfo.BufferPtr_());
        isCreatedByBufferPtr_ = true;
        return;
    }

    // VkBuffer の作成
    {
        const auto nativeCreateInfo = createInfo.NativeCreateInfo_();
        const auto result = device_.Instance_().createBuffer(
            &nativeCreateInfo, nullptr, &buffer_);
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }

    // メモリ割り当て
    {
        AE_BASE_ASSERT(createInfo.DataAddress().Memory().IsValid());
        const auto result = device_.Instance_().bindBufferMemory(buffer_,
            createInfo.DataAddress().Memory().Instance_(),
            createInfo.DataAddress().Offset());
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }
}

//------------------------------------------------------------------------------
BufferResource::~BufferResource() {
    // ImagePtr から作った場合は何もしない
    if (isCreatedByBufferPtr_) {
        buffer_ = ::vk::Buffer();
        return;
    }

    device_.Instance_().destroyBuffer(buffer_, nullptr);
    buffer_ = ::vk::Buffer();
}

} // namespace gfx_low
} // namespace ae
// EOF
