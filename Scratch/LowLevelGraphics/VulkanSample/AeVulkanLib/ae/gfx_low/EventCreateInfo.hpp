// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class Device;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// Event オブジェクト作成に必要な情報。
class EventCreateInfo {
public:
    /// 属する Device オブジェクトのポインタ。（初期値：nullptr）
    gfx_low::Device* Device() const { return device_.Get(); }

    /// Device() の設定。（設定必須）
    EventCreateInfo& SetDevice(gfx_low::Device* system) {
        device_.Reset(system);
        return *this;
    }

private:
    base::Pointer<gfx_low::Device> device_;
};

} // namespace gfx_low
} // namespace ae
// EOF
