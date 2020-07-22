// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_PodSTRUCT_HPP)
#else
#define AE_BASE_INCLUDED_PodSTRUCT_HPP

#include <ae/base/StaticAssert.hpp>
#include <ae/base/TypeTraits.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Types
//@{
/// @brief PodClassの既定クラスとなる構造体。
/// @details バイナリデータの定義で使うことを想定しています。
template< typename T >
struct PodStruct
{
    /// 値の型名。
    typedef T ValueType;

    /// @brief 既定値(0で初期化された値)を取得する。
    /// @return 初期化された値。
    static const ValueType DefaultValue() { return ValueType(); }

    /// @brief 値のポインタを取得。
    /// @return 値のポインタ。
    const ValueType* ptr()const { return &readRef(); }
    ValueType*       ptr() { return &ref(); }     ///< @copydoc ptr()const

    /// @brief コピーされた値を取得。
    /// @return コピーされた値。
    const ValueType  get()const { return readRef(); }

    /// @brief 値の参照を取得。
    /// @return 値の参照。
    const ValueType& readRef()const { return value_; }
    const ValueType& ref()const { return value_; } ///< @copydoc readRef
    ValueType&       ref() { return value_; } ///< @copydoc readRef
    //@}

    /// @brief 暗黙変換の実装。
    /// @return 値の参照。
    operator const ValueType& ()const { return readRef(); }

    /// @brief 暗黙変換の実装。
    /// @return 値の参照。
    operator ValueType& () { return ref(); }

    // 値。直接アクセスすることは想定していない。
    ValueType value_;

private:
    AE_BASE_STATIC_ASSERT(TypeTraits::IsPod< typename ValueType >::Value);         // Pod型のチェック。
};
//@}

}} // namespace
#endif
// EOF
