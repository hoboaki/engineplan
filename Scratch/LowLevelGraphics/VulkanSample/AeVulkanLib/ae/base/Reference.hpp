// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_REFERENCE_HPP)
#else
#define AE_BASE_INCLUDED_REFERENCE_HPP

#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Util
//@{
/// @brief Ref() 用の参照のラッパークラス。
/// @details
/// 通常は Ref() 関数を使うのでこのクラスを意識することはないはずです。
template <typename T>
class Reference {
public:
    Reference(T& ref)
    : ptr_(&ref)
    {
    }

    operator T&() const
    {
        AE_BASE_ASSERT_POINTER(ptr_);
        return *ptr_;
    }

private:
    T* ptr_;
};
//@}

} // namespace ae::base
#endif
// EOF
