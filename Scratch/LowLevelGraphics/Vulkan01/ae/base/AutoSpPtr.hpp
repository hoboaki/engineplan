// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_AUTOSPPTR_HPP)
#else
#define AE_BASE_INCLUDED_AUTOSPPTR_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/Pointer.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Memory
//@{
/// AutoPtrのAllocator指定版。
template< typename T >
class AutoSpPtr
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// デフォルトで作成。
    AutoSpPtr()
    {
    }

    /// 0引数 init() で作成。
    AutoSpPtr(::ae::base::IAllocator& aAllocator)
    {
        init(aAllocator);
    }

    /// 1引数 init() で作成。
    template< typename A0 >
    AutoSpPtr(::ae::base::IAllocator& aAllocator, A0 a0)
    {
        init(aAllocator, a0);
    }

    /// 2引数 init() で作成。
    template< typename A0, typename A1 >
    AutoSpPtr(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1)
    {
        init(aAllocator, a0, a1);
    }

    /// 3引数 init() で作成。
    template< typename A0, typename A1, typename A2 >
    AutoSpPtr(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1, A2 a2)
    {
        init(aAllocator, a0, a1, a2);
    }

    /// 4引数 init() で作成。
    template< typename A0, typename A1, typename A2, typename A3 >
    AutoSpPtr(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1, A2 a2, A3 a3)
    {
        init(aAllocator, a0, a1, a2, a3);
    }

    /// 5引数 init() で作成。
    template< typename A0, typename A1, typename A2, typename A3, typename A4 >
    AutoSpPtr(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
    {
        init(aAllocator, a0, a1, a2, a3, a4);
    }

    /// 6引数 init() で作成。
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5 >
    AutoSpPtr(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
    {
        init(aAllocator, a0, a1, a2, a3, a4, a5);
    }

    /// 7引数 init() で作成。
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6 >
    AutoSpPtr(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
    {
        init(aAllocator, a0, a1, a2, a3, a4, a5, a6);
    }

    /// 8引数 init() で作成。
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7 >
    AutoSpPtr(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
    {
        init(aAllocator, a0, a1, a2, a3, a4, a5, a6, a7);
    }

    /// 9引数 init() で作成。
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8 >
    AutoSpPtr(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
    {
        init(aAllocator, a0, a1, a2, a3, a4, a5, a6, a7, a8);
    }

    /// 10引数 init() で作成。
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9 >
    AutoSpPtr(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
    {
        init(aAllocator, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }

    /// 破棄責任を委譲して作成。
    AutoSpPtr(const AutoSpPtr<T>& aPtr)
    {
        *this = aPtr;
    }

    /// 破棄責任を委譲して作成。
    template< typename OtherType >
    AutoSpPtr(const AutoSpPtr<OtherType>& aPtr)
    {
        *this = aPtr;
    }

    /// デストラクタ
    ~AutoSpPtr()
    {
        reset();
    }

    //@}

    /// @name 取得
    //@{
    /// ポインタが設定されていなければtrueを返す。
    bool isNull()const
    {
        return mPtr.isNull();
    }

    /// ポインタが設定されていればtrueを返す。
    bool isValid()const
    {
        return mPtr.isValid();
    }

    /// ポインタの参照を取得する。
    T& ref()const
    {
        AE_BASE_ASSERT(isValid());
        return *mPtr;
    }

    /// @brief ポインタの値をそのまま取得する。
    /// @details 設定されていないときは0を返します。
    T* get()const
    {
        return mPtr.get();
    }
    //@}

    /// @name 破棄
    //@{
    /// ポインタを設定していない状態にする。
    void reset()
    {
        if (isNull())
        {
            return;
        }
        T* ptr = mPtr.get();
        mPtr.reset();
        ptr->~T();
        operator delete (ptr, mAllocatorPtr.ref());
        mAllocatorPtr.reset();
    }

    //@}

    /// @name 生成
    //@{
    void init(::ae::base::IAllocator& aAllocator)
    {
        prepareCtor(aAllocator);
        mPtr.reset(new (aAllocator) T());
    }
    template< typename A0 >
    void init(::ae::base::IAllocator& aAllocator, A0 a0)
    {
        prepareCtor(aAllocator);
        mPtr.reset(new (aAllocator) T(a0));
    }
    template< typename A0, typename A1 >
    void init(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1)
    {
        prepareCtor(aAllocator);
        mPtr.reset(new (aAllocator) T(a0, a1));
    }
    template< typename A0, typename A1, typename A2 >
    void init(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1, A2 a2)
    {
        prepareCtor(aAllocator);
        mPtr.reset(new (aAllocator) T(a0, a1, a2));
    }
    template< typename A0, typename A1, typename A2, typename A3 >
    void init(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1, A2 a2, A3 a3)
    {
        prepareCtor(aAllocator);
        mPtr.reset(new (aAllocator) T(a0, a1, a2, a3));
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4 >
    void init(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
    {
        prepareCtor(aAllocator);
        mPtr.reset(new (aAllocator) T(a0, a1, a2, a3, a4));
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5 >
    void init(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
    {
        prepareCtor(aAllocator);
        mPtr.reset(new (aAllocator) T(a0, a1, a2, a3, a4, a5));
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6 >
    void init(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
    {
        prepareCtor(aAllocator);
        mPtr.reset(new (aAllocator) T(a0, a1, a2, a3, a4, a5, a6));
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7 >
    void init(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
    {
        prepareCtor(aAllocator);
        mPtr.reset(new (aAllocator) T(a0, a1, a2, a3, a4, a5, a6, a7));
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8 >
    void init(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
    {
        prepareCtor(aAllocator);
        mPtr.reset(new (aAllocator) T(a0, a1, a2, a3, a4, a5, a6, a7, a8));
    }
    template< typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9 >
    void init(::ae::base::IAllocator& aAllocator, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
    {
        prepareCtor(aAllocator);
        mPtr.reset(new (aAllocator) T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9));
    }
    //@}

    /// @name 演算子オーバーロード
    //@{
    /// 特別な代入演算子。
    AutoSpPtr< T >& operator=(const AutoSpPtr< T >& aRHS)
    {
        reset();
        if (aRHS.isValid())
        {
            mPtr.set(*aRHS.mPtr);
            mAllocatorPtr = aRHS.mAllocatorPtr;
            aRHS.mPtr.reset();
            aRHS.mAllocatorPtr.reset();
        }
        return *this;
    }

    /// 特別な代入演算子。
    template< typename OtherType >
    AutoSpPtr< T >& operator=(const AutoSpPtr< OtherType >& aRHS)
    {
        reset();
        if (aRHS.isValid())
        {
            mPtr.set(*aRHS.mPtr);
            mAllocatorPtr = aRHS.mAllocatorPtr;
            aRHS.mPtr.reset();
            aRHS.mAllocatorPtr.reset();
        }
        return *this;
    }

    /// 参照演算子。
    T& operator*()const
    {
        return ref();
    }

    /// 参照演算子
    T* operator->()const
    {
        AE_BASE_ASSERT(isValid());
        return get();
    }
    //@}

private:
    mutable Pointer< T >          mPtr;
    mutable Pointer< IAllocator > mAllocatorPtr;
    //------------------------------------------------------------------------------
    void prepareCtor(::ae::base::IAllocator& aAllocator)
    {
        reset();
        mAllocatorPtr.set(aAllocator);
    }
};
//@}

}} // namespace
#endif
// EOF
