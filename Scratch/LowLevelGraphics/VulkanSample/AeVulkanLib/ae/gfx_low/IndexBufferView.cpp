// 文字コード：UTF-8
#include <ae/gfx_low/IndexBufferView.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/BufferResource.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/IndexBufferViewCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
IndexBufferView::IndexBufferView(const IndexBufferViewCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, bufferResource_(base::PtrToRef(createInfo.Resource()))
, region_(createInfo.Region())
, format_(createInfo.Format()) {
}

//------------------------------------------------------------------------------
IndexBufferView::~IndexBufferView() {
}

} // namespace gfx_low
} // namespace ae
// EOF
