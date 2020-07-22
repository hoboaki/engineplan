// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_SCALERSTRUCT_HPP)
#else
#define AE_BASE_INCLUDED_SCALERSTRUCT_HPP

#include <limits>
#include <ae/base/PodStruct.hpp>
#include <ae/base/ShortString.hpp>
#include <ae/base/ShortStringFactory.hpp>
#include <ae/base/StaticAssert.hpp>
#include <ae/base/TypeTraits.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Types
//@{
/// Scaler型のPodラッパーテンプレート構造体。
template< typename T >
struct ScalerStruct : public PodStruct<T>
{
    static typename PodStruct<T>::ValueType MaxValue() { return std::numeric_limits< typename PodStruct<T>::ValueType >::max(); } ///< 最大値を取得する。 @return 最大値。
    static typename PodStruct<T>::ValueType MinValue() { return std::numeric_limits< typename PodStruct<T>::ValueType >::min(); } ///< 最小値を取得する。 @return 最小値。

    /// ShortStringに変換する。@return 変換された文字列。
    const ShortString toShortString()const { return ::ae::base::ShortStringFactory::Create(PodStruct<T>::readRef()); }

private:
    typedef ::ae::base::PodStruct< T > SuperStruct; // 親クラスのエイリアス。
    AE_BASE_STATIC_ASSERT(TypeTraits::IsPod< SuperStruct >::Value); // Pod型のチェック。
    AE_BASE_STATIC_ASSERT(sizeof(SuperStruct) == sizeof(ValueType)); // サイズが同じであることを保証。        
};
//@}

}} // namespace
#endif
// EOF
