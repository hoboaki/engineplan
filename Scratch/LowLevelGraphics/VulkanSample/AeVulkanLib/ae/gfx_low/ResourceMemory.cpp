// 文字コード：UTF-8
#include <ae/gfx_low/ResourceMemory.hpp>

// includes
#include <ae/gfx_low/ResourceMemoryAddress.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

//------------------------------------------------------------------------------
ResourceMemoryAddress ResourceMemory::Address(const size_t offset) const
{
    return ResourceMemoryAddress(*this, offset);
}

} // namespace ae::gfx_low
// EOF
