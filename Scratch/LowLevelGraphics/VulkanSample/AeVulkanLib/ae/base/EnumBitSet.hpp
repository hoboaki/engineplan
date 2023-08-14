// 文字コード：UTF-8
#pragma once

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <limits>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Collection
//@{
/// @brief Enum 値を Key とする BitSet(Pod版)。
/// @details
/// TEnumType には enum class の型を、TDataType には uint32_t
/// などフラグを管理するデータ型を指定してください。
template <typename TEnumType, typename TDataType>
struct EnumBitSetPod
{
    /// @name 内部処理用機能
    //@{
    TDataType bits_;
    //@}

    /// @name 型・定数
    //@{
    using EnumType = TEnumType; ///< キーとなる Enum の型。
    using DataType = TDataType; ///< フラグを保持するデータの型。
    using MyType = EnumBitSetPod<EnumType, DataType>; ///< 自分自身の型。
    static constexpr int BitCount = sizeof(DataType) * 8; ///< ビット数。
    //@}

    /// @name 定数プロパティ
    //@{
    /// 全ビット true のオブジェクトを取得。
    static constexpr MyType AllOn()
    {
        if (int(EnumType::TERM) == BitCount) {
            return MyType{ ::std::numeric_limits<DataType>::max() };
        }
        return MyType{ (DataType(1) << int(EnumType::TERM)) - 1 };
    }
    //@}

    /// @name 全ビットの操作
    //@{
    /// 全ビットをfalseにする。
    void Clear() { bits_ = 0; }
    //@}

    /// @name 各ビットの設定・取得
    //@{
    /// 指定番目のビットの値を設定する。
    MyType& Set(EnumType index, bool flag)
    {
        // チェック
        if (BitCount <= int(index)) {
            AE_BASE_ERROR_INVALID_VALUE(int(index));
            return *this;
        }

        // 設定
        const auto mask = DataType(1 << DataType(index));
        bits_ = (bits_ & ~mask) | (flag ? mask : 0);
        return *this;
    }

    /// 指定番目のビットをたてる。
    MyType& On(EnumType index) { return Set(index, true); }

    /// 指定番目のビットをおろす。
    MyType& Off(EnumType index) { return Set(index, false); }

    /// 指定番目のビットの値を取得する。
    bool Get(EnumType index) const
    {
        // チェック
        if (BitCount <= int(index)) {
            AE_BASE_ERROR_INVALID_VALUE(int(index));
            return bool();
        }

        // 取得
        const DataType mask = 1 << DataType(index);
        return (bits_ & mask) != 0 ? true : false;
    }

    /// 1つ以上のビットがたっているか。
    bool IsAnyOn() const { return bits_ != 0; }
    /// 全てのビットがたっていない状態か。
    bool IsAllOff() const { return !IsAnyOn(); }
    /// 全てのビットがたっている状態か。
    bool IsAllOn() const
    {
        const auto allOnBits = IsAllOn().bits_;
        return (allOnBits & bits_) == allOnBits;
    }
    //@}

    /// @name 演算
    //@{
    /// ビットを反転した値を取得。
    const MyType operator~() const { return MyType{ ~bits_ }; }

    /// 論理積を取得。
    const MyType operator&(const MyType& rhs) const
    {
        return MyType{ bits_ & rhs.bits_ };
    }

    /// 論理和を取得。
    const MyType operator|(const MyType& rhs) const
    {
        return MyType{ bits_ | rhs.bits_ };
    }

    /// 排他的論理和を取得。
    const MyType operator^(const MyType& rhs) const
    {
        return MyType{ bits_ ^ rhs.bits_ };
    }
    //@}
};

/// EnumBitSetPod のクラス版。
template <typename TEnumType, typename TDataType>
class EnumBitSet : public EnumBitSetPod<TEnumType, TDataType> {
public:
    /// @name コンストラクタ
    //@{
    /// 全てoffの状態で作成。
    EnumBitSet() { EnumBitSetPod<TEnumType, TDataType>::Clear(); }

    /// コピーして作成。
    EnumBitSet(const EnumBitSetPod<TEnumType, TDataType>& obj)
    {
        static_cast<EnumBitSetPod<TEnumType, TDataType>&>(*this) = obj;
    }

    //@}
};
//@}

/// 32bit版 EnumBitSetPod。
template <typename TEnumType>
using EnumBitSetPod32 = EnumBitSetPod<TEnumType, uint32_t>;

/// 32bit版 EnumBitSet。
template <typename TEnumType>
using EnumBitSet32 = EnumBitSet<TEnumType, uint32_t>;

} // namespace ae::base
// EOF
