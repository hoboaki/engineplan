// 文字コード：UTF-8
#include <aesk/Shader.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/ResourceMemoryAllocInfo.hpp>
#include <ae/gfx_low/ResourceMemoryRegion.hpp>
#include <ae/gfx_low/ResourceMemoryRequirements.hpp>
#include <ae/gfx_low/ShaderModuleResourceCreateInfo.hpp>
#include <aesk/GfxBasicKit.hpp>

//------------------------------------------------------------------------------
namespace aesk {

//------------------------------------------------------------------------------
Shader::Shader(
    GfxBasicKit* gfxKit, const void* shaderCode, const size_t shaderCodeSize) {
    auto& kit = ::ae::base::PtrToRef(gfxKit);
    const auto specInfo =
        ::ae::gfx_low::ShaderModuleResourceSpecInfo().SetSize(shaderCodeSize);
    memory_.Reset(&kit.Device(),
        ::ae::gfx_low::ResourceMemoryAllocInfo()
            .SetKind(::ae::gfx_low::ResourceMemoryKind::SharedNonCached)
            .SetParams(kit.Device().CalcResourceMemoryRequirements(specInfo)));
    ::std::memcpy(
        kit.Device().MapResourceMemory(*memory_,
            ::ae::gfx_low::ResourceMemoryRegion().SetSize(shaderCodeSize)),
        shaderCode, shaderCodeSize);
    kit.Device().UnmapResourceMemory(*memory_);
    resource_.reset(new ::ae::gfx_low::ShaderModuleResource(
        ::ae::gfx_low::ShaderModuleResourceCreateInfo()
            .SetDevice(&kit.Device())
            .SetSpecInfo(specInfo)
            .SetDataAddress(*memory_)));
}

//------------------------------------------------------------------------------
Shader::~Shader() {}

} // namespace aesk
// EOF
