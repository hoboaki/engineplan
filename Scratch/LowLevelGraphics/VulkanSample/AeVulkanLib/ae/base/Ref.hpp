// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_REF_HPP)
#else
#define AE_BASE_INCLUDED_REF_HPP

#include <ae/base/Reference.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Util
//@{
/// std::tr1::ref と同じ役割の関数。
template <typename T>
const Reference<T> Ref(T& obj)
{
    return Reference<T>(obj);
}
//@}

} // namespace ae::base
#endif
// EOF
