// 文字コード：UTF-8
#include <ae/gfx_low/VertexBufferView.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/BufferResource.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/VertexBufferViewCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
VertexBufferView::VertexBufferView(const VertexBufferViewCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, bufferResource_(base::PtrToRef(createInfo.Resource()))
, region_(createInfo.Region())
{
}

//------------------------------------------------------------------------------
VertexBufferView::~VertexBufferView()
{
}

} // namespace ae::gfx_low
// EOF
