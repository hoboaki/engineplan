// 文字コード：UTF-8
#pragma once

#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

/// Enum を Key とした配列。
/// @tparam TEnumType キーとなる Enum 型。TERM の定義が必要。
/// @tparam TValue
/// 値となる型。デフォルトコンストラクタによる初期化が可能な型に限る。
template <typename TEnumType, typename TValueType>
class EnumKeyArray {
public:
    /// @name 型定義
    //@{
    /// Key-Value の Key となる Enum 型。
    using EnumType = TEnumType;

    /// Key-Value の Value となる型。
    using ValueType = TValueType;
    //@}

    /// @name コンストラクタ
    //@{
    EnumKeyArray()
    : values_()
    {
    }
    //@}

    /// @name API
    //@{
    /// 配列の総数。
    constexpr int Count() const { return int(EnumType::TERM); }

    /// 指定番目の要素にアクセス。
    ValueType& At(const int index)
    {
        if (index < 0 || Count() <= index) {
            AE_BASE_ASSERT_MIN_TERM(index, 0, Count());
            return values_[0]; // fail safe code
        }
        return values_[index];
    }

    /// 指定番目の要素にアクセス。
    const ValueType& At(const int index) const
    {
        if (index < 0 || Count() <= index) {
            AE_BASE_ASSERT_MIN_TERM(index, 0, Count());
            return values_[0]; // fail safe code
        }
        return values_[index];
    }

    /// 指定キーの要素にアクセス。
    ValueType& At(const EnumType enumValue) { return At(int(enumValue)); }

    /// 指定キーの要素にアクセス。
    const ValueType& At(const EnumType enumValue) const
    {
        return At(int(enumValue));
    }

    /// 指定の値を全要素に代入。
    void Fill(const ValueType& value)
    {
        for (int i = 0; i < Count(); ++i) {
            values_[i] = value;
        }
    }
    //@}

    /// @name 演算子オーバーロード
    //@{
    /// At() のエイリアス。
    ValueType& operator[](const int index) { return At(index); }

    /// At()const のエイリアス。
    const ValueType& operator[](const int index) const { return At(index); }

    /// At() のエイリアス。
    ValueType& operator[](const EnumType enumValue) { return At(enumValue); }

    /// At()const のエイリアス。
    const ValueType& operator[](const EnumType enumValue) const
    {
        return At(enumValue);
    }
    //@}

    ValueType values_[static_cast<int>(TEnumType::TERM)];
};

} // namespace ae::base
// EOF
