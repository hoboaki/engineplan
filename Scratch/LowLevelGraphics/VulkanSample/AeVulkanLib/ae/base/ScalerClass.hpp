// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_SCALERCLASS_HPP)
#else
#define AE_BASE_INCLUDED_SCALERCLASS_HPP

#include <ae/base/ScalerStruct.hpp>
#include <ae/base/StaticAssert.hpp>
#include <ae/base/TypeTraits.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Types
//@{
/// @brief Scaler型のラッパーテンプレートクラス。
/// @copydetails PodClass
template <typename T>
class ScalerClass : public ScalerStruct<T> {
public:
    /// @name コンストラクタ
    //@{
    /// 既定値で初期化する。
    ScalerClass()
    : SuperClass()
    {
    }

    /// 指定された値で初期化する。
    ScalerClass(const typename ScalerStruct<T>::ValueType value)
    {
        SuperClass::value_ = value;
    };
    //@}

private:
    typedef ::ae::base::ScalerStruct<T> SuperClass; // 親クラスのエイリアス。
    AE_BASE_STATIC_ASSERT(
        sizeof(SuperClass) ==
        sizeof(SuperClass::ValueType)); // サイズが同じであることを保証。
};
//@}

} // namespace ae::base
#endif
// EOF
