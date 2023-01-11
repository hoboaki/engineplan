// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_PodSTRUCT_HPP)
#else
#define AE_BASE_INCLUDED_PodSTRUCT_HPP

#include <ae/base/StaticAssert.hpp>
#include <ae/base/TypeTraits.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Types
//@{
/// @brief PodClassの既定クラスとなる構造体。
/// @details バイナリデータの定義で使うことを想定しています。
template <typename T>
struct PodStruct
{
    /// 値の型名。
    typedef T ValueType;

    /// @brief 既定値(0で初期化された値)を取得する。
    /// @return 初期化された値。
    static const ValueType DefaultValue() { return ValueType(); }

    /// @brief 値のポインタを取得。
    /// @return 値のポインタ。
    const ValueType* Ptr() const { return &ReadRef(); }
    ValueType* Ptr() { return &Ref(); } ///< @copydoc Ptr()const

    /// @brief コピーされた値を取得。
    /// @return コピーされた値。
    const ValueType Get() const { return ReadRef(); }

    /// @brief 値の参照を取得。
    /// @return 値の参照。
    const ValueType& ReadRef() const { return value_; }
    const ValueType& Ref() const { return value_; } ///< @copydoc readRef
    ValueType& Ref() { return value_; } ///< @copydoc readRef
    //@}

    /// @brief 暗黙変換の実装。
    /// @return 値の参照。
    operator const ValueType&() const { return ReadRef(); }

    /// @brief 暗黙変換の実装。
    /// @return 値の参照。
    operator ValueType&() { return Ref(); }

    // 値。直接アクセスすることは想定していない。
    ValueType value_;

private:
    AE_BASE_STATIC_ASSERT(
        TypeTraits::IsPod<ValueType>::Value); // Pod型のチェック。
};
//@}

} // namespace ae::base
#endif
// EOF
