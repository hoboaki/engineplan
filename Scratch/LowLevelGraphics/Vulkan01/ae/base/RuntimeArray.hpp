// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_RUNTIMEARRAY_HPP)
#else
#define AE_BASE_INCLUDED_RUNTIMEARRAY_HPP

#include <ae/base/Compiler.hpp>
#include <ae/base/IAllocator.hpp>
#include <ae/base/Noncopyable.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Collection
//@{
/// 実行時に確保する大きさが決まる配列。
template <typename T>
class RuntimeArray : ::ae::base::Noncopyable<RuntimeArray<T>> {
public:
    /// @name typedef
    //@{
    typedef T ValueType;
    //@}

    /// @name コンストラクタとデストラクタ
    //@{

    /// @brief コンストラクタ。
    /// @param count 配列長。
    /// @param allocator 配列データを確保する際に使用するアロケータ。
    /// @details
    /// 配列長が0の場合、アロケートは走りません。
    RuntimeArray(IAllocator* allocator = &IAllocator::Default())
    : RuntimeArray(0, allocator) {}
    RuntimeArray(int count, IAllocator* allocator = &IAllocator::Default())
    : allocator_()
    , count_(0)
    , ptr_(nullptr) {
        resize(count, allocator);
    }

    /// 非推奨版。
    RuntimeArray(int count, IAllocator& allocator = IAllocator::Default())
    : RuntimeArray(count, &allocator) {}

    /// デストラクタ。
    ~RuntimeArray() { resize(0); }

    //@}

    /// @name 変更処理
    //@{
    /// サイズを変更。
    /// @details 確保済配列領域を一度破棄＆再確保＆全要素デフォルトコンストラクタを呼ぶ。
    void resize(const int count, IAllocator* allocator = &IAllocator::Default()) {
        // まず破棄処理
        if (ptr_ != nullptr) {
            // 逆順でデストラクタを呼び出す
            for (int i = count_; 0 < i; --i) {
                at(i - 1).~ValueType();
            }

            ValueType* ptr = ptr_;
            ptr_ = nullptr;
            allocator_->free(reinterpret_cast<ptr_t>(ptr));
            count_ = 0;
        }

        // アロケータ変更
        allocator_.reset(&PtrToRef(allocator));

        // 0なら確保せず終了
        count_ = count;
        if (count_ == 0) {
            return;
        }

        // デフォルト初期化
        ptr_ = reinterpret_cast<ValueType*>(
            allocator_->alloc(sizeof(ValueType) * count_));
        for (int i = 0; i < count; ++i) {
#if defined(AE_BASE_COMPILER_MSVC)
#pragma warning(push)
#pragma warning(disable : 4345)
#endif
            new (&at(i)) ValueType();  // 初期値で初期化
#if defined(AE_BASE_COMPILER_MSVC)
#pragma warning(pop)
#endif
        }
    }

    /// 全要素を指定の値で埋める。
    void fill(const ValueType& value) {
        for (int i = 0; i < count_; ++i) {
            ptr_[i] = value;
        }
    }
    //@}

    /// @name アクセス
    //@{
    /// 配列長。
    int count() const { return count_; }

    /// 0番目の要素のポインタ。 
    ValueType* head() { 
        AE_BASE_ASSERT_LESS(0, count_);
        return ptr_;
    }

    /// 0番目の要素のポインタ。
    const ValueType* head() const {
        AE_BASE_ASSERT_LESS(0, count_);
        return ptr_;
    }

    /// 指定番目の要素にアクセス。
    ValueType& at(const int index) {
        if (count_ <= index) {
            AE_BASE_ASSERT_LESS(index, count_);
            return ptr_[0];  // fail safe code
        }
        return ptr_[index];
    }

    /// 指定番目の要素にアクセス。
    const ValueType& at(const int index) const {
        if (count_ <= index) {
            AE_BASE_ASSERT_LESS(index, count_);
            return ptr_[0];  // fail safe code
        }
        return ptr_[index];
    }

    //@}

    /// @name 演算子オーバーロード
    //@{
    /// at() のエイリアス。
    ValueType& operator[](const int index) {
        return at(index);
    }

    /// at()const のエイリアス。
    const ValueType& operator[](const int index) const {
        return at(index);
    } 
    //@}

private:
    Pointer<IAllocator> allocator_;
    int count_;
    ValueType* ptr_;
};
//@}

}  // namespace base
}  // namespace ae
#endif
// EOF
