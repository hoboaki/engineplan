// 文字コード：UTF-8
#include <ae/base/ShortStringFactory.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
namespace {

// ShortString作成用テンプレート関数。
template <typename T>
const ShortString tToShortString(const char* format, const T& value)
{
    // note: ポインタチェックはFromtFormatでやっているので省略。
    return ShortString::FromFormat(format, value);
}

} // namespace

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const bool val)
{
    return ShortString(val ? "true" : "false");
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const int val)
{
    return tToShortString("%d", val);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const u32 val)
{
    return tToShortString("%u", val);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const f32 val)
{
    return tToShortString("%f", val);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const f64 val)
{
    return tToShortString("%f", val);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const s8 val)
{
    return tToShortString("%hhd", val);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const s16 val)
{
    return tToShortString("%hd", val);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const s64 val)
{
    return tToShortString("%lld", val);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const u8 val)
{
    return tToShortString("%hhu", val);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const u16 val)
{
    return tToShortString("%hu", val);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const u64 val)
{
    return tToShortString("%llu", val);
}

//------------------------------------------------------------------------------
#if !defined(AE_BASE_OS_WINDOWS)
const ShortString ShortStringFactory::Create(pword_t val)
{
    if (sizeof(pword_t) == 4) {
        return Create(u32(val));
    } else {
        return Create(u64(val));
    }
}
#endif

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(ptr_t ptr)
{
    return tToShortString("%p", ptr);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const_ptr_t ptr)
{
    return tToShortString("%p", ptr);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(anyptr_t ptr)
{
    return tToShortString("%p", ptr);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const_anyptr_t ptr)
{
    return tToShortString("%p", ptr);
}

//------------------------------------------------------------------------------
const ShortString ShortStringFactory::Create(const char* ptr)
{
    return tToShortString("%s", ptr);
}

} // namespace ae::base
// EOF
