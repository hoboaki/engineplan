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
        : mAllocator(PtrToRef(aAllocator))
        , mCountMax(aCountMax)
        , mCount(0)
        , mPtr(0)
    {
        if (0 < aCountMax)
        {
            mPtr = reinterpret_cast<ValueType*>(mAllocator.alloc(sizeof(ValueType) * aCountMax));
        }
    }

    /// 非推奨版。
    RuntimeAutoArray(
        int aCountMax, IAllocator& aAllocator = IAllocator::Default())
    : RuntimeAutoArray(aCountMax, &aAllocator) {}

    /// デストラクタ。
    ~RuntimeAutoArray()
    {
        // 全てをデストラクト
        clear();

        if (mPtr != 0)
        {
            ValueType* ptr = mPtr;
            mPtr = 0;
            mAllocator.free(reinterpret_cast<ptr_t>(ptr));
        }
    }

    //@}

    /// @name アクセス
    //@{
    /// 要素が１つもない状態か。
    bool isEmpty()const
    {
        return mCount == 0;
    }

    /// 要素数が最大の状態か。
    bool isFull()const
    {
        return mCount == mCountMax;
    }

    /// 現在の要素数。
    int count()const
    {
        return mCount;
    }

    /// 最大の要素数。
    int countMax()const
    {
        return mCountMax;
    }

    /// 指定番目の要素にアクセス。
    ValueType& at(const int aIndex)const
    {
        if (mCount <= aIndex)
        {
            AE_BASE_ASSERT_LESS(aIndex, mCount);
            return mPtr[0]; // fail safe code
        }
        return mPtr[aIndex];
    }

    /// 最初の要素にアクセス。
    ValueType& first() { return at(0); }
    /// @copydoc first()
    const ValueType& first()const { return at(0); }

    /// 最後の要素にアクセス。
    ValueType& last() { return at(mCount - 1); }
    /// @copydoc last()
    const ValueType& last()const { return at(mCount - 1); }

    //@}

    /// @name 要素の削除
    //@{

    /// 全ての要素を削除する。
    void clear()
    {
        if (mPtr == 0)
        {
            return;
        }

        // 逆順でデストラクタを呼び出す
        for (int i = mCount; 0 < i; --i)
        {
            const int idx = i - 1;
            at(idx).~ValueType();
        }
        mCount = 0;
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
        new (&mPtr[mCount]) ValueType();
        ++mCount;
    }
    template< typename A0 >
    void add(A0 a0)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&mPtr[mCount]) ValueType(a0);
        ++mCount;
    }
    template< typename A0, typename A1 >
    void add(A0 a0, A1 a1)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&mPtr[mCount]) ValueType(a0, a1);
        ++mCount;
    }
    template< typename A0, typename A1, typename A2 >
    void add(A0 a0, A1 a1, A2 a2)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&mPtr[mCount]) ValueType(a0, a1, a2);
        ++mCount;
    }
    template< typename A0, typename A1, typename A2, typename A3 >
    void add(A0 a0, A1 a1, A2 a2, A3 a3)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&mPtr[mCount]) ValueType(a0, a1, a2, a3);
        ++mCount;
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4 >
    void add(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&mPtr[mCount]) ValueType(a0, a1, a2, a3, a4);
        ++mCount;
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5 >
    void add(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&mPtr[mCount]) ValueType(a0, a1, a2, a3, a4, a5);
        ++mCount;
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6 >
    void add(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&mPtr[mCount]) ValueType(a0, a1, a2, a3, a4, a5, a6);
        ++mCount;
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7 >
    void add(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&mPtr[mCount]) ValueType(a0, a1, a2, a3, a4, a5, a6, a7);
        ++mCount;
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8 >
    void add(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&mPtr[mCount]) ValueType(a0, a1, a2, a3, a4, a5, a6, a7, a8);
        ++mCount;
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9 >
    void add(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        new (&mPtr[mCount]) ValueType(a0, a1, a2, a3, a4, a5, a6.a7, a8, a9);
        ++mCount;
    }

    //@}

    /// @name 演算子オーバーロード
    //@{
    ValueType& operator[](const int aIndex)const { return at(aIndex); } ///< at()const のエイリアス。
    //@}

private:
    IAllocator& mAllocator;
    const int  mCountMax;
    int        mCount;
    ValueType*  mPtr;
};
//@}

}} // namespace
#endif
// EOF
