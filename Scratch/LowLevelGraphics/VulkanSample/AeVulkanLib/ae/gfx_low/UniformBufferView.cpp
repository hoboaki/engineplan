// 文字コード：UTF-8
#include <ae/gfx_low/UniformBufferView.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/BufferResource.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/InternalEnumUtil.hpp>
#include <ae/gfx_low/UniformBufferViewCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
UniformBufferView::UniformBufferView(
    const UniformBufferViewCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, bufferResource_(base::PtrToRef(createInfo.Resource()))
, region_(createInfo.Region()) {
}

//------------------------------------------------------------------------------
UniformBufferView::~UniformBufferView() {
}

} // namespace gfx_low
} // namespace ae
// EOF
