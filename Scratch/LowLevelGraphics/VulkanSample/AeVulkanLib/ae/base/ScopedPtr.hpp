// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_SCOPEDPTR_HPP)
#else
#define AE_BASE_INCLUDED_SCOPEDPTR_HPP

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Memory
//@{
/// boost::scoped_ptrと同じオートポインタクラス。
template <typename T>
class ScopedPtr {
public:
    /// コンストラクタ
    //@{
    /// ポインタを指定して作成。
    explicit ScopedPtr(T* ptr = 0)
    : ptr_(ptr)
    {
    }
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
