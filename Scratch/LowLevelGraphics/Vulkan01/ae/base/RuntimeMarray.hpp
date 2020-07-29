// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_RuntimeMarray_HPP)
#else
#define AE_BASE_INCLUDED_RuntimeMarray_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/Noncopyable.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Collection
//@{
/// 実行時に最大要素数が決定する可変長配列。
template< typename T >
class RuntimeMarray : ::ae::base::Noncopyable<RuntimeMarray<T>>
{
public:
    /// @name typedef
    //@{
    typedef T ValueType;
    //@}

    /// @name コンストラクタとデストラクタ
    //@{

    /// @brief コンストラクタ。
    /// @param aCountMax 最大配列長。
    /// @param aAllocator 配列データを確保する際に使用するアロケータ。
    /// @details 
    /// 配列長が0の場合、アロケートは走りません。
    RuntimeMarray(int aCountMax, IAllocator& aAllocator = IAllocator::Default())
        : allocator_(aAllocator)
        , countMax_(aCountMax)
        , count_(0)
        , ptr_(0)
    {
        if (0 < aCountMax)
        {
            ptr_ = reinterpret_cast<ValueType*>(allocator_.alloc(sizeof(ValueType) * aCountMax));
        }
    }

    /// デストラクタ。
    ~RuntimeMarray()
    {
        if (ptr_ != 0)
        {
            // 逆順でデストラクタを呼び出す
            for (int i = count_; 0 < i; --i)
            {
                const int idx = i - 1;
                at(idx).~ValueType();
            }

            ValueType* ptr = ptr_;
            ptr_ = 0;
            allocator_.free(reinterpret_cast<ptr_t>(ptr));
        }
    }

    //@}

    /// @name アクセス
    //@{
    /// 要素が１つもない状態か。
    bool isEmpty()const
    {
        return count_ == 0;
    }

    /// 要素数が最大の状態か。
    bool isFull()const
    {
        return count_ == countMax_;
    }

    /// 現在の要素数。
    int count()const
    {
        return count_;
    }

    /// 最大の要素数。
    int countMax()const
    {
        return countMax_;
    }

    /// 指定番目の要素にアクセス。
    ValueType& at(const int aIndex)
    {
        if (count_ <= aIndex)
        {
            AE_BASE_ASSERT_LESS(aIndex, count_);
            return ptr_[0]; // fail safe code
        }
        return ptr_[aIndex];
    }

    /// 指定番目の要素にアクセス。
    const ValueType& at(const int aIndex)const
    {
        if (count_ <= aIndex)
        {
            AE_BASE_ASSERT_LESS(aIndex, count_);
            return ptr_[0]; // fail safe code
        }
        return ptr_[aIndex];
    }

    /// 最初の要素にアクセス。
    ValueType& first() { return at(0); }
    /// @copydoc first()
    const ValueType& first()const { return at(0); }

    /// 最後の要素にアクセス。
    ValueType& last() { return at(count_ - 1); }
    /// @copydoc last()
    const ValueType& last()const { return at(count_ - 1); }

    //@}

    /// @name 要素の追加と削除
    //@{

    /// 全ての要素を削除する。
    void clear()
    {
        count_ = 0;
    }

    /// 指定の要素を末尾に追加する。
    void add(const ValueType& aVal)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        ptr_[count_] = aVal;
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
    ValueType& operator[](const int aIndex) { return at(aIndex); } ///< at() のエイリアス。
    const ValueType& operator[](const int aIndex)const { return at(aIndex); } ///< at()const のエイリアス。
    //@}

private:
    IAllocator& allocator_;
    const int  countMax_;
    int        count_;
    ValueType*  ptr_;
};
//@}

}} // namespace
#endif
// EOF
