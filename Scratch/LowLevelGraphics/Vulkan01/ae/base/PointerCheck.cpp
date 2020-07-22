// 文字コード：UTF-8
#include <ae/base/PointerCheck.hpp>

#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
bool PointerCheck::IsValid(const_anyptr_t aPtr)
{
    return aPtr != 0;
}

//------------------------------------------------------------------------------
bool PointerCheck::InvalidCheck(const_anyptr_t aPtr)
{
    if (!IsValid(aPtr)) {
        AE_BASE_ERROR_INVALID_VALUE(aPtr);
        return true;
    }
    return false;
}

}} // namespace
// EOF
