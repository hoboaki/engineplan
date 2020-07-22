// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_REFERENCE_HPP)
#else
#define AE_BASE_INCLUDED_REFERENCE_HPP

#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Util
//@{
/// @brief Ref() 用の参照のラッパークラス。
/// @details
/// 通常は Ref() 関数を使うのでこのクラスを意識することはないはずです。
template< typename T >
class Reference
{
public:
    Reference(T& aRef)
        : mPtr(&aRef)
    {
    }

    operator T& ()const
    {
        AE_BASE_ASSERT_POINTER(mPtr);
        return *mPtr;
    }

private:
    T* mPtr;
};
//@}

}} // namespace
#endif
// EOF
