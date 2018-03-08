// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_RUNTIMEARRAY_HPP)
#else
#define AE_BASE_INCLUDED_RUNTIMEARRAY_HPP

#include <ae/base/Compiler.hpp>
#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Collection
//@{
/// 実行時に確保する大きさが決まる配列。
template< typename T >
class RuntimeArray : public ::ae::base::NonCopyable
{
public:
    /// @name typedef
    //@{
    typedef T ValueType;
    //@}

    /// @name コンストラクタとデストラクタ
    //@{

    /// @brief コンストラクタ。
    /// @param aCount 配列長。
    /// @param aAllocator 配列データを確保する際に使用するアロケータ。
    /// @details 
    /// 配列長が0の場合、アロケートは走りません。
    RuntimeArray(int aCount, IAllocator& aAllocator = IAllocator::Default())
        : mAllocator(aAllocator)
        , mCount(aCount)
        , mPtr(0)
    {
        if (0 < mCount)
        {
            mPtr = reinterpret_cast<ValueType*>(mAllocator.alloc(sizeof(ValueType) * mCount));

            for (int i = 0; i < aCount; ++i)
            {
            #if defined(AE_BASE_COMPILER_MSVC)
            #pragma warning(push)
            #pragma warning(disable: 4345)
            #endif
                new (&at(i)) ValueType(); // 初期値で初期化                    
            #if defined(AE_BASE_COMPILER_MSVC)
            #pragma warning(pop)
            #endif
            }
        }
    }

    /// デストラクタ。
    ~RuntimeArray()
    {
        if (mPtr != 0)
        {
            // 逆順でデストラクタを呼び出す
            for (int i = mCount; 0 < i; --i)
            {
                at(i - 1).~ValueType();
            }

            ValueType* ptr = mPtr;
            mPtr = 0;
            mAllocator.free(reinterpret_cast<ptr_t>(ptr));
        }
    }

    //@}

    /// @name アクセス
    //@{
    /// 配列長。
    int count()const
    {
        return mCount;
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

    //@}

    /// @name 演算子オーバーロード
    //@{
    ValueType& operator[](const int aIndex) { return at(aIndex); } ///< at() のエイリアス。
    const ValueType& operator[](const int aIndex)const { return at(aIndex); } ///< at()const のエイリアス。
    //@}

private:
    IAllocator& mAllocator;
    const int  mCount;
    ValueType*  mPtr;
};
//@}

}} // namespace
#endif
// EOF
