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
, nativeObject_()
, isCreatedByNativeObjectPtr_(false) {
    // NativeObjectPtr からの作成
    if (createInfo.NativeObjectPtr_() != nullptr) {
        AE_BASE_ASSERT(createInfo.NativeObjectPtr_() != nullptr);
        nativeObject_ = base::PtrToRef(createInfo.NativeObjectPtr_());
        isCreatedByNativeObjectPtr_ = true;
        return;
    }

    // VkBuffer の作成
    {
        const auto nativeCreateInfo = createInfo.NativeCreateInfo_();
        const auto result = device_.Instance_().createBuffer(
            &nativeCreateInfo, nullptr, &nativeObject_);
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }

    // メモリ割り当て
    {
        AE_BASE_ASSERT(createInfo.DataAddress().Memory().IsValid());
        const auto result = device_.Instance_().bindBufferMemory(nativeObject_,
            createInfo.DataAddress().Memory().Instance_(),
            createInfo.DataAddress().Offset());
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }
}

//------------------------------------------------------------------------------
BufferResource::~BufferResource() {
    // NativeObjectPtr から作った場合は何もしない
    if (isCreatedByNativeObjectPtr_) {
        nativeObject_ = ::vk::Buffer();
        return;
    }

    device_.Instance_().destroyBuffer(nativeObject_, nullptr);
    nativeObject_ = ::vk::Buffer();
}

} // namespace gfx_low
} // namespace ae
// EOF
