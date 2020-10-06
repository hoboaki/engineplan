// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/ShaderModuleResource.hpp>
#include <ae/gfx_low/UniqueResourceMemory.hpp>
#include <memory>

namespace aesk {
class GfxBasicKit;
}

//------------------------------------------------------------------------------
namespace aesk {

/// メモリ管理も行う ShaderModuleResource のラッパークラス。
class Shader
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    Shader(GfxBasicKit* gfxKit, const void* shaderCode, size_t shaderCodeSize);
    ~Shader();
    //@}

    /// @name プロパティ
    //@{
    ::ae::gfx_low::ShaderModuleResource& Resource() const { return *resource_; }
    //@}

private:
    ::ae::gfx_low::UniqueResourceMemory memory_;
    ::std::unique_ptr<::ae::gfx_low::ShaderModuleResource> resource_;
};

}
// EOF
