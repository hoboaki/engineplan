// 文字コード：UTF-8
#include <ae/gfx_low/Fence.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/FenceCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
Fence::Fence(const FenceCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, nativeObject_()
{
    const auto fenceCreateInfo = ::vk::FenceCreateInfo();
    const auto result = device_.NativeObject_().createFence(
        &fenceCreateInfo,
        nullptr,
        &nativeObject_);
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
}

//------------------------------------------------------------------------------
Fence::~Fence()
{
    AE_BASE_ASSERT(!isActive_);
    device_.NativeObject_().destroyFence(nativeObject_, nullptr);
}

//------------------------------------------------------------------------------
void Fence::Wait()
{
    if (!isActive_) {
        return;
    }

    // 待機
    {
        const auto result = device_.NativeObject_().waitForFences(
            1,
            &nativeObject_,
            VK_TRUE,
            UINT64_MAX);
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }

    // 内部状態をリセット
    {
        const auto result =
            device_.NativeObject_().resetFences(1, &nativeObject_);
        AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
    }
    isActive_ = false;
}

//------------------------------------------------------------------------------
void Fence::OnSubmit_()
{
    // Wait 抜け検知
    AE_BASE_ASSERT(!isActive_);
    isActive_ = true;
}

} // namespace ae::gfx_low
// EOF
