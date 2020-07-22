// 文字コード：UTF-8
#pragma once

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
template <typename T>
class Pointer {
public:
    /// @name コンストラクタ
    //@{
    Pointer()
    : ptr_(0) {}
    Pointer(T* aObj)
    : ptr_(aObj) {
    }
    Pointer(T& aObj)
    : ptr_(0) {
        set(aObj);
    }
    //@}

    /// @name 取得
    //@{
    /// 何も設定されていないときにtrueを返す。
    bool isNull() const { return ptr_ == 0; }

    /// 何か設定されているときにtrueを返す。
    bool isValid() const { return ptr_ != 0; }

    /// @brief ポインタの値をそのまま返す。
    /// @details 設定されていないときは0を返します。
    T* get() const { return ptr_; }

    /// ポインタが設定されているとして参照を返す。
    T& ref() const {
        AE_BASE_ASSERT_POINTER(ptr_);
        return *ptr_;
    }

    /// 同じポインタを指しているか。
    bool equals(const Pointer<T>& aRHS) const { return ptr_ == aRHS.ptr_; }
    //@}

    /// @name 設定
    //@{
    /// ポインタが何も設定されていない状態にする。
    void reset() { reset(0); }

    /// 指定されたポインタをそのまま設定する。
    void reset(T* aPtr) { ptr_ = aPtr; }

    /// @brief 未設定な状態で指定された参照を設定する。
    /// @details 既に設定済みな状況で呼ぶとエラーになります。
    void set(T& aRef) {
        AE_BASE_ASSERT(isNull());
        ptr_ = &aRef;
    }

    /// @brief 設定済みな状態で設定を解除する。
    /// @details 未設定な状況で呼ぶとエラーになります。
    void unset() { unset(ref()); }

    /// @brief 指定のオブジェクトが設定されている状態で設定を解除する。
    /// @details
    /// 未設定な状況で呼んだり指定のオブジェクト以外が設定されているとエラーになる。
    void unset(T& aRef) {
        AE_BASE_ASSERT(isValid());
        AE_BASE_ASSERT(ptr_ == &aRef);
        AE_BASE_UNUSED(aRef);
        ptr_ = 0;
    }
    //@}

    /// @name 演算子オーバーロード
    //@{
    T* operator->() const { return get(); }  ///< get()のエイリアス。
    T& operator*() const { return ref(); }   ///< ref()のエイリアス。
    bool operator==(const Pointer<T>& aRHS) const {
        return equals(aRHS);
    }  ///> equals()のエイリアス。
    //@}

private:
    T* ptr_;
};
//@}

}  // namespace base
}  // namespace ae
// EOF
