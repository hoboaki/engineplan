// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_AUTOPTR_HPP)
#else
#define AE_BASE_INCLUDED_AUTOPTR_HPP

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Memory
//@{
/// std::auto_ptrと同じオートポインタクラス。
template <typename T>
class AutoPtr {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// ポインタを指定して作成。
    explicit AutoPtr(T* ptr = 0)
    : ptr_(ptr)
    {
    }

    /// 破棄責任を委譲して作成。
    AutoPtr(const AutoPtr<T>& ptr)
    : ptr_(0)
    {
        *this = ptr;
    }

    /// 破棄責任を委譲して作成。
    template <typename OtherType>
    AutoPtr(const AutoPtr<OtherType>& ptr)
    : ptr_(0)
    {
        *this = ptr;
    }

    /// デストラクタ
    ~AutoPtr() { Reset(); }

    //@}

    /// @name 取得
    //@{
    /// ポインタが設定されていなければtrueを返す。
    bool IsNull() const { return ptr_ == 0; }

    /// ポインタが設定されていればtrueを返す。
    bool IsValid() const { return ptr_ != 0; }

    /// ポインタの参照を取得する。
    T& Ref() const
    {
        AE_BASE_ASSERT(IsValid());
        return *ptr_;
    }

    /// @brief ポインタの値をそのまま取得する。
    /// @details 設定されていないときは0を返します。
    T* Get() const { return ptr_; }
    //@}

    /// @name 変更
    //@{
    /// ポインタの破棄責任を剥奪し、抱えていたポインタを取得する。
    T* Release()
    {
        AE_BASE_ASSERT(IsValid());
        T* ptr = ptr_;
        ptr_ = 0;
        return ptr;
    }

    /// ポインタを設定していない状態にする。
    void Reset() { Reset(0); }

    /// ポインタをリセットする。
    void Reset(T* ptr)
    {
        T* ptr = ptr_;
        ptr_ = 0;
        if (ptr != 0) {
            delete ptr;
        }
        ptr_ = ptr;
    }
    //@}

    /// @name 演算子オーバーロード
    //@{
    /// 特別な代入演算子。
    AutoPtr<T>& operator=(const AutoPtr<T>& rHS)
    {
        T* ptr = rHS.ptr_;
        rHS.ptr_ = 0;
        Reset(ptr);
        return *this;
    }

    /// 特別な代入演算子。
    template <typename OtherType>
    AutoPtr<T>& operator=(const AutoPtr<OtherType>& rHS)
    {
        T* ptr = rHS.ptr_;
        rHS.ptr_ = 0;
        Reset(ptr);
        return *this;
    }

    /// 参照演算子。
    T& operator*() const { return Ref(); }

    /// 参照演算子
    T* operator->() const
    {
        AE_BASE_ASSERT(IsValid());
        return Get();
    }
    //@}

private:
    mutable T* ptr_;
};
//@}

} // namespace ae::base
#endif
// EOF
