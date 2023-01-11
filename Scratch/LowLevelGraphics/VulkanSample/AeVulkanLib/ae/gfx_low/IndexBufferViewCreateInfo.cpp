// 文字コード：UTF-8
#include <ae/gfx_low/IndexBufferViewCreateInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
IndexBufferViewCreateInfo& IndexBufferViewCreateInfo::SetFormat(
    const IndexFormat format)
{
    AE_BASE_ASSERT_ENUM(format, IndexFormat);
    AE_BASE_ASSERT(format != IndexFormat::Invalid);
    format_ = format;
    return *this;
}

} // namespace ae::gfx_low
// EOF
