// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_RUNTIMEAUTOARRAY_HPP)
#else
#define AE_BASE_INCLUDED_RUNTIMEAUTOARRAY_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Collection
//@{
/// @brief 実行時に最大要素数が決定するAutoPtr配列。
template< typename T >
class RuntimeAutoArray : ::ae::base::Noncopyable<RuntimeAutoArray<T>>
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
    RuntimeAutoArray(
        int aCountMax, IAllocator* aAllocator = &IAllocator::Default()
        )
        : allocator_(PtrToRef(aAllocator))
        , countMax_(aCountMax)
        , count_(0)
        , ptr_(0)
    {
        if (0 < aCountMax)
        {
            ptr_ = reinterpret_cast<ValueType*>(allocator_.alloc(sizeof(ValueType) * aCountMax));
        }
    }

    /// 非推奨版。
    RuntimeAutoArray(
        int aCountMax, IAllocator& aAllocator)
    : RuntimeAutoArray(aCountMax, &aAllocator) {}

    /// デストラクタ。
    ~RuntimeAutoArray()
    {
        // 全てをデストラクト
        clear();

        if (ptr_ != 0)
        {
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
    ValueType& at(const int aIndex)const
    {
        if (aIndex < 0 || count_ <= aIndex)
        {
            AE_BASE_ASSERT_MIN_TERM(aIndex, 0, count_);
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

    /// @name 要素の削除
    //@{

    /// 全ての要素を削除する。
    void clear()
    {
        if (ptr_ == 0)
        {
            return;
        }

        // 逆順でデストラクタを呼び出す
        for (int i = count_; 0 < i; --i)
        {
            const int idx = i - 1;
            at(idx).~ValueType();
        }
        count_ = 0;
    }

    //@}

    /// @name 要素の追加
    //@{

    void add()
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&ptr_[count_]) ValueType();
        ++count_;
    }
    template< typename A0 >
    void add(A0 a0)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&ptr_[count_]) ValueType(a0);
        ++count_;
    }
    template< typename A0, typename A1 >
    void add(A0 a0, A1 a1)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&ptr_[count_]) ValueType(a0, a1);
        ++count_;
    }
    template< typename A0, typename A1, typename A2 >
    void add(A0 a0, A1 a1, A2 a2)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&ptr_[count_]) ValueType(a0, a1, a2);
        ++count_;
    }
    template< typename A0, typename A1, typename A2, typename A3 >
    void add(A0 a0, A1 a1, A2 a2, A3 a3)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&ptr_[count_]) ValueType(a0, a1, a2, a3);
        ++count_;
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4 >
    void add(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&ptr_[count_]) ValueType(a0, a1, a2, a3, a4);
        ++count_;
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5 >
    void add(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&ptr_[count_]) ValueType(a0, a1, a2, a3, a4, a5);
        ++count_;
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6 >
    void add(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&ptr_[count_]) ValueType(a0, a1, a2, a3, a4, a5, a6);
        ++count_;
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7 >
    void add(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&ptr_[count_]) ValueType(a0, a1, a2, a3, a4, a5, a6, a7);
        ++count_;
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8 >
    void add(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&ptr_[count_]) ValueType(a0, a1, a2, a3, a4, a5, a6, a7, a8);
        ++count_;
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9 >
    void add(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&ptr_[count_]) ValueType(a0, a1, a2, a3, a4, a5, a6.a7, a8, a9);
        ++count_;
    }

    //@}

    /// @name イテレータ
    //@{
    ValueType* begin() const { return ptr_; }
    ValueType* end() const { return &ptr_[count_]; }
    //@}

    /// @name 演算子オーバーロード
    //@{
    ValueType& operator[](const int aIndex)const { return at(aIndex); } ///< at()const のエイリアス。
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
