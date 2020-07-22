// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_PodCLASS_HPP)
#else
#define AE_BASE_INCLUDED_PodCLASS_HPP

#include <ae/base/PodStruct.hpp>
#include <ae/base/StaticAssert.hpp>
#include <ae/base/TypeTraits.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Types
//@{    
/// @brief Pod型のラッパーテンプレートクラス。
/// @details
/// boost::value_initializedのようにデフォルトコンストラクタで必ず初期化をすることで未初期化を防ぎます。
template< typename T >
class PodClass : public PodStruct<T>
{
public:
    /// Struct型のエイリアス。
    typedef ::ae::base::PodStruct<T> StructType;

    PodClass() { StructType::ref() = StructType::DefaultValue(); }   ///< 規定値で初期化される。
    PodClass(const PodStruct<T>& aValue) { StructType::ref() = aValue; } ///< 値を指定して初期化。

private:
    typedef StructType SuperClass;
    AE_BASE_STATIC_ASSERT(TypeTraits::IsPod< StructType >::Value);
    AE_BASE_STATIC_ASSERT(sizeof(SuperClass) == sizeof(ValueType)); // サイズが同じであることを保証。
};
//@}

}} // namespace
#endif
// EOF
