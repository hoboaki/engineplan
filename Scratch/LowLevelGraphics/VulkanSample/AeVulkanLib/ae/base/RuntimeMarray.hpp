// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_RuntimeMarray_HPP)
#else
#define AE_BASE_INCLUDED_RuntimeMarray_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/Noncopyable.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Collection
//@{
/// 実行時に最大要素数が決定する可変長配列。
template <typename T>
class RuntimeMarray : ::ae::base::Noncopyable<RuntimeMarray<T>> {
public:
    /// @name typedef
    //@{
    typedef T ValueType;
    //@}

    /// @name コンストラクタとデストラクタ
    //@{

    /// @brief コンストラクタ。
    /// @param countMax 最大配列長。
    /// @param allocator 配列データを確保する際に使用するアロケータ。
    /// @details
    /// 配列長が0の場合、アロケートは走りません。
    RuntimeMarray(int countMax, IAllocator& allocator = IAllocator::Default())
    : allocator_(allocator)
    , countMax_(countMax)
    , count_(0)
    , ptr_(0)
    {
        if (0 < countMax) {
            ptr_ = reinterpret_cast<ValueType*>(
                allocator_.Alloc(sizeof(ValueType) * countMax));
        }
    }

    /// デストラクタ。
    ~RuntimeMarray()
    {
        if (ptr_ != 0) {
            // 逆順でデストラクタを呼び出す
            for (int i = count_; 0 < i; --i) {
                const int idx = i - 1;
                At(idx).~ValueType();
            }

            ValueType* ptr = ptr_;
            ptr_ = 0;
            allocator_.Free(reinterpret_cast<ptr_t>(ptr));
        }
    }

    //@}

    /// @name アクセス
    //@{
    /// 要素が１つもない状態か。
    bool IsEmpty() const { return count_ == 0; }

    /// 要素数が最大の状態か。
    bool IsFull() const { return count_ == countMax_; }

    /// 現在の要素数。
    int Count() const { return count_; }

    /// 最大の要素数。
    int CountMax() const { return countMax_; }

    /// 指定番目の要素にアクセス。
    ValueType& At(const int index)
    {
        if (count_ <= index) {
            AE_BASE_ASSERT_LESS(index, count_);
            return ptr_[0]; // fail safe code
        }
        return ptr_[index];
    }

    /// 指定番目の要素にアクセス。
    const ValueType& At(const int index) const
    {
        if (count_ <= index) {
            AE_BASE_ASSERT_LESS(index, count_);
            return ptr_[0]; // fail safe code
        }
        return ptr_[index];
    }

    /// 最初の要素にアクセス。
    ValueType& First() { return At(0); }
    /// @copydoc First()
    const ValueType& First() const { return At(0); }

    /// 最後の要素にアクセス。
    ValueType& Last() { return At(count_ - 1); }
    /// @copydoc Last()
    const ValueType& Last() const { return At(count_ - 1); }

    //@}

    /// @name 要素の追加と削除
    //@{

    /// 全ての要素を削除する。
    void Clear() { count_ = 0; }

    /// 指定の要素を末尾に追加する。
    void Add(const ValueType& val)
    {
        if (IsFull()) {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        ptr_[count_] = val;
        ++count_;
    }

    //@}

    /// @name イテレータ
    //@{
    ValueType* begin() { return ptr_; }
    const ValueType* begin() const { return ptr_; }
    ValueType* end() { return &ptr_[count_]; }
    const ValueType* end() const { return &ptr_[count_]; }
    //@}

    /// @name 演算子オーバーロード
    //@{
    ValueType& operator[](const int index)
    {
        return At(index);
    } ///< At() のエイリアス。
    const ValueType& operator[](const int index) const
    {
        return At(index);
    } ///< At()const のエイリアス。
    //@}

private:
    IAllocator& allocator_;
    const int countMax_;
    int count_;
    ValueType* ptr_;
};
//@}

} // namespace ae::base
#endif
// EOF
