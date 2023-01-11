// 文字コード：UTF-8
#include <ae/base/PointerCheck.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
bool PointerCheck::IsValid(const_anyptr_t ptr)
{
    return ptr != 0;
}

//------------------------------------------------------------------------------
bool PointerCheck::InvalidCheck(const_anyptr_t ptr)
{
    if (!IsValid(ptr)) {
        AE_BASE_ERROR_INVALID_VALUE(ptr);
        return true;
    }
    return false;
}

} // namespace ae::base
// EOF
