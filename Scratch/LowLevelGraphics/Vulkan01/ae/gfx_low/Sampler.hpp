// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class Device;
class SamplerCreateInfo;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// サンプラーを扱うクラス。
class Sampler {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    Sampler(const SamplerCreateInfo& createInfo);
    ~Sampler();
    //@}

    /// @name プロパティ
    //@{
    /// 所属する Device。
    gfx_low::Device& Device() const { return device_; }
    //@}

    /// @name 内部処理用機能
    //@{
    ::vk::Sampler& NativeObject_() { return nativeObject_; }
    //@}

private:
    gfx_low::Device& device_;
    ::vk::Sampler nativeObject_;
};

} // namespace gfx_low
} // namespace ae
// EOF
