// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_PLACEMENT_HPP)
#else
#define AE_BASE_INCLUDED_PLACEMENT_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <new>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Util
//@{
/// @brief
/// 確保済みのメモリ領域からオブジェクトを生成するためのテンプレートクラス。
/// @details
/// クラスメンバの初期化子で生成できないメンバ変数を後から初期化するときに使います。@n
/// @n
/// init 関数の引数に参照を渡す場合は Ref() を使うことをおすすめします。@n
/// Ref() を使わない場合はオブジェクトのコピーが走るので注意してください。 @n
/// @code
/// // 例
/// ::ae::base::Placement< ::ae::base::Vector3 > vec3;
/// vec3.Init( 1 , 2 , 3 );
/// const float len = vec3->Length();
/// @endcode
template <typename T>
class Placement {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    Placement()
    : ptr_(0)
    , bytes_()
    {
    }
    ~Placement() { Reset(); }
    //@}

    /// @name アクセス
    //@{
    /// 生成済みか。
    bool IsValid() const { return ptr_ != 0; }

    /// 生成済みのオブジェクトのポインタを取得する。
    T* Ptr() const
    {
        AE_BASE_ASSERT_POINTER(ptr_);
        return ptr_;
    }

    /// 生成済みのオブジェクトの参照を取得する。
    T& Ref() const { return *Ptr(); }
    //@}

    /// @name 演算子オーバーロード
    //@{
    T* operator->() const { return Ptr(); } ///< Ptr() のエイリアス。
    T& operator*() const { return Ref(); } ///< Ref() のエイリアス。
    //@}

    /// @name 破棄
    //@{
    /// 生成済みなら破棄する。
    void Reset()
    {
        if (IsValid()) {
            ptr_->~T();
            ptr_ = 0;
        }
    }
    //@}

    /// @name 生成
    //@{
    void Init()
    {
        PrepareCtor();
        new (ptr_) T();
    }
    template <typename A0>
    void Init(A0 a0)
    {
        PrepareCtor();
        new (ptr_) T(a0);
    }
    template <typename A0, typename A1>
    void Init(A0 a0, A1 a1)
    {
        PrepareCtor();
        new (ptr_) T(a0, a1);
    }
    template <typename A0, typename A1, typename A2>
    void Init(A0 a0, A1 a1, A2 a2)
    {
        PrepareCtor();
        new (ptr_) T(a0, a1, a2);
    }
    template <typename A0, typename A1, typename A2, typename A3>
    void Init(A0 a0, A1 a1, A2 a2, A3 a3)
    {
        PrepareCtor();
        new (ptr_) T(a0, a1, a2, a3);
    }
    template <typename A0, typename A1, typename A2, typename A3, typename A4>
    void Init(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
    {
        PrepareCtor();
        new (ptr_) T(a0, a1, a2, a3, a4);
    }
    template <
        typename A0,
        typename A1,
        typename A2,
        typename A3,
        typename A4,
        typename A5>
    void Init(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
    {
        PrepareCtor();
        new (ptr_) T(a0, a1, a2, a3, a4, a5);
    }
    template <
        typename A0,
        typename A1,
        typename A2,
        typename A3,
        typename A4,
        typename A5,
        typename A6>
    void Init(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
    {
        PrepareCtor();
        new (ptr_) T(a0, a1, a2, a3, a4, a5, a6);
    }
    template <
        typename A0,
        typename A1,
        typename A2,
        typename A3,
        typename A4,
        typename A5,
        typename A6,
        typename A7>
    void Init(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
    {
        PrepareCtor();
        new (ptr_) T(a0, a1, a2, a3, a4, a5, a6, a7);
    }
    template <
        typename A0,
        typename A1,
        typename A2,
        typename A3,
        typename A4,
        typename A5,
        typename A6,
        typename A7,
        typename A8>
    void Init(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
    {
        PrepareCtor();
        new (ptr_) T(a0, a1, a2, a3, a4, a5, a6, a7, a8);
    }
    template <
        typename A0,
        typename A1,
        typename A2,
        typename A3,
        typename A4,
        typename A5,
        typename A6,
        typename A7,
        typename A8,
        typename A9>
    void Init(
        A0 a0,
        A1 a1,
        A2 a2,
        A3 a3,
        A4 a4,
        A5 a5,
        A6 a6,
        A7 a7,
        A8 a8,
        A9 a9)
    {
        PrepareCtor();
        new (ptr_) T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }
    //@}

private:
    T* ptr_;
    byte_t bytes_[sizeof(T)];
    //------------------------------------------------------------------------------
    void PrepareCtor()
    {
        Reset();
        ptr_ = reinterpret_cast<T*>(bytes_);
    }
};

//@}

} // namespace ae::base
#endif
// EOF
