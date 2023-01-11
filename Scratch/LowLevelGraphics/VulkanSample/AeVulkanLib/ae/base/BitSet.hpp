// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_BITSET_HPP)
#else
#define AE_BASE_INCLUDED_BITSET_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Collection
//@{
/// @brief ビットを扱うコレクション(Pod版)。
/// @details
/// BIT_COUNTには扱うビット数を指定してください。 @n
/// ALIGNMENTには要求するアライメント値を指定してください。 @n
template <int BIT_COUNT, int ALIGNMENT = 4>
struct BitSetPod
{
    //============================================================
    // private
    enum
    {
        ByteSizeRaw_ = (BIT_COUNT + 7) / 8,
        ByteSize_ = ByteSizeRaw_ + (ALIGNMENT - 1) / ALIGNMENT
    };
    byte_t bits_[ByteSize_];

    //============================================================
    // public

    /// @name 型・定数
    //@{
    enum
    {
        BitCount = BIT_COUNT
    }; ///< ビット数。
    typedef BitSetPod<BitCount> MyType; ///< 自分自身の型。
    //@}

    /// @name 定数プロパティ
    //@{
    /// 全ビット true のオブジェクトを取得。
    static MyType AllOn()
    {
        MyType result;
        for (int i = 0; i < MyType::ByteSize_; ++i) {
            result.bits_[i] = 0xFF;
        }
        return result;
    }
    //@}

    /// @name 全ビットの操作
    //@{
    /// 全ビットをfalseにする。
    void Clear()
    {
        for (int i = 0; i < MyType::ByteSize_; ++i) {
            bits_[i] = 0;
        }
    }
    //@}

    /// @name 各ビットの設定・取得
    //@{
    /// 指定番目のビットの値を設定する。
    void Set(int index, bool flag)
    {
        // チェック
        if (BitCount <= index) {
            AE_BASE_ERROR_INVALID_VALUE(index);
            return;
        }

        // 設定
        byte_t& val = bits_[index >> 3];
        const byte_t mask = byte_t(1 << (index & 0x7));
        val = (val & ~mask) | (flag ? mask : 0);
    }

    /// 指定番目のビットをたてる。
    void On(int index) { Set(index, true); }

    /// 指定番目のビットをおろす。
    void Off(int index) { Set(index, false); }

    /// 指定番目のビットの値を取得する。
    bool Get(int index) const
    {
        // チェック
        if (BitCount <= index) {
            AE_BASE_ERROR_INVALID_VALUE(index);
            return bool();
        }

        // 取得
        const byte_t& val = bits_[index >> 3];
        const byte_t mask = byte_t(1 << (index & 0x7));
        return (val & mask) != 0 ? true : false;
    }
    /// 1つ以上のビットがたっているか。
    bool IsAnyOn() const
    {
        for (int i = 0; i < ByteSize_; ++i) {
            if (bits_[i] != 0) {
                return true;
            }
        }
        return false;
    }
    /// 全てのビットがたっていない状態か。
    bool IsAllOff() const { return !IsAnyOn(); }
    /// 全てのビットがたっている状態か。
    bool IsAllOn() const
    {
        for (int i = 0; i < BitCount; ++i) {
            if (!Get(i)) {
                return false;
            }
        }
        return true;
    }
    //@}

    /// @name 演算
    //@{
    /// ビットを反転した値を取得。
    const MyType operator~() const
    {
        MyType obj = *this;
        for (int i = 0; i < ByteSize_; ++i) {
            obj.bits_[i] = ~obj.bits_[i];
        }
        return obj;
    }

    /// 論理積を取得。
    const MyType operator&(const MyType& rHS) const
    {
        MyType obj = *this;
        for (int i = 0; i < ByteSize_; ++i) {
            obj.bits_[i] = bits_[i] & rHS.bits_[i];
        }
        return obj;
    }

    /// 論理和を取得。
    const MyType operator|(const MyType& rHS) const
    {
        MyType obj = *this;
        for (int i = 0; i < ByteSize_; ++i) {
            obj.bits_[i] = bits_[i] | rHS.bits_[i];
        }
        return obj;
    }

    /// 排他的論理和を取得。
    const MyType operator^(const MyType& rHS) const
    {
        MyType obj = *this;
        for (int i = 0; i < ByteSize_; ++i) {
            obj.bits_[i] = bits_[i] ^ rHS.bits_[i];
        }
        return obj;
    }
    //@}
};

/// BitSetPod のクラス版。
template <int BIT_COUNT, int ALIGNMENT = 4>
class BitSet : public BitSetPod<BIT_COUNT, ALIGNMENT> {
public:
    /// @name コンストラクタ
    //@{
    /// 全てoffの状態で作成。
    BitSet() { BitSetPod<BIT_COUNT, ALIGNMENT>::Clear(); }

    /// コピーして作成。
    BitSet(const BitSetPod<BIT_COUNT, ALIGNMENT>& obj)
    {
        static_cast<BitSetPod<BIT_COUNT, ALIGNMENT>&>(*this) = obj;
    }

    //@}
};
//@}

} // namespace ae::base
#endif
// EOF
