// 文字コード：UTF-8
#include <ae/gfx_low/IndirectBufferView.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/BufferResource.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/IndirectBufferViewCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
IndirectBufferView::IndirectBufferView(
    const IndirectBufferViewCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, bufferResource_(base::PtrToRef(createInfo.Resource()))
, region_(createInfo.Region())
{
}

//------------------------------------------------------------------------------
IndirectBufferView::~IndirectBufferView()
{
}

} // namespace ae::gfx_low
// EOF
