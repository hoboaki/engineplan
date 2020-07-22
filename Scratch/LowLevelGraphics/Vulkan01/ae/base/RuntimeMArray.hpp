// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_RUNTIMEMARRAY_HPP)
#else
#define AE_BASE_INCLUDED_RUNTIMEMARRAY_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Collection
//@{
/// 実行時に最大要素数が決定する可変長配列。
template< typename T >
class RuntimeMArray : public ::ae::base::NonCopyable
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
    RuntimeMArray(int aCountMax, IAllocator& aAllocator = IAllocator::Default())
        : mAllocator(aAllocator)
        , mCountMax(aCountMax)
        , mCount(0)
        , mPtr(0)
    {
        if (0 < aCountMax)
        {
            mPtr = reinterpret_cast<ValueType*>(mAllocator.alloc(sizeof(ValueType) * aCountMax));
        }
    }

    /// デストラクタ。
    ~RuntimeMArray()
    {
        if (mPtr != 0)
        {
            // 逆順でデストラクタを呼び出す
            for (int i = mCount; 0 < i; --i)
            {
                const int idx = i - 1;
                at(idx).~ValueType();
            }

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
    ValueType& at(const int aIndex)
    {
        if (mCount <= aIndex)
        {
            AE_BASE_ASSERT_LESS(aIndex, mCount);
            return mPtr[0]; // fail safe code
        }
        return mPtr[aIndex];
    }

    /// 指定番目の要素にアクセス。
    const ValueType& at(const int aIndex)const
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

    /// @name 要素の追加と削除
    //@{

    /// 全ての要素を削除する。
    void clear()
    {
        mCount = 0;
    }

    /// 指定の要素を末尾に追加する。
    void add(const ValueType& aVal)
    {
        if (isFull())
        {
            AE_BASE_ASSERT_NOT_REACHED();
            return;
        }
        mPtr[mCount] = aVal;
        ++mCount;
    }

    //@}

    /// @name 演算子オーバーロード
    //@{
    ValueType& operator[](const int aIndex) { return at(aIndex); } ///< at() のエイリアス。
    const ValueType& operator[](const int aIndex)const { return at(aIndex); } ///< at()const のエイリアス。
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
