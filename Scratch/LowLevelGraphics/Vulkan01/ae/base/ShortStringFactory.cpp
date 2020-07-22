// 文字コード：UTF-8
#include <ae/base/ShortStringFactory.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
namespace {

// ShortString作成用テンプレート関数。
template< typename T >
const ShortString tToShortString(const char* aFormat, const T& aValue)
{
    // note: ポインタチェックはFromtFormatでやっているので省略。
    return ShortString::FromFormat(
        aFormat,
        aValue
        );
}

} // namespace

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const bool aVal)
{
    return ShortString(aVal ? "true" : "false");
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const int aVal)
{
    return tToShortString("%d", aVal);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const u32 aVal)
{
    return tToShortString("%u", aVal);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const f32 aVal)
{
    return tToShortString("%f", aVal);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const f64 aVal)
{
    return tToShortString("%f", aVal);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const s8 aVal)
{
    return tToShortString("%hhd", aVal);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const s16 aVal)
{
    return tToShortString("%hd", aVal);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const s64 aVal)
{
    return tToShortString("%lld", aVal);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const u8 aVal)
{
    return tToShortString("%hhu", aVal);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const u16 aVal)
{
    return tToShortString("%hu", aVal);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const u64 aVal)
{
    return tToShortString("%llu", aVal);
}

//------------------------------------------------------------------------------
#if !defined(AE_BASE_OS_WINDOWS)
const ShortString ShortStringFactory::Create(pword_t aVal)
{
    if (sizeof(pword_t) == 4) {
        return Create(u32(aVal));
    }
    else
    {
        return Create(u64(aVal));
    }
}
#endif

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(ptr_t aPtr)
{
    return tToShortString("%p", aPtr);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const_ptr_t aPtr)
{
    return tToShortString("%p", aPtr);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(anyptr_t aPtr)
{
    return tToShortString("%p", aPtr);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const_anyptr_t aPtr)
{
    return tToShortString("%p", aPtr);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const char* aPtr)
{
    return tToShortString("%s", aPtr);
}

}} // namespace
// EOF
