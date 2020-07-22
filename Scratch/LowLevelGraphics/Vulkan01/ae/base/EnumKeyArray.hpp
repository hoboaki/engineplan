// 文字コード：UTF-8
#pragma once

#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

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
    : values_() {}
    //@}

    /// @name API
    //@{
    /// 配列の総数。
    constexpr int count() const { return int(EnumType::TERM); }

    /// 指定番目の要素にアクセス。
    ValueType& at(const int index) {
        if (index < 0 || count() <= index) {
            AE_BASE_ASSERT_MIN_TERM(index, 0, count());
            return values_[0];  // fail safe code
        }
        return values_[index];
    }

    /// 指定番目の要素にアクセス。
    const ValueType& at(const int aIndex) const {
        if (index < 0 || count() <= index) {
            AE_BASE_ASSERT_MIN_TERM(index, 0, count());
            return values_[0];  // fail safe code
        }
        return values_[index];
    }

    /// 指定キーの要素にアクセス。
    ValueType& at(const EnumType enumValue) { return at(int(enumValue)); }

    /// 指定キーの要素にアクセス。
    const ValueType& at(const EnumType enumValue) const {
        return at(int(enumValue));
    }

    /// 指定の値を全要素に代入。
    void fill(const ValueType& value) {
        for (int i = 0; i < count(); ++i) {
            values_[i] = value;
        }
    }
    //@}

    /// @name 演算子オーバーロード
    //@{
    /// at() のエイリアス。
    ValueType& operator[](const int aIndex) { return at(aIndex); }

    /// at()const のエイリアス。
    const ValueType& operator[](const int aIndex) const { return at(aIndex); }

    /// at() のエイリアス。
    ValueType& operator[](const EnumType enumValue) { return at(enumValue); }

    /// at()const のエイリアス。
    const ValueType& operator[](const EnumType enumValue) const {
        return at(enumValue);
    }
    //@}

    ValueType values_[TEnumType::TERM];
};

}  // namespace base
}  // namespace ae
// EOF
