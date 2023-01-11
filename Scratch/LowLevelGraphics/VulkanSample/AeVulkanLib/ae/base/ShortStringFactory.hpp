// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_SHORTSTRINGFACTORY)
#else
#define AE_BASE_INCLUDED_SHORTSTRINGFACTORY

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/Os.hpp>
#include <ae/base/ShortString.hpp>
#include <ae/base/TypeTraits.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

// ShortStringを作る関数群。
class ShortStringFactory {
public:
    // 特殊化された関数達。
    static const ::ae::base::ShortString Create(bool val);
    static const ::ae::base::ShortString Create(int val);
    static const ::ae::base::ShortString Create(uint val);
    static const ::ae::base::ShortString Create(f32 val);
    static const ::ae::base::ShortString Create(f64 val);
    static const ::ae::base::ShortString Create(s8 val);
    static const ::ae::base::ShortString Create(s16 val);
    static const ::ae::base::ShortString Create(s64 val);
    static const ::ae::base::ShortString Create(u8 val);
    static const ::ae::base::ShortString Create(u16 val);
    static const ::ae::base::ShortString Create(u64 val);
#if !defined(AE_BASE_OS_WINDOWS)
    static const ::ae::base::ShortString Create(pword_t val);
#endif
    static const ::ae::base::ShortString Create(ptr_t val);
    static const ::ae::base::ShortString Create(const_ptr_t val);
    static const ::ae::base::ShortString Create(anyptr_t val);
    static const ::ae::base::ShortString Create(const_anyptr_t val);
    static const ::ae::base::ShortString Create(const char* val);

    // デフォルトの実装。toShortString関数を使う。
    template <typename T, class Cond = void>
    class Impl {
    public:
        static const ::ae::base::ShortString Create(const T& obj)
        {
            return obj.ToShortString();
        }
    };

    // 特殊化できなかったものは、Implに委譲。
    template <typename T>
    static const ::ae::base::ShortString Create(const T& obj)
    {
        return Impl<T>::Create(obj);
    };
};

} // namespace ae::base
#endif
// EOF
