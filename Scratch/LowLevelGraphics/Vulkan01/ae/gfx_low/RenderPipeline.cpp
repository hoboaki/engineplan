// 文字コード：UTF-8
#include <ae/gfx_low/RenderPipeline.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/RenderPipelineCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
RenderPipeline::RenderPipeline(const RenderPipelineCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, nativeObject_() {}


//------------------------------------------------------------------------------
RenderPipeline::~RenderPipeline() {}

} // namespace gfx_low
} // namespace ae
// EOF
