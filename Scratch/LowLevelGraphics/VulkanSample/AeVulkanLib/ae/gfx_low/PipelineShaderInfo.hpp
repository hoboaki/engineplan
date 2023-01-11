// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>

namespace ae::gfx_low {
class ShaderModuleResource;
}

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// パイプラインに渡すシェーダーに関する情報。
class PipelineShaderInfo {
public:
    /// @name プロパティ
    //@{
    /// 使用する ShaderModuleResource のポインタ。（初期値：nullptr）
    ShaderModuleResource* Resource() const { return resource_.Get(); }

    /// Resource() の設定。（設定必須）
    PipelineShaderInfo& SetResource(ShaderModuleResource* imageResource)
    {
        resource_.Reset(imageResource);
        return *this;
    }

    /// エントリーポイントとなる関数名のポインタ。（初期値：nullptr）
    const char* EntryPointNamePtr() const { return entryPointNamePtr_; }

    /// EntryPointNamePtr() の設定。
    PipelineShaderInfo& SetEntryPointNamePtr(const char* entryPointNamePtr)
    {
        entryPointNamePtr_ = entryPointNamePtr;
        return *this;
    }
    //@}

private:
    base::Pointer<ShaderModuleResource> resource_;
    const char* entryPointNamePtr_ = nullptr;
};

} // namespace ae::gfx_low
// EOF
