// 文字コード：UTF-8
#pragma once

#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/Unused.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

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
    : ptr_(0)
    {
    }
    Pointer(T* obj)
    : ptr_(obj)
    {
    }
    Pointer(T& obj)
    : ptr_(0)
    {
        Set(obj);
    }
    //@}

    /// @name 取得
    //@{
    /// 何も設定されていないときにtrueを返す。
    bool IsNull() const { return ptr_ == 0; }

    /// 何か設定されているときにtrueを返す。
    bool IsValid() const { return ptr_ != 0; }

    /// @brief ポインタの値をそのまま返す。
    /// @details 設定されていないときは0を返します。
    T* Get() const { return ptr_; }

    /// ポインタが設定されているとして参照を返す。
    T& Ref() const
    {
        AE_BASE_ASSERT_POINTER(ptr_);
        return *ptr_;
    }

    /// 同じポインタを指しているか。
    bool Equals(const Pointer<T>& rHS) const { return ptr_ == rHS.ptr_; }
    //@}

    /// @name 設定
    //@{
    /// ポインタが何も設定されていない状態にする。
    void Reset() { Reset(0); }

    /// 指定されたポインタをそのまま設定する。
    void Reset(T* ptr) { ptr_ = ptr; }

    /// @brief 未設定な状態で指定された参照を設定する。
    /// @details 既に設定済みな状況で呼ぶとエラーになります。
    void Set(T& ref)
    {
        AE_BASE_ASSERT(IsNull());
        ptr_ = &ref;
    }

    /// @brief 設定済みな状態で設定を解除する。
    /// @details 未設定な状況で呼ぶとエラーになります。
    void Unset() { Unset(Ref()); }

    /// @brief 指定のオブジェクトが設定されている状態で設定を解除する。
    /// @details
    /// 未設定な状況で呼んだり指定のオブジェクト以外が設定されているとエラーになる。
    void Unset(T& ref)
    {
        AE_BASE_ASSERT(IsValid());
        AE_BASE_ASSERT(ptr_ == &ref);
        AE_BASE_UNUSED(ref);
        ptr_ = 0;
    }
    //@}

    /// @name 演算子オーバーロード
    //@{
    T* operator->() const { return Get(); } ///< Get()のエイリアス。
    T& operator*() const { return Ref(); } ///< Ref()のエイリアス。
    bool operator==(const Pointer<T>& rHS) const
    {
        return Equals(rHS);
    } ///> Equals()のエイリアス。
    //@}

private:
    T* ptr_;
};
//@}

} // namespace ae::base
// EOF
