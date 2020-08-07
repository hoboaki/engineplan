// 文字コード：UTF-8
#include <ae/gfx_low/ShaderModuleResource.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/ShaderModuleResourceCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
ShaderModuleResource::ShaderModuleResource(const ShaderModuleResourceCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, data_(createInfo.DataAddress()) {

}

//------------------------------------------------------------------------------
ShaderModuleResource::~ShaderModuleResource() {
}

} // namespace gfx_low
} // namespace ae
// EOF
