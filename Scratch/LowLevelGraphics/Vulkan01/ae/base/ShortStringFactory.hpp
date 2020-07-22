// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_SHORTSTRINGFACTORY)
#else
#define AE_BASE_INCLUDED_SHORTSTRINGFACTORY

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/Os.hpp>
#include <ae/base/ShortString.hpp>
#include <ae/base/TypeTraits.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

// ShortStringを作る関数群。
class ShortStringFactory
{
public:
    // 特殊化された関数達。
    static const ::ae::base::ShortString Create(bool aVal);
    static const ::ae::base::ShortString Create(int aVal);
    static const ::ae::base::ShortString Create(uint aVal);
    static const ::ae::base::ShortString Create(f32 aVal);
    static const ::ae::base::ShortString Create(f64 aVal);
    static const ::ae::base::ShortString Create(s8 aVal);
    static const ::ae::base::ShortString Create(s16 aVal);
    static const ::ae::base::ShortString Create(s64 aVal);
    static const ::ae::base::ShortString Create(u8 aVal);
    static const ::ae::base::ShortString Create(u16 aVal);
    static const ::ae::base::ShortString Create(u64 aVal);
#if !defined(AE_BASE_OS_WINDOWS)
    static const ::ae::base::ShortString Create(pword_t aVal);
#endif
    static const ::ae::base::ShortString Create(ptr_t aVal);
    static const ::ae::base::ShortString Create(const_ptr_t aVal);
    static const ::ae::base::ShortString Create(anyptr_t aVal);
    static const ::ae::base::ShortString Create(const_anyptr_t aVal);
    static const ::ae::base::ShortString Create(const char* aVal);

    // デフォルトの実装。toShortString関数を使う。
    template< typename T, class Cond = void >
    class Impl
    {
    public:
        static const ::ae::base::ShortString Create(const T& aObj)
        {
            return aObj.toShortString();
        }
    };

    // 特殊化できなかったものは、Implに委譲。
    template< typename T >
    static const ::ae::base::ShortString Create(const T& aObj)
    {
        return Impl< T >::Create(aObj);
    };
};


}} // namespace
#endif
// EOF
