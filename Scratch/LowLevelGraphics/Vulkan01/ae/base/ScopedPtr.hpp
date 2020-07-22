// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_SCOPEDPTR_HPP)
#else
#define AE_BASE_INCLUDED_SCOPEDPTR_HPP

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Memory
//@{
/// boost::scoped_ptrと同じオートポインタクラス。
template< typename T >
class ScopedPtr
{
public:
    /// コンストラクタ
    //@{
    /// ポインタを指定して作成。
    explicit ScopedPtr(T* aPtr = 0)
        : mPtr(aPtr)
    {
    }
    //@}

    /// @name 取得
    //@{
    /// ポインタが設定されていなければtrueを返す。
    bool isNull()const
    {
        return mPtr == 0;
    }

    /// ポインタが設定されていればtrueを返す。
    bool isValid()const
    {
        return mPtr != 0;
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
        return mPtr;
    }
    //@}

    /// @name 変更
    //@{
    /// ポインタを設定していない状態にする。
    void reset()
    {
        reset(0);
    }

    /// ポインタをリセットする。
    void reset(T* aPtr)
    {
        T* ptr = mPtr;
        mPtr = 0;
        if (ptr != 0)
        {
            delete ptr;
        }
        mPtr = aPtr;
    }
    //@}

    /// @name 演算子オーバーロード
    //@{
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
    mutable T* mPtr;
};
//@}

}} // namespace
#endif
// EOF
