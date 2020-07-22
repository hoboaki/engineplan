// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_TYPETRAITS_HPP)
#else
#define AE_BASE_INCLUDED_TYPETRAITS_HPP

#include <ae/base/Compiler.hpp>

// type_traitsのインクルード
#if defined(AE_BASE_COMPILER_MSVC)
    #include <type_traits>
#endif

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Types
//@{
/// 型特性。
struct TypeTraits
{
#if defined(AE_BASE_COMPILER_MSVC)
    template< typename T >
    struct IsPod { enum { Value = ::std::is_pod< T >::value }; };

    template< typename T >
    struct IsScaler { enum { Value = ::std::is_scaler< T >::value }; };
#else
        // サポートしていないコンパイラでは常にtrueを返す。
        /// Pod型。
    template< typename T > struct IsPod { enum { Value = true }; };
    /// スカラー型か。
    template< typename T > struct IsScaler { enum { Value = true }; };
#endif
};
//@}

}} // namespace
#endif
// EOF
