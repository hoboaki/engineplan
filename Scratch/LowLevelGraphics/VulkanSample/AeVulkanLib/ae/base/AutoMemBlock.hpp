// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_AUTOMEMBLOCK_HPP)
#else
#define AE_BASE_INCLUDED_AUTOMEMBLOCK_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/MemBlock.hpp>
#include <ae/base/Pointer.hpp>

namespace ae::base {
class IAllocator;
}

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Memory
//@{
/// @brief MemBlockのオートポインタ。
/// @details
/// デストラクタで自分が抱えているMemBlockを解放します。 @n
/// std::auto_ptr と同じようにインスタンスをコピーしたら破棄責任も移動します。
/// @n
class AutoMemBlock {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// 空のオブジェクトを作成。
    AutoMemBlock();

    /// @brief
    /// 指定のサイズのブロックを指定のアロケータから確保したメモリブロックを作成。
    /// @details メモリの確保に失敗したら IsEmpty() はtrueを返します。
    AutoMemBlock(
        pword_t size,
        IAllocator& allocator = IAllocator::Default(),
        pword_t alignment = IAllocator::DefaultAlignment);

    /// @brief 指定のブロックを抱えたメモリブロックを作成。
    /// @param block メモリブロック。
    /// @param allocator block を確保する際に使用したアロケータ。
    AutoMemBlock(const MemBlock& block, IAllocator& allocator);

    /// 破棄責任を移動して作成。
    AutoMemBlock(const AutoMemBlock&);

    /// ブロックを保持していれば破棄する。
    ~AutoMemBlock();
    //@}

    /// @name 情報取得
    //@{
    /// @brief ブロックを保持していなければtrueを返す。
    /// @details
    /// 抱えているブロックのサイズが0の場合でもブロックは保持しているのでfalseを返します。
    bool IsEmpty() const;

    /// @brief 保持しているブロックを解放する。
    /// @details 保持していなければ何もしません。
    void Clear();

    /// ブロックの参照を取得する。
    const MemBlock& Ref() const;
    //@}

    /// @name 演算子オーバーロード
    //@{
    /// 代入演算子。
    AutoMemBlock& operator=(const AutoMemBlock& rHS);

    /// 参照演算子。
    const MemBlock& operator*() const;

    /// アドレス演算子。
    const MemBlock* operator->() const;
    //@}

private:
    mutable MemBlock block_;
    mutable Pointer<IAllocator> allocatorPtr_;
};
//@}

} // namespace ae::base
#endif
// EOF
