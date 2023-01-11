// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_AUTOSPPTR_HPP)
#else
#define AE_BASE_INCLUDED_AUTOSPPTR_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/Pointer.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Memory
//@{
/// AutoPtrのAllocator指定版。
template <typename T>
class AutoSpPtr {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// デフォルトで作成。
    AutoSpPtr() {}

    /// 0引数 Init() で作成。
    AutoSpPtr(::ae::base::IAllocator& allocator) { Init(allocator); }

    /// 1引数 Init() で作成。
    template <typename A0>
    AutoSpPtr(::ae::base::IAllocator& allocator, A0 a0)
    {
        Init(allocator, a0);
    }

    /// 2引数 Init() で作成。
    template <typename A0, typename A1>
    AutoSpPtr(::ae::base::IAllocator& allocator, A0 a0, A1 a1)
    {
        Init(allocator, a0, a1);
    }

    /// 3引数 Init() で作成。
    template <typename A0, typename A1, typename A2>
    AutoSpPtr(::ae::base::IAllocator& allocator, A0 a0, A1 a1, A2 a2)
    {
        Init(allocator, a0, a1, a2);
    }

    /// 4引数 Init() で作成。
    template <typename A0, typename A1, typename A2, typename A3>
    AutoSpPtr(::ae::base::IAllocator& allocator, A0 a0, A1 a1, A2 a2, A3 a3)
    {
        Init(allocator, a0, a1, a2, a3);
    }

    /// 5引数 Init() で作成。
    template <typename A0, typename A1, typename A2, typename A3, typename A4>
    AutoSpPtr(
        ::ae::base::IAllocator& allocator,
        A0 a0,
        A1 a1,
        A2 a2,
        A3 a3,
        A4 a4)
    {
        Init(allocator, a0, a1, a2, a3, a4);
    }

    /// 6引数 Init() で作成。
    template <
        typename A0,
        typename A1,
        typename A2,
        typename A3,
        typename A4,
        typename A5>
    AutoSpPtr(
        ::ae::base::IAllocator& allocator,
        A0 a0,
        A1 a1,
        A2 a2,
        A3 a3,
        A4 a4,
        A5 a5)
    {
        Init(allocator, a0, a1, a2, a3, a4, a5);
    }

    /// 7引数 Init() で作成。
    template <
        typename A0,
        typename A1,
        typename A2,
        typename A3,
        typename A4,
        typename A5,
        typename A6>
    AutoSpPtr(
        ::ae::base::IAllocator& allocator,
        A0 a0,
        A1 a1,
        A2 a2,
        A3 a3,
        A4 a4,
        A5 a5,
        A6 a6)
    {
        Init(allocator, a0, a1, a2, a3, a4, a5, a6);
    }

    /// 8引数 Init() で作成。
    template <
        typename A0,
        typename A1,
        typename A2,
        typename A3,
        typename A4,
        typename A5,
        typename A6,
        typename A7>
    AutoSpPtr(
        ::ae::base::IAllocator& allocator,
        A0 a0,
        A1 a1,
        A2 a2,
        A3 a3,
        A4 a4,
        A5 a5,
        A6 a6,
        A7 a7)
    {
        Init(allocator, a0, a1, a2, a3, a4, a5, a6, a7);
    }

    /// 9引数 Init() で作成。
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
    AutoSpPtr(
        ::ae::base::IAllocator& allocator,
        A0 a0,
        A1 a1,
        A2 a2,
        A3 a3,
        A4 a4,
        A5 a5,
        A6 a6,
        A7 a7,
        A8 a8)
    {
        Init(allocator, a0, a1, a2, a3, a4, a5, a6, a7, a8);
    }

    /// 10引数 Init() で作成。
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
    AutoSpPtr(
        ::ae::base::IAllocator& allocator,
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
        Init(allocator, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }

    /// 破棄責任を委譲して作成。
    AutoSpPtr(const AutoSpPtr<T>& ptr) { *this = ptr; }

    /// 破棄責任を委譲して作成。
    template <typename OtherType>
    AutoSpPtr(const AutoSpPtr<OtherType>& ptr)
    {
        *this = ptr;
    }

    /// デストラクタ
    ~AutoSpPtr() { Reset(); }

    //@}

    /// @name 取得
    //@{
    /// ポインタが設定されていなければtrueを返す。
    bool IsNull() const { return ptr_.IsNull(); }

    /// ポインタが設定されていればtrueを返す。
    bool IsValid() const { return ptr_.IsValid(); }

    /// ポインタの参照を取得する。
    T& Ref() const
    {
        AE_BASE_ASSERT(IsValid());
        return *ptr_;
    }

    /// @brief ポインタの値をそのまま取得する。
    /// @details 設定されていないときは0を返します。
    T* Get() const { return ptr_.Get(); }
    //@}

    /// @name 破棄
    //@{
    /// ポインタを設定していない状態にする。
    void Reset()
    {
        if (IsNull()) {
            return;
        }
        T* ptr = ptr_.Get();
        ptr_.Reset();
        ptr->~T();
        operator delete(ptr, allocatorPtr_.Ref());
        allocatorPtr_.Reset();
    }

    //@}

    /// @name 生成
    //@{
    void Init(::ae::base::IAllocator& allocator)
    {
        PrepareCtor(allocator);
        ptr_.Reset(new (allocator) T());
    }
    template <typename A0>
    void Init(::ae::base::IAllocator& allocator, A0 a0)
    {
        PrepareCtor(allocator);
        ptr_.Reset(new (allocator) T(a0));
    }
    template <typename A0, typename A1>
    void Init(::ae::base::IAllocator& allocator, A0 a0, A1 a1)
    {
        PrepareCtor(allocator);
        ptr_.Reset(new (allocator) T(a0, a1));
    }
    template <typename A0, typename A1, typename A2>
    void Init(::ae::base::IAllocator& allocator, A0 a0, A1 a1, A2 a2)
    {
        PrepareCtor(allocator);
        ptr_.Reset(new (allocator) T(a0, a1, a2));
    }
    template <typename A0, typename A1, typename A2, typename A3>
    void Init(::ae::base::IAllocator& allocator, A0 a0, A1 a1, A2 a2, A3 a3)
    {
        PrepareCtor(allocator);
        ptr_.Reset(new (allocator) T(a0, a1, a2, a3));
    }
    template <typename A0, typename A1, typename A2, typename A3, typename A4>
    void Init(
        ::ae::base::IAllocator& allocator,
        A0 a0,
        A1 a1,
        A2 a2,
        A3 a3,
        A4 a4)
    {
        PrepareCtor(allocator);
        ptr_.Reset(new (allocator) T(a0, a1, a2, a3, a4));
    }
    template <
        typename A0,
        typename A1,
        typename A2,
        typename A3,
        typename A4,
        typename A5>
    void Init(
        ::ae::base::IAllocator& allocator,
        A0 a0,
        A1 a1,
        A2 a2,
        A3 a3,
        A4 a4,
        A5 a5)
    {
        PrepareCtor(allocator);
        ptr_.Reset(new (allocator) T(a0, a1, a2, a3, a4, a5));
    }
    template <
        typename A0,
        typename A1,
        typename A2,
        typename A3,
        typename A4,
        typename A5,
        typename A6>
    void Init(
        ::ae::base::IAllocator& allocator,
        A0 a0,
        A1 a1,
        A2 a2,
        A3 a3,
        A4 a4,
        A5 a5,
        A6 a6)
    {
        PrepareCtor(allocator);
        ptr_.Reset(new (allocator) T(a0, a1, a2, a3, a4, a5, a6));
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
    void Init(
        ::ae::base::IAllocator& allocator,
        A0 a0,
        A1 a1,
        A2 a2,
        A3 a3,
        A4 a4,
        A5 a5,
        A6 a6,
        A7 a7)
    {
        PrepareCtor(allocator);
        ptr_.Reset(new (allocator) T(a0, a1, a2, a3, a4, a5, a6, a7));
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
    void Init(
        ::ae::base::IAllocator& allocator,
        A0 a0,
        A1 a1,
        A2 a2,
        A3 a3,
        A4 a4,
        A5 a5,
        A6 a6,
        A7 a7,
        A8 a8)
    {
        PrepareCtor(allocator);
        ptr_.Reset(new (allocator) T(a0, a1, a2, a3, a4, a5, a6, a7, a8));
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
        ::ae::base::IAllocator& allocator,
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
        PrepareCtor(allocator);
        ptr_.Reset(new (allocator) T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9));
    }
    //@}

    /// @name 演算子オーバーロード
    //@{
    /// 特別な代入演算子。
    AutoSpPtr<T>& operator=(const AutoSpPtr<T>& rHS)
    {
        Reset();
        if (rHS.IsValid()) {
            ptr_.Set(*rHS.ptr_);
            allocatorPtr_ = rHS.allocatorPtr_;
            rHS.ptr_.Reset();
            rHS.allocatorPtr_.Reset();
        }
        return *this;
    }

    /// 特別な代入演算子。
    template <typename OtherType>
    AutoSpPtr<T>& operator=(const AutoSpPtr<OtherType>& rHS)
    {
        Reset();
        if (rHS.IsValid()) {
            ptr_.Set(*rHS.ptr_);
            allocatorPtr_ = rHS.allocatorPtr_;
            rHS.ptr_.Reset();
            rHS.allocatorPtr_.Reset();
        }
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
    mutable Pointer<T> ptr_;
    mutable Pointer<IAllocator> allocatorPtr_;
    //------------------------------------------------------------------------------
    void PrepareCtor(::ae::base::IAllocator& allocator)
    {
        Reset();
        allocatorPtr_.Set(allocator);
    }
};
//@}

} // namespace ae::base
#endif
// EOF
