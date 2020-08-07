// 文字コード：UTF-8
#include <ae/gfx_low/GraphicsPipeline.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/GraphicsPipelineCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
GraphicsPipeline::GraphicsPipeline(const GraphicsPipelineCreateInfo& createInfo)
: device_(base::PtrToRef(createInfo.Device()))
, nativeObject_() {}


//------------------------------------------------------------------------------
GraphicsPipeline::~GraphicsPipeline() {}

} // namespace gfx_low
} // namespace ae
// EOF
