// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_POINTER_HPP)
#else
#define AE_BASE_INCLUDED_POINTER_HPP

#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/Unused.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Util
//@{
/// @brief ポインタのラッパーテンプレートクラス。
/// @details
/// ヌルポインタアクセスを防いだり意図しない二回設定を防ぐために使います。
template< typename T >
class Pointer
{
public:
    /// @name コンストラクタ
    //@{
    Pointer() : mPtr(0) {}
    Pointer(T& aObj) : mPtr(0) { set(aObj); }
    //@}

    /// @name 取得
    //@{
    /// 何も設定されていないときにtrueを返す。
    bool isNull()const
    {
        return mPtr == 0;
    }

    /// 何か設定されているときにtrueを返す。
    bool isValid()const
    {
        return mPtr != 0;
    }

    /// @brief ポインタの値をそのまま返す。 
    /// @details 設定されていないときは0を返します。
    T*   get()const
    {
        return mPtr;
    }

    /// ポインタが設定されているとして参照を返す。
    T&   ref()const
    {
        AE_BASE_ASSERT_POINTER(mPtr);
        return *mPtr;
    }

    /// 同じポインタを指しているか。
    bool equals(const Pointer< T >& aRHS)const
    {
        return mPtr == aRHS.mPtr;
    }
    //@}

    /// @name 設定
    //@{
    /// ポインタが何も設定されていない状態にする。
    void reset()
    {
        reset(0);
    }

    /// 指定されたポインタをそのまま設定する。
    void reset(T* aPtr)
    {
        mPtr = aPtr;
    }

    /// @brief 未設定な状態で指定された参照を設定する。
    /// @details 既に設定済みな状況で呼ぶとエラーになります。
    void set(T& aRef)
    {
        AE_BASE_ASSERT(isNull());
        mPtr = &aRef;
    }

    /// @brief 設定済みな状態で設定を解除する。
    /// @details 未設定な状況で呼ぶとエラーになります。
    void unset()
    {
        unset(ref());
    }

    /// @brief 指定のオブジェクトが設定されている状態で設定を解除する。
    /// @details 未設定な状況で呼んだり指定のオブジェクト以外が設定されているとエラーになる。
    void unset(T& aRef)
    {
        AE_BASE_ASSERT(isValid());
        AE_BASE_ASSERT(mPtr == &aRef);
        AE_BASE_UNUSED(aRef);
        mPtr = 0;
    }
    //@}

    /// @name 演算子オーバーロード
    //@{
    T* operator->()const { return get(); } ///< get()のエイリアス。
    T& operator*()const { return ref(); } ///< ref()のエイリアス。
    bool operator==(const Pointer<T>& aRHS)const { return equals(aRHS); } ///> equals()のエイリアス。
    //@}

private:
    T* mPtr;
};
//@}

}} // namespace
#endif
// EOF
