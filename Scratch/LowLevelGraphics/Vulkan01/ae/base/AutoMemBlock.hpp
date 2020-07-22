// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_AUTOMEMBLOCK_HPP)
#else
#define AE_BASE_INCLUDED_AUTOMEMBLOCK_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/MemBlock.hpp>
#include <ae/base/Pointer.hpp>

namespace ae {
namespace base {
class IAllocator;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Memory
//@{
    /// @brief MemBlockのオートポインタ。
    /// @details
    /// デストラクタで自分が抱えているMemBlockを解放します。 @n
/// std::auto_ptr と同じようにインスタンスをコピーしたら破棄責任も移動します。 @n
class AutoMemBlock
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// 空のオブジェクトを作成。
    AutoMemBlock();

    /// @brief 指定のサイズのブロックを指定のアロケータから確保したメモリブロックを作成。
    /// @details メモリの確保に失敗したら isEmpty() はtrueを返します。
    AutoMemBlock(pword_t aSize, IAllocator& aAllocator = IAllocator::Default(), pword_t aAlignment = IAllocator::DefaultAlignment);

    /// @brief 指定のブロックを抱えたメモリブロックを作成。
    /// @param aBlock メモリブロック。
    /// @param aAllocator aBlock を確保する際に使用したアロケータ。
    AutoMemBlock(const MemBlock& aBlock, IAllocator& aAllocator);

    /// 破棄責任を移動して作成。
    AutoMemBlock(const AutoMemBlock&);

    /// ブロックを保持していれば破棄する。
    ~AutoMemBlock();
    //@}

    /// @name 情報取得
    //@{
    /// @brief ブロックを保持していなければtrueを返す。
    /// @details 抱えているブロックのサイズが0の場合でもブロックは保持しているのでfalseを返します。
    bool isEmpty()const;

    /// @brief 保持しているブロックを解放する。
    /// @details 保持していなければ何もしません。
    void clear();

    /// ブロックの参照を取得する。
    const MemBlock& ref()const;
    //@}

    /// @name 演算子オーバーロード
    //@{
    /// 代入演算子。
    AutoMemBlock& operator=(const AutoMemBlock& aRHS);

    /// 参照演算子。
    const MemBlock& operator*()const;

    /// アドレス演算子。
    const MemBlock* operator->()const;
    //@}

private:
    mutable MemBlock mBlock;
    mutable Pointer< IAllocator > mAllocatorPtr;
};
//@}

}} // namespace
#endif
// EOF
