// 文字コード：UTF-8
#include <ae/gfx_low/ShaderModuleResource.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/ShaderModuleResourceCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
ShaderModuleResource::ShaderModuleResource(
    const ShaderModuleResourceCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
{
    const auto nativeCreateInfo =
        ::vk::ShaderModuleCreateInfo()
            .setCodeSize(createInfo.SpecInfo().Size())
            .setPCode(reinterpret_cast<uint32_t*>(
                &createInfo.DataAddress()
                     .Memory()
                     .Head_()[createInfo.DataAddress().Offset()]));
    const auto result = device_.NativeObject_().createShaderModule(
        &nativeCreateInfo,
        nullptr,
        &nativeObject_);
    AE_BASE_ASSERT(result == ::vk::Result::eSuccess);
}

//------------------------------------------------------------------------------
ShaderModuleResource::~ShaderModuleResource()
{
    device_.NativeObject_().destroyShaderModule(nativeObject_, nullptr);
}

} // namespace ae::gfx_low
// EOF
